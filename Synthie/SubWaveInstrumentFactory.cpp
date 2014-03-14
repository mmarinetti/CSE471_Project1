#include "StdAfx.h"
#include "SubWaveInstrumentFactory.h"
#include <cmath>
#include "audio/DirSoundSource.h"

CSubWaveInstrumentFactory::CSubWaveInstrumentFactory(void)
{
	m_wave.clear();
}

CSubWaveInstrumentFactory::~CSubWaveInstrumentFactory(void)
{
}


CSubWaveInstrument *CSubWaveInstrumentFactory::CreateInstrument()
{
    CSubWaveInstrument *instrument = new CSubWaveInstrument();
	instrument->SetNote(m_note);
    instrument->GetPlayer()->SetSamples(&m_wave[0], (int)m_wave.size());
    return instrument;
}

bool CSubWaveInstrumentFactory::LoadFiles()
{
    m_wave.clear();

	const char *square = "square.wav";
	const char *triangle = "triangle.wav";
	const char *sawtooth = "sawtooth.wav";

	//Will load all three files at once, and combine each frame of them while avoiding clipping at the same time
	//This is so the subtractive implementation can go from there to remove frequencies from the combined result
	CDirSoundSource m_squarefile;
	CDirSoundSource m_sawfile;
	CDirSoundSource m_trifile;

    if(!m_squarefile.Open(square))
    {
        CString msg = L"Unable to open audio file: ";
        msg += square;
        AfxMessageBox(msg);
        return false;
    }

	if(!m_trifile.Open(triangle))
    {
        CString msg = L"Unable to open audio file: ";
        msg += square;
        AfxMessageBox(msg);
        return false;
    }

	if(!m_sawfile.Open(sawtooth))
    {
        CString msg = L"Unable to open audio file: ";
        msg += square;
        AfxMessageBox(msg);
        return false;
    }

	//Loop through a few waveforms and store them in a "wavetable"
	double dur = m_squarefile.GetDuration();
	double rate = m_squarefile.SampleRate();

    for(int i=0;  i<(m_squarefile.SampleRate());  i++)
    {
        short frame[2];
		short frame2[2];
		short frame3[2];
        m_squarefile.ReadFrame(frame);
		m_trifile.ReadFrame(frame2);
		m_sawfile.ReadFrame(frame3);

		double combined = frame[0] + frame2[0] + frame3[0];

		//Avoid clipping
		if (combined > 32000 )
		{
			m_wave.push_back(32000);
		}
		else if ( combined < -32000)
		{
			m_wave.push_back(-32000);
		}
		else
		{
			m_wave.push_back((short)combined); //Saw + square + triangle waves combined
		}
    }

    m_squarefile.Close();
    m_trifile.Close();
	m_sawfile.Close();

    return true;
}
