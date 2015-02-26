//=============================================================================
// Company:
//      Hypercom Inc
//
// Product:
//      Hyperware Base Application
//      (c) Copyright 2006
//
// File Name:
//      HyperwareMain.cpp
//
// File Contents:
//      Implementation of HyperwareMain
//
//=============================================================================
#if defined(__GNUC__)
#pragma implementation
#endif
#include <HypCTransactionManager.hpp>
#include <HypCJournal.hpp>
#include <HypCGrafixMsgBox.hpp>
#include <HypCGrafixMenu.hpp>
#include <HypCEvent.hpp>
#include <HypCEventInfo.hpp>
#include <HypCPAN.hpp>
#include <HypCFinancialDecoder.hpp>
#include <HypCGrafixUtil.hpp>
#include <HypCMSRArbReader.hpp>
#include <HypCServiceRequest.hpp>
#include <HypCSREventWait.hpp>
#include <HypCSRBlockingWait.hpp>
#include <HypCHostInterface.hpp>
#include <HypCPrinter.hpp>
#include <HypCpdsAAE.hpp>
#include <HypCSocket_Nucleus.hpp>
#include <HString.hpp>
#include <HypCTransactionData.hpp>
#include <HypTrace.h>
#include <HypCCodePage.hpp>
#include <HypCInfoBox.hpp>

// Uncomment the lines below to switch off logging in debug mode

//#if defined(DBGPRINTF)
//#undef DBGPRINTF
//#define DBGPRINTF(...)
//#endif

#include "YemekSepetiMain.hpp"
#include "YemekSepetiTags.h"
#include "TransactionFactory.hpp"
#include "StepFactory.hpp"
#include "HostFactory.hpp"
#include "DocumentManager.hpp"
#include "YemekSepetiConfig.hpp"
//#include "MultiLang.hpp"
#include "UIScreenFactory.hpp"
#include "TransportFactory.hpp"
#include ".\Moduller\Posserver.h"
#include ".\Moduller\RingListener.hpp"
#include ".\Moduller\Message.hpp"
#include ".\Moduller\SiparisData.h"
#include ".\Moduller\SystemManager.h"

// Fonts used in application
#include <Internal/GAL/Fonts.hpp>

// Key events registered on the main menu
#define DEBIT_KEY  	USER_EVENTS + 1
#define ADJUST_KEY 	USER_EVENTS + 2
#define SETTLE_KEY	USER_EVENTS + 3
#define REPRINT_KEY	USER_EVENTS + 4
#define REFUND_KEY	USER_EVENTS + 5
#define REVIEW_KEY	USER_EVENTS + 6
#define TOTALS_KEY	USER_EVENTS + 7

// Hyperware class for debugging
const char* CLASS_HYPERWARE = "Hyperware";

extern STATUS Buzzer_TurnOn( int NumTicks );
extern STATUS Buzzer_TurnOff( void );

//=============================================================================
// journal identificators
//=============================================================================

// tag for Hypercom journal
const char* JournalTags::HYPERCOM	= "HYPERCOM";
// journal for VISA host
const char* JournalTags::VISA		= "VISAII";
// Journal for Amex host
const char* JournalTags::AMEX		= "AMEX";
// journal for Batch records
const char* JournalTags::BATCH_REC	= "BATCH_REC";
// service tag to specify access to all hosts
const char* JournalTags::ALL_HOSTS	= "ALL HOSTS";
// service tag to specify access to something all
const char* JournalTags::ALL		= "ALL";


//-----------------------------------------------------------------------------
//!
//!      Constructor
//!
//! \return
//!      void
//!
//! \note
//!
HyperwareMain::HyperwareMain( const char* strAppName,
							 const char* strAppVersion,
							 unsigned int nRevision,
							 const char* nLocaleID ) :
	HypCApplication( strAppName, strAppVersion, nRevision, nLocaleID ),
	m_Window(0),
	m_StepFactory(0),
	m_TransactionFactory(0),
	m_HostFactory(0),
	m_HostInterface(0),
	m_Communication(0),
	m_ScreenFactory( 0 ),
	m_pPrinterPDS ( NULL )
{
}

//-----------------------------------------------------------------------------
//!
//!	 virtual destructor
//!
//! \return
//!      void
//!
//! \note
//!		Returns any resources obtained to the system. We have to find out how
//!      this will work when an application is a DLL module.
//!		m_Impl is deleted automatically by the destructor.
//!
HyperwareMain::~HyperwareMain()
{

	if( m_Communication )
	{
		delete m_Communication;
		m_Communication = NULL;
	}

	if( m_Printer )
	{
		delete m_Printer;
		m_Printer = NULL;
	}

	if ( m_pPrinterPDS )
	{
		delete m_pPrinterPDS;
		m_pPrinterPDS = NULL;
	}


	if( m_HostInterface )
	{
		delete m_HostInterface;
		m_HostInterface = NULL;
	}


	if( m_DocumentManager )
	{
		delete m_DocumentManager;
		m_DocumentManager = NULL;
	}

	if( m_UserInterface )
	{
		delete m_UserInterface;
		m_UserInterface = NULL;
	}


	if( m_Window )
	{
		delete m_Window;
		m_Window = NULL;
	}

	if( m_StepFactory )
	{
		delete m_StepFactory;
		m_StepFactory = NULL;
	}

	if( m_ScreenFactory )
	{
		delete m_ScreenFactory;
		m_ScreenFactory = 0;
	}
	if( m_TransactionManager )
	{
		delete m_TransactionManager;
		m_TransactionManager = NULL;
	}

	if( m_TransactionFactory )
	{
		delete m_TransactionFactory;
		m_TransactionFactory = NULL;
	}

	if( m_HostFactory )
	{
		delete m_HostFactory;
		m_HostFactory = NULL;
	}

	if( m_MultiLang )
	{
		delete m_MultiLang;
		m_MultiLang = NULL;
	}

    // Actually this could be skipped because smart pointer will deallocate space taken
    // by HypCCodePage instance anyway. Although deallocation will happen after function "main" which means
    // that trace will show memory used by HypCCodePage instance as a memory leak.
    // That is why manual deallocation happen here.
    HypCCodePage::Instance().Reset();
}




