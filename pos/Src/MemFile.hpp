//=============================================================================
// Company:
//      Hypercom Inc
//
// Product:
//      Hypercom Foundation Classes
//      (c) Copyright 2006
//
// File Name:
//      MemFile.hpp
//
// File Contents:
//      Declaration of MemFile class
//
//=============================================================================
#if !defined( _MEMFILE_HPP_ )
#define _MEMFILE_HPP_

#include <HString.hpp>
#include <compiler.h>

//=============================================================================
// Public defines and typedefs
//=============================================================================
#include <HypCFile.hpp>

//=============================================================================
// Forward definitions
//=============================================================================


//=============================================================================
//!
//! \brief
//!      Read data from memory like a file.
//!
//!      Reads data from memory using functions like HypCFile
//!      Data can be loaded directly or from other file.
//!
//!      This class is intended for temporary use with HyperwareConfig 
//!      class. File open is slow with current O/S causing long delay when
//!      reading paramters form the TM Database. The long delay is 
//!      very noticeable after a card swipe and prior to amoumt prompt
//!      being shown.  Thus, the need for MemFile.  All data from the file 
//!      is loaded into memory so the file does not need to be opened/closed 
//!      for each parameter read. File open will be greatly 
//!      improved with near future O/S and this class will not be needed.
//!
//!      If the file could be opened once and not ever closed, then 
//!      the delay would not exist. However, the file cannot be left open 
//!      always because it is being read from different processes at 
//!      different times -  so must be opened/closed for each process.
//!
//! \sa
//!      HypCFile
//!
//=============================================================================
class MemFile : public HypCFile
{
	public:

		//! constructor
		MemFile();

		//! Destructor closes file if necessary.
		virtual ~MemFile();

		//! All file members must be wrapped with Open/Close member calls.
		virtual bool Open();

		//! close the file
		virtual bool Close();

		//! read returns bytes successfully read, -1 on failure
		//! could be less than requested in case of EOF
		virtual bool Read( void *buffer, unsigned int length, unsigned int& bytes_read );

		//! write bytes stored in the buffer
		virtual bool Write( const void *buffer, unsigned int length, unsigned int &bytes_written );

		//! Returns the number of bytes moved during seek
		virtual unsigned int Seek( int offset, SeekPosition fromwhere );

		//! Tell the current postion in the file
		virtual inline unsigned int Tell(  );

		//! Check for a valid handle value
		bool IsOpen() const;

		//! return size of file
		unsigned int FileSize();

		//! get one char from the file
		int Getc(  );

		//! Load data from file, deletes any previous data
		bool Load( HypCFile &file );
        
		//! Load data from memory, deletes any previos data
		bool Load( void *data, unsigned int length );


	protected:
		
	private:


		//! position in the file
		unsigned int m_offset;

		//! remember if file is open or closed
		bool m_bOpen;

		//! Buffer containing data
		unsigned char *m_pBuffer;

		//! Size of buffer	
		unsigned int m_BufferSize;		

};

// MemFile

//-----------------------------------------------------------------------------
//!
//!      Tell the current postion in the file
//!
//! \return
//!      offset inside the file
//!
//! \note
//!
inline unsigned int MemFile::Tell(  )
{
	return m_offset;
}


#endif // #if !defined( _MEMFILE_HPP_ )


