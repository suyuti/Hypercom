//=============================================================================
// Company:
//      Hypercom Inc
//
// Product:
//      Hypercom Foundation Classes 
//      (c) Copyright 2006
//
// File Name:
//      UIScreenFactory.hpp
//
// File Contents:
//      Declaration of UIScreenFactory class
//
//=============================================================================
#if !defined( _UISCREENFACTORY_HPP_ )
#define _UISCREENFACTORY_HPP_

#if defined(__GNUC__)
#pragma interface
#endif

#include <HypCUIScreenFactory.hpp>
#include <HypCStatus.hpp>

class HypCGrafixWindow;
class HString;

//=============================================================================
//!
//! \brief
//!      Creates user interface screens of type HypCUIElement.
//!
//!      
//! \sa
//!      
class UIScreenFactory : public HypCUIScreenFactory
{
//=============================================================================
// Member functions
//=============================================================================
	public:
		//! Font types used by Hyperware
		typedef enum _HyperwareFontType
		{
			//! Font used for promts
			PROMPT_TEXT_FONT = 0,
			//! Font used for title bar
			TITLEBAR_FONT,
			//! Font used for list screen
			LIST_TEXT_FONT,
			//! Font used for button text
			BUTTON_TEXT_FONT,
			//! Maximum font types
            HYPERWARE_MAX_FONTS
		} HyperwareFontType;

        struct Status
        {
            enum ErrorCodeType {
                FontNotSet
            };

            static const char *ClassFacility() { return "UIScreenFactory"; }
        };

		//! default constructor
		UIScreenFactory( HypCGrafixWindow *wnd, const HString& strLocale );

		//! Creates the font specified by its font name and assigns it to the font type
		const HypCFont* CreateFontType( HyperwareFontType font_type, const HString& strFileName );

		//! Set the font using a given HypCFont *
		HypCStatus SetFontType ( HyperwareFontType font_type, const HypCFont* pFont );

		//! Returns the requested font based on on type. 
		const HypCFont* GetFontType ( HyperwareFontType font_type );
		   
		//! Destructor
		virtual ~UIScreenFactory();
	
	protected:
		//! No implemented on purpose. We don't want copies of this class.
		UIScreenFactory();
		

		//! Create an instance of specified data type
		virtual HypCUIElement* doCreateInstance( HScreenType ScreenType, 
												 HypCUserInterface *iface, 
												 const char *dialogName );


	private:

		//! This function is called from the constructor to populate the
		//! array of fonts the application will use.
		void CreateFonts( const HString& strLocale );

		//! Destroys the fonts used by the screen factory
		void ResetFonts();

		//! A pointer to the main window of the application
		HypCGrafixWindow *m_Window;

		//! The font repository for the Hyperware application
		const HypCFont*	m_HyperwareFonts[HYPERWARE_MAX_FONTS];
	
}; 

inline void HypCStatusConstruct( HypCStatus &that, UIScreenFactory::Status::ErrorCodeType code )
{
    that.Assign( UIScreenFactory::Status::ClassFacility(), true, code );
}

inline bool HypCStatusEqual( const HypCStatus &that, UIScreenFactory::Status::ErrorCodeType code )
{
    return that.Facility() == UIScreenFactory::Status::ClassFacility()
           && that.RawErrorCode() == code;
}

#endif // #if !defined( _UISCREENFACTORY_HPP_ )

