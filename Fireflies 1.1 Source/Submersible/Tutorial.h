#pragma once

#if !defined(__Tutorial_H__)
#define __Tutorial_H__

// Library Includes

// Local Includes
#include "Session.h"
#include "TipBox.h"

// Types

// Constants

// Prototypes


class CTutorial : public CSession
{
// Member Functions
public:
	CTutorial();
	~CTutorial();
	void Process(float _fDeltaTick);
	void ProcessTutorial(float _fDeltaTick);

protected:

private:

// Member Variables
public:
	float m_fEventTimer;

protected:

private:

};

#endif // __Tutorial_H__
