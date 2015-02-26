//=============================================================================
// Company:
//      Hypercom Inc
//
// Product:
//      Hyperware Base Application
//      (c) Copyright 2006
//
// File Name:
//      StepHostCommunicate.cpp
//
// File Contents:
//      Implementation of StepHostCommunicate
//
//=============================================================================
#include <compiler.h>
#include <HypCHostInterface.hpp>
#include <HypCTransaction.hpp>
#include <HypCInfoBox.hpp>
#include "YemekSepetiMain.hpp"
#include "StepHostCommunicate.hpp"
#include "PromptsDef.h"

//-----------------------------------------------------------------------------
//!
//!      Execution of step
//!
//! \return
//!      None
//!
//! \note
//!
//=============================================================================
bool StepHostCommunicate::doExecute()
{
	HypCEvent event(20);
	HypCEventInfo Ei;
	HypInfoParam dsc;
	int reqId;
	int status;
	HString msg;
	const char *ptr;
	HypCMultiLang* prompt = Transaction().GetMultiLang();
	
	// set up defaults for msg box
	dsc.Title = prompt->GetPrompt( Prompts::PROCESSING_TRANS );

	// get the user interface
	HypCUserInterface *m_Interface = Transaction().GetUserInterface();

	// get the host interface
	HyperwareMain *pApp = static_cast<HyperwareMain*>( Transaction().GetApplication() );
	HypCHostInterface *pHost = pApp->GetHostInterface();


	// request auto status update from host
	pHost->RequestAutoStatus( event );

	// perform the transaction
	pHost->PerformTransaction( event, Transaction() );

	// show the current state
	int currentstate = pHost->GetHostState();
	dsc.Message = GetHostStateText( currentstate, prompt );
#ifdef PLATFORM_M4100	
	m_Interface->InfoBox()->SetTextColor( clBlack ); 
	m_Interface->InfoBox()->SetMsgY( WIN_H/2 - 23 );
    m_Interface->InfoBox()->SetMsgH( 80 );
#endif
	// show initial host state message
	m_Interface->InfoBox()->Show( event, dsc);


	bool bLoop = true;

	do
	{
		// wait for status change or transaction complete
		// or user key
		event.Wait(Ei);

		if( pHost == Ei.GetDevice() )
		{
			switch( reqId = Ei.GetRequestID() )
			{
				case HypCHostInterface::AUTO_STATE_REQUEST:
					ptr = GetHostStateText( Ei.GetStatus(), prompt );
#ifdef PLATFORM_M4100	
					m_Interface->InfoBox()->SetTextColor( clBlack ); 
					m_Interface->InfoBox()->SetMsgY( WIN_H/2 - 23 );
                    m_Interface->InfoBox()->SetMsgH( 80 );
#endif
					m_Interface->InfoBox()->UpdateText( ptr );
					break;

				case HypCHostInterface::TRANSACTION_REQUEST:
					// cancel auto request
					pHost->CancelAutoStatus( );
					
					// cancel current UI request
					m_Interface->InfoBox()->Cancel();

					
					// step to check host results
					status = Ei.GetStatus();
					if( status != HOST_OK )
					{
						// show error and abort transaction!	
						GetHostErrorText( status, dsc.Message, m_Interface );
						if ( pHost->GetErrDesc(  ) != "" )
						{
							dsc.Message += ": ";
							dsc.Message += pHost->GetErrDesc(  );
						}
#ifdef PLATFORM_M4100	
						m_Interface->InfoBox()->SetTextColor( clBlack ); 
#endif
						m_Interface->InfoBox()->Show( event, dsc );
						event.Reset(  );
						if( !event.Wait(Ei, 2000) )
						{
							// we timed out
							m_Interface->InfoBox()->Cancel();
						}		
						
						// abort the transaction
						SetExecAction ( TRANS_ABORT );
						return false;
					}

					// good host result, host results are
					// now in TransactionTag::HOST_RESPONSE_TEXT
					// break loop, continue to next step		
					bLoop = false;
					
					break;
			}
		}
		else if( m_Interface == Ei.GetDevice() )
		{
			// Attempt to cancel Host operation if allowable
			(pHost->GetCurrentHost())->CancelHost();
		}

	} while( bLoop );

	// cancel auto request
	pHost->CancelAutoStatus( );

	SetExecAction ( STEP_NEXT );


	// No need for step post-processing
	return false;
}


