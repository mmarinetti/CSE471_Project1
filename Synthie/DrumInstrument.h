#pragma once
#include "Instrument.h"
#include "Noise.h"
#include "WavePlayer.h"
#include "DrumWave.h"

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
    void SetAttack(double x){m_attack=x;}
    void SetDecay(double x){m_decay=x;}
    void SetRelease(double x){m_decay=x;}
	void SetAdsr(){adsr=true;}

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
    double m_decay;
	double m_sustain;
    double m_freq;
	double factor;
	bool adsr;

    double x0;
    double x1;
    double x2;
    double y0;

    CDrumWave m_drumwave;
    CNoise   m_noise;
    CWavePlayer m_wavePlayer;
};