//-----------------------------------------------------------------------------
//!
//!	    Initialization code for the application
//!
//! \return
//!      void
//!
//! \note
//!
bool HyperwareMain::Init()
{
	bool bRetVal = false;
	m_StepFactory = new StepFactory ( 0 );

	m_TransactionManager = new HypCTransactionManager( this );

	if ( m_StepFactory && m_TransactionManager )
	{
		m_TransactionFactory = new TransactionFactory( m_StepFactory, m_TransactionManager );
		if ( m_TransactionFactory )
		{
			m_TransactionManager->SetTransactionFactory( m_TransactionFactory );
			m_TransactionManager->SetDefaultTransaction( TransactionNameTag::TRANS_ANKET_YAP );
			bRetVal = true;
		}
	}

/*	if (!CSystemManager::EthernetUp()) {
		HypCEvent ev;
		HypCEventInfo evinfo;
		HypMsgBoxParam prm;
		prm.Title = "Ethernet Up olmadi";
		HypCMsgBox *pMsgBox = m_UserInterface->MsgBox();
		pMsgBox->SetParams(prm);
		pMsgBox->Message(ev);
		if (ev.Wait(evinfo, 3000))
		{
			if (pMsgBox->AsyncResult() == KEY_ENTER) 
			{
			}
		}
	}
*/
    CreateThreads();

	return bRetVal;
}


//-----------------------------------------------------------------------------
//!
//!      Show the application error message in a Message Box
//!
//! \return
//!      void
//!
//! \note
//!
void HyperwareMain::ShowErrorMsg()
{
	if ( m_UserInterface )
	{
        HypMsgBoxParam Msg ( GetAppName().c_str(),
							 m_MultiLang->GetPrompt(m_ErrorMsg.c_str()),
							 BUTTON_OK,
							 NULL );
		m_UserInterface->MsgBox()->Message( Msg );
	}
}

