//=============================================================================
// Company:
//      Hypercom Inc
//
// Product:
//      Hyperware Base Application
//      (c) Copyright 2006
//
// File Name:
//      HyperwareMain.hpp
//
// File Description:
//      Declaration of the Class HyperwareMain
//
//=============================================================================
#if !defined( _HYPERWAREMAIN_HPP_ )
#define _HYPERWAREMAIN_HPP_

#include <HypCApplication.hpp>
#include <HypCFont.hpp>
#include <HypCGrafixWindow.hpp>
#include <HypCSmartCardDeviceAAE.hpp>
#include <HypCSecurityProvider.hpp>
#include <HypCImage.hpp>
#include <HypCEvent.hpp>
#include <HypCTimer.hpp>
#include ".\Moduller\Globals.h"
#include ".\Moduller\YemekSepetiClient.hpp"
//=============================================================================
// Public defines and typedefs
//=============================================================================

struct JournalTags
{
	//! tag for Hypercom journal
	static const char * HYPERCOM;
	
	//! journal for VISA host
	static const char * VISA;

	//! journal for AMEX host
	static const char * AMEX;
	
	//! journal for Batch records
	static const char * BATCH_REC;
	
	//! service tag to specify access to all hosts
	static const char * ALL_HOSTS;
	
	//! service tag to specify access to something all
	static const char * ALL;
};

//  Device ID's used in this application
enum DeviceIds
{
	DEVICE_ID_USER_INTERFACE = 15,  // start with 15, just do not use zero
	DEVICE_ID_CARD_READER,
	DEVICE_ID_PIN_PAD,
	DEVICE_ID_PRINTER,
	DEVICE_ID_MODEM,
	DEVICE_ID_HOST_COMM,
	DEVICE_ID_HOST_INTERFACE,
	DEVICE_ID_SERIAL_PORT,
	DEVICE_ID_CHECK_READER,
	DEVICE_ID_SMART_CARD_READER,
	DEVICE_ID_NOT_USED
};

// Hyperware class for debugging
extern const char* CLASS_HYPERWARE;

//=============================================================================
// Forward definitions
//=============================================================================

class HypCTransactionStepFactory;
class HypCTransactionFactory;
class HypCHostFactory;
class HypCHostInterface;
class HypCMLTransport;
class HypCGrafixMsgBox;
class HypCGrafixInputBox;
class HypCGrafixMenu;
class HypCGrafixInfoBox;
class HypCGrafixList;
class HypCPDSGraphic;
class HypCUIScreenFactory;
class GrafixWindow;

//=============================================================================
//!
//! \brief
//!      Main class for application
//!
//! \sa
//!      HypCApplication
//!
//=============================================================================
#define STACK_SIZE	(16 * 1024)

class HyperwareMain : public HypCApplication
{
    private:
        NU_TASK*    m_pPosListenerTask;
        NU_TASK*    m_pRingListenerTask;
		NU_TASK*	m_pYemekSepetiClientTask;
        NU_QUEUE*   m_pQueue;
        HypCEvent   read_event;
		HypCTimer	*m_pNetworkWatchTimer;

        void CreateThreads();

    public:
    NU_QUEUE* GetQueue() { return m_pQueue; };
    HypCEvent* GetListenEvent() { return &read_event;};
    void PrintString(const char *printStr);
    void PrintBmp(const char *filename );
    bool BMPtoPDS( const char *file,  HString& Buffer );
    

    public:
		//! The constructor initializes the name, version number and revision
		HyperwareMain( const char* strAppName,
					   const char* strAppVersion,
					   unsigned int nRevision = 1,
					   const char* nLocaleID = DefaultLocale ); // American English

		//! Destructor
		HyperwareMain::~HyperwareMain();


		//! Child classes must create their own host interface object
		HypCHostInterface *GetHostInterface()
		{
			return m_HostInterface;
		}


		//! Returns pointer to main window
		HypCGrafixWindow* GetMainWindow()
		{
			return reinterpret_cast<HypCGrafixWindow*>(m_Window);
		}

