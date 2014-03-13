#pragma once
#include "audionode.h"

class CNoise :
    public CAudioNode
{
public:
    CNoise(void);
    ~CNoise(void);

public:
    virtual void Start();
    virtual bool Generate();

    void SetFreq(double f) {m_freq = f;}
    void SetAmplitude(double a) {m_amp = a;}

private:
    double m_freq;
    double m_phase;
    double m_amp;

};