#ifndef _MSDCOMM_HPP_
#define _MSDCOMM_HPP_

#define _INCLUDE_NUCLEUS_NET_
#include <HypCTransport.hpp> 


class CMsdComm
{
    enum {
        PacketSize = 1024
    };
    enum {
        BuffSize = 2048 + 15
    };
    enum {
        _RecvFiles,
        _SendFiles,
        _RecvFile,
        _SendFile,
        _Begin_Talk,
        _End_Talk,
        _Send_Message_ACK,
        _Send_Message_NO_ACK,
        _SendMessage,
        _RecvMessage,
        _Transfer_OK
    };
private:

    bool m_initialized;
    bool m_talkActive;
    int m_serverSocket;
    struct addr_struct m_destAddr;
    unsigned long m_IPAddrres;
    unsigned short m_port;
    char m_cIPAddress[40];

    bool SocketExists()
    {
        return (m_serverSocket!= NU_INVALID_SOCKET);
    }
public:
    void Initialize(unsigned long ip, unsigned short port);
    void Initialize(unsigned char *ip, unsigned short port);
    int OpenSocket();
    void CloseSocket();

/*    const char* GetIPAddress()
    {
        return m_cIPAddress;
    }
    unsigned short  GetPort()
    {
        return m_port;
    }
*/
    CMsdComm();
    virtual ~CMsdComm();

    int BeginTalk();
    int EndTalk();

    int Send(char* buff);
    int Send(int command);
    int Send(char* buff, int size);

    int Recv(char* buff);
    int Recv(int *pCommand);

    void SetIP(unsigned long ip);
    bool SetIP(char *ip);
  //  void SetPort(unsigned short port);
    int SendMessage(char* Message, int msgLen, char* result = NULL, int* resLen = NULL);
    bool ConnectToServer();
    int GetConnectionState();
    int EstablishConnect();
    int SetEventObjects();

};
#endif
