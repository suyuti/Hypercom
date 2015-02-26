//=============================================================================
//                       Hypercom Inc
//                      (c) Copyright 2006
//=============================================================================
//
// Module overview:
//	    DDLMain.cpp
//
//  This is the starting module for the Hyperware sample application
//  As usual, execution starts at main() which in turn calls Hyperware_App
//  The main application object is instantiated and starts execution.
//
//=============================================================================
#if !defined(DDL_MODULE)
#define DDL_MODULE
#endif

#define _INCLUDE_NUCLEUS_FILE_
#include <HycDDL.h>
#include <HypCFile.hpp>

#include <errno.h>
#include <hycddl.h>
#include <HypCFileSystem.hpp>
#include <HypCCodePage.hpp>
#include <HypTrace.h>
//#include <HypCDebugHeap.hpp>
#include "YemekSepetiMain.hpp"

//=============================================================================
// External references
//=============================================================================


//=============================================================================
// Private defines and typedefs
//=============================================================================

extern "C"
{

// Application Version 
#define _HYPERWARE_VERSION_	"1.4"

//=============================================================================
// Public data definitions
//=============================================================================
const unsigned int _STACKSIZE = APPLICATION_STACK_SIZE;
char _APPNAME[8] = "HypWare";

const unsigned int _DYNAMIC_MEMORY_SIZE = DYNAMIC_MEMORY_SIZE;
char DynamicMemoryPool[DYNAMIC_MEMORY_SIZE];

char ApplicationStack[APPLICATION_STACK_SIZE];

// Logging library support
DECLARE_DBG_LOGGER;


//=============================================================================
// Private data definitions
//=============================================================================


//=============================================================================
// Private function definitions
//=============================================================================
static int Hyperware_App( int argc, char * * argv );
//void alloc_break() { ; }

//-----------------------------------------------------------------------------
//!  main
//!
//!		argc, argv  Just placeholders now
//!
//!  Global Inputs:
//!
//! \return
//!		A return code to the OS
//!
//! \note
//!
int main( int argc, char * * argv )
{
    HYPTRACE_INIT_FROM_FILE( _APPNAME );
	//HypCDebugHeap::TopInstance()->SetBreakAtAlloc( 7512, alloc_break );

	STATUS status = NU_SUCCESS;
	{
		HypCFileSystem Disks;

		const char FlashFileSystem = 'C';
		const char SRAMFileSystem = 'D';

		status = Disks.Initialize( SRAMFileSystem );
		if ( NU_SUCCESS != status )
			return status;

		// The Flash File System will remain the default drive.
		// This is expected by some modules, like printing scripts.
		status = Disks.Initialize( FlashFileSystem );
		if ( NU_SUCCESS != status )
			return status;

		NU_Become_File_User();
		// Run the main application
		status = Hyperware_App( argc, argv );
	}

	HYPTRACE_CLOSE();
	return status;
}


/**
 * These functions belong to newlib. They are here only as a temporary solution
 * while newlib itself is modified.
 */

//-----------------------------------------------------------------------------
//!  _sbrk
//!
//!		incr   How much to decrease the heap size
//!
//!  Global Inputs:
//!		heap_end
//!
//! \return
//!
//! \note
//!
#if defined(PLATFORM_T4100)

static char * heap_end = 0;

caddr_t
_sbrk (int incr)
{
	extern char   end asm ("end");	// Defined by the linker.
	extern char   heapend asm ("heapend");
	char *        prev_heap_end;

	if (heap_end == NU_NULL)
	{
		heap_end = &end;
	}

	prev_heap_end = heap_end;

	if (heap_end + incr > &heapend)
	{
		errno = ENOMEM;   // we just run out of heap space
		return (caddr_t) -1;
	}
	heap_end += incr;

	return (caddr_t) prev_heap_end;
}

#if defined(_DEBUG)
extern int _FreeHeap_Report(void)
{
    extern char   heapend asm ("heapend");
    return (&heapend - heap_end);
}
#endif

void
_exit (int n)
{
    n = n;
    HYC_Unload_Itself( );
    // Keep the compiler happy, this function is NOT supposed to exit
    do {} while ( true );
}

// Should be re-defined from the standard implementation in newlib.
void
abort (void)
{
	DBGPRINTF ( VLVL_QUIET, CLASS_HYPERWARE, "%s", __FUNCTION__ );
	HYC_Unload_Itself( );
    // Keep the compiler happy, this function is NOT supposed to exit
    do {} while ( true );
}
#endif

}	// extern "C"


//-----------------------------------------------------------------------------
//!  Hyperware_App
//!
//!      This function starts the execution
//!
//!		argc, argv  Just placeholders now
//!
//!  Global Inputs:
//!
//! \return
//!		A return code to the OS
//!
//! \note
//!
int Hyperware_App( int argc, char ** argv )
{
	STATUS status = argc + reinterpret_cast < STATUS > ( argv );

    // If you want ASCII support for a language other than English, you have to have a codepage
    // for that language in .cp format. The format is very simple - a file contains 256 UTF-8 encoded symbols
    // that form the ASCII table (i.e. the first UTF-8 symbol in the .cp file will be the first
    // in the resulting ASCII table and so on).
    // NB: .cp file should contain exactly 256 symbols to be valid.
    // Below is the usage sample, uncomment it to get ASCII support for Russian language.
    // There is another condition: HyperwareMain constructor should be supplied with the correct
    // language string to be able to load an appropriate display font.

    //HypCFile src("C:\\windows-1251.cp");
    //HypCStatus res = HypCCodePage::Instance().Add( src );
    //src.Close();

	HyperwareMain MainApplication( "Hyperware", _HYPERWARE_VERSION_, 1, "English" );
	status = MainApplication.Execute();

	return status;
}