//-----------------------------------------------------------------------------
//!
//!      Returns host string based on host state from HypCHostInterface.
//!
//! \param
//!      state           state as returned from HypCHostInterface
//! \param
//!      str             string based on state identifier stored here
//!
//! \return
//!      None
//!
//! \note
//!
const char *StepHostCommunicate::GetHostStateText( int state, HypCMultiLang* m_Lang)
{
	
	const char *ptr;

	// for testing just check them all
	switch( state )
	{
		case HostCreation:
			ptr = m_Lang->GetPrompt( Prompts::HOST_CREATE );
			break;

		case StartTransaction:
			ptr = m_Lang->GetPrompt( Prompts::START_TRANS );
			break;

		case PreProcessingTransaction:
			ptr = m_Lang->GetPrompt( Prompts::PRE_PROC );
			break;

		case EncodingRequest:
			ptr = m_Lang->GetPrompt( Prompts::ENC_REQ );
			break;

		case SendingRequest:
			ptr = m_Lang->GetPrompt( Prompts::SEND_REQ );
			break;

		case Connecting:
			ptr = m_Lang->GetPrompt( Prompts::CONNECT );
			break;

		case NoDialTone:
			ptr = m_Lang->GetPrompt( Prompts::NO_DIAL_TONE );
			break;

		case Busy:
			ptr = m_Lang->GetPrompt( Prompts::WAIT_LINE );
			break;


		case Processing:
			ptr = m_Lang->GetPrompt( Prompts::PROCESS );
			break;

		case WaitingForResponse:
			ptr = m_Lang->GetPrompt( Prompts::WAIT_RESP );
			break;

		case ProcessingResponse:
			ptr = m_Lang->GetPrompt( Prompts::PROC_RESP );
			break;

		case DecodingResponse:
			ptr = m_Lang->GetPrompt( Prompts::DEC_RESP );
			break;

		case PostProcessingTransaction:
			ptr = m_Lang->GetPrompt( Prompts::POST_PROC );
			break;

		case JournalSaving:
			ptr = m_Lang->GetPrompt( Prompts::SAV_JOURN );
			break;

		case TransactionFinished:
			ptr = m_Lang->GetPrompt( Prompts::TRANS_COMPL );
			break;

		case TransactionFinishedWithError:
			ptr = m_Lang->GetPrompt( Prompts::TRANS_FAILED );
			break;

		case SettlementProcessing:
			ptr = m_Lang->GetPrompt( Prompts::SETTLE_PROC );
			break;

		default:
			ptr = m_Lang->GetPrompt( Prompts::UN_HOST_STATE );
			break;
	}


	return ptr;
}


//-----------------------------------------------------------------------------
//!
//!      Get a text sting to associate with error result 
//!      as returned by host interface
//!
//! \param
//!      Result          host error typically from enum HypEHostResult
//!
//! \return
//!      None
//!
//! \note
//!
void StepHostCommunicate::GetHostErrorText( int Result, HString& str, HypCUserInterface* UI )
{
	char buff[3];
	
	switch( Result )
	{
		//  Transaction incomplete
		case HOST_INCOMPLETE_TRANS:
			str = "Incomplete Transaction";
			break;

		// Communication error
		case HOST_COMM_ERROR:
			str = "Communication Error";
			break;
		
		// Comm device not initialized
		case HOST_COMM_NOT_INITIALIZED:
			str = "Comm Not Initialized";
			break;

		// Host is busy and cannot accept request
		case HOST_BUSY:
			str = "Host Busy";
			break;

		// Host was not set
		case HOST_INVALID:
			str = "Host Not Set";
			break;	
			
		// Requested transaction not supported
		case HOST_UNSUPPORTED_TRANSACTION:
			str = "Unsupported Transaction";
			break;	
	
		// Journal error, critical
		case HOST_JOURNAL_FAIL:
			str = "Batch Write Error";
			break;

		// Host canceled by user
		case HOST_CANCELED:
			str = "Canceled by User";
			break;

		// Bad response
		case HOST_FAIL:
			str = "Bad response from host";
			break;

		// Bad response
		case HOST_RESPONSE_CONTINUE:
			str = "Should process another response from host";
			break;

		default:
			sprintf( buff, "%2d", Result );
			str = "Unknown Host Error ";
			str+=buff;	
			break;
	}
	UI->Beep(UI->LONG_BEEP);
}

