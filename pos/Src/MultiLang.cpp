//=============================================================================
// Company:
//      Hypercom Inc
//
// Product:
//      Hypercom Foundation Classes
//      (c) Copyright 2006
//
// File Name:
//      MultiLang.cpp
//
// File Contents:
//      Initialization of prompts used by Hyperware
//
//=============================================================================
#if defined(__GNUC__)  // GNU compiler
#pragma implementation
#endif

#include "MultiLang.hpp"

//=============================================================================
//
//=============================================================================
void MultiLang::InitConstants()
{
	using namespace Prompts;
	
	UNC_MSG				=	"Unknown message";
	NO_ACC_JRN			=	"No access to journal";
	NO_ACC_AMT			=	"No access to amount";
	NO_DYN_MEMORY		=	"No dynamic memory";
	TOT_CS_CORRECT		=	"Total %c%s correct?";
	JRN_NO_CARD_ACC 	=	"Journal: no access to card acceptor";
	JRN_NO_STAT_FLAGS 	= 	"Journal: no access to status flags";
	JRN_NO_TYPE 		= 	"Journal: no access to type";
	TRANS_NO_CARD_ACC	=	"Transaction: no card acceptor";
	NO_ACC_CONF			=	"No access to configuration";
	SALES_TOT_CS_CORRECT=	"Sales total %c%s correct?";
	REFUNDS_TOT_CS_CORRECT ="Refunds total %c%s correct?";
	ENTER_SALES_TOTAL	= 	"Enter sales total:";
	WRONG_SALES_TOTAL	= 	"Wrong sales total";
	ENTER_REFUNDS_TOTAL	=	"Enter refunds total:";
	WRONG_REFUNDS_TOTAL	=	"Wrong refunds total";
	NO_ACC_INVOICE		=	"Transaction: no access to invoice";
	NO_ACC_STATUS		=	"No access to status flags";
	NO_ACC_TYPE			=	"No access to type";
	NO_ACC_PAN			=	"Transaction: no access to PAN";
	NO_ACC_DATE_TIME	=	"Transaction: no access to date/time";
	NO_ACC_ISS			=	"Journal: no access to issuer";
	PROC_SETTLE			=	"Processing settlement";
	ENTER_AMOUNT		=	"Enter amount:";
	EXP_DATE			=	"Expiration Date MMYY";
	INV_ENTRY			=	"Invalid entry";
	ENT_INVOICE			=	"Enter invoice:";
	DUP_ENTRY 			=	"Duplicate Entry, Please Re-Enter";
	INV_ENTRY_RE		=	"Invalid Entry, Please Re-Enter";
	ENT_CARD_NUM		=	"Enter Card Number:";
	UNC_DEV_ID			=	"Unknown device ID";
	ENT_PASS			=	"Enter password:";
	NO_TERM_PASS		=	"No access to terminal\'s password";
	NO_ACC_HINT			=	"No access to host interface";
	ENTER_HOST			=	"Enter host number (0-all):";
	NO_ACC_MENU			=	"No access to menu";
	NO_HOST_DEF			=	"No hosts defined";
	HOST_NOT_FOUND		=	"HOST NOT FOUND";
	ISS_NOT_FOUND		= 	"ISSUER NOT FOUND";
	ERROR				=	"ERROR";
	RESP_NOT_FOUND		=	"Host Response Text Not Found";
	TRANS_RESULT		=	"Transaction result";
	TRANS_DOESNT_EXIST 	= 	"TRANSACTION DOES NOT EXIST!";
	BATCH_EMPTY 		=	"BATCH EMPTY";
	VOID_COMPLETED 		=	"VOID COMPLETED";
	SYSTEM_VERSION 		=	"SYSTEM VERSION";
	PAPER_OUT 			=	"Sorry, paper out";
	ADJ_VOID_TRANS 		=	"Can\'t adjust voided transaction";
	HOSTS_FAILED_SETTLE =	"Some hosts failed to settle";
	PROCESSING_TRANS 	=	"Processing Trans.";
	ENT_PIN				=	"Enter PIN";
	HOST_CREATE			=	"Host Creation";
	START_TRANS			=	"Start Transaction";
	PRE_PROC	 	   	=	"PreProcessing";
	ENC_REQ	 	   		=	"Encode Request";
	SEND_REQ	 	   	=	"Sending Request";
	CONNECT	 	   		=	"Connecting";
    CONNECT_GPRS        =   "Connecting GPRS";
    CONNECT_FAILED      =   "Connection Failed";
	NO_DIAL_TONE 	   	=	"No Dial Tone";
	WAIT_LINE 	   		=	"Waiting For Line";
	PROCESS 	 	  	=	"Processing";
	WAIT_RESP	 	  	=   "WaitingForResponse";
	PROC_RESP	 	  	=   "Processing Response";
	DEC_RESP	 	  	=   "Decoding Response";
	POST_PROC  	  		=   "Post Processing";
	SAV_JOURN  	  		=   "Saving to Journal";
	TRANS_COMPL  	  	=   "Transaction Complete";
	TRANS_FAILED 	  	=   "Transaction Failed";
	SETTLE_PROC 	  	=   "Settlement Processing";
	UN_HOST_STATE   	=   "Unknown Host State";
	SWIPE_CARD  	 	=	"Swipe the card or enter card number";
    SWIPE_OR_TAP_CARD  	=	"Provide card or enter card number";
	READ_PIN			=	"Reading PIN";
	INVOICE_NOT_FOUND	=	"Inv. Number Missing";
	DECLINED  			= 	"Declined";
	CARD_DECLINE		=	"Card decline";
	OVERRIDE_Q			=	"Override?";
	NO_TERM_DATA		=   "Can\'t write terminal data to the EMV library";
	APP_SELECT			=   "App selection";
	BAD_APP_SELECT		=   "Bad application selection";
	SELECTING			=   "Selecting";
	LAST_TRY			=	"Last try left";
	TRIES_LEFT			=   "Tries left: ";
	PIN_TRIES_EX		= 	"PIN tries exceeded";
	CARD_FAIL			= 	"Card failure";
	PIN_BLOCKED			=   "PIN blocked";
	EMV_CANT_AUTH		=   "Can\'t authenticate";
	CONFIRM				=   "Confirm";
	FORCE_ONLINE		= 	"Force online?";
	VALID_FAILED		=   "Validation failed";
	EMV_CANT_WRITE_AMOUNT = "Can\'t write amount to EMV";
	EMV_CANT_WRITE_FLOOR =  "Can\'t write floor amount to EMV";
	EMV_CANT_WRITE_INV 	=  "Can\'t write invoice number to EMV";
	// Language names. Codes and representation comes from ISO 639.2
	Languages::ENG = "English";
	Languages::RUS = "Russian";
	Languages::LAT = "Latvian";
	Languages::SPA = "Spanish";
	
	
	// Additionally set for each language
	
	// Font's target
	FontTarget::H_PROMPT 	= "Prompts";
	FontTarget::H_TITLE 	= "Title";
	FontTarget::H_EDIT_BOX 	= "Edit box";
	
	
	// Font's style
	FontStyle::H_NORMAL 	 = "Normal";
	FontStyle::H_BOLD 		 = "Bold";
	FontStyle::H_ITALIC 	 = "Italic";
	FontStyle::H_BOLD_ITALIC = "Bold italic";

}
