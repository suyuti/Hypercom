#include "SiparisData.h"

string CSiparis::xmlKeys[] = {
	KN_SiparisID		,		
	KN2_SiparisID		,	
	KN_RestaurantID		,		
	KN2_RestaurantID	,	
	KN_SiparisTarih		,	
	KN2_SiparisTarih	,	
	KN_SiparisSaat		,	
	KN2_SiparisSaat		,	
	KN_MusteriAdi		,	
	KN2_MusteriAdi		,	
	KN_MusteriAdresi	,	
	KN2_MusteriAdresi	,	
	KN_MusteriTelefon	,	
	KN2_MusteriTelefon	,	
	KN_SiparisDetay		,	
	KN2_SiparisDetay	
};


CSiparis::CSiparis()
{
}
//----------------
CSiparis::CSiparis(std::string xmlData)
{
	Parse(xmlData);
}
void CSiparis::Parse(string xmlData)
{
	m_valid = false;
	int pos1, pos2;
	
	pos1 = xmlData.find(xmlKeys[SiparisID]);
	if (pos1 == -1) {
		goto EXIT_NOT_VALID;
	}
	pos2 = xmlData.find(xmlKeys[SiparisID2], pos1);
	if (pos2 == -1) {
		goto EXIT_NOT_VALID;
	}
	m_SiparisID = xmlData.substr(pos1 + xmlKeys[SiparisID].size() ,pos2 - pos1 - (xmlKeys[SiparisID2].size() - 1));

	//////////////////////////////////////////////////////////////////////////

	pos1 = xmlData.find(xmlKeys[RestaurantID]);
	if (pos1 == -1) {
		goto EXIT_NOT_VALID;
	}
	pos2 = xmlData.find(xmlKeys[RestaurantID2], pos1);
	if (pos2 == -1) {
		goto EXIT_NOT_VALID;
	}
	m_RestaurantID = xmlData.substr(pos1 + xmlKeys[RestaurantID].size() ,pos2 - pos1 - (xmlKeys[RestaurantID2].size() - 1));

	//////////////////////////////////////////////////////////////////////////

	pos1 = xmlData.find(xmlKeys[SiparisTarih]);
	if (pos1 == -1) {
		goto EXIT_NOT_VALID;
	}
	pos2 = xmlData.find(xmlKeys[SiparisTarih2], pos1);
	if (pos2 == -1) {
		goto EXIT_NOT_VALID;
	}
	m_SiparisTarih = xmlData.substr(pos1 + xmlKeys[SiparisTarih].size() ,pos2 - pos1 - (xmlKeys[SiparisTarih2].size() - 1));

	//////////////////////////////////////////////////////////////////////////

	pos1 = xmlData.find(xmlKeys[SiparisSaat]);
	if (pos1 == -1) {
		goto EXIT_NOT_VALID;
	}
	pos2 = xmlData.find(xmlKeys[SiparisSaat2], pos1);
	if (pos2 == -1) {
		goto EXIT_NOT_VALID;
	}
	m_SiparisSaat = xmlData.substr(pos1 + xmlKeys[SiparisSaat].size() ,pos2 - pos1 - (xmlKeys[SiparisSaat2].size() - 1));

	//////////////////////////////////////////////////////////////////////////

	pos1 = xmlData.find(xmlKeys[MusteriAdi]);
	if (pos1 == -1) {
		goto EXIT_NOT_VALID;
	}
	pos2 = xmlData.find(xmlKeys[MusteriAdi2], pos1);
	if (pos2 == -1) {
		goto EXIT_NOT_VALID;
	}
	m_MusteriAdi = xmlData.substr(pos1 + xmlKeys[MusteriAdi].size() ,pos2 - pos1 - (xmlKeys[MusteriAdi2].size() - 1));

	//////////////////////////////////////////////////////////////////////////

	pos1 = xmlData.find(xmlKeys[MusteriAdresi]);
	if (pos1 == -1) {
		goto EXIT_NOT_VALID;
	}
	pos2 = xmlData.find(xmlKeys[MusteriAdresi2], pos1);
	if (pos2 == -1) {
		goto EXIT_NOT_VALID;
	}
	m_MusteriAdresi = xmlData.substr(pos1 + xmlKeys[MusteriAdresi].size() ,pos2 - pos1 - (xmlKeys[MusteriAdresi2].size() - 1));

	//////////////////////////////////////////////////////////////////////////

	pos1 = xmlData.find(xmlKeys[MusteriTelefon]);
	if (pos1 == -1) {
		goto EXIT_NOT_VALID;
	}
	pos2 = xmlData.find(xmlKeys[MusteriTelefon2], pos1);
	if (pos2 == -1) {
		goto EXIT_NOT_VALID;
	}
	m_MusteriTelefon = xmlData.substr(pos1 + xmlKeys[MusteriTelefon].size() ,pos2 - pos1 - (xmlKeys[MusteriTelefon2].size() - 1));

	//////////////////////////////////////////////////////////////////////////

	pos1 = xmlData.find(xmlKeys[SiparisDetay]);
	if (pos1 == -1) {
		goto EXIT_NOT_VALID;
	}
	pos2 = xmlData.find(xmlKeys[SiparisDetay2], pos1);
	if (pos2 == -1) {
		goto EXIT_NOT_VALID;
	}
	m_SiparisDetay = xmlData.substr(pos1 + xmlKeys[SiparisDetay].size() ,pos2 - pos1 - (xmlKeys[SiparisDetay2].size() - 1));


	m_valid = true;

	m_size = m_SiparisID.size() + m_SiparisDetay.size();
	return;
EXIT_NOT_VALID:
	m_valid = false;
}
