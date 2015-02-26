#define _INCLUDE_NUCLEUS_FILE_
#include <HycDDL.h>
#include <hycddl.h>
#include <HypCFileSystem.hpp>
#include <HypCFile.hpp>
#include "FileSysUtils.hpp"

void CFileSysUtils::InitDisks()
{
	HypCFileSystem Disks;
	STATUS status = NU_SUCCESS;

	const char FlashFileSystem	= 'C';
	const char SRAMFileSystem	= 'D';

    int i = 0;
    while (NU_Become_File_User() == NO || i < 5)
    {
        NU_Release_File_User();
        ++i;
    }

    status = Disks.Initialize( SRAMFileSystem );
	if ( NU_SUCCESS != status )
		return;

	status = Disks.Initialize( FlashFileSystem );
	if ( NU_SUCCESS != status )
		return;
	NU_Become_File_User();
}
