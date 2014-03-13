#pragma once

#include "AudioNode.h"

class CAttackRelease : public CAudioNode
{
public:
    CAttackRelease(void);
    virtual ~CAttackRelease(void);

    void SetSource(CAudioNode *source){m_source = source;}
    void SetDuration(double duration){m_duration = duration;}
    void SetAttack(double attack){m_attack = attack;}
    void SetRelease(double release){m_release = m_release;}


    virtual void Start();
    virtual bool Generate();

private:
    double m_attack;
    double m_release;
    double m_duration;
    double m_time;
    CAudioNode *m_source;
};

