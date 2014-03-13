#pragma once
#include "Instrument.h"
#include "Noise.h"
#include "WavePlayer.h"

class CDrumInstrument :
    public CInstrument
{
public:
    CDrumInstrument(void);
    ~CDrumInstrument(void);

    virtual void Start();
    virtual bool Generate();
    virtual void SetNote(CNote *note);

    void SetState(int state);

    void SetDuration(double d) {m_duration=d;}
    void SetFreq(double f) {m_freq = f;}
    void SetAmplitude(double d) {m_amp=d;}

    CWavePlayer *GetPlayer() {return &m_wavePlayer;}

private:
    int m_state;
    bool m_synthesizing;        //true if using synthesized drum, false if using samples from .wav

    int count;

    double m_amp;
    double m_time;
    double m_duration;
	double m_release;
    double m_attack;
    double m_freq;

    double x0;
    double x1;
    double x2;
    double y0;

    CNoise   m_noise;
    CWavePlayer m_wavePlayer;
};