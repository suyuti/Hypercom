#define _INCLUDE_NUCLEUS_NET_
#include <hycddl.h>
#include <HypCTransport.hpp> 
#include "POSComm.hpp"
#include <vector>

int split(const char* str, const char* delim, 
     vector<string>& results, bool empties = true);

CPosComm::CPosComm()
{
}
CPosComm::~CPosComm()
{
}
void CPosComm::Initialize(string ip, int port)
{
    m_destIp = ip;
    m_port = port;
    SetDestinationIP(ip);
}
void CPosComm::BeginTalk()
{
}
void CPosComm::EndTalk()
{
}

void CPosComm::SetDestinationIP(string ip)
{
    vector<string> stdResults;
    split(ip.c_str(), ".", stdResults);
    m_ip[0] = atoi(stdResults[0].c_str());
    m_ip[1] = atoi(stdResults[1].c_str());
    m_ip[2] = atoi(stdResults[2].c_str());
    m_ip[3] = atoi(stdResults[3].c_str());
}

int CPosComm::OpenSocket()
{
    int status;
    struct addr_struct servaddr;

    servaddr.family = NU_FAMILY_IP;
    servaddr.port = m_port;
    servaddr.id.is_ip_addrs[0] = m_ip[0];
    servaddr.id.is_ip_addrs[1] = m_ip[1];
    servaddr.id.is_ip_addrs[2] = m_ip[2];
    servaddr.id.is_ip_addrs[3] = m_ip[3];
    servaddr.name = "server";

    m_serverSocket = NU_Socket(NU_FAMILY_IP, NU_TYPE_STREAM, 0);
    status = NU_Connect(m_serverSocket, &servaddr, 0);
    if (status == NU_INVALID_SOCKET)
    {
        return (-1);
    }
    return 0;
}
void CPosComm::CloseSocket()
{
    NU_Close_Socket(m_serverSocket);
}

string CPosComm::SiparisDatasiAl()
{
    // SendCmd siparisVer
    // Recv siparisDataUzunluk (long)
    // Recv data[len]
    // SendCmd OK

    int sent, recvd;
    int cmd = _SiparisDatasiGonder;
    long dataLen = 0L;
    string data;
    char buff[1024];

    sent = NU_Send(m_serverSocket, (char*)&cmd, sizeof(int), 0);
    if (sent == sizeof(int))
    {
        recvd = NU_Recv(m_serverSocket, (char*)&dataLen, sizeof(long), 0);
        if (recvd == sizeof(long))
        {
            int i = 0;
            data = "";
            while (i < dataLen)
            {
                recvd = NU_Recv(m_serverSocket, buff, 1024, 0);
                data += buff;
                i = i + recvd;
            }
            NU_Send(m_serverSocket, "OK", 2, 0);
        }
    }
    return data;
}
bool CPosComm::TumSiparisSorgula()
{
    // Send MüsteriNo
    // Recv SiparisAdedi
    // 
    // SiparisDatasiAl();

    int sent, recvd;
    int siparisAdedi = 0;
    char buff[100] = "";

    strcpy(buff, "M.1");

    OpenSocket();

    sent = NU_Send(m_serverSocket, buff, strlen(buff), 0);
    if (sent == strlen(buff))
    {
        recvd = NU_Recv(m_serverSocket, (char*)&siparisAdedi, sizeof(int), 0);
        if (recvd == sizeof(int))
        {
            for (int i = 0; i < siparisAdedi; ++i)
            {
                SiparisDatasiAl();
            }
        }
    }
    CloseSocket();
    return false;
}

void taskEntry(UNSIGNED x, VOID* y)
{
    int top = 0;
    for (int i = 0; i < 10; ++i)
    {
        top += i;
    }
}

void taskEntry2(UNSIGNED x, VOID* y)
{
    int top = 0;
    for (int i = 0; i < 10; ++i)
    {
        top += i;
    }
}

#define STACK_SIZE	(16 * 1024)

void CPosComm::Listen()
{
//    if (!OpenSocket())
//    {
//        return;
//    }
    INT socketd; 
    INT newSocket; 
 //   char *buff; 
    struct addr_struct myaddr;
    struct addr_struct cliaddr;
    int clilen;
    int count;
    myaddr.family = NU_FAMILY_IP; 
    myaddr.port = 7000; 
    myaddr.id.is_ip_addrs[0] = 172;
    myaddr.id.is_ip_addrs[1] = 16; 
    myaddr.id.is_ip_addrs[2] = 0; 
    myaddr.id.is_ip_addrs[3] = 219;
    myaddr.name = "my_name";
    socketd = NU_Socket(NU_FAMILY_IP, NU_TYPE_STREAM, 0);
    socketd = NU_Bind(socketd, &myaddr, 0);
    NU_Listen(socketd, 0);
    newSocket = NU_Accept(socketd, &cliaddr, 0);
    char buff[] = "Selam";
    NU_Send(newSocket, buff, strlen(buff), 0);
    NU_Close_Socket(newSocket);
    //count = NU_Recv_From (socketd, buff, strlen(buff), 0,cliaddr, clilen);
    //if (count < 0)
    //printf(“an error occurred\n\r”);
//    CloseSocket();
}

bool CPosComm::Dinle()
{
	STATUS status;
    NU_TASK*  m_pAuthTask = NULL;
    NU_TASK*  m_pAuthTask2 = NULL;
    BYTE*	TaskStack;
    BYTE*	TaskStack2;

    TaskStack = new BYTE[STACK_SIZE];
    TaskStack2 = new BYTE[STACK_SIZE];
	if ( TaskStack )
	{
        #if defined(_DEBUG)
		memset (TaskStack,0xAA,STACK_SIZE);
        #endif
		status = Hyc_AllocControlBlock( CB_NU_TASK, (void **)&m_pAuthTask );
		if (NU_SUCCESS == status)
		{
			status = NU_Create_Task( m_pAuthTask,
                                     "AuthTask",
                                     taskEntry, 
                                     0, this,
                                     TaskStack, 
                                     STACK_SIZE, 
                                     DEFAULT_PRIORITY, DEFAULT_TIMESLICE,
                                     NU_PREEMPT, NU_START );
			if (NU_SUCCESS != status)
			{
				Hyc_FreeControlBlock( m_pAuthTask );
			}
		}
		if ( NU_SUCCESS != status )
		{
			delete[] TaskStack;
		}
	}

    if ( TaskStack2 )
    {
        #if defined(_DEBUG)
        memset (TaskStack2,0xAA,STACK_SIZE);
        #endif
        status = Hyc_AllocControlBlock( CB_NU_TASK, (void **)&m_pAuthTask2 );
        if (NU_SUCCESS == status)
        {
            status = NU_Create_Task( m_pAuthTask2,
                                     "AuthTask",
                                     taskEntry2, 
                                     0, this,
                                     TaskStack2, 
                                     STACK_SIZE, 
                                     DEFAULT_PRIORITY, DEFAULT_TIMESLICE,
                                     NU_PREEMPT, NU_START );
            if (NU_SUCCESS != status)
            {
                Hyc_FreeControlBlock( m_pAuthTask2 );
            }
        }
        if ( NU_SUCCESS != status )
        {
            delete[] TaskStack2;
        }
    }

/*    if (!OpenSocket()) {
        return false;
    }
    NU_Fcntl (m_serverSocket, NU_SETFLAG, OS_FALSE);
*/
    return true;
}
void CPosComm::OnSiparisVar()
{
}
