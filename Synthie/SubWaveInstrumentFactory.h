#pragma once
#include "SubWaveInstrument.h"
#include <vector>

class CSubWaveInstrumentFactory
{
public:
    CSubWaveInstrumentFactory(void);
    ~CSubWaveInstrumentFactory(void);

    CSubWaveInstrument *CreateInstrument();
	bool LoadFiles();
	void SetNote( CNote *note) { m_note = note; }

private:
    std::vector<short> m_wave;
	CNote *m_note;
};