//-----------------------------------------------------------------------------
//!
//!      Main execution routine for the application
//!
//! \return
//!      void
//!
//! \note
//!
int HyperwareMain::MainAppProcessing()
{
	//HypCEvent       read_event;
	HypCEventInfo   eventInfo;

	if( (!CreateBatRec()) || ( !CreateVisaJrn() ) || ( !CreateAmexJrn() ) )
	{
		ShowErrorMsg();
		Shutdown();
		return false;
	}
	if ( NULL == GetPrinter() )
	{
		m_ErrorMsg = "No Printer Available";
		ShowErrorMsg();
	}

	int ec = static_cast <HyperwareConfig*> ( m_DocumentManager->GetPOSConfig(  ) )->GetErrCode(  );

	if ( ec == -1 || ec == -2 )
	{
		if ( ec == -1 )
		{
			m_ErrorMsg = "Could not open configuration storage file";
		}
		else
		{
			m_ErrorMsg = "Could not open configuration format file";
		}
		ShowErrorMsg();
	}

	HypCMSRArbReader CardReader ( DEVICE_ID_CARD_READER,
								  const_cast<CHAR*>(GetAppName().c_str()),
								  m_Window->GetWndHandle() );
	if ( CardReader.IsArbitratorSessionOK() )
	{
        // Register a card range that this application supports.
		HANDLE nRangeHandle;
        CardReader.AddCardRange ( "11", "99", 2, &nRangeHandle );
	} else
	{
		m_ErrorMsg = "MSR Arb. not found";
		ShowErrorMsg();
		Shutdown();
		return false;
	}

	m_TimeToExit = false;
	m_UserInterface->Beep(m_UserInterface->TWO_SHORT_BEEP);
	while( !m_TimeToExit )
	{
        read_event.Reset();

#ifdef MAKE_EMV
        // Create an open_request which will be automatically close 
        // when it reaches the end of the scope
        HypCServiceRequest<HypCSmartCardDevice::Request::Open, HypCSREventWait> 
            open_request;

        open_request.ApplicationName = GetAppName().c_str();
        open_request.ApplicationMainWindow = GetMainWindow()->GetWndHandle() ;
        open_request.Event = &read_event;
        open_request.EventInfo.Set( 0, DEVICE_ID_SMART_CARD_READER, 0 );
#endif
		// Make sure to delete any previous user interface element request
		m_UserInterface->CancelRequests();

		// Issue read request to our devices:
		CardReader.Request( read_event, HypCMSRReader::READ_CARD );

        m_UserInterface->Menu( )->SetSPOSStyle( );

#ifdef MAKE_EMV
        if( SmartCardDevice().Schedule( &open_request ).Failed() )
        {
            m_ErrorMsg = "Smart Card Open Failed";
            ShowErrorMsg();
        }
#endif		
		// Request the user interface to show the main menu
		if ( !m_UserInterface->Request( read_event, HypCUserInterface::MENU_INPUT ) )
		{
			// Unable to execute request. Maybe the menu file does not exist!
			m_ErrorMsg = "Menu Error";
			ShowErrorMsg();
			m_TimeToExit = true;
			continue;
		}

		// Every call to HypCGrafixUserInterface->Request() will reset the list of
		// terminating keys. We need to add them each time.
		AddMenuShortcuts();



//---------------------------------------------------------

//---------------------------------------------------------





        HypCEvent ev;
        HypCEventInfo evinfo;
        HypMsgBoxParam prm;


		// Waiting for events on the CardReader and the Menu
		read_event.Wait ( eventInfo );
        int deviceID = eventInfo.GetDevice() == 0 ? eventInfo.GetRequestID() : eventInfo.GetDevice()->GetID();
        STATUS status;
		switch( deviceID )
		{
            case 9995:
            {
                prm.Title	= "Network";
                prm.Message = "Connection Test";
                HypCMsgBox *pMsgBox = m_UserInterface->MsgBox();
                pMsgBox->SetParams(prm);
                pMsgBox->Message(ev);
                if (ev.Wait(evinfo, 300))
                {
                    if (pMsgBox->AsyncResult() == KEY_ENTER) 
                    {
                    }
                }
            }
            break;
            case 9996:
            {
                /*prm.Title	= "Network";
                prm.Message = "Accepted!...";
                HypCMsgBox *pMsgBox = m_UserInterface->MsgBox();
                pMsgBox->SetParams(prm);
                pMsgBox->Message(ev);
                if (ev.Wait(evinfo, 10))
                {
                    if (pMsgBox->AsyncResult() == KEY_ENTER) 
                    {
                    }
                }
				*/
            }
            break;
			case 9997:
			{
				/*
				prm.Title	= "Network problemi";
				prm.Message = "kablo cikti";
				HypCMsgBox *pMsgBox = m_UserInterface->MsgBox();
				pMsgBox->SetParams(prm);
				pMsgBox->Message(ev);
				if (ev.Wait(evinfo, 5000))
				{
					if (pMsgBox->AsyncResult() == KEY_ENTER) 
					{
					}
				}
				*/
			}
			break;
			case 9998: // Network watch Timer
				{
					HypCSocket_Nucleus s;
                    s.CheckLink();
				}
			break;
            case 9999: // siparis var.
            {
				//status = NU_Suspend_Task(m_pPosListenerTask);
				//status = NU_Suspend_Task(m_pRingListenerTask);
                CMessage* pMsg;
                prm.Title = "Gelen Siparis";
                char buff[STACK_SIZE] = "";
                UNSIGNED actualSize;
                CSiparis *pSip = NULL;
                // mesaj kuyuda
                status = NU_Receive_From_Queue(m_pQueue,
                                               buff,
                                               2048,
                                               &actualSize,
                                               NU_SUSPEND);
                if (status == NU_SUCCESS)
                {
                    pMsg = (CMessage*)buff;
                    pSip = (CSiparis *)pMsg->GetObject();
					
					prm.Message = pSip->m_SiparisID.c_str();
                    prm.Title = pMsg->GetTime().AsString();
                }
                else {
                    prm.Message = "<hata>";
                }
				
                string prnMsg = "_______________________________________________________\r\n";
				prnMsg += "Siparis No : " + pSip->m_SiparisID + "\r\n";
				prnMsg += "Saat       : " + pSip->m_SiparisSaat + "\r\n";
				prnMsg += "Tarih      : " + pSip->m_SiparisTarih + "\r\n";
				prnMsg += "Musteri    : " + pSip->m_MusteriAdi + "\r\n";
				prnMsg += "Adres      : " + pSip->m_MusteriAdresi + "\r\n";
				prnMsg += "Telefon    : " + pSip->m_MusteriTelefon + "\r\n\r\n";
				prnMsg += "Siparis    : " + pSip->m_SiparisDetay + "\r\n";
                prnMsg += "_______________________________________________________\r\n";

				PrintBmp("siparislogo.bmp");
				PrintString(prnMsg.c_str());
                PrintBmp("yemeksepetilogo.bmp");
                PrintString("\r\n\r\n\r\n\r\n");

				//Buzzer_TurnOn(100);
				//Buzzer_TurnOff();
				/*
                HypCMsgBox *pMsgBox = m_UserInterface->MsgBox();
                pMsgBox->SetParams(prm);
                pMsgBox->Message(ev);
                if (ev.Wait(evinfo, 100))
                {
                    if (pMsgBox->AsyncResult() == KEY_ENTER) 
                    {
                    }
                }
				*/
                m_Communication->Reset();
                m_HostInterface->Reset();
                m_TransactionManager->Reset();

                m_UserInterface->Beep(m_UserInterface->LONG_BEEP);
                delete pSip;

				//status = NU_Resume_Task(m_pRingListenerTask);
				//status = NU_Resume_Task(m_pPosListenerTask);
            }
            break;
			case DEVICE_ID_USER_INTERFACE:
			{
				CardReader.CancelRequests();
				HypCMenu::SelectionType result = m_UserInterface->Menu()->MenuResult();

				switch ( result )
				{
				case HypCMenu::OptionSelected:
					{
						if ( m_UserInterface->Menu()->MenuResultString() == TransactionNameTag::QUIT_APP )
						{
							// Exit the application
							m_TimeToExit = PromptToExitApp();
						} else
						{
                            // set the transaction name and change
							// processing to new transaction
                            //HString str = m_UserInterface->Menu()->MenuResultString();
                            m_TransactionManager->ExecuteTransaction ( m_UserInterface->Menu()->MenuResultString().c_str() );
                            //m_TransactionManager->ExecuteTransaction ( str.c_str() );
						}
					}
					break;
				case HypCMenu::TerminatingKeyPressed:
					ProcessMenuKey( m_UserInterface->Menu()->GetTerminatingKey() );
					break;
				case HypCMenu::Escape:
					// do Nothing.. Cancel key should not terminate the application
					break;

				case HypCMenu::NoSelection:
					// do Nothing..
					break;

				}

                // clean up heap
                m_Communication->Reset();
                m_HostInterface->Reset();
                m_TransactionManager->Reset();

				m_UserInterface->Beep(m_UserInterface->LONG_BEEP);
			}
			break;

			case DEVICE_ID_CARD_READER:
			{
			}
			break;
            #ifdef MAKE_EMV
			case DEVICE_ID_SMART_CARD_READER:
			{
			}
			break;
            #endif // MAKE_EMV
			default:
				break;
		} // end switch

		IdleProcessing();
	}

	return 0;
}

