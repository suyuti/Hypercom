//=============================================================================
// Company:
//      Hypercom Inc
//
// Product:
//      Hypercom Foundation Classes 
//      (c) Copyright 2006
//
// File Name:
//      HypCData.hpp
//
// File Contents:
//      Basic data type base class (BatchTotalPage) declaration.
//
//=============================================================================
#if !defined( _BATCHTOTALPAGE_HPP_ )
#define _BATCHTOTALPAGE_HPP_

#if defined(__GNUC__)
//#pragma interface
#endif

#include <compiler.h>
#include <HypCString.hpp>
#include <HString.hpp>
#include <HypCData.hpp>
#include <HypCCurrency.hpp>
#include <HypCInt32.hpp>

//=============================================================================
// Public defines and typedefs
//=============================================================================

//=============================================================================
// Forward definitions
//=============================================================================

//=============================================================================
//!
//! \brief
//!      Base class for containing batch totals. 
//!
//!      This is the base class for different POS applications related data
//!      classes. BatchTotalPage is pure virtual base class which provides basic common
//!      API for any particular data storage class. Main purpose of this class is
//!      transaction data item storage as HypCTransactionData data item.
//!
//! \sa
//!      HypCTransactionData, HypCString, HypCQWord, HypcDateTime and other derived classes
//!
//=============================================================================
class BatchTotalPage : public HypCData
{
//=============================================================================
// Member functions
//=============================================================================
	public:
		//! Creates an empty data object
		inline BatchTotalPage(  );

		//! copy constructor
		inline BatchTotalPage( const BatchTotalPage &another );

		//! destructor
		inline virtual ~BatchTotalPage();

		//! returns HString interpretation of the data (always possible)
		virtual HString AsString() const;

		//! creates data item from HString
		inline virtual void AsString( const HString& value );

		//! Assigns a HString representation of the data to the object
		//!HypCData& operator= ( const HString& sData );

		//! True if the HString is valid as data source
		inline virtual bool CheckIsValid( const HString& sData ) const;

		//! determines if contained data is valid
		inline virtual bool IsValid() const;

		//! Returns true if the object does not contain any data
		inline virtual bool IsEmpty() const;

		//! returns integer interpretation if possible or 0 otherwise
		inline virtual word AsWord() const;

		//! returns 0
		inline virtual int AsInt() const;

		//! functions needed by Database to actual data value
		//! returns actual data type

		//! returns pointer to the stored data
		inline virtual const void* GetDataPtr() const;

		//! returns size of the stored data
		inline virtual int GetDataSize() const;

		//! sets the data by pointer
		inline virtual void SetRawData( const void *data, int length );

		//! returns the symbolic name of this class 
		inline virtual HString GetClassName() const;

		//! Makes a copy of itself. Required for data map operation
		inline virtual HypCData* Clone() const;

		//! addition operator
		virtual HypCData& operator+= ( const HypCData& rhs );

		//! substraction operator
		virtual HypCData& operator-= ( const HypCData& rhs );

		//! get total amount for sales
		inline HypCCurrency GetSalesTotal(  ) const;

		//! get total amount for refunds
		inline HypCCurrency GetRefundsTotal(  ) const;

		//! get total number of sales
		inline HypCInt32 GetNumOfSales(  ) const;

		//! get total number of refunds
		inline HypCInt32 GetNumOfRefunds(  ) const;

		//! reset total amount for sales to the specified value
		inline void SetSalesTotal( const HypCCurrency& cur );

		//! reset total amount for refunds to the specified value
		inline void SetRefundsTotal( const HypCCurrency& cur  );

		//! increase the number of sales
		inline void IncNumOfSales(  );

		//! increase the number of refunds
		inline void IncNumOfRefunds(  );

		//! Serialization of a data type into a file - mode is READ_MODE or WRITE_MODE,
		virtual unsigned int  Serialize (HypCFile& fileHandle, enum serialMode /* mode */);


	protected:
	private:

//=============================================================================
// Member variables
//=============================================================================

	protected:

	private:

		//! total amount, for sales
		HypCCurrency m_sales_total;	

		//! total amount, for refunds
		HypCCurrency m_refunds_total;	

		//! total sales transactions number
		HypCInt32 m_num_of_sales;

		//! total refunds transactions number
		HypCInt32 m_num_of_refunds;
}; 
// BatchTotalPage

// Creates an empty data object
inline BatchTotalPage::BatchTotalPage(  ) : HypCData(  ), 
	m_sales_total( 0 ),
	m_refunds_total( 0 ), 
	m_num_of_sales( 0 ), 
	m_num_of_refunds( 0 )
{  }

// copy constructor
inline BatchTotalPage::BatchTotalPage( const BatchTotalPage &another ) : HypCData( another )
{ 
	operator=( another );
}

// destructor
inline BatchTotalPage::~BatchTotalPage() { }

// creates data item from HString
inline void BatchTotalPage::AsString( const HString& /* value */) {  }

// Assigns a HString representation of the data to the object
//HypCData& operator= ( const HString& /* sData */ );

// True if the HString is valid as data source
inline bool BatchTotalPage::CheckIsValid( const HString& /* sData */) const { return true; }

// determines if contained data is valid
inline bool BatchTotalPage::IsValid() const { return true; }

// Returns true if the object does not contain any data
inline bool BatchTotalPage::IsEmpty() const { return false; }

// returns integer interpretation if possible or 0 otherwise
inline word BatchTotalPage::AsWord() const { return 0; } //const = 0;

// returns integer interpretation if possible or 0 otherwise
inline int BatchTotalPage::AsInt() const { return 0; } //const = 0;

// functions needed by Database to actual data value
// returns actual data type

inline const void* BatchTotalPage::GetDataPtr() const { return NULL; }

// returns pointer to the stored data
inline int BatchTotalPage::GetDataSize() const { return 0; }

// sets the data by pointer
inline void BatchTotalPage::SetRawData( const void* /* data */, int /* length */ ) {  }

// returns the symbolic name of this class 
inline HString BatchTotalPage::GetClassName() const { return HString("BatchTotalPage"); }

// Makes a copy of itself. Required for data map operation
inline HypCData* BatchTotalPage::Clone() const { return new BatchTotalPage( *this ); }

// get total amount for sales
inline HypCCurrency BatchTotalPage::GetSalesTotal(  ) const { return m_sales_total; }

// get total number of refunds
inline HypCCurrency BatchTotalPage::GetRefundsTotal(  ) const { return m_refunds_total; }

// get total number of sales
inline HypCInt32 BatchTotalPage::GetNumOfSales(  ) const { return m_num_of_sales; }

// get total number of refunds
inline HypCInt32 BatchTotalPage::GetNumOfRefunds(  ) const { return m_num_of_refunds; }

// reset total amount for sales to the specified value
inline void BatchTotalPage::SetSalesTotal( const HypCCurrency& cur ) { m_sales_total = cur; }

// reset total amount for refunds to the specified value
inline void BatchTotalPage::SetRefundsTotal( const HypCCurrency& cur  ) { m_refunds_total = cur; }

// increase the number of sales
inline void BatchTotalPage::IncNumOfSales(  ) { m_num_of_sales += 1; }

// increase the number of refunds
inline void BatchTotalPage::IncNumOfRefunds(  ) { m_num_of_refunds += 1; }

// addition operator
inline HypCData& BatchTotalPage::operator+= ( const HypCData& /* rhs */ )
{
  return *this;
}

// substraction operator
inline HypCData& BatchTotalPage::operator-= ( const HypCData& /* rhs */ )
{
  return *this;
}

#endif // #if !defined( _BATCHTOTALPAGE_HPP_ )

