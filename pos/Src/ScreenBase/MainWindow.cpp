#if defined(__GNUC__)
#pragma implementation
#endif

#include <hycddl.h>
#include <HypCGrafixWindow.hpp>
#include "..\Screens\Defines.hpp"
#include "MainWindow.hpp"
#include "..\Screens\FirstScreen.hpp"
#include "..\Screens\SecondScreen.hpp"


//-----------------------------------------------------------------------------
// Class costructor
// 
MainWindow::MainWindow( NU_EVENT_GROUP* eventGroup, int eventFlag ) :
    AppWindow( eventGroup, eventFlag )
{
}


//-----------------------------------------------------------------------------
// Displays screen with specified ID
// 
void MainWindow::ShowScreen( int screenID )
{
    // destroy previous screen
    if ( m_currentScreen )
    {
        delete m_currentScreen;
        m_currentScreen = NULL;
    }

    // create new screen
    switch ( screenID )
    {
    case SCREEN_FIRST:
        // create the first window
        m_currentScreen = new FirstScreen( this );
        break;
    case SCREEN_SECOND:
        // create the second window
        m_currentScreen = new SecondScreen( this );
        break;


    default:
        return;
    }

    // display current screen
    m_currentScreen->DisplayScreen( );
}


