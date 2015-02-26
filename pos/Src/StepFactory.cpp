//=============================================================================
// Company:
//      Hypercom Inc
//
// Product:
//      Hyperware Base Application
//      (c) Copyright 2006
//
// File Name:
//      StepFactory.cpp
//
// File Contents:
//      Implementation of StepFactory
//
//=============================================================================
#include <compiler.h>
#include "YemekSepetiTags.h"
#include "StepFactory.hpp"
#include "StepAnketBaslat.hpp"
#include "StepAnketSec.hpp"
#include "StepSoruSor.hpp"
#include "StepModemTest.hpp"
#include "StepSiparisListeGoster.hpp"
//-----------------------------------------------------------------------------
// Initialize step names
//-----------------------------------------------------------------------------

// Step to print last report
//const char* StepNameTag::STEP_LAST_REPORT		="LASTREP";
const char* StepNameTag::STEP_SIPARIS_LISTE_GOSTER = "SIPLISTEGOSTER";
const char* StepNameTag::STEP_ANKET_BASLAT  = "ANKET_BASLAT";
const char* StepNameTag::STEP_ANKET_SEC     = "ANKET_SEC";
const char* StepNameTag::STEP_SORULAR       = "SORULAR";
const char* StepNameTag::STEP_ANKET_SONUC   = "ANKET_SONUC";
const char* StepNameTag::STEP_MODEM_TEST    = "MODEMTEST";


//-----------------------------------------------------------------------------
//!
//!      StepFactory constructor. Initializes pointer to step table and
//!      table entry count
//!
//! \return
//!      Nothing
//!
//! \note
//!
StepFactory::StepFactory( HypCTransaction *pTransaction ) :
	HypCTransactionStepFactory(  )
{
	//=============================================================================
	// Transaction step names
	//=============================================================================
	SetTransaction( pTransaction );
}


//-----------------------------------------------------------------------------
//!
//!      Creates a transaction step based on the step name.
//!
//! \param
//!      sStepName       Name of the step to be created
//!
//! \return
//!      pointer to the newly created Step object
//!
//! \note
//!
HypCTransactionStep *StepFactory::DoCreateStep( const char* sStepName )			
{
	HString StepName = sStepName;

    if (StepName == StepNameTag::STEP_ANKET_BASLAT)
    {
        return new CStepAnketBaslat();
    }
    else if (StepName == StepNameTag::STEP_ANKET_SEC)
    {
        return new CStepAnketSec();
    }
    else if (StepName == StepNameTag::STEP_ANKET_SONUC)
    {
    }
    else if (StepName == StepNameTag::STEP_SORULAR)
    {
        return new CStepSoruSor();
    }
	if( StepName == StepNameTag::STEP_MODEM_TEST )
	{
		return new CStepModemTest();
	}
	if( StepName == StepNameTag::STEP_SIPARIS_LISTE_GOSTER )
	{
		return new CStepSiparisListeGoster();
	}
/*	if( StepName == StepNameTag::STEP_EMV_COMPL_TRANS )
	{
		return new StepEMVCompleteTransaction( );
	}
    */
	return 0;
}
