#include "BatchTotalPage.hpp"
#include <HypCTransaction.hpp>

//-----------------------------------------------------------------------------
//!
//!      Returns combined HString value using sale/refund transaction numbers and 
//!      total amounts.
//!
//! \return
//!      HString - combined result
//!
//! \note
//!
HString BatchTotalPage::AsString(  ) const
{ 
	HString item = "SALES\n    ";

	item += m_num_of_sales.AsString(  );
	item += " items\n    ";
	//item += m_cur_symbol.AsString(  );
	item += m_sales_total.AsString(  );

	item += "\nREFUNDS\n    ";
	item += m_num_of_refunds.AsString(  );
	item += " items\n    ";
	//item += m_cur_symbol.AsString(  );
	item += m_refunds_total.AsString(  );

	return item;
}


//-----------------------------------------------------------------------------
//!
//!      Serialization of object into a file
//!
//! \param
//!      file handle       A reference to a handle to an opened file
//!		mode              Either WRITE_MODE or READ_MODE
//!
//! \return
//!		dword (unsigned long) to indicate the number of bytes written or read to/from file
//!
//! \note
//!      not implemented for this class
//!
unsigned int  BatchTotalPage::Serialize(HypCFile& fileHandle, enum serialMode mode  )
{

	return 0;
}