//-----------------------------------------------------------------------------
//!
//!      Check what to do with a keypress in the main menu
//!
//! \param
//!      nKeyID      The key we got from the main menu
//!
//! \return
//!      void
//!
//! \note
//!
void HyperwareMain::ProcessMenuKey( INT16 nKeyID )
{
	DBGPRINTF ( VLVL_NORMAL, CLASS_HYPERWARE, "%s - Received key %c == %x\n", __FUNCTION__, nKeyID, nKeyID );
	switch ( nKeyID )
	{
	case DEBIT_KEY:
		// Execute a debit transaction
		//m_TransactionManager->ExecuteTransaction( TransactionNameTag::TRANS_SALE_DEBIT );
		break;
	case ADJUST_KEY:
		//m_TransactionManager->ExecuteTransaction( TransactionNameTag::TRANS_BATCH_REVIEW );
		break;
	case SETTLE_KEY:
		//m_TransactionManager->ExecuteTransaction( TransactionNameTag::TRANS_SETTLE );
		break;
	case REPRINT_KEY:
		//m_TransactionManager->ExecuteTransaction( TransactionNameTag::LAST_REPORT );
		break;
	case REFUND_KEY:
		//m_TransactionManager->ExecuteTransaction( TransactionNameTag::TRANS_REFUND_CREDIT );
		break;
	case REVIEW_KEY:
		//m_TransactionManager->ExecuteTransaction( TransactionNameTag::TRANS_BATCH_REVIEW );
		break;
	case TOTALS_KEY:
		//m_TransactionManager->ExecuteTransaction( TransactionNameTag::TRANS_BATCH_TOTAL );
		break;
	// the digits:
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	{
		char strDigit[2];
		HypCTransactionData TransData;

		strDigit[0] = nKeyID;
		strDigit[1] = '\0';
		HypCPAN pan ( strDigit );

		TransData.insert( TransactionTag::PAN, pan );
		m_TransactionManager->DefaultTransaction( TransData );

	}
		break;
	default:
		break;
	}
}


//-----------------------------------------------------------------------------
//!
//!      Applications should call this function before actually exit the application.
//!      This will save open documents and close them
//!
//! \return
//!      void
//!
//! \note
//!
bool HyperwareMain::Close()
{
	return true;
}


//-----------------------------------------------------------------------------
//!
//!      Provides idle processing functionality. Returns true if there's
//!      more activity
//!
//! \return
//!      true if there's more activity, else false
//!
//! \note
//!
bool HyperwareMain::IdleProcessing()
{
	NU_Relinquish();
	return true;
}


//-----------------------------------------------------------------------------
//!
//!      Child classes must create their own document manager object here
//!
//! \return
//!      True if document manager creation was successful
//!
//! \note
//!
bool HyperwareMain::CreateDocManager()
{
	bool bRetValue = false;

	m_DocumentManager = DocumentManager::GetDocManager();

	if ( NULL == m_DocumentManager )
	{
		return bRetValue;
	}

	m_DocumentManager->CreateDocuments();

	// Make sure the host factory is created before the host interface
	m_HostFactory = new HostFactory ();

	if ( NULL == m_HostFactory )
	{
		return bRetValue;
	}

	// Create the host interface device
	m_HostInterface = new HypCHostInterface( DEVICE_ID_HOST_INTERFACE );

	if ( m_HostInterface )
	{
		// Create transport factory object used by hosts to create transpott object
        m_Communication = new TransportFactory( DEVICE_ID_HOST_COMM );
        reinterpret_cast< TransportFactory * >(m_Communication)->SetInterface(m_UserInterface, m_MultiLang);
		// Set the communication driver for the host interface
		m_HostInterface->SetCommDevice( *m_Communication );
		bRetValue = true;
	}

	return bRetValue;
}


//-----------------------------------------------------------------------------
//!
//! \return
//!      True if the user interface was created succesfully
//!
//! \note
//!
bool HyperwareMain::CreateUserInterface()
{
	bool bRetVal = true;
#ifdef PLATFORM_M4100
	m_Window = new GrafixWindow( 0, HFC::Internal::DAL::Screen::AppMgrStatusTop, WIN_W, WIN_H - HFC::Internal::DAL::Screen::AppMgrStatusTop - HFC::Internal::DAL::Screen::AppMgrStatusBottom );
#else
	m_Window = new HypCGrafixWindow( 0, HFC::Internal::DAL::Screen::AppMgrStatusTop, WIN_W, WIN_H - HFC::Internal::DAL::Screen::AppMgrStatusTop - HFC::Internal::DAL::Screen::AppMgrStatusBottom );
#endif
	
	if ( m_Window )
	{
#ifdef PLATFORM_M4100		
		m_Window->EnableCustomBackground( );
#endif

        //m_Window->SetupWindow( WindowComplete,this, "", true, true, true );

		UIScreenFactory *ScreenFactory = new UIScreenFactory( m_Window, GetLocale() );
		if ( ScreenFactory )
		{
			// Save pointer so ScreenFactory can be deleted later
			m_ScreenFactory = ScreenFactory;

			m_Window->SetTitleFont( ScreenFactory->GetFontType( UIScreenFactory::TITLEBAR_FONT ) );
#ifndef PLATFORM_M4100
  //  		MultiLang* pCurrLang = new MultiLang("prompts.xml", GetLocale().c_str() );
#else
//			MultiLang* pCurrLang = new MultiLang("prompts_M2.xml", GetLocale().c_str() );
#endif
/*			if ( pCurrLang )
			{
				m_MultiLang = pCurrLang;

				// Get the font name for prompts in current locale:
				const HString& pNewFontName = pCurrLang->GetFontName( GetLocale().c_str(),
																	  FontTarget::H_PROMPT,
																	  FontStyle::H_NORMAL );

				ScreenFactory->CreateFontType( UIScreenFactory::PROMPT_TEXT_FONT,
											   pNewFontName );

                // Create the user interface
				m_UserInterface = new HypCUserInterface( DEVICE_ID_USER_INTERFACE, m_ScreenFactory );
			}
            */
            // Create the user interface
            m_UserInterface = new HypCUserInterface( DEVICE_ID_USER_INTERFACE, m_ScreenFactory );
		}
	}

	if ( NULL == m_UserInterface )
	{
		return false;
	}

	return bRetVal;
}