		//! Returns application version string
		const HString& GetVersion() const;

		//! Returns the host factory
		HypCHostFactory  *GetHostFactory()
		{
			return m_HostFactory;
		}

        //! Returns reference to Smart Card Device
        HypCSmartCardDeviceAAE& SmartCardDevice()
        {
            return m_SmartCardDevice;
        }

        //! Returns reference to Smart Card Device
        HypCSecurityProvider& SecurityProvider()
        {
            return m_SecurityProvider;
        }
		//static void WindowComplete( HypCGrafixWindow& window, void *arg );

	protected:

	private:

		// Displays a error message box using the variable m_ErrorMsg
		void ShowErrorMsg();

		//! This is a place to put initialization code for the application
		virtual bool Init();

		//! Main loop for event processing
		virtual int MainAppProcessing();

		//! Applications should call this function before actually exit the
		//! application. This will save open documents and close them
		virtual bool Close();

		//! Provides idle processing functionality. Returns true if there's
		//! more activity to do.
		virtual bool IdleProcessing();

		//! Create the document manager object
		virtual bool CreateDocManager();

		//! Create the user interface object
		virtual bool CreateUserInterface();

		//! Create the journal object
		virtual bool CreateJournal();

		//! Create journal for VISA transactions
		virtual bool CreateVisaJrn();

		//! Create journal for AMEX transactions
		virtual bool CreateAmexJrn();

		//! Create and setup batch records database for application
		virtual bool CreateBatRec();
		//! Create the printer object
		virtual bool CreatePrinter();

		void ProcessMenuKey( INT16 nKeyID );

		//! Prompt the user to exit the application
		bool PromptToExitApp();

		//! Registers the menu terminating keys that associate the keys on the
		//! factory keypad overlay with Hyperware functions.
		void AddMenuShortcuts();

	protected:
		

	private:
#ifdef PLATFORM_M4100		
		//! Window used by user interface
		GrafixWindow*		        m_Window;
#else
		HypCGrafixWindow*		    m_Window;
#endif

		//! Application step factory
		HypCTransactionStepFactory* m_StepFactory;

		//! Transaction factory
		HypCTransactionFactory*     m_TransactionFactory;

		//! Host factory
		HypCHostFactory*            m_HostFactory;

		//! Host interface
		HypCHostInterface*          m_HostInterface;

		//! Host communication object
		HypCMLTransport*          	m_Communication;

		HypCUIScreenFactory*        m_ScreenFactory;

		//! The version number is increased when there's a change in functionality
        HString          			m_Version;

		//! Font used for regular printer font
		HypCFont 					m_PrinterRegFont;

		//! Font used for double printer font
		HypCFont 					m_PrinterDoubleFont;

		//! The PDS object for the printer
		HypCPDSGraphic*				m_pPrinterPDS;

        //! Smart card device
        HypCSmartCardDeviceAAE      m_SmartCardDevice;

        //! Security Provider 
        HypCSecurityProvider        m_SecurityProvider;
}; // HyperwareMain
#ifdef PLATFORM_M4100
//=============================================================================
//!
//! \brief
//!      Main class for user interface
//!
//! \sa
//!      HypCGrafixWindow
//!
//=============================================================================
class GrafixWindow : public HypCGrafixWindow
{
//=============================================================================
// Member functions
//=============================================================================
	public:

        //! Constructor
		GrafixWindow( int left = 0, int top = 0, int width = WIN_W, int height = WIN_H ):
					  HypCGrafixWindow(left, top, width, height),
					  background_left_( 15, 35, 75 ),
					  background_right_( 68, 157, 210 )
		{
		}

		//! Destructor
		~GrafixWindow()
		{
		}

	private:

		//! backgroung routine
		void PaintBackground( HFC::Internal::GAL::Window::Handle theWindow );

//=============================================================================
// Member variables
//=============================================================================
		//! background color left
		HColor background_left_;
		//! background color right
		HColor background_right_;

        //! Background image
        HypCImage m_BackgroundImage;

};
#endif
#endif // #if !defined( _HYPERWAREAPPMAIN_HPP_ )

