#define _INCLUDE_NUCLEUS_FILE_
#include <HycDDL.h>
#include "FileSiparis.hpp"
#include "..\Utils\FileSysUtils.hpp"
#include <hycddl.h>
#include <HypCFileSystem.hpp>
#include <HypCFile.hpp>


string CFileSiparis::m_gelenSiparislerFolderName = FOLDER_NAME;

CFileSiparis::CFileSiparis()
{
	InitDisks();
}
CFileSiparis::CFileSiparis(string fileName)
{
	InitDisks();
}
CFileSiparis::~CFileSiparis()
{
}
void CFileSiparis::AppendRec(string rec)
{
}
bool CFileSiparis::Open()
{
}
void CFileSiparis::Close()
{
}
bool CFileSiparis::MakeDir()
{
    CFileSysUtils::InitDisks();
	//InitDisks();
	STATUS status = NU_Make_Dir (FOLDER_NAME);
    if (status == NU_SUCCESS || status == NUF_EXIST || status == (-3000))
    {
		return true;
    }
    return false;
}
void CFileSiparis::Save(CSiparis& sip)
{
	//string csfileName = m_gelenSiparislerFolderName + ID_FILE_NAME;
	string csfileName = FOLDER_NAME ID_FILE_NAME;

	HypCFile curSipIDFile;
	if (!curSipIDFile.Open(csfileName.c_str(), F_OPEN_EXISTING|F_SHARE_READ, F_READ|F_WRITE)) {
		curSipIDFile.Open(csfileName.c_str(), F_CREATE|F_SHARE_READ|F_SHARE_WRITE, F_READ|F_WRITE);
	}
	int currentSipID = 0;
	unsigned int read;

	curSipIDFile.Read((void*)&currentSipID, (unsigned int)sizeof(int), read);
	++currentSipID;
	curSipIDFile.Seek(0, HypCFile::beginSeekPosition);
	curSipIDFile.Write(&currentSipID, (unsigned int)sizeof(int), read);
	curSipIDFile.Close();
	
	char i[50] = "";
	sprintf(i, "Sip_%d.sip", currentSipID);
	//string fileName = m_gelenSiparislerFolderName + "\\" + i + ".sip";
	string fileName = FOLDER_NAME "\\";
	fileName += i;

	std::ofstream file(fileName.c_str());
	if (file.is_open())
	{
		file << sip.m_SiparisID		<< endl;
		file << sip.m_RestaurantID	<< endl;
		file << sip.m_SiparisTarih	<< endl;
		file << sip.m_SiparisSaat	<< endl;
		file << sip.m_MusteriAdi	<< endl;
		file << sip.m_MusteriAdresi	<< endl;
		file << sip.m_MusteriTelefon<< endl;
		file << sip.m_SiparisDetay	<< endl;
		file.close();
	}
}
CSiparis CFileSiparis::GetSiparis(string sipFileName)
{
	CSiparis sip;
	std::ofstream file(sipFileName.c_str());
	if (file.is_open())
	{
		
/*		file >> sip.m_SiparisID		<< endl;
		file >> sip.m_RestaurantID	<< endl;
		file >> sip.m_SiparisTarih	<< endl;
		file >> sip.m_SiparisSaat	<< endl;
		file >> sip.m_MusteriAdi	<< endl;
		file << sip.m_MusteriAdresi	<< endl;
		file << sip.m_MusteriTelefon<< endl;
		file << sip.m_SiparisDetay	<< endl;
*/
		file.close();
	}
	return sip;
}

void CFileSiparis::InitDisks()
{
	HypCFileSystem Disks;
	STATUS status = NU_SUCCESS;

	const char FlashFileSystem	= 'C';
	const char SRAMFileSystem	= 'D';

	status = Disks.Initialize( SRAMFileSystem );
	if ( NU_SUCCESS != status )
		return;

	status = Disks.Initialize( FlashFileSystem );
	if ( NU_SUCCESS != status )
		return;
}

