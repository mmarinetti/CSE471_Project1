#include "StdAfx.h"
#include "AttackRelease.h"
#include "AudioNode.h"

using namespace std;

CAttackRelease::CAttackRelease(void)
{
    m_attack = 0.05;
    m_release = 0.05;
    m_duration = 0;
    m_time = 0;
    m_source = NULL;
}


CAttackRelease::~CAttackRelease(void)
{
}

void CAttackRelease::Start()
{
    m_time=0;
}


bool CAttackRelease::Generate()
{

    m_frame[0] = m_source->Frame(0);
    m_frame[1] = m_source->Frame(1);

    /*if(m_time < m_attack)
    {
        m_frame[0] = m_frame[0]*(m_time/m_attack);
        m_frame[1] = m_frame[1]*(m_time/m_attack);
    }
    else if ((m_duration - m_time) < 0.05)
    {
        m_frame[0] = m_frame[0]*((m_duration-m_time)/m_attack);
        m_frame[1] = m_frame[1]*((m_duration-m_time)/m_attack);
    }*/

    m_time += GetSamplePeriod();
    return m_duration < m_time;
}