#ifndef _YEMEKSEPETICLIENT_HPP_
#define _YEMEKSEPETICLIENT_HPP_

#define _INCLUDE_NUCLEUS_NET_
#include <hycddl.h>
#include <HypCTransport.hpp> 
#include <string>
#include <vector>
#include "..\YemekSepetiMain.hpp"

using namespace std;

class HyperwareMain;



class CYemekSepetiClient
{
public:
	static void Run(UNSIGNED, VOID*);
public:
    CYemekSepetiClient(string ip);
    virtual ~CYemekSepetiClient();
    void SetRestaurantID(int id)    {m_restaurantID = id;};
    int GetRestaurantID()           {return m_restaurantID;};
    void SetServerIP(string ip)     {m_yemekSepetiIP = ip;};
    string GetServerIP()            {return m_yemekSepetiIP;};

    string GetSiparis(int restaurantID);
    void SetApp(HyperwareMain* app) { m_app = app;};
private:
    CYemekSepetiClient();
    string m_yemekSepetiIP;
    int m_restaurantID;
    int m_ip[4];
    INT m_serverSocket;
    HyperwareMain* m_app;

};

#endif
