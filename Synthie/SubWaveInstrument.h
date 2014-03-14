#pragma once
#include "instrument.h"
#include "SubWavePlayer.h"
#include <vector>

class CSubWaveInstrument :
    public CInstrument
{
public:
    CSubWaveInstrument(void);
    ~CSubWaveInstrument(void);

    virtual void Start();
    virtual bool Generate();
    virtual void SetNote(CNote *note);
	void SetDuration(double d) {m_duration = d;}
    void SetFreq(double f) {m_freq = f;}
	short RemoveClipping( double a );
    CSubWavePlayer *GetPlayer() {return &m_wavePlayer;}

private:
    CSubWavePlayer m_wavePlayer;
    double m_duration;
    double m_time;
	double m_freq;
	double m_release;
	double m_attack;

	double y1;
	double y2;
	double y0;
};