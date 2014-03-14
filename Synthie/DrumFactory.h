#pragma once
#include "Druminstrument.h"
#include <vector>

class CNote;

//Two different ways to use a techno drum,
enum DrumStates{TechOne, Tech, TechThree, BassL, BassM, BassH, CrashHi, CrashLo,
                HatClosed, HatOpen, Ride, ShakerL, ShakerM, ShakerH, SnareL, SnareM,
                SnareH, Tom1L, Tom1M, Tom1H, Tom2L, Tom2M, Tom2H};

class CDrumFactory
{
public:
    CDrumFactory(void);
    ~CDrumFactory(void);

    CDrumInstrument *CreateInstrument();
    void SetState(int state){m_state = state;}

    void SetNote(CNote *note);
    void SetAmp(double d){m_amp = d;}
    bool LoadFile(const char *filename);
    int TypeToState(const WCHAR *name);

    std::vector<std::vector<short>> m_waves;

    double m_amp;
    double m_freq;
    double m_attack;
    double m_release;
    double m_decay;
    bool m_fast;
    bool m_slow;
	bool m_adsr;

    int m_state;
};