//-----------------------------------------------------------------------------
//!
//!      Create and setup journal for application
//!      Create and setup the Amex journal for application
//!
//! \return
//!      Nothing
//!
//! \note
//!
bool HyperwareMain::CreateAmexJrn()
{
	const char tablename[] = "amexjrn";

	const char tabledir[] = "D:\\";

	struct Field
	{
		const char *pTag;
		HypEType type;
	};

	struct Field SearchableFields[] =
	{
		{ TransactionTag::STATUS_FLAGS, TYPE_INT64 },
		{ TransactionTag::TYPE_NAME, TYPE_STRING },
		{ TransactionTag::KEY, TYPE_STRING },
		{ TransactionTag::PAN, TYPE_STRING },
		{ TransactionTag::ISSUER_NAME, TYPE_STRING },
		{ TransactionTag::CARD_ACCEPTOR_NAME, TYPE_STRING },
		{ TransactionTag::TOTAL_AMOUNT, TYPE_INT64 },
		{ TransactionTag::INVOICE, TYPE_STRING },
		{ TransactionTag::DATE_TIME, TYPE_DATE_TIME }
	};

	// create journal and assign to table
	m_Journal = new HypCJournal( tabledir, tablename );
	bool bRetValue = (NULL != m_Journal);

	if ( bRetValue )
	{
		// Try to open the journal
		bRetValue = m_Journal->Open();

		// try to open table, if not open need to create
		if( !bRetValue )
		{

			bRetValue = true;
			DBFieldDescriptor fields;

			// add the searchable fields
			for( size_t i = 0;
				 i < sizeof(SearchableFields)/sizeof( struct Field ); i++ )
			{
				fields.push_back( DBFieldDescr( SearchableFields[i].pTag,
												SearchableFields[i].type, 0 ) );
			}

			// create new table
			bRetValue = m_Journal->Create( fields );
			if ( !bRetValue )
			{
				m_ErrorMsg = "Not able to create the Amex journal";
			}
			else
			{
				bRetValue = m_Journal->Open();
				if ( !bRetValue )
				{
					m_ErrorMsg = "The Amex journal won't open";
				}
			}
		}
		m_Journals.Insert( JournalTags::AMEX, m_Journal );
	} else
	{
		m_ErrorMsg = "Journal Out of memory";
	}

	// close table
	m_Journal->Close();

	return bRetValue;
}

//-----------------------------------------------------------------------------
//!
//!      Create and setup a Hypercom journal for application
//!
//! \return
//!      Nothing
//!
//! \note
//!
bool HyperwareMain::CreateJournal()
{
	const char tablename[] = "journal";

	const char tabledir[] = "D:\\";

	struct Field
	{
		const char *pTag;
		HypEType type;
	};

	struct Field SearchableFields[] =
	{
		{ TransactionTag::STATUS_FLAGS, TYPE_INT64 },
		{ TransactionTag::TYPE_NAME, TYPE_STRING },
		{ TransactionTag::KEY, TYPE_STRING },
		{ TransactionTag::PAN, TYPE_STRING },
		{ TransactionTag::ISSUER_NAME, TYPE_STRING },
		{ TransactionTag::CARD_ACCEPTOR_NAME, TYPE_STRING },
		{ TransactionTag::TOTAL_AMOUNT, TYPE_INT64 },
		{ TransactionTag::INVOICE, TYPE_STRING },
		{ TransactionTag::DATE_TIME, TYPE_DATE_TIME }
	};

	// create journal and assign to table
	m_Journal = new HypCJournal( tabledir, tablename );
	bool bRetValue = (NULL != m_Journal);

	if ( bRetValue )
	{
		// Try to open the journal
		bRetValue = m_Journal->Open();

		// try to open table, if not open need to create
		if( !bRetValue )
		{
			bRetValue = true;
			DBFieldDescriptor fields;

			// add the searchable fields
			for( size_t i = 0;
				 i < sizeof(SearchableFields)/sizeof( struct Field ); i++ )
			{
				fields.push_back( DBFieldDescr( SearchableFields[i].pTag,
												SearchableFields[i].type, 0 ) );
			}

			// create new table
			bRetValue = m_Journal->Create( fields );
			if ( !bRetValue )
			{
				m_ErrorMsg = "Not able to create the Hypercom journal";
			}
			else
			{
				bRetValue = m_Journal->Open();
				if ( !bRetValue )
				{
                    //m_ErrorMsg = Prompts::NO_ACC_JRN;
				}
			}
		}
		m_Journals.Insert( JournalTags::HYPERCOM, m_Journal );
	} else
	{
		m_ErrorMsg = "Journal Out of memory";
	}

	// close table
	m_Journal->Close();

	return bRetValue;
}

