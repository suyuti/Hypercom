#ifndef _SIPARIS_FILE_HPP_
#define _SIPARIS_FILE_HPP_
#include <hycddl.h>
#include <HypCFileSystem.hpp>
#include "SiparisData.h"
#include <string>
#include <stdio.h>
#include <iostream>
#include <fstream>

using namespace std;

#define FOLDER_NAME	"\\GelSips"
//#define FOLDER_NAME		""
#define ID_FILE_NAME	"\\cursip.id"

class CFileSiparis
{
public:
	CFileSiparis();
	CFileSiparis(string fileName);
    virtual ~CFileSiparis();
    void AppendRec(string rec);
    bool Open();
    void Close();
	static bool MakeDir();
	void Save(CSiparis& sip);
	CSiparis GetSiparis(string sipFileName);
	static void InitDisks();
protected:
private:
    string m_fileName;
	static string m_gelenSiparislerFolderName;
};
#endif
