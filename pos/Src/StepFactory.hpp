//=============================================================================
// Company:
//      Hypercom Inc
//
// Product:
//      Hyperware Base Application
//      (c) Copyright 2006
//
// File Name:
//      StepFactory.hpp
//
// File Description:
//      StepFactory declaration
//
//=============================================================================
#if !defined( _STEPFACTORY_HPP_ )
#define _STEPFACTORY_HPP_

#include <compiler.h>
#include <HypCTransactionStepFactory.hpp>

//=============================================================================
// Public defines and typedefs
//=============================================================================

//! Contains pointers to names of steps
struct StepNameTag
{
public:
	//! Select debit or credit
    static const char* STEP_SIPARIS_LISTE_GOSTER;
    static const char* STEP_ANKET_BASLAT;
    static const char* STEP_ANKET_SEC;
    static const char* STEP_SORULAR;
    static const char* STEP_ANKET_SONUC;

    static const char* STEP_MODEM_TEST;
};


//=============================================================================
//! \brief
//!      Creates transaction steps.
//!
//!      This class provides a factory that creates transaction steps based
//!      on a given name. The steps are added on application startup by calling
//!      CreateAssociations().
//!
//!      Use base class member CreateStep( const string& sStepName ) to create 
//!      a step 
//!
//! \sa
//!      HypCTransactionStepFactory
//!
//=============================================================================
class StepFactory : public HypCTransactionStepFactory
{
	public:

		//! Constructor
		StepFactory( HypCTransaction *pTransaction );
		
		//! Destructor
		virtual ~StepFactory( ) {};

		
//=============================================================================
// Member variables
//=============================================================================
	protected:	
		
		//! Create an instance of specified step		
		HypCTransactionStep *DoCreateStep( const char *sStepName );
};
// StepFactory

#endif // #if !defined( _STEPFACTORY_HPP )

