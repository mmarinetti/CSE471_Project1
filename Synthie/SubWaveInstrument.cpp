#include "StdAfx.h"
#include "SubWaveInstrument.h"
#include "Notes.h"

using namespace std;

CSubWaveInstrument::CSubWaveInstrument(void)
{
	m_gain= 10;
	m_release = .1;
	m_attack = .1;
}

CSubWaveInstrument::~CSubWaveInstrument(void)
{
}


void CSubWaveInstrument::Start()
{
    m_wavePlayer.SetSampleRate(GetSampleRate());
    m_wavePlayer.Start();

	m_time = 0;

	y0=0;
	y1=0;
	y2=0;

}


void CSubWaveInstrument::SetNote(CNote *note)
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

        // Get the value of the attribute.  A CComVariant is a variable
        // that can have any type. It loads the attribute value as a
        // string (UNICODE), but we can then change it to an integer 
        // (VT_I4) or double (VT_R8) using the ChangeType function 
        // and then read its integer or double value from a member variable.
        CComVariant value;
        attrib->get_nodeValue(&value);

        if(name == "duration")
        {
            value.ChangeType(VT_R8);
            SetDuration(value.dblVal);
        }
		else if(name == "note")
        {
            SetFreq(NoteToFrequency(value.bstrVal));
        }
		else if (name == "attack")
		{
			value.ChangeType(VT_R8);
			m_attack = value.dblVal;
		}
		else if (name == "release")
		{
			value.ChangeType(VT_R8);
			m_release = value.dblVal;
		}
		else if (name == "gain")
		{
			value.ChangeType(VT_R8);
			m_gain = value.dblVal;
		}

    }
}

short CSubWaveInstrument::RemoveClipping( double a )
{
	if ( a > 32768 )
	{
		return 32700;
	}
	else if ( a < -32768 )
	{
		return -32700;
	}
	else
	{
		return ( (short) a );
	}
}

bool CSubWaveInstrument::Generate()
{
    bool valid = m_wavePlayer.Generate();

	double f = m_freq;// GetSampleRate(); Dividing breaks reson filter?

	double frame0 = m_wavePlayer.Frame(0);
	double frame1 = m_wavePlayer.Frame(1);

	double b = 0.2;
    double R = 1-b/2;

    double theta = acos(cos(2*PI*f)/(1+pow(R, 2)));
    double A = m_gain * (1-pow(R,2))*sin(theta);

    double y0 = A*frame0+(2*R*cos(theta))*y1-pow(R,2)*y2;
            

	if ( (m_time >= 0) && (m_time <= m_attack) )
	{
		y0 *= ( m_time / m_attack );
	}
	else if ( m_time >= (m_duration * GetSecondsPerBeat() - m_release ) )
	{
		double factor = ( ((m_duration * GetSecondsPerBeat()) - m_time) / m_release );
		y0 *= factor;
	}
	m_frame[0]=m_frame[1] = RemoveClipping(y0);
	
	y2 = y1; //y2 is the second to last output pushed
    y1 = y0; //y1 is the previous output pushed, y0 is the current output being pushed

	m_time += GetSamplePeriod();

	return m_time < (m_duration * GetSecondsPerBeat());
}