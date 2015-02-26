#if !defined( _DEFINES_HPP_ )
#define _DEFINES_HPP_

#include <HypCGrafixWindow.hpp>
#include <Internal/GAL/Window.hpp>

// Screen size definistions
#define SCREEN_WIDTH    HFC::Internal::DAL::Screen::Width
#define SCREEN_HEIGHT   ( HFC::Internal::DAL::Screen::Height - HFC::Internal::DAL::Screen::AppMgrStatusTop - HFC::Internal::DAL::Screen::AppMgrStatusBottom )

// Button size definition
#define BUTTON_H	16
#define BUTTON_W	58

// Events definition
#define EVENT_FINISH        0x01

// Window definition
#define SCREEN_FIRST		1
#define SCREEN_SECOND       2

#endif
