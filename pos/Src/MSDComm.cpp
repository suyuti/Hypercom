#include "MSDComm.hpp"
CMsdComm::CMsdComm()
{
    m_talkActive = false;
    m_initialized = false;
    m_serverSocket = NU_INVALID_SOCKET;
}
CMsdComm::~CMsdComm()
{
    m_initialized = false;
    CloseSocket();
    m_serverSocket = NU_INVALID_SOCKET;
}
void CMsdComm::Initialize(unsigned long ip, unsigned short port)
{
    SetIP(ip);
 //   SetPort(port);
    m_initialized = true;
}
void CMsdComm::Initialize(unsigned char *ip, unsigned short port)
{
    memcpy(&m_IPAddrres, ip, 4);
   // SetPort(port);
    m_initialized = true;
}
int CMsdComm::BeginTalk()
{
    //try
    //{
        int ret = OpenSocket();
        if (ret != 0)
        {
            return ret;
        }
        Send(_Begin_Talk);
        m_talkActive = true;

/*    } catch (...)
    {
        CloseSocket();
        m_talkActive = false;
        return 1;
    }
    */
    return 0;
}
int CMsdComm::EndTalk()
{
	if(!m_talkActive)
	{
		return (0);
	}
	//try
	//{
		Send(_End_Talk);
	//}
	//catch(...)
	//{
	
	//}
	CloseSocket();
	m_talkActive = false;
}
void CMsdComm::SetIP(unsigned long ip)
{
    m_IPAddrres = ip;
}
bool CMsdComm::SetIP(char *ip)
{
}
/*
void CMsdComm::SetPort(unsigned short port)
{
    m_port = port;
}
*/
int CMsdComm::SendMessage(char* Message, int msgLen, char* result, int* resLen)
{
    if (SocketExists())
    {
        //try
        //{
            if (result)
            {
                Send(_Send_Message_ACK);
                Send(Message, msgLen);
                if (resLen)
                {
                    *resLen = Recv(result);
                }
                else
                {
                    Recv(result);
                }
            }
            else {
                Send(_Send_Message_NO_ACK);
                Send(Message, msgLen);
            }
            return 0;
        //} catch (...)
        //{

            //}
    } // SocketExists()
    return -1;
}
bool CMsdComm::ConnectToServer()
{
    return true;
}
int CMsdComm::GetConnectionState()
{
    return 0;
}
int CMsdComm::EstablishConnect()
{
    return 0;
}

int CMsdComm::SetEventObjects()
{
}

