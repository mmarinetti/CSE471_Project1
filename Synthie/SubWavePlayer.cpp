#include "StdAfx.h"
#include "SubWavePlayer.h"

CSubWavePlayer::CSubWavePlayer(void)
{
    m_samples = NULL;
    m_numsamples = 0;
}

CSubWavePlayer::~CSubWavePlayer(void)
{
}

void CSubWavePlayer::Start()
{
    m_position = 0;
}

bool CSubWavePlayer::Generate()
{
    if(m_position > m_numsamples)
    {
		m_position=0;
    }
    m_frame[0] = m_samples[m_position++];
    m_frame[1] = m_frame[0];
    return true;
}