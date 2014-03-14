#include "StdAfx.h"
#include "DrumFactory.h"
#include "DrumInstrument.h"
#include <cstdlib>     /* srand, rand */
#include <time.h>       /* time */
#include "Note.h"
#include "Notes.h"
#include "audio/DirSoundSource.h"
#include <map>
#include <string>


CDrumFactory::CDrumFactory(void)
{
    m_amp = .3;
    m_waves.clear();
    m_attack = .05;
    m_release = .05;
    m_decay = .05;
	m_slow=false;
	m_fast=false;
	m_adsr=false;
    
    LoadFile("BassL.wav");
    LoadFile("BassM.wav");
    LoadFile("BassH.wav");
    LoadFile("CrashHi.wav");
    LoadFile("CrashLo.wav");
    LoadFile("HatClosed.wav");
    LoadFile("HatOpen.wav");
    LoadFile("Ride.wav");
    LoadFile("ShakerL.wav");
    LoadFile("ShakerM.wav");
    LoadFile("ShakerH.wav");
    LoadFile("SnareL.wav");
    LoadFile("SnareM.wav");
    LoadFile("SnareH.wav");
    LoadFile("Tom1L.wav");
    LoadFile("Tom1M.wav");
    LoadFile("Tom1H.wav");
    LoadFile("Tom2L.wav");
    LoadFile("Tom2M.wav");
    LoadFile("Tom2H.wav");
}


CDrumFactory::~CDrumFactory(void)
{
}

CDrumInstrument *CDrumFactory::CreateInstrument()
{
    CDrumInstrument *instrument = new CDrumInstrument();

    instrument->SetAmplitude(m_amp);
    instrument->SetState(m_state);
    instrument->SetFreq(m_freq);
    instrument->SetAttack(m_attack);
    instrument->SetDecay(m_decay);
    instrument->SetRelease(m_release);

    if(m_state != TechOne && m_state != Tech && m_state != TechThree)
    {
        instrument->GetPlayer()->SetSamples(&m_waves[m_state-3][0], (int)(m_waves[m_state-3].size()));
    }

    if (m_slow){instrument->GetPlayer()->SetSlow();}
    if (m_fast){instrument->GetPlayer()->SetFast();}
	if (m_adsr){instrument->SetAdsr();}

    return instrument;
}

void CDrumFactory::SetNote(CNote *note)
{
    // Get a list of all attribute nodes and the
    // length of that list
    CComPtr<IXMLDOMNamedNodeMap> attributes;
    note->Node()->get_attributes(&attributes);
    long len;
    attributes->get_length(&len);

    // Loop over the list of attributes
    for(int i=0;  i<len;  i++)
    {
        // Get attribute i
        CComPtr<IXMLDOMNode> attrib;
        attributes->get_item(i, &attrib);

        // Get the name of the attribute
        CComBSTR name;
        attrib->get_nodeName(&name);

        CComVariant value;
        attrib->get_nodeValue(&value);

        if(name == "DrumType")
        {
            SetState(TypeToState(value.bstrVal));
        }
        else if(name == "amplitude")
        {
            value.ChangeType(VT_R8);
            m_amp=(value.dblVal);
        }
        else if(name == "note")
        {
            m_freq=(NoteToFrequency(value.bstrVal));
        }
        else if(name == "freq")
        {
            value.ChangeType(VT_R8);
            m_freq=(value.dblVal);
        }
        else if(name == "attack")
        {
            value.ChangeType(VT_R8);
            m_attack=(value.dblVal);
			bool m_adsr = true;
        }        
        else if(name == "release")
        {
            value.ChangeType(VT_R8);
            m_release=(value.dblVal);
			bool m_adsr = true;
        }
        else if(name == "decay")
        {
            value.ChangeType(VT_R8);
            m_release=(value.dblVal);
			bool m_adsr = true;
        }
        else if(name == "slow")
        {
            value.ChangeType(VT_R8);
            m_slow=(value.dblVal);
        }
        else if(name == "fast")
        {
            value.ChangeType(VT_R8);
            m_fast=(value.dblVal);
        }
    }

}

bool CDrumFactory::LoadFile(const char *filename)
{
    CDirSoundSource m_file;

    std::vector<short> m_wave;

    if(!m_file.Open(filename))
    {
        CString msg = L"Unable to open audio file: ";
        msg += filename;
        AfxMessageBox(msg);
        return false;
    }

    for(int i=0;  i<m_file.NumSampleFrames();  i++)
    {
        short frame[2];
        m_file.ReadFrame(frame);
        m_wave.push_back(frame[0]);
    }

    m_file.Close();

    m_waves.push_back(m_wave);
    return true;
}


int CDrumFactory::TypeToState(const WCHAR *name)
{
    if(std::wstring(name) == L"TechOne"){return 0;}
    else if(std::wstring(name) == L"Tech"){return 1;}
    else if(std::wstring(name) == L"TechThree"){return 2;}
    else if(std::wstring(name) == L"BassL"){return 3;}
    else if(std::wstring(name) == L"BassM"){return 4;}
    else if(std::wstring(name) == L"BassH"){return 5;}
    else if(std::wstring(name) == L"CrashHi"){return 6;}
    else if(std::wstring(name) == L"CrashLo"){return 7;}
    else if(std::wstring(name) == L"HatClosed"){return 8;}
    else if(std::wstring(name) == L"HatOpen"){return 9;}
    else if(std::wstring(name) == L"Ride"){return 10;}
    else if(std::wstring(name) == L"ShakerL"){return 11;}
    else if(std::wstring(name) == L"ShakerM"){return 12;}
    else if(std::wstring(name) == L"ShakerH"){return 13;}
    else if(std::wstring(name) == L"SnareL"){return 14;}
    else if(std::wstring(name) == L"SnareM"){return 15;}
    else if(std::wstring(name) == L"SnareH"){return 16;}
    else if(std::wstring(name) == L"Tom1L"){return 17;}
    else if(std::wstring(name) == L"Tom1M"){return 18;}
    else if(std::wstring(name) == L"Tom1H"){return 19;}
    else if(std::wstring(name) == L"Tom2L"){return 20;}
    else if(std::wstring(name) == L"Tom2M"){return 21;}
    else if(std::wstring(name) == L"Tom2H"){return 22;}
    else{return 3;}
}