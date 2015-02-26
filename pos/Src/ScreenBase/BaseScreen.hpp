#if !defined( _BASESCREEN_HPP_ )
#define _BASESCREEN_HPP_

#include "AppWindow.hpp"

//-----------------------------------------------------------------------------
// Base application sceen class
//
class BaseScreen 
{
public:

	// Constructor
	BaseScreen( AppWindow* window, const char *pTitle, bool titlebar );

	// Destructor
	virtual ~BaseScreen( );

	// Add controls and display particular screen
	virtual void DisplayScreen( ) = 0;

	// Event processing for screen
	virtual bool ProcessEvents( int returnCode ) = 0;

protected:

	// Graphix window 
	HypCGrafixWindow* m_wnd;

	// Main application window
	AppWindow* m_window;

private:

	// Window callback processing function
	void static OnComplete(HypCGrafixWindow& wnd, void* pArg);
};


#endif
