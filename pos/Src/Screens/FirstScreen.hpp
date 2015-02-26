#if !defined( _FIRSTSCR_HPP_ )
#define _FIRSTSCR_HPP_

#if defined(__GNUC__)
#pragma interface
#endif

#include "..\ScreenBase\BaseScreen.hpp"

//-----------------------------------------------------------------------------
// First screen class
//
class FirstScreen : public BaseScreen
{
public:

    // Constructor
    FirstScreen( AppWindow* window );

    // Destructor
    ~FirstScreen( );

    // Display current screent
	virtual void DisplayScreen( );

protected:

    // Process events of the screen
	virtual bool ProcessEvents( int ReturnCode );

};

#endif