//-----------------------------------------------------------------------------
//!
//!      Create and setup batch records database for application
//!
//! \return
//!      Nothing
//!
//! \note
//!
bool HyperwareMain::CreateBatRec()
{
	const char tablename[] = "batrec";

	const char tabledir[] = "D:\\";

	struct Field
	{
		const char *pTag;
		HypEType type;
	};

	struct Field SearchableFields[] =
	{
		{ TransactionTag::CARD_ACCEPTOR_NAME, TYPE_STRING },
		{ TransactionTag::LAST_SETL_ATT, TYPE_DATE_TIME },
		{ TransactionTag::LAST_SETL_SUCC, TYPE_DATE_TIME },
		{ TransactionTag::REV_COUNT, TYPE_INT64 },
		{ TransactionTag::ADJ_COUNT, TYPE_INT64 },
		{ TransactionTag::ADV_COUNT, TYPE_INT64 },
	};

	// create journal and assign to table
	HypCJournal* j_BatRecords = new HypCJournal( tabledir, tablename );
	bool bRetValue = ( NULL != j_BatRecords );
	if ( bRetValue )
	{
		// Try to open the journal
		bRetValue = j_BatRecords->Open(  );

		// try to open table, if not open need to create
		if( !bRetValue )
		{
			bRetValue = true;
			DBFieldDescriptor fields;

			// add the searchable fields
			for( size_t i = 0;
				 i < sizeof( SearchableFields )/sizeof( struct Field ); i++ )
			{
				fields.push_back( DBFieldDescr( SearchableFields[i].pTag,
												SearchableFields[i].type, 0 ) );
			}

			// create new table
			bRetValue = j_BatRecords->Create( fields );
			if ( !bRetValue )
			{
				m_ErrorMsg = "Not able to create the batch records journal";
			}
			else
			{
				bRetValue = j_BatRecords->Open(  );
				if ( !bRetValue )
				{
					//m_ErrorMsg = Prompts::NO_ACC_JRN;
				}
			}
		}

		m_Journals.Insert( JournalTags::BATCH_REC, j_BatRecords );

	} else
	{
		m_ErrorMsg = "Journal Out of memory";
	}

	// close table
	j_BatRecords->Close();

	return bRetValue;
}

//-----------------------------------------------------------------------------
//!
//!      Create journal for Visa transactions
//!
//! \return
//!      Nothing
//!
//! \note
//!
bool HyperwareMain::CreateVisaJrn()
{
	const char tablename[] = "visajrn";

	const char tabledir[] = "D:\\";

	struct Field
	{
		const char *pTag;
		HypEType type;
	};

	struct Field SearchableFields[] =
	{
		{ TransactionTag::STATUS_FLAGS, TYPE_INT64 },
		{ TransactionTag::TYPE_NAME, TYPE_STRING },
		{ TransactionTag::KEY, TYPE_STRING },
		{ TransactionTag::PAN, TYPE_STRING },
		{ TransactionTag::ISSUER_NAME, TYPE_STRING },
		{ TransactionTag::CARD_ACCEPTOR_NAME, TYPE_STRING },
		{ TransactionTag::TOTAL_AMOUNT, TYPE_INT64 },
		{ TransactionTag::INVOICE, TYPE_STRING },
		{ TransactionTag::DATE_TIME, TYPE_DATE_TIME },
		{ TransactionTag::ACI, TYPE_STRING },
		{ TransactionTag::AUTH_SRC, TYPE_STRING },
		{ TransactionTag::AVS_RESPONSE, TYPE_STRING },
		{ TransactionTag::VALIDATION_CODE, TYPE_STRING },
		{ TransactionTag::KEY, TYPE_STRING }
	};

	// create journal and assign to table
	HypCJournal* v_Journal = new HypCJournal( tabledir, tablename );
	bool bRetValue = (NULL != v_Journal);

	if ( bRetValue )
	{
		// Try to open the journal
		bRetValue = v_Journal->Open();

		// try to open table, if not open need to create
		if( !bRetValue )
		{

			bRetValue = true;
			DBFieldDescriptor fields;

			// add the searchable fields
			for( size_t i = 0;
				 i < sizeof(SearchableFields)/sizeof( struct Field ); i++ )
			{
				fields.push_back( DBFieldDescr( SearchableFields[i].pTag,
												SearchableFields[i].type, 0 ) );
			}

			// create new table
			bRetValue = v_Journal->Create( fields );
			if ( !bRetValue )
			{
				m_ErrorMsg = "Not able to create the Visa journal";
			}
			else
			{
				bRetValue = v_Journal->Open();
				if ( !bRetValue )
				{
					//m_ErrorMsg = Prompts::NO_ACC_JRN;
				}
			}
		}

		m_Journals.Insert( JournalTags::VISA, v_Journal );
	} else
	{
		m_ErrorMsg = "Journal Out of memory";
	}

	// close table
	v_Journal->Close();

	return bRetValue;
}

//-----------------------------------------------------------------------------
//!
//!      Create and setup printer object for application
//!
//! \return
//!      True if printer creation was succesfull
//!
//! \note
//!
bool HyperwareMain::CreatePrinter()
{
#define CLASSHYPWARE  MAKE_APP_CLASS(1)

	bool bRetValue = false;
	m_Printer = NULL;

	HypCPDSAAE* pTempPDS = new HypCPDSAAE( m_Window->GetWndHandle( ) );

	if ( !pTempPDS || !pTempPDS->IsArbitratorSessionOK() )
	{
		delete pTempPDS;
		m_pPrinterPDS = NULL;
		return bRetValue;
	} else
	{
		m_pPrinterPDS = pTempPDS;
	}

	// Set the printer font
	m_PrinterRegFont.SetFontPtr( HFC::Internal::GAL::Fonts::Get_HelvM15() );

	m_pPrinterPDS->SetFontType(  HypCPDS::REGULAR_FONT, &m_PrinterRegFont );

	// Create printer device
	HypCPrinter *prn = new HypCPrinter( DEVICE_ID_PRINTER, *m_pPrinterPDS );

	if ( prn )
	{
		if( prn->Init() )
		{
			bRetValue = true;
			m_Printer = prn;
		} else
		{
			delete prn;
		}
	}

	return bRetValue;
}


//-----------------------------------------------------------------------------
//!
//!      Prompt the user to exit the application
//!
//! \return
//!      true if the user wants to exit the application
//!
//! \note
//!
bool HyperwareMain::PromptToExitApp()
{
	const char* pExitPrompt = m_MultiLang->GetPrompt( "Çýkmak  istiyor musunuz ?" );
	HypMsgBoxParam ExitPrompt ( GetAppName().c_str(), pExitPrompt, BUTTON_YES_NO, NULL );
	return ( KEY_ENTER == m_UserInterface->MsgBox()->Message( ExitPrompt ) );
}

