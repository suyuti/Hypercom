//=============================================================================
// Company:
//      Hypercom Inc
//
// Product:
//      Hyperware Base Application
//      (c) Copyright 2003
//
// File Name:
//      StepGetPAN.cpp
//
// File Contents:
//      Implementation of StepGetPAN
//
//=============================================================================
#include <compiler.h>
#include <HypCTransaction.hpp>
#include <HypCMsgBox.hpp>
#include <HypCInfoBox.hpp>
#include <HypCInputBox.hpp>
#include <HypCPAN.hpp>
#include "../HyperwareTags.h"
#include <HypCFinancialDecoder.hpp>

#include "../HyperwareMain.hpp"
#include "StepGetPAN_EMV.hpp"
#include "GrafixKeyCodes.h"
#include "ico_card.h"
#include <HypCMultiLang.hpp>
#include "../PromptsDef.h"

#define ONE_SECOND  1000    // milliseconds


//-----------------------------------------------------------------------------
// Name:
//      StepGetPAN::PreCondition
//
// Description
//      Pre condition processing
//
// Parameters:
//      None
//
// Returns:
//      true if successful, else false
//
// Notes:
//
bool StepGetPAN::PreCondition()
{
	// check if we have a valid PAN already
	const HypCData* dptr = Transaction().TransactionData().get( TransactionTag::PAN );

	if( dptr )
	{
		if( dptr->IsValid() && dptr->AsString().length() > 1 )
		{
			// already have PAN, so skip this step
			SetExecAction( STEP_NEXT );
			return false;
		}
	}

	return true;
}

//-----------------------------------------------------------------------------
// Name:
//      StepGetPAN::doExecute
//
// Description
//      Execution of step. Check if PAN data available. If PAN partially
//      complete, inputs the remaining PAN manually.  Otherwise
//      ask user to swipe card.
//
// Parameters:
//      None
//
// Returns:
//      None
//
// Notes:
//
bool StepGetPAN::doExecute()
{
	const unsigned int T_30_SECONDS = 30 * ONE_SECOND;
	HString retData;	
	
	HypCUserInterface *UI = Transaction().GetUserInterface();
	
	HypCTransactionData &TransData = Transaction().TransactionData();

	HypCInfoBox *info = UI->InfoBox();

	HypCMultiLang* prompt = Transaction().GetMultiLang();

	// Doing this, we get rid of old user interface elements.
	UI->CancelRequests();

	HypCData* dptr = (HypCData* )TransData.get( TransactionTag::PAN );

	SetExecAction( TRANS_ABORT );

	// do we have a partial PAN already
	if( dptr )
	{
		if( dptr->AsString().length() > 0 )
		{
			// continue with PAN entry
			retData = dptr->AsString();

			if( 0 == UI->StandardInputForm( INPUT_TYPE_NUM,
	                           Transaction().GetTitle().c_str(),
	                           prompt->GetPrompt( Prompts::ENT_CARD_NUM ),
	                           retData, 16, 5 ) )
			{							
			

							// update the current data
							dptr->AsString( retData ); 
			}
			else
			{
				// exit?
				return false;
			}

			// check PAN validity
			if(  !dptr->IsValid() )
			{
				// report invalid PAN
		
				UI->StandardMessageBox( Transaction().GetTitle().c_str(),
				      prompt->GetPrompt( Prompts::INV_ENTRY ),								
				      BUTTON_OK );

								
				// bad entry, so quit transaction
			}
			else
			{
				// manually entered PAN okay
				// set the POS entry mode to indicate manual
				TransData.insert( TransactionTag::POS_ENTRY_MODE, "012");
				// go to next step
				SetExecAction( STEP_NEXT );
			}
			return true;
		}

	}
	// Ask to swipe card or get PAN
	HypCPAN pan;
	HypCEvent event;
	HypCEventInfo eventInfo;
	int result;

	HypCFinancialDecoder *pCardDecoder = NULL;
	HyperwareMain* pApp = reinterpret_cast<HyperwareMain*>(Transaction().GetApplication() );

#if (defined(USING_AAE) && defined(AAE_SCR))
	// add processing for smart card reader using arbitrator
#else
	HypCInternalSCReader *pSCCardReader =
			new HypCInternalSCReader( DEVICE_ID_SMART_CARD_READER );
	if ( !pSCCardReader )
	{
		return false;
	}
#endif

	pSCCardReader->Request( event, HypCSmartCardReader::READ_CARD );

	HypInfoParam inf;
	inf.Message = prompt->GetPrompt( Prompts::SWIPE_CARD );
	inf.Title = Transaction().GetTitle();

	inf.Sprite1.Image = reinterpret_cast<ICON*>(&ico_card);
	inf.Sprite1.Step = 1;
	inf.Sprite1.Delay = 7;
	inf.Sprite1.Direction = SPRITE_MOVE_DOWN;
	

	inf.Sprite1.Xmin = 160 - inf.Sprite1.Image->imWidth - 8;
	inf.Sprite1.Ymin = 26;

	inf.Sprite1.Xmax = inf.Sprite1.Xmin + inf.Sprite1.Image->imWidth + 1;
	inf.Sprite1.Ymax = 80 - 4;

	// set up termination keys; first parameter is code returned on close
	// second - key scancode.
	// Simply make all digits in the keypad terminating keys, returning
	// its own value
	for ( char key = '0'; key <= '9'; ++key)
	{
		info->SetTermKey( key, key );
	}

	info->Show( event, inf );
	//m_UserInterface->Request( event, HypCUserInterface::INFOBOX_INPUT );

	// wait for card or key press for 30 seconds.
	if ( !event.Wait ( eventInfo, T_30_SECONDS ) )
	{
		// time out waiting for the card, cancel the transaction
		SetExecAction( TRANS_ABORT );
		info->Cancel();
		delete pSCCardReader;
		return false;
	}

	HypInfoParam dscc;

	switch( eventInfo.GetDevice()->GetID() )
	{
		case DEVICE_ID_USER_INTERFACE:
			pSCCardReader->CancelRequests();
			result = info->AsyncResult();

			// either PAN started or ESC or CLEAR was pressed
			if( ( result >= '0' ) && 
				( result <= '9' ) )
			{
				char buf[2];
				buf[0] = static_cast<char>( result );
				buf[1] = '\0';

				// save partial PAN data
				pan.AsString( buf );

				TransData.insert( TransactionTag::PAN, pan );

				// repeat this step to get pan manually
				SetExecAction( STEP_REPEAT );
				break;
			}
			else
			{
				SetExecAction( TRANS_ABORT );
			}
			break;

		case DEVICE_ID_SMART_CARD_READER:
			// got read from card
			UI->CancelRequests();
			pCardReader->CancelRequests();

			// don't process at the moment
			SetExecAction( TRANS_ABORT );

			break;

		default:
			HypInfoParam dsc;
			dsc.Message = prompt->GetPrompt( Prompts::UNC_DEV_ID );
			Transaction(  ).GetUserInterface(  )->InfoBox(  )->Show( dsc );

			SetExecAction( TRANS_ABORT );

	} // end switch

	delete pSCCardReader;
	return true;

}

