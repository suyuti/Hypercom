#if !defined( _APPWINDOW_HPP_ )
#define _APPWINDOW_HPP_

#if defined(__GNUC__)
#pragma interface
#endif

#include <HypCGrafixWindow.hpp>

class BaseScreen;

//-----------------------------------------------------------------------------
// Base application window class
//
class AppWindow
{
public:

	// Constructor
	AppWindow( NU_EVENT_GROUP* eventGroup, int eventFlag );

	// Destructor
	virtual ~AppWindow( );

	// Displays particular screen
	virtual void ShowScreen( int ) = 0;

	// Terminate application
	virtual void Close( );

	// Return Graphix window instance
    HypCGrafixWindow* GetWindow( ) { return m_wnd; };

protected:

    // Current screen
    BaseScreen* m_currentScreen;

    // Application window
    HypCGrafixWindow* m_wnd;

private:

	// Reference counter for singleton-like workaround
	static int s_refcount;

	// Event group for event processing
	NU_EVENT_GROUP* m_eventGroup;

    // Event flag to set exit signaling
    int m_eventFlag;
};

#endif

