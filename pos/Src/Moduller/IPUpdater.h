#ifndef _IP_UPDATER_HPP_
#define _IP_UPDATER_HPP_

#include <string>
using namespace std;

class CIPUpdater
{
public:
	CIPUpdater(string serverIp, string restID);
	void Update();
protected:
private:
	string m_serverIP;
	string m_restID;
};
#endif