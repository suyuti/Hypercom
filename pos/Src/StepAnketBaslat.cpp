#include "StepAnketBaslat.hpp"
#include <HypCTransaction.hpp>
#include <HypCApplication.hpp>
#include <HypCUserInterface.hpp>
#include "TransactionTags.h"

#include <compiler.h>
#include <HypCTransaction.hpp>
#include <HypCMsgBox.hpp>
#include <HypCInfoBox.hpp>
#include <HypCInputBox.hpp>
#include <HypCPAN.hpp>
#include "YemekSepetiTags.h"
#include <HypCFinancialDecoder.hpp>
#include <HypCMSRArbReader.hpp>

#include "YemekSepetiMain.hpp"
#include "GrafixKeyCodes.h"
#include "ico_card.h"
#include "CardSwipe.h"
//#include <HypCMultiLang.hpp>
#include "PromptsDef.h"

#define ONE_SECOND  1000    // milliseconds

using namespace HFC::Internal::DAL::Forms;

/*bool CStepAnketBaslat::doExecute()
{
    HypCUserInterface *ui = Transaction().GetUserInterface();
    HypCApplication* app = Transaction().GetApplication();
    ui->CancelRequests();

    HString _isim;
    if (0 == ui->StandardInputForm(INPUT_TYPE_ALPHA , "isim giriniz...", "iSiM", _isim,25,1,30))
    {
        ui->StandardMessageBox("Mesaj", _isim.c_str());
    }
        HypCMSRArbReader *pCardReader =
			new HypCMSRArbReader ( DEVICE_ID_CARD_READER, 
								  const_cast<CHAR*>(Transaction().GetTitle().c_str()), 
								  pApp->GetMainWindow()->GetWndHandle() );
    return true;
}
*/

