//=============================================================================
// Company:
//      Hypercom Inc
//
// Product:
//      Hypercom Foundation Classes
//      (c) Copyright 2006
//
// File Name:
//      MultiLang.hpp
//
// File Contents:
//      MultiLang class declaration
//
//=============================================================================
#if !defined( _MULTILANG_HPP_ )
#define _MULTILANG_HPP_

#if defined(__GNUC__)
#pragma interface
#endif

#include <compiler.h>
#include <HypCMultiLang.hpp>
#include "PromptsDef.h"

//=============================================================================
// Public defines and typedefs
//=============================================================================

//=============================================================================
// Forward definitions
//=============================================================================


//=============================================================================
//!
//! \brief
//!      Contains application spefic messages.
//!
//!      The language class with application specific messages
//!
//! \sa
//!      HypCMultiLang
//!
//=============================================================================
class MultiLang : public HypCMultiLang
{
//=============================================================================
// Member functions
//=============================================================================
	public:
		//! creates an object with a specified language
		MultiLang( const char* filename, 
				   const char* strDefaultLang ):
			HypCMultiLang( filename, strDefaultLang )
		{
			InitConstants();
		}

		//! creates an object language by default
		~MultiLang()
		{
		}

	protected:

	private:

		void InitConstants();
//=============================================================================
// Member variables
//=============================================================================
	public:

	protected:

	private:

};
// MultiLang

#endif // #if !defined( _MULTILANG_HPP_ )

