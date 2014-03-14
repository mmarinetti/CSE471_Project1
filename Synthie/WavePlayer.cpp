#include "StdAfx.h"
#include "WavePlayer.h"
#include <cmath>

CWavePlayer::CWavePlayer(void)
{
    m_samples = NULL;
    m_numsamples = 0;
    count=0;
	m_attack=0;
	m_decay=0;
	m_release=0;
    slow = false;
    fast = false;
	adsr = false;
}

CWavePlayer::~CWavePlayer(void)
{
}

void CWavePlayer::Start()
{
	m_time=0;
    m_position = 0;
	m_duration = m_numsamples/44100;
}

bool CWavePlayer::Generate()
{
    if(m_position < (m_numsamples-1))
    {
        if (fast)
        {
            m_frame[0] = m_frame[1] = m_samples[m_position++] / 32768.0;
            m_position++;

            return true;
        }
        else if (slow)
        {
            if (count%2 == 1)
            {
                m_frame[0] = m_frame[1] = ((m_samples[m_position]+m_samples[m_position+1])/2) / 32768.0;
                count++;
            }
            else
            {
                m_frame[0] = m_frame[1] = m_samples[m_position++] / 32768.0;
                count++;
            }
        }
        else
        {
            m_frame[0] = m_frame[1] = m_samples[m_position++] / 32768.0;
        }

		if(adsr)
		{
            double factor;

        	//ATTACK AND RELEASE IMPLEMENATION
        	if(m_time < m_attack)
    		{
        		factor = m_time/m_attack;
        		m_frame[0] *= factor;
        		m_frame[1] *= factor;
           	}
            else if (m_time < (m_attack + m_decay))
            {
                factor = abs((1 + (.5 - 1) * (m_time / (m_attack + m_decay))));
    		    m_frame[0] = m_frame[0]*factor;
    		    m_frame[1] = m_frame[1]*factor;
            }
            else if (m_time < (m_duration - m_release))
            {
                factor = .5;
    		    m_frame[0] *= factor;
    		    m_frame[1] *= factor;  
            }
            else
            {
                factor = (.5 + (0 - .501) * (m_time / (m_duration)));  
    		    m_frame[0] *= factor;
    		    m_frame[1] *= factor;  
            }


        // Update time
        m_time += GetSamplePeriod();

        // We return true until the time reaches the duration.
        return m_time < (m_duration * GetSecondsPerBeat());
		}
	}

    else
    {
        m_frame[1] = m_frame[0] = 0;
        return false;
    }
}