bool CStepAnketBaslat::doExecute()
{
	const unsigned int T_30_SECONDS = 30 * ONE_SECOND;
	HString retData;	
	
	HypCUserInterface *UI = Transaction().GetUserInterface();

	HypCApplication* app = Transaction().GetApplication();
	
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
#if !defined (PLATFORM_M4100)
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
#else
			UI->InputBox()->SetPromtColor( clBlack );
            UI->InputBox()->SetTextLocation( InputBox::EditX, InputBox::EditY + 69,
											 InputBox::EditW, InputBox::EditH );
			UI->InputBox()->SetMsgLocation( InputBox::MsgX, InputBox::MsgY + 69,
											InputBox::MsgW, InputBox::MsgH );

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
#endif
			// check PAN validity
			if(  !dptr->IsValid() )
			{
				// report invalid PAN
#ifdef PLATFORM_M4100
				UI->MsgBox()->SetButtonTextColor( clBlack );
				UI->MsgBox()->SetMessageColor( clBlack );
				UI->MsgBox()->SetMsgY( WIN_H/2 - 23 );
                UI->MsgBox()->SetMsgH( 80 );
				HString msg("-\n");
				msg += prompt->GetPrompt( Prompts::INV_ENTRY );
				UI->StandardMessageBox( Transaction().GetTitle().c_str(),
										msg.c_str(),								
										BUTTON_OK );
#else
				UI->StandardMessageBox( Transaction().GetTitle().c_str(),
										prompt->GetPrompt( Prompts::INV_ENTRY ),								
										BUTTON_OK );
#endif								
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

	bool use_rfid = false;

#ifdef PLATFORM_M4100
    HypCPOSConfig *pCfg = &Transaction().POSConfig();
    HYP_CFG_HANDLE termRecord = pCfg->GetTable( TermConfigTag::TERMINAL_TABLE );
    use_rfid = pCfg->IsOptionSet( termRecord, TCL_USE_RFID );
#endif

    HypCMSRArbReader *pCardReader =
			new HypCMSRArbReader ( DEVICE_ID_CARD_READER, 
								  const_cast<CHAR*>(Transaction().GetTitle().c_str()), 
								  pApp->GetMainWindow()->GetWndHandle() );
	if ( pCardReader && pCardReader->IsArbitratorSessionOK() )
	{

        if ( use_rfid )
        {
            pCardReader->SetDevicesToRead( AAE_MSR_DATA | AAE_RFID_DATA );
        }
        else
        {
            pCardReader->SetDevicesToRead( AAE_MSR_DATA );
        }
        // Register to get all possible cards.
		HANDLE nRangeHandle;
        pCardReader->AddCardRange ( "10", "99", 2, &nRangeHandle );
	} else
	{
		return false;
	}

	// Issue read request for card reader
	pCardReader->Request( event, HypCMSRReader::READ_CARD );

	HypInfoParam inf;
	inf.Message = "";
	inf.Title = Transaction().GetTitle();

#ifndef PLATFORM_M4100
	inf.Sprite1.Step = 1;
	inf.Sprite1.Delay = 7;
	inf.Sprite1.Direction = SPRITE_MOVE_DOWN;

	inf.Sprite1.Image = reinterpret_cast<ICON*>(&ico_card);
	inf.Sprite1.Xmin = 160 - inf.Sprite1.Image->imWidth - 8;
	inf.Sprite1.Ymin = 26;

	inf.Sprite1.Xmax = inf.Sprite1.Xmin + inf.Sprite1.Image->imWidth + 1;
	inf.Sprite1.Ymax = 80 - 4;
#else
	UI->InfoBox()->SetTextColor( clBlack );
	UI->InfoBox()->SetMsgY( WIN_H/2 - 23 );
#endif

    if( use_rfid )
    {
        inf.Message += prompt->GetPrompt( Prompts::SWIPE_OR_TAP_CARD );
    }
    else
    {
        inf.Message += prompt->GetPrompt( Prompts::SWIPE_CARD );
    }
	info->Show( event, inf );

    // set up termination keys; first parameter is code returned on close
	// second - key scancode.
	// Simply make all digits in the keypad terminating keys, returning
	// its own value
	for ( char key = '0'; key <= '9'; ++key)
	{
		info->SetTermKey( key, key );
	}

	// wait for card or key press for 30 seconds.
	if ( !event.Wait ( eventInfo, T_30_SECONDS ) )
	{
		// time out waiting for the card, cancel the transaction
		SetExecAction( TRANS_ABORT );
		info->Cancel();
		delete pCardReader;
		return false;
	}

//	HypInfoParam dscc;
    HString track1;
    HString name;

	switch( eventInfo.GetDevice()->GetID() )
	{
		case DEVICE_ID_USER_INTERFACE:
    		pCardReader->CancelRequests();
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

		case DEVICE_ID_CARD_READER:
			// got read from card
			UI->CancelRequests();

			// Create decoder for card
			pCardDecoder = new HypCFinancialDecoder( *pCardReader );

			// Parse the data
			pCardDecoder->Read();

			if ( !pCardDecoder->GetStatus( TRACK2, HypCMSRDecoder::ISO_DATA ) )
			{
				// There's no data available in the reader, 
				// just abort the transaction
				UI->Beep(UI->CRITICAL_ERROR);
				SetExecAction( TRANS_ABORT );
				break;
			}
			UI->Beep();

			// save all card data to transaction record

			// save pan
			pan.AsString( pCardDecoder->GetPAN());
			TransData.insert( TransactionTag::PAN, pan );

			// save expiration date
			TransData.insert( TransactionTag::EXPIRATION_DATE,
				pCardDecoder->GetExpDate() );

			// save track 1 data
			TransData.insert( TransactionTag::TRACK1,
				pCardDecoder->GetTrack( TRACK1 ));

            track1 = pCardDecoder->GetTrack( TRACK1 );
            name = track1.substr(track1.find_first_of("^") + 1, 26);
            TransData.insert(TransactionTag::ISIM, name.c_str());

			// save track 2 data
			TransData.insert( TransactionTag::TRACK2,
				pCardDecoder->GetTrack( TRACK2 ));

			delete pCardDecoder;
			SetExecAction( STEP_NEXT );
			break;

		default:
			HypInfoParam dsc;
			dsc.Message = prompt->GetPrompt( Prompts::UNC_DEV_ID );
#ifdef PLATFORM_M4100	
			UI->InfoBox()->SetTextColor( clBlack ); 
#endif
			UI->InfoBox(  )->Show( event, dsc );
			if( !event.Wait( eventInfo, 2000 ) )
			{
				// we timed out
				UI->InfoBox()->Cancel();
			}		

			SetExecAction( TRANS_ABORT );

	} // end switch

	delete pCardReader;
	return true;

}


