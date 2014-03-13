#include "StdAfx.h"
#include "DrumInstrument.h"
#include "DrumFactory.h"
#include "Notes.h"
#include <cmath>

#define PI 3.14159

CDrumInstrument::CDrumInstrument(void)
{
    m_attack = .05;
    m_release = .05;
    m_freq = 500;
    m_amp = .5;
    m_synthesizing = false;
}


CDrumInstrument::~CDrumInstrument(void)
{
}

void CDrumInstrument::Start()
{
    m_noise.SetSampleRate(GetSampleRate());
    m_noise.Start();
    m_wavePlayer.Start();
    m_wavePlayer.SetSampleRate(GetSampleRate());
    m_time=0;
    /*x11=0;
    x21=0;
    x12=0;
    x22=0;*/
}


void CDrumInstrument::SetNote(CNote *note)
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

        /*if(name == "duration")
        {
            value.ChangeType(VT_R8);
            m_duration=(value.dblVal);
        }
        else if(name == "amplitude")
        {
            value.ChangeType(VT_R8);
            m_amp=(value.dblVal);
        }
        else if(name == "note")
        {
            SetFreq(NoteToFrequency(value.bstrVal));
        }
        else if(name == "attack")
        {
            value.ChangeType(VT_R8);
            m_attack=(value.dblVal);
        }
        else if(name == "release")
        {
            value.ChangeType(VT_R8);
            m_release=(value.dblVal);
        }*/

    }

}

void CDrumInstrument::SetState(int state)
{
    m_state = state;

    if(m_state == TechOne)
    {
        m_duration = .1;
        m_attack = .025;
        m_release = .75;
        m_synthesizing = true;
    }
    else if (m_state == TechTwo)
    {
        m_duration = 1;
        m_attack = .4;
        m_release = .4;
        m_synthesizing = true;
    }
    else if (m_state == TechThree)
    {
        m_duration = 1;
        m_attack = .4;
        m_release = .4;
        m_synthesizing = true;
    }
}

bool CDrumInstrument::Generate()
{
    if(m_synthesizing)
    {
        m_freq = m_freq/44100;
        // Tell the component to generate an audio sample
        m_noise.Generate();
	

        m_frame[0] = m_noise.Frame(0);
        m_frame[1] = m_noise.Frame(1);
        
        if(m_state == TechTwo)
        {
            double x0 = m_noise.Frame(0);

            double R = .05;
            double theta = acos(cos(2*PI*m_freq)/(1+pow(R, 2)));
            double A = (1-pow(R,2))*sin(theta);

            double y0 = A*x0+(2*R*cos(theta))*x1-pow(R,2)*x2;
            
            m_frame[0]=m_frame[1]=y0;

            x2 = x1;
            x1 = x0;

        }

        else if(m_state == TechThree)
        {
            double x0 = m_noise.Frame(0);

            double new_freq = m_freq + m_freq*(m_time/m_duration);

            double R = .05;
            double theta = acos(cos(2*PI*new_freq)/(1+pow(R, 2)));
            double A = (1-pow(R,2))*sin(theta);

            double y0 = A*x0+(2*R*cos(theta))*x1-pow(R,2)*x2;
            
            m_frame[0]=m_frame[1]=y0;

            x2 = x1;
            x1 = y0;
        }


    	//ATTACK AND RELEASE IMPLEMENATION
    	double factor = 0;
    	if(m_time < m_attack){
    		factor = m_time*1./m_attack;
    		m_frame[0] *= factor;
    		m_frame[1] *= factor;
    	}
    	else if(m_time > ((m_duration * GetSecondsPerBeat()) - m_release)){
    		factor = m_time*-1./m_release + (1./m_release)*(m_duration*GetSecondsPerBeat());
    		m_frame[0] *= factor;
    		m_frame[1] *= factor;
        }


        // Update time
        m_time += GetSamplePeriod();

        // We return true until the time reaches the duration.
        return m_time < (m_duration * GetSecondsPerBeat());
    }
    else
    {
        bool valid = m_wavePlayer.Generate();

        m_frame[0] = m_wavePlayer.Frame(0)*m_amp;
        m_frame[1] = m_wavePlayer.Frame(1)*m_amp;

        return valid;
    }
}