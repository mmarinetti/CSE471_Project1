#include "StdAfx.h"
#include "DrumInstrument.h"
#include "DrumFactory.h"
#include "DrumWave.h"
#include "Notes.h"
#include <cmath>

#define PI 3.14159

CDrumInstrument::CDrumInstrument(void)
{
    m_attack = .05;
    m_release = .05;
	m_decay = .05;
    m_sustain = .5;
    m_freq = 500;
    m_amp = .3;
    m_synthesizing = false;
	adsr=false;
    m_drumwave.SetFreq(100);
}


CDrumInstrument::~CDrumInstrument(void)
{
}

void CDrumInstrument::Start()
{
    m_noise.SetSampleRate(GetSampleRate());
    m_noise.Start();
    m_wavePlayer.Start();
    m_wavePlayer.SetSampleRate(GetSampleRate());
    m_time=0;

    if(m_state < 3)
    {
        m_synthesizing = true;
        m_attack = .3;
        m_decay = .1;
        m_release = .3;
        m_duration = .8;
    }
}


void CDrumInstrument::SetNote(CNote *note)
{
    // Get a list of all attribute nodes and the
    // length of that list
    CComPtr<IXMLDOMNamedNodeMap> attributes;
    note->Node()->get_attributes(&attributes);
    long len;
    attributes->get_length(&len);

    // Loop over the list of attributes
    for(int i=0;  i<len;  i++)
    {
        // Get attribute i
        CComPtr<IXMLDOMNode> attrib;
        attributes->get_item(i, &attrib);

        // Get the name of the attribute
        CComBSTR name;
        attrib->get_nodeName(&name);

        CComVariant value;
        attrib->get_nodeValue(&value);

    }

}

void CDrumInstrument::SetState(int state)
{
    m_state = state;

    if(m_state < 3)
    {
        m_synthesizing = true;
        m_attack = .05;
        m_decay = .05;
        m_release = .4;
        m_duration = .6;
    }
}

bool CDrumInstrument::Generate()
{
    if(m_synthesizing)
    {
        // Tell the component to generate an audio sample
        m_noise.Generate();
        m_drumwave.Generate();

		m_frame[0]=m_drumwave.Frame(0);
		m_frame[1]=m_drumwave.Frame(1);

    	//ATTACK AND RELEASE IMPLEMENATION
    	if(m_time < m_attack)
		{
    		factor = m_time/m_attack;
    		m_frame[0] *= factor;
    		m_frame[1] *= factor;
			assert(m_time<.3);
    	}
        else if (m_time < (m_attack + m_decay))
        {
            factor = abs((1 + (m_sustain - 1) * (m_time / (m_attack + m_decay))));
    		m_frame[0] = m_frame[0]*factor;
    		m_frame[1] = m_frame[1]*factor;
			assert(m_time > .29);
        }
        else if (m_time < (m_duration - m_release))
        {
            factor = m_sustain;
    		m_frame[0] *= factor;
    		m_frame[1] *= factor;  
        }
        else
        {
            factor = (.5 + (0 - .5) * (m_time / (m_duration)));  
    		m_frame[0] *= factor;
    		m_frame[1] *= factor;  
        }


        // Update time
        m_time += GetSamplePeriod();

        // We return true until the time reaches the duration.
        return m_time < (m_duration * GetSecondsPerBeat());
    }
    else
    {
		if(adsr)
		{
			m_wavePlayer.SetAttack(m_attack);
			m_wavePlayer.SetDecay(m_decay);
			m_wavePlayer.SetRelease(m_release);
		}

        bool valid = m_wavePlayer.Generate();

        m_frame[0] = m_wavePlayer.Frame(0)*m_amp;
        m_frame[1] = m_wavePlayer.Frame(1)*m_amp;

        return valid;
    }


}