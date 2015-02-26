#if defined(__GNUC__)
#pragma implementation
#endif

#include <hycddl.h>
#include "BaseScreen.hpp"


//-----------------------------------------------------------------------------
// Class costructor
// 
BaseScreen::BaseScreen( AppWindow* window, const char *pTitle, bool titlebar ) :
    m_window ( window )
{
    m_wnd = window->GetWindow( );

    // Assign callback function and screen properties
    m_wnd->SetupWindow( OnComplete, this, pTitle ); 
}


//-----------------------------------------------------------------------------
// Class destructor
// 
BaseScreen::~BaseScreen( )
{
}

//-----------------------------------------------------------------------------
// Window event processing callback function
// 
void BaseScreen::OnComplete( HypCGrafixWindow& wnd, void* pArg )
{
    bool retVal = static_cast<BaseScreen*>(pArg)->ProcessEvents( wnd.ReturnCode( ) );

    // Window should be refreshed each time for further event processing
    if ( retVal )
    {
        wnd.Open();
    }
}

