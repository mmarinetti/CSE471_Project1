#pragma once
#include "audionode.h"

class CWavePlayer : public CAudioNode
{
public:
    CWavePlayer(void);
    ~CWavePlayer(void);

public:
    virtual void Start();
    virtual bool Generate();

    void SetSlow(){slow=true; fast=false;}
    void SetFast(){fast=true; slow=false;}
	void SetAdsr(){adsr=true;}

	void SetAttack(double x){m_attack=x;}
    void SetDecay(double x){m_decay=x;}
    void SetRelease(double x){m_decay=x;}

    void SetSamples(short *s, int n) {m_samples = s; m_numsamples = n;}

private:
    bool slow;
    bool fast;
	bool adsr;

    int count;

    short *m_samples;
    int    m_numsamples;
    int    m_position;

	double m_release;
    double m_attack;
    double m_decay;

	double m_time;
	double m_duration;
};