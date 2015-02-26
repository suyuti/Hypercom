#if defined(__GNUC__)
#pragma implementation
#endif

#include <hycddl.h>
#include "AppWindow.hpp"
#include "BaseScreen.hpp"

int AppWindow::s_refcount = 0; 

//-----------------------------------------------------------------------------
// Class costructor
// 
AppWindow::AppWindow( NU_EVENT_GROUP* eventGroup, int eventFlag ) :
    m_eventGroup ( eventGroup ),
    m_eventFlag( eventFlag ),
    m_currentScreen( NULL )

{
	// Create HypCGrafixWindow if not already created  
	if ( s_refcount++ == 0 )
	{
		m_wnd = new HypCGrafixWindow(0, HFC::Internal::DAL::Screen::AppMgrStatusTop, WIN_W,  WIN_H - HFC::Internal::DAL::Screen::AppMgrStatusTop - HFC::Internal::DAL::Screen::AppMgrStatusBottom);
	}
}


//-----------------------------------------------------------------------------
// Class destructor
// 
AppWindow::~AppWindow( )
{
    // delete current screen
    if ( m_currentScreen )
    {
        delete m_currentScreen;
        m_currentScreen = NULL;
    }

    // delete graphix window
    if( --s_refcount == 0 ) 
    {
        delete m_wnd;
    }
}


//-----------------------------------------------------------------------------
// Close application window
// 
void AppWindow::Close( )
{
    // delete current screen
    if ( m_currentScreen )
    {
        delete m_currentScreen;
        m_currentScreen = NULL;
    }

	// Set finish event to terminate application
	NU_Set_Events( m_eventGroup, m_eventFlag, NU_OR );	
}