//-----------------------------------------------------------------------------
//!
//!      Registers the menu terminating keys that associate the keys on the
//!		factory keypad overlay with Hyperware functions.
//!
//! \return
//!      void
//!
//! \note
//!
void HyperwareMain::AddMenuShortcuts()
{
	typedef struct _KeyAsoc
	{
		INT16 HyperwareKey;
		INT16 KeyDef;
	}  KeyAsoc;

	// See keypad layout on keypad.h
	const KeyAsoc Shortcuts[] =
	{
		{ DEBIT_KEY,   KEY_CTRL_F1 },   // Debit key on overlay
		{ ADJUST_KEY,  KEY_F12 },       // Adjust key
		{ SETTLE_KEY,  KEY_CTRL_F4 },   // Settle key
		{ REPRINT_KEY, KEY_CTRL_F10 },  // Reprint key
		{ REFUND_KEY,  KEY_F10 },       // Refund key
		{ REVIEW_KEY,  'I' },           // Review key
		{ TOTALS_KEY,  'P' },           // Totals key
	};

	for ( size_t i = 0; i < sizeof (Shortcuts)/sizeof(KeyAsoc); i++ )
	{
		m_Window->AddTermKey( Shortcuts[i].HyperwareKey, Shortcuts[i].KeyDef );
	}

}

#ifdef PLATFORM_M4100
#include <HypCImage.hpp>
//-----------------------------------------------------------------------------
//!
//!      Call back function for window background. Not intended to be called
//!      directly. Calls on redraw member in derived classes.
//!
//! \param
//!      theWindow          handle to window making callback
//!
//! \return
//!      None
//!
//! \note
//!
void GrafixWindow::PaintBackground( HFC::Internal::GAL::Window::Handle theWindow )
{
	static bool imgFromFile = true;
	if( imgFromFile )
	{
		static bool imgDownloaded = false;
		if( !imgDownloaded )
		{
			if( !m_BackgroundImage.LoadImgFromFile( "c:\\background.bin" ) )
			{
				imgFromFile = false;
			}
			else
			{
				imgDownloaded = true;
				m_BackgroundImage.Draw( theWindow->wRect );
			}
		}
		else
		{
			m_BackgroundImage.Draw( theWindow->wRect );
		}
	}
	else
	{
		penState    thePenState;
		GetPenState(&thePenState); 

		HypCGrafixUtil::GradientFill( theWindow->wRect, background_left_, background_right_ );

		RS_Pen_Setup( DecodeColor( HColor( 255, 255, 255 ) ) );
		rect rc = theWindow->wRect;
		rc.Ymin = rc.Ymin + HFC::Internal::DAL::TitleBar::Height;
		rc.Ymax = rc.Ymin + 1;
		RS_Rectangle_Draw( FRAME, &rc, -1, 0, 0 );
		BackColor( DecodeColor( HColor( 10, 38, 85 ) ) );
		rc = theWindow->wRect;
		rc.Ymax = rc.Ymin + HFC::Internal::DAL::TitleBar::Height;
		RS_Rectangle_Draw( ERASE, &rc, -1, 0, 0 );
		SetPenState(&thePenState);
	}
}
#endif
/*
void HyperwareMain::WindowComplete( HypCGrafixWindow& window, void *arg )
{
	HypCUIElement *pElement = static_cast<HypCUIElement *>( arg );
	pElement->OnComplete();
}
*/

//----------------------------------------------------------------------
void HyperwareMain::CreateThreads()
{
    // NetListenThread
    // RingListenThread
   
    STATUS  status;
    BYTE*	TaskStack1 = NULL;
    BYTE*	TaskStack2 = NULL;
	//BYTE*	TaskStack3 = NULL;
    BYTE*	QueueStack = NULL;

    //QueueStack = new BYTE[1000];
    QueueStack = new BYTE[STACK_SIZE];
    TaskStack1 = new BYTE[STACK_SIZE];
	TaskStack2 = new BYTE[STACK_SIZE];
	//TaskStack3 = new BYTE[STACK_SIZE];

	//CGlobal::CreateQueue();

    if (QueueStack)
    {
#if defined(_DEBUG)
        memset (QueueStack, 0xAA, STACK_SIZE);
#endif
        status = Hyc_AllocControlBlock( CB_NU_QUEUE, (void **)&m_pQueue );
        //status = NU_Create_Queue(m_pQueue, "kuyu", QueueStack, 1000, NU_VARIABLE_SIZE, 20, NU_FIFO);
		//status = NU_Create_Queue(m_pQueue, "kuyu", QueueStack, STACK_SIZE, NU_VARIABLE_SIZE, 2048, NU_FIFO);
		status = NU_Create_Queue(m_pQueue, "kuyu", QueueStack, STACK_SIZE, NU_VARIABLE_SIZE, 4096, NU_FIFO);
        if (status != NU_SUCCESS)
        {
            delete[] QueueStack;
            return;
        }
    }
    if ( TaskStack1 ) {
#if defined(_DEBUG)
        memset (TaskStack1, 0xAA, STACK_SIZE);
#endif
        status = Hyc_AllocControlBlock( CB_NU_TASK, (void **)&m_pPosListenerTask );
        if (NU_SUCCESS == status) {
            status = NU_Create_Task( m_pPosListenerTask,
                                     "PosServerTask",
                                     PosServerThreadProc, 
                                     0, this,
                                     TaskStack1, 
                                     STACK_SIZE, 
                                     DEFAULT_PRIORITY, DEFAULT_TIMESLICE,
                                     NU_PREEMPT, NU_START );
            if (NU_SUCCESS != status)
            {
                Hyc_FreeControlBlock( m_pPosListenerTask );
            }
        }
        if ( NU_SUCCESS != status )
        {
            delete[] TaskStack1;
            return;
        }
    }
    
    if ( TaskStack2 )
    {
#if defined(_DEBUG)
        memset (TaskStack2,0xAA,STACK_SIZE);
#endif
        status = Hyc_AllocControlBlock( CB_NU_TASK, (void **)&m_pRingListenerTask );
        if (NU_SUCCESS == status)
        {
            status = NU_Create_Task( m_pRingListenerTask,
                                     "RingListenerTask",
                                     RingListenerThreadProc, 
                                     0, this,
                                     TaskStack2, 
                                     STACK_SIZE, 
                                     DEFAULT_PRIORITY, DEFAULT_TIMESLICE,
                                     NU_PREEMPT, NU_START );
            if (NU_SUCCESS != status)
            {
                Hyc_FreeControlBlock( m_pRingListenerTask );
            }
        }
        if ( NU_SUCCESS != status )
        {
            delete[] TaskStack2;
            return;
        }
    }

	m_pNetworkWatchTimer = new HypCTimer(read_event, 9998);
	m_pNetworkWatchTimer->Start(5000);
	/*
	if ( TaskStack3 )
	{
#if defined(_DEBUG)
		memset (TaskStack3,0xAA,STACK_SIZE);
#endif
		status = Hyc_AllocControlBlock( CB_NU_TASK, (void **)&m_pYemekSepetiClientTask);
		if (NU_SUCCESS == status)
		{
			status = NU_Create_Task( m_pYemekSepetiClientTask,
				"YemekSepetiClientTask",
				CYemekSepetiClient::Run, 
				0, this,
				TaskStack3, 
				STACK_SIZE, 
				DEFAULT_PRIORITY, DEFAULT_TIMESLICE,
				NU_PREEMPT, NU_START );
			if (NU_SUCCESS != status)
			{
				Hyc_FreeControlBlock( m_pYemekSepetiClientTask);
			}
		}
		if ( NU_SUCCESS != status )
		{
			delete[] TaskStack3;
			return;
		}
	}
	*/
}


