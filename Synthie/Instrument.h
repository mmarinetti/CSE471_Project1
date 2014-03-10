#pragma once
#include "audionode.h"
#include "Note.h"

class CInstrument :
	public CAudioNode
{
public:
	CInstrument(void);
	virtual ~CInstrument(void);
	virtual void SetNote(CNote *note) = 0;
};

