// Library Includes
#include "windows.h"

// Local Includes

// This include
#include "Clock.h"

// Constants

// Static Variables

// Static Function Prototypes

// Implementation

CClock::CClock()
: m_fTimeElapsed(0.0f)
, m_fDeltaTime(0.0f)
, m_uLastTime(0)
, m_uCurrentTime(0)
{

}

CClock::~CClock()
{
}

bool CClock::Initialise()
{
	return(true);
}

/**
* Process function for the entire game time.
* 
* @Author Kurt
*/
void CClock::Process()
{
	m_fDeltaTime = 0;
	m_uLastTime = m_uCurrentTime;


	m_uCurrentTime = timeGetTime();

	if(m_uLastTime == 0.0f)
	{
		m_uLastTime = m_uCurrentTime;
	}
	
	unsigned int uDiff = m_uCurrentTime - m_uLastTime;
	
	m_fDeltaTime = static_cast<float>(uDiff);
	

	m_fTimeElapsed += m_fDeltaTime;
}

/**
* This function is to retrieve the current delta tick - accurately.
* 
* @Author Kurt
* @return fDeltaTick
*/
float CClock::GetDeltaTick()
{
	return(m_fDeltaTime / 1000.0f);
}

