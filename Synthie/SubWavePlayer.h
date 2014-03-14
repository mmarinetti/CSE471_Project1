#pragma once
#include "audionode.h"

class CSubWavePlayer : public CAudioNode
{
public:
    CSubWavePlayer(void);
    ~CSubWavePlayer(void);

public:
    virtual void Start();
    virtual bool Generate();

    void SetSamples(short *s, int n) {m_samples = s; m_numsamples = n;}
    void SetFreq(double f) {m_freq = f;}
	void SetDuration(double d) { m_duration = d; }
    //! Set the sample rate
    void SetSampleRate(double s) {m_sampleRate = s;}

private:
    short *m_samples;
    int    m_numsamples;
    int    m_position;
	double m_freq;
    double m_duration;
	double m_sampleRate;
};

