#if defined(__GNUC__)
#pragma implementation
#endif

#include <hycddl.h>
#include <HypCStaticText.hpp>
#include <HypCButton.hpp>
#include <HypTrace.h>
#include "FirstScreen.hpp"
#include "Defines.hpp"

// Controls identifiers
#define ID_TEXT_CONTROL 9000
#define ID_BTN_NEXT		9001
#define ID_BTN_EXIT		9002

//-----------------------------------------------------------------------------
// Class costructor
// 
FirstScreen::FirstScreen( AppWindow* window ) :
    BaseScreen( window, "Hypercom Hello World", true )
{
}


//-----------------------------------------------------------------------------
// Class destructor
// 
FirstScreen::~FirstScreen( )
{
}


//-----------------------------------------------------------------------------
// Display current screent
// 
void FirstScreen::DisplayScreen( )
{
	int offset;

    DBGPRINTF( LOG_TRACE, CLASS_HFC, "First screen" );

    // get title height
	offset = m_wnd->GetTitleHeight( );

	// add some controls
	HypCStaticText  text1( SCREEN_WIDTH / 2 - 20, 5 + offset, 80, 20, ID_TEXT_CONTROL, "Hello World", LTEXT );
	HypCStaticText  text2( 10, 20 + offset, 80, 20, ID_TEXT_CONTROL, "First Screen", LTEXT );
	HypCButton      nextButton( "Next", SCREEN_WIDTH / 2 - BUTTON_W - 15, m_wnd->GetWindowHeight() - BUTTON_H - 10,
                                    BUTTON_W, BUTTON_H, ID_BTN_NEXT, KEY_F3 );
	HypCButton  	exitButton( "Exit", SCREEN_WIDTH / 2 + 14, m_wnd->GetWindowHeight() - BUTTON_H - 10,
                                    BUTTON_W, BUTTON_H, ID_BTN_EXIT, KEY_F6 );

    text1.SetTransparent(true);
    text2.SetTransparent(true);

    m_wnd->AddControl( text1 );
	m_wnd->AddControl( text2 );
	m_wnd->AddControl( nextButton );
	m_wnd->AddControl( exitButton );

	// open window
	m_wnd->Open( );

}


//-----------------------------------------------------------------------------
// Process events of the screen
// 
bool FirstScreen::ProcessEvents( int ReturnCode )
{
	switch( ReturnCode )
	{
    case ID_BTN_NEXT:
        // switch to next screen
		m_window->ShowScreen( SCREEN_SECOND );
		return false;

    case ID_BTN_EXIT:
        // close main window
		m_window->Close( );
		return false;

	default:
		break;
	}

    // return true, to stay on the screen
	return true;
}
