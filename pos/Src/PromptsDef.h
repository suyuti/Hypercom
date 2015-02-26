//=============================================================================
// Company:
//      Hypercom Inc
//
// Product:
//      Hyperware Base Application
//      (c) Copyright 2006
//
// File Name:
//      PromptsDef.h
//
// File Contents:
//      Declaration of the constants used by Hyperware for its Multi-Language
// 		classes.
//
//=============================================================================
#if !defined(_PROMPTSDEF_H_)
#define _PROMPTSDEF_H_

//=============================================================================
// Public defines and typedefs
//=============================================================================

// Pointers to prompt text found in the xml file.
namespace Prompts
{
	const char*  UNC_MSG;
	const char*  NO_ACC_JRN;
	const char*  NO_ACC_AMT;
	const char*  NO_DYN_MEMORY;
	const char*  TOT_CS_CORRECT;
	const char*  JRN_NO_CARD_ACC;
	const char*  JRN_NO_STAT_FLAGS;
	const char*  JRN_NO_TYPE;
	const char*  TRANS_NO_CARD_ACC;
	const char*  NO_ACC_CONF;
	const char*  SALES_TOT_CS_CORRECT;
	const char*  REFUNDS_TOT_CS_CORRECT;
	const char*  ENTER_SALES_TOTAL;
	const char*  WRONG_SALES_TOTAL;
	const char*  ENTER_REFUNDS_TOTAL;
	const char*  WRONG_REFUNDS_TOTAL;
	const char*  NO_ACC_INVOICE;
	const char*  NO_ACC_STATUS;
	const char*  NO_ACC_TYPE;
	const char*  NO_ACC_PAN;
	const char*  NO_ACC_DATE_TIME;
	const char*  NO_ACC_ISS;
	const char*  PROC_SETTLE;
	const char*  ENTER_AMOUNT;
	const char*  EXP_DATE;
	const char*  INV_ENTRY;
	const char*  ENT_INVOICE;
	const char*  DUP_ENTRY;
	const char*  INV_ENTRY_RE;
	const char*  ENT_CARD_NUM;
	const char*  UNC_DEV_ID;
	const char*  ENT_PASS;
	const char*  NO_TERM_PASS;
	const char*  NO_ACC_HINT;
	const char*  ENTER_HOST;
	const char*  NO_ACC_MENU;
	const char*  NO_HOST_DEF;
	const char*  HOST_NOT_FOUND;
	const char*  ISS_NOT_FOUND;
	const char*  ERROR;
	const char*  RESP_NOT_FOUND;
	const char*  TRANS_RESULT;
	const char*  TRANS_DOESNT_EXIST;
	const char*  BATCH_EMPTY;
	const char*  VOID_COMPLETED;
	const char*  SYSTEM_VERSION;
	const char*  PAPER_OUT;
	const char*  ADJ_VOID_TRANS;
	const char*  HOSTS_FAILED_SETTLE;
	const char*  PROCESSING_TRANS;
	const char*  ENT_PIN;
	const char*  HOST_CREATE;
	const char*  START_TRANS;
	const char*  PRE_PROC;
	const char*  ENC_REQ;
	const char*  SEND_REQ;
	const char*  CONNECT;
    const char*  CONNECT_GPRS;
    const char*  CONNECT_FAILED;
	const char*  NO_DIAL_TONE;
	const char*  WAIT_LINE;
	const char*  PROCESS;
	const char*  WAIT_RESP;
	const char*  PROC_RESP;
	const char*  DEC_RESP;
	const char*  POST_PROC;
	const char*  SAV_JOURN;
	const char*  TRANS_COMPL;
	const char*  TRANS_FAILED;
	const char*  SETTLE_PROC;
	const char*  UN_HOST_STATE;     
	const char*  SWIPE_CARD;
    const char*  SWIPE_OR_TAP_CARD;
	const char*  READ_PIN;
	const char*  INVOICE_NOT_FOUND;
	const char*  DECLINED;
	const char*  CARD_DECLINE;
	const char*  OVERRIDE_Q;
	const char*  NO_TERM_DATA;
	const char*  APP_SELECT;
	const char*  BAD_APP_SELECT;
	const char*  SELECTING;
	const char*  LAST_TRY;
	const char*  TRIES_LEFT;
	const char*  PIN_TRIES_EX;
	const char*  CARD_FAIL;
	const char*  PIN_BLOCKED;
	const char*  EMV_CANT_AUTH;
	const char*  CONFIRM;
	const char*  FORCE_ONLINE;
	const char*  VALID_FAILED;
	const char*  EMV_CANT_WRITE_AMOUNT;
	const char*  EMV_CANT_WRITE_FLOOR;
	const char*  EMV_CANT_WRITE_INV;
}   

// Language names. Codes and representation comes from ISO 639.2
namespace Languages
{
	const char* ENG;
	const char* RUS;
	const char* SPA;
	const char* LAT;
}

// Additionally set for each language

// Font's target
namespace FontTarget
{
	const char* H_PROMPT;
	const char* H_TITLE;
	const char* H_EDIT_BOX;
}

// Font's style
namespace FontStyle
{
	const char* H_NORMAL;
	const char* H_BOLD;
	const char* H_ITALIC;
	const char* H_BOLD_ITALIC;
}

#endif // #if !defined( _PROMPTSDEF_H_ )

