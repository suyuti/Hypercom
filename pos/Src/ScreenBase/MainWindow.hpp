#if !defined( _MAINWINDOW_HPP_ )
#define _MAINWINDOW_HPP_

#include "AppWindow.hpp"

//-----------------------------------------------------------------------------
// Main window of Hello World application
//
class MainWindow : public AppWindow
{
public:

	// Class constructor
	MainWindow( NU_EVENT_GROUP* eventGroup, int eventFlag );

	// Displays screen with specified ID
	void ShowScreen( int screenID );
};


#endif
