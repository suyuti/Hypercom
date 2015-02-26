#ifndef _SIPARIS_DATA_HPP_
#define _SIPARIS_DATA_HPP_
#include "Base.h"
#include <string>
using namespace std;

#define KN_SiparisID		"<SiparisID>"
#define KN_RestaurantID		"<RestaurantID>"
#define KN_SiparisTarih		"<SiparisTarih>"
#define KN_SiparisSaat		"<SiparisSaat>"
#define KN_MusteriAdi		"<MusteriAdi>"
#define KN_MusteriAdresi	"<MusteriAdresi>"
#define KN_MusteriTelefon	"<MusteriTelefon>"
#define KN_SiparisDetay		"<SiparisDetay>"
#define KN2_SiparisID		"</SiparisID>"
#define KN2_RestaurantID	"</RestaurantID>"
#define KN2_SiparisTarih	"</SiparisTarih>"
#define KN2_SiparisSaat		"</SiparisSaat>"
#define KN2_MusteriAdi		"</MusteriAdi>"
#define KN2_MusteriAdresi	"</MusteriAdresi>"
#define KN2_MusteriTelefon	"</MusteriTelefon>"
#define KN2_SiparisDetay	"</SiparisDetay>"

class CSiparis : public CBase
{
public:
	CSiparis();
	CSiparis(string xmlData);
	virtual ~CSiparis() {};

	string m_SiparisID;
	string m_RestaurantID;
	string m_SiparisTarih;
	string m_SiparisSaat;
	string m_MusteriAdi;
	string m_MusteriAdresi;
	string m_MusteriTelefon;
	string m_SiparisDetay;

	bool m_valid;

	bool IsValid() { return m_valid;};

protected:
	void Parse(string xmlData);
public:
    
	enum {
		SiparisID = 0,
		SiparisID2,
		RestaurantID,
		RestaurantID2,
		SiparisTarih,
		SiparisTarih2,
		SiparisSaat,
		SiparisSaat2,
		MusteriAdi,
		MusteriAdi2,
		MusteriAdresi,
		MusteriAdresi2,
		MusteriTelefon,
		MusteriTelefon2,
		SiparisDetay,
		SiparisDetay2
	};
    
private:
        static string xmlKeys[];
};
#endif
