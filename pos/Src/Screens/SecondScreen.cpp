#if defined(__GNUC__)
#pragma implementation
#endif

#include <hycddl.h>
#include <HypCStaticText.hpp>
#include <HypCButton.hpp>
#include <HypTrace.h>
#include "SecondScreen.hpp"
#include "Defines.hpp"

// Controls identifiers
#define ID_TEXT_CONTROL	9000
#define ID_BTN_BACK		9001
#define ID_BTN_EXIT		9002

//-----------------------------------------------------------------------------
// Class costructor
// 
SecondScreen::SecondScreen( AppWindow* window ) :
    BaseScreen( window, "Hypercom Hello World", true )
{
}


//-----------------------------------------------------------------------------
// Class destructor
// 
SecondScreen::~SecondScreen( )
{
}



//-----------------------------------------------------------------------------
// Display current screent
// 
void SecondScreen::DisplayScreen( )
{
	int offset;

    DBGPRINTF( LOG_TRACE, CLASS_HFC, "Second screen" );

    // get title height
    offset = m_wnd->GetTitleHeight( );

    // add some controls
    HypCStaticText  text1( SCREEN_WIDTH / 2 - 20, 5 + offset, 80, 20, ID_TEXT_CONTROL, "Hello World", LTEXT );
    HypCStaticText  text2( 10, 20 + offset, 80, 20, ID_TEXT_CONTROL, "Second Screen", LTEXT );
    HypCButton      backButton( "Back", SCREEN_WIDTH / 2 - BUTTON_W - 15, m_wnd->GetWindowHeight() - BUTTON_H - 10,
                                    BUTTON_W, BUTTON_H, ID_BTN_BACK, KEY_F3 );
    HypCButton  	exitButton( "Exit", SCREEN_WIDTH / 2 + 14, m_wnd->GetWindowHeight() - BUTTON_H - 10,
                                    BUTTON_W, BUTTON_H, ID_BTN_EXIT, KEY_F6 );


    text1.SetTransparent(true);
    text2.SetTransparent(true);

    // add some controls
    m_wnd->AddControl( text1 );
    m_wnd->AddControl( text2 );
    m_wnd->AddControl( backButton );
    m_wnd->AddControl( exitButton );

    // open window
	m_wnd->Open();
}


//-----------------------------------------------------------------------------
// Process events of the screen
// 
bool SecondScreen::ProcessEvents( int ReturnCode )
{

	switch(ReturnCode)
	{
    case ID_BTN_BACK:
        // switch to back screen
	    m_window->ShowScreen( SCREEN_FIRST );
		return false;

    case ID_BTN_EXIT:
        // close main window
		m_window->Close();
		return false;

	default:
		break;
	}

    // return true, to stay on the screen
    return true;
}
