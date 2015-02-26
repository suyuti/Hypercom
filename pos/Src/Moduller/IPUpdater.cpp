#include "IPUpdater.h"
#define _INCLUDE_NUCLEUS_NET_
#include <hycddl.h>
#include <HypCTransport.hpp> 
#include <vector>

int split(const char* str, const char* delim, vector<string>& results, bool empties = true);

CIPUpdater::CIPUpdater(string serverIp, string restID):
m_serverIP(serverIp),
m_restID(restID)
{
}

void CIPUpdater::Update()
{
	string retVal;
	INT serverSocket;
    int m_ip[4];

	vector<string> stdResults;
	split(m_serverIP.c_str(), ".", stdResults);
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
	servaddr.name = "host";

	serverSocket = NU_Socket(NU_FAMILY_IP, NU_TYPE_STREAM, 0);
	status = NU_Connect(serverSocket, &servaddr, 0);
	if (status < 0)
	{
		return ;
	}
	char buff[1024];
	
	sprintf(buff, "GET /YemekSepeti/IpUpdate.aspx?restID=%s HTTP/1.1\r\nHost: localhost\r\nUser-Agent: Mozilla/4.0\r\n\r\n\r\n", m_restID.c_str());

	int sent = NU_Send(serverSocket, buff, strlen(buff), 0);
	NU_Close_Socket(serverSocket);
}