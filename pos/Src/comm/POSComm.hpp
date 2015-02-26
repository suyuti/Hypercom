#ifndef _POSCOMM_HPP_
#define _POSCOMM_HPP_
#define _INCLUDE_NUCLEUS_NET_

#include <string>
using namespace std;

class CPosComm
{
public:
    enum Commands {
        _BeginTalk,
        _EndTalk,
        _SendMessage_ACK,
        _SendMessage_NO_ACK,
        _RecvMessage,
        _OK,
        _Bitti,
        _SiparisDatasiGonder
    };
    enum {
        _BufferSize = 2048,
        _PacketSize = 1024
    };
public:
    CPosComm();
    virtual ~CPosComm();
    void Initialize(string ip, int port);
    void BeginTalk();
    void EndTalk();
    bool TumSiparisSorgula();

    bool Dinle();
    virtual void OnSiparisVar();
    void Listen();

private:
    string SiparisDatasiAl();
    int OpenSocket();
    void CloseSocket();
    void SetDestinationIP(string ip);

private:
    int m_serverSocket;

    string m_destIp;
    int m_port;
    int m_ip[4];
};

#endif