void HyperwareMain::PrintString(const char *printStr)
{
	HString Buffer;
	struct pds_header h;

	h.width = pds_default_width;

	memcpy( &h, &pds_default_header, sizeof( struct pds_header ) );

	char align[3] = { 0x1b,PDS_ALIGN_LEFT, 0 };
	// put header first, then alignment specifier, then user string
    Buffer.append( reinterpret_cast <char*> ( &h ), sizeof( struct pds_header ) );
	Buffer.append( align );
	Buffer.append( printStr );

	// print a string in PDS format
	m_Printer->Print( Buffer );
}

void HyperwareMain::PrintBmp(const char *filename )
{
	HString Buffer;
	HString bmpPDS;
	struct pds_header h;

	h.width = pds_default_width;

	memcpy( &h, &pds_default_header, sizeof( struct pds_header ) );

	char align[3] = { 0x1b,PDS_ALIGN_LEFT, 0 };
    // put header first, then alignment specifier, then user string
    Buffer.append( reinterpret_cast <char*> ( &h ), sizeof( struct pds_header ) );
	Buffer.append( align );
	BMPtoPDS( filename,  bmpPDS );	
	Buffer.append( bmpPDS.c_str(),bmpPDS.length() );

	// print a string in PDS format
	m_Printer->Print( Buffer );
}
bool HyperwareMain::BMPtoPDS( const char *file,  HString& Buffer )
{

	#ifndef LONG
	typedef int LONG;
	#endif

	DWORD   bfOffBits;
	LONG    biWidth;
	LONG    biHeight;
	WORD    biBitCount;
	DWORD	biSizeImage;

	char* ddata;
	unsigned int bytes_read = 0;

	HypCFile fin( file, F_OPEN_EXISTING | F_SHARE_READ, F_READ, false );

	if ( !( fin.Open(  ) ) )
	{
		return false;
	}

	const int size_buf = 14 + 40;
	char buf[ size_buf ];
	fin.Read( buf, size_buf, bytes_read );

	memcpy( &bfOffBits, buf + 10, 4 );
	memcpy( &biWidth, buf + 18, 4 );
	memcpy( &biHeight, buf + 22, 4 );
	memcpy( &biBitCount, buf + 28, 2 );
	memcpy( &biSizeImage, buf + 34, 4 );

	int width_in_bytes = biSizeImage / biHeight;

	ddata = new char [ biSizeImage + width_in_bytes ];


	fin.Seek( bfOffBits, HypCFile::beginSeekPosition );
	fin.Read( ddata, biSizeImage, bytes_read );

	fin.Close(  );


	// swap bitmap lines in the right order
	char* line1, *line2;
	int i, k;

		int times = biHeight >> 1;
		char* temp_line = ddata + biSizeImage;
		for ( i = 0, line1 = ddata, line2 = ddata +
			_off_t( biSizeImage - width_in_bytes );
			i < times; i++, line1 += _off_t( width_in_bytes ),
			line2 -= _off_t( width_in_bytes ) )
		{
			memmove( temp_line, line1, width_in_bytes );
			memmove( line1, line2, width_in_bytes );
			memmove( line2, temp_line, width_in_bytes );
			for ( k = 0; k < width_in_bytes; k++ )
			{
				line1[k] = ~line1[k];
				line2[k] = ~line2[k];
			}
		}

	Buffer += PDS_ESC;
	Buffer += PDS_GRAPHICS;

	Buffer.append( const_cast<const char*> ( reinterpret_cast < char * > ( & biSizeImage ) ), sizeof( DWORD ) );
	Buffer.append( const_cast<const char*> ( reinterpret_cast < char * > ( & biWidth ) ), sizeof( DWORD ) );
	Buffer.append( const_cast<const char*> ( reinterpret_cast < char * > ( & width_in_bytes ) ), sizeof( DWORD ) );
	Buffer += static_cast <char> ( biBitCount );
	Buffer.append( static_cast <const char*> ( ddata + 0), biSizeImage );

	delete [] ddata;

	return true;
}


