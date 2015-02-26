//=============================================================================
// Company:
//      Hypercom Inc
//
// Product:
//      Hypercom Foundation Classes
//      (c) Copyright 2006
//
// File Name:
//      MemFile.cpp
//
// File Contents:
//      Implements MemFile class
//
//=============================================================================
#include <compiler.h>
#include "MemFile.hpp"


//-----------------------------------------------------------------------------
//!
//!      Default constructor
//!
//! \return
//!      None
//!
//! \note
//!      Constructor builds an object, leaving it ready for a call to Open
//!
MemFile::MemFile():HypCFile(),
	m_offset(0),
	m_bOpen(false),
	m_pBuffer(0),
	m_BufferSize()	
{
}


//-----------------------------------------------------------------------------
//!
//!      Destructor
//!
//! \return
//!      None
//!
//! \note
//!      Makes sure the file is closed.
//!
MemFile::~MemFile()
{
	delete m_pBuffer;
}


//-----------------------------------------------------------------------------
//!
//!      opens the file
//!
//! \return
//!      true is file is opened succesfuly
//!
//! \note
//!      To be used when you specify namefile in the constructor, but the open
//!      parameters is false.
//!
bool MemFile::Open()
{
	m_bOpen = true;
	m_offset = 0;
	return true;
}	


//-----------------------------------------------------------------------------
//!
//!      Close file handle
//!
//! \return
//!      true if the file closed succesfully
//!
//! \note
//!
bool MemFile::Close()
{
	m_bOpen = false;
	return true;
}

//-----------------------------------------------------------------------------
//!
//!      Reads 'length' bytes and puts them in 'buffer'.
//!
//! \param
//!      buffer          A pointer to the location in memory to read to
//! \param
//!      length          Maximum number of bytes to read from the file
//! \param
//!      bytes_read      on exit, contains how many bytes were actually read
//!                      from the file.
//!
//! \return
//!      true if data was read from the file
//!
//! \note
//!
bool MemFile::Read( void *buffer, unsigned int length, unsigned int& bytes_read )
{
	
	unsigned int readBytes;

	if( m_offset+length > m_BufferSize )
	{
		readBytes = m_BufferSize - m_offset;
	}
	else
	{
		readBytes = length;
	}

	memcpy( buffer, (m_pBuffer+m_offset), readBytes );

    m_offset += readBytes;

	bytes_read = readBytes;

	return true;
}


//-----------------------------------------------------------------------------
//!
//!      Writes 'length' bytes from 'buffer' to the file
//!
//! \param
//!      buffer          A pointer to the location in memory for write buffer
//! \param
//!      length          Maximum number of bytes to write to the file
//! \param
//!      bytes_read      on exit, contains how many bytes were actually written
//!                      to the file.
//!
//! \return
//!      true if data was written to the file
//!
//! \note
//!
bool MemFile::Write( const void */*buffer*/, unsigned int /*length*/, unsigned int &/*bytes_written*/ )
{
	return false;
}


//-----------------------------------------------------------------------------
//!
//!      Repositions the file pointer
//!
//! \param
//!      offset          How many bytes to move
//! \param
//!      fromWhere       Where should seek start counting
//!
//! \return
//!      Number of bytes actually moved from current position
//!
//! \note
//!
unsigned int MemFile::Seek( int offset, SeekPosition fromwhere )
{
	unsigned int moved = 0;
	unsigned int current = m_offset;

	switch ( fromwhere )
	{
		case beginSeekPosition:
			if( offset >= static_cast<int>( m_BufferSize ) )
			{
				m_offset = m_BufferSize-1;	
			}
			else
			{
				m_offset = offset;
			}
			moved = m_offset;
			break;
		case currentSeekPosition:
			if( (m_offset+offset) >=  m_BufferSize )
			{
				m_offset = m_BufferSize-1;	
				moved = m_offset-current;
			}
			else
			{
				m_offset += offset;
				moved = offset;
			}
            break;
		case endSeekPosition:
			if( offset > 0 )
			{
				m_offset = m_BufferSize-1;
				moved = m_offset-current;
			}
			else
			{
				if( (m_BufferSize+offset) < 0 )
				{
					m_offset = 0;
					moved = current;
				}
				else
				{
					m_offset = m_BufferSize + offset;
					moved = offset;
				}
			}
            break;
	}
	
	return ( moved );
}


//-----------------------------------------------------------------------------
//!
//!      Returns the file size in bytes.
//!
//! \return
//!      File size in bytes
//!
//! \note
//!
unsigned int MemFile::FileSize()
{
	return m_BufferSize;
	
}




//-----------------------------------------------------------------------------
//!
//!      Checks if the file is open
//!
//! \return
//!      bool if file is currently open
//!
//! \note
//!
bool MemFile::IsOpen() const
{
	return m_bOpen;
}

//-----------------------------------------------------------------------------
//!
//!      Get one character from the file
//!
//! \return
//!      character or EOF
//!
//! \note
//!
int MemFile::Getc(  )
{
	char c;
	if( m_offset < m_BufferSize )
	{
		c  =  *(m_pBuffer+m_offset);
		m_offset++;
		return (int)c;
	}
	else
	{
		return EOF;
	}
}


//-----------------------------------------------------------------------------
//!
//!      Load all data from file into memory buffer
//!
//! \param
//!      file referenced to open file to load
//!
//! \return
//!      true if successful , else false for file error
//!
//! \note
//!
bool MemFile::Load( HypCFile &file )
{
	unsigned int fileLen = file.FileSize();

	if( m_pBuffer)
	{
		delete m_pBuffer;
	}

	m_BufferSize = fileLen;	
	m_pBuffer = new unsigned char[m_BufferSize];
	
	unsigned int readBytes;

	// copy file contents into memory
	file.Read( m_pBuffer, fileLen, readBytes );
	return true;

}

//-----------------------------------------------------------------------------
//!
//!      Load data from memory, deletes any previous data
//!
//! \param
//!      file referenced to open file to load
//!
//! \return
//!      true if successful , else false
//!
//! \note
//!
bool MemFile::Load( void *data, unsigned int length )
{
	data = 0;
	length = 0;
	return false;
}

// MemFile.cpp



