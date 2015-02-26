#include "YemeksepetiClient.hpp"
#include "Message.hpp"
#include "XMLParser.hpp"
//#include <ExpatXMLParser\expat.h>
//#include <HypCPrompts.hpp>
#include "FileSiparis.hpp"
#include "SiparisData.h"

int split(const char* str, const char* delim, vector<string>& results, bool empties = true);


//HyperwareMain* CYemekSepetiClient::m_app;

CYemekSepetiClient::CYemekSepetiClient()
{

}
CYemekSepetiClient::CYemekSepetiClient(string ip) :
m_yemekSepetiIP(ip)
{
}

CYemekSepetiClient::~CYemekSepetiClient()
{
}

string CYemekSepetiClient::GetSiparis(int restaurantID)
{
    string retVal;

    vector<string> stdResults;
    split(m_yemekSepetiIP.c_str(), ".", stdResults);
    m_ip[0] = atoi(stdResults[0].c_str());
    m_ip[1] = atoi(stdResults[1].c_str());
    m_ip[2] = atoi(stdResults[2].c_str());
    m_ip[3] = atoi(stdResults[3].c_str());

    int status;
    struct addr_struct servaddr;

    servaddr.family = NU_FAMILY_IP;
    servaddr.port = 80;
    servaddr.id.is_ip_addrs[0] = m_ip[0];
    servaddr.id.is_ip_addrs[1] = m_ip[1];
    servaddr.id.is_ip_addrs[2] = m_ip[2];
    servaddr.id.is_ip_addrs[3] = m_ip[3];
    servaddr.name = "yemeksepeti";

    m_serverSocket = NU_Socket(NU_FAMILY_IP, NU_TYPE_STREAM, 0);
    status = NU_Connect(m_serverSocket, &servaddr, 0);
	if (status < 0)
    {
        return "";
    }
    char buff[1024];
    sprintf(buff, "POST /YemekSepetiTest/Service1.asmx HTTP/1.1\r\nHost: localhost\r\nContent-Type: text/xml; charset=utf-8\r\nContent-Length: 368\r\nSOAPAction: \"http://tempuri.org/GetSiparis\"\r\n\r\n<?xml version=\"1.0\" encoding=\"utf-8\"?>\r\n<soap:Envelope xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\" xmlns:soap=\"http://schemas.xmlsoap.org/soap/envelope/\">\r\n\r\n  <soap:Body>\r\n\r\n    <GetSiparis xmlns=\"http://tempuri.org/\">\r\n      <restaurantID>5</restaurantID>\r\n    </GetSiparis>\r\n  </soap:Body>\r\n</soap:Envelope>\r\n\r\n\r\n");

    /*
		POST /Test/Service1.asmx HTTP/1.1
		Host: localhost
		Content-Type: text/xml; charset=utf-8
		Content-Length: 368
		SOAPAction: "http://tempuri.org/GetSiparis"

		<?xml version="1.0" encoding="utf-8"?>
		<soap:Envelope xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xmlns:xsd="http://www.w3.org/2001/XMLSchema" xmlns:soap="http://schemas.xmlsoap.org/soap/envelope/">
		  <soap:Body>
			<GetSiparis xmlns="http://tempuri.org/">
			  <restaurantID>5</restaurantID>
			</GetSiparis>
		  </soap:Body>
		</soap:Envelope>
	*/


    int sent = NU_Send(m_serverSocket, buff, strlen(buff), 0);
    int i = 0;

    memset(buff, '\0', 1024);
    while((i = NU_Recv(m_serverSocket, buff, sizeof(buff) - 1, 0)) > 0 && i > 0) {
        retVal += buff;
        memset(buff, '\0', 1024);
    }

    char* pMsg = new char[retVal.size()];
	strcpy(pMsg, retVal.c_str());


    CSiparis *sip = new CSiparis(retVal);
	//CSiparis sip(retVal);
	if (sip->IsValid()) {
		if (m_app != NULL) {
			NU_QUEUE* pQ = m_app->GetQueue();
			CMessage msg;
			msg.SetObject((CBase*)sip);
			status = NU_Send_To_Queue(pQ, &msg, sizeof(msg), NU_SUSPEND);
		}
	}



	// Gelen data XML
	///size_t pos = retVal.find("<GetSiparisResult>");
	///size_t pos2 = retVal.find("</GetSiparisResult>", pos);

    //CXMLParser::Get("GetSiparisResult", pMsg, retVal.size());

    // kuyuya gonder
    /*
	if (m_app != NULL)
    {
        NU_QUEUE* pQ = m_app->GetQueue();
        
		size_t pos = retVal.find("<GetSiparisResult>");
        size_t pos2 = retVal.find("</GetSiparisResult>", pos);
        int len = pos2 - pos;
        if (pos != string::npos)
        {
            string cev = retVal.substr(pos + 18, len);
            CMessage msg(cev);
            msg.SetRawData(retVal);
            status = NU_Send_To_Queue(pQ, &msg, sizeof(msg), NU_SUSPEND);
        }
        else {
            CMessage msg(retVal);
            msg.SetRawData(retVal);
            //status = NU_Send_To_Queue(pQ, pMsg, retVal.size(), NU_SUSPEND);
            status = NU_Send_To_Queue(pQ, &msg, sizeof(msg), NU_SUSPEND);
        }
    }
	*/
    delete pMsg;

    NU_Close_Socket(m_serverSocket);

// Kaydet:
	if (CFileSiparis::MakeDir()) {
		CFileSiparis fs;
		fs.Save(*sip);
	}

    return retVal;
}




void CYemekSepetiClient::Run(UNSIGNED i, VOID* app)
{
	STATUS stat;
	UNSIGNED msg;
	UNSIGNED receivedSize;
	while (true) {
		stat = NU_Receive_From_Queue(CGlobal::g_pQueuePOSServerYSClient, &msg, sizeof(UNSIGNED), &receivedSize, NU_SUSPEND);
		if (stat == NU_SUCCESS) {
			CYemekSepetiClient cli("172.16.0.215");
			cli.SetApp((HyperwareMain *)app);
			cli.GetSiparis(msg);
			HypCEvent* event = ((HyperwareMain *)app)->GetListenEvent();
			event->Send(9999);
		}
	}
}
