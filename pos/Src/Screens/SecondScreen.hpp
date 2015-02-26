#if !defined( _SECONDSCR_HPP_ )
#define _SECONDSCR_HPP_

#if defined(__GNUC__)
#pragma interface
#endif

#include "..\ScreenBase\BaseScreen.hpp"

//-----------------------------------------------------------------------------
// Second screen class
//
class SecondScreen : public BaseScreen
{
public:

    // Constructor
    SecondScreen( AppWindow* window );

    // Destructor
    ~SecondScreen( );

    // Display current screent
	virtual void DisplayScreen( );

protected:

    // Process events of the screen
	virtual bool ProcessEvents( int ReturnCode );

};


#endif

