#define _INCLUDE_NUCLEUS_NET_
#include <hycddl.h>
#include <string>
#include <HypCTransport.hpp> 
#include "PosServer.h"
#include "YemekSepetiClient.hpp"
#include "..\YemeksepetiMain.hpp"
#include <HypCInfoBox.hpp> 
using namespace std;

// lklkl
// yeni satir
#define STACK_SIZE	(16 * 1024)

void PosServerThreadProc(UNSIGNED x, VOID* y)
{
    HyperwareMain* pApp = (HyperwareMain*)y;
    INT socketd; 
    INT newSocket; 
    struct addr_struct myaddr;
    struct addr_struct cliaddr;
    int clilen;
    int count;
	char ipadr[4];
    int kez = 0;
    //while (true)
    //{
    
	MgrGetTermIpAddr(ipadr);

    myaddr.family = NU_FAMILY_IP; 
    myaddr.port = 7000; 
    myaddr.id.is_ip_addrs[0] = (int)ipadr[0];
    myaddr.id.is_ip_addrs[1] = (int)ipadr[1];
    myaddr.id.is_ip_addrs[2] = (int)ipadr[2];
    myaddr.id.is_ip_addrs[3] = (int)ipadr[3];
    myaddr.name = "pos";
    socketd = NU_Socket(NU_FAMILY_IP, NU_TYPE_STREAM, 0);
    socketd = NU_Bind(socketd, &myaddr, 0);
    NU_Setsockopt_SO_KEEPALIVE(socketd, 1); 
    NU_Listen(socketd, 0);
	STATUS stat;
	bool lock = false;
    while (true)
    {
		//if (lock) {
		//	continue;
		//}
		//lock = true;
        HypCEvent* event = pApp->GetListenEvent();
        newSocket = NU_Accept(socketd, &cliaddr, 0);
        event = pApp->GetListenEvent();
        event->Send(9996);

		int cmd;
		int recvd = NU_Recv(newSocket, (char*)&cmd, sizeof(int), 0);
		if (recvd == sizeof(int)) {
			switch(cmd) {
				case cmdSiparisVar:
					OnCmdSiparisVar(pApp);
					break;
				case cmdConnectionTest:
                    event->Send(9995);
					OnCmdConnectionTest(pApp, newSocket);
					break;
				case cmdVersionCheck:
					OnCmdVersionCheck(pApp, newSocket);
					break;
            default:
                ;
			}
		}
		NU_Close_Socket(newSocket);
		//lock = false;
    } // while
	HypCEvent* event = pApp->GetListenEvent();
	event->Send(9997);
    ++kez;
   //}
}

void PosServerConnectThreadProc(UNSIGNED x, VOID* y)
{
    //INT socket = (INT)y;
    //char buff[] = "Selam";
    //NU_Send(socket, buff, strlen(buff), 0);
    //NU_Close_Socket(socket);
}

void OnCmdSiparisVar(HyperwareMain *pApp)
{
	CYemekSepetiClient cli("172.16.0.215");
	cli.SetApp(pApp);
	string resp = cli.GetSiparis(5);
	HypCEvent* event = pApp->GetListenEvent();
	event->Send(9999);
}
void OnCmdConnectionTest(HyperwareMain *pApp, INT sock)
{
	int bir = 1;
	NU_Send(sock, (char*)&bir, sizeof(int), 0);
}
void OnCmdVersionCheck(HyperwareMain *pApp, INT sock)
{
}


