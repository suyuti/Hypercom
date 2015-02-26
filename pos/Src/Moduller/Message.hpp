#ifndef _MESSAGE_HPP_
#define _MESSAGE_HPP_

#include <HypCDateTime.hpp> 
#include "Base.h"
#include <string>
using namespace std;

class CMessage 
{
public:
    CMessage();
    CMessage(string msg);
    virtual ~CMessage() {};
    string GetData() { return m_data;};
    string GetRawData() {return m_rawData;};
    void SetRawData(string data) {m_rawData = data;};
	void SetObject(CBase* obj);
	CBase* GetObject() { return m_object;};
    HypCDateTime& GetTime() { return m_dateTime;};
	//int GetSize() { return (sizeof(int) + )};

private:
    int             m_messageSize;
	int				m_messageType;
	CBase*			m_object;
    string          m_data;
    string          m_rawData;
    HypCDateTime    m_dateTime;
};
#endif
