#include "Message.hpp"

CMessage::CMessage() :
    m_data (""),
    m_messageSize (0)
{
    this->m_dateTime.CurrentTime();
	this->m_messageSize = 0;
}

CMessage::CMessage(string msg)
{
    this->m_dateTime.CurrentTime();
    this->m_data = msg;
    this->m_messageSize = msg.size();
}

void CMessage::SetObject(CBase* obj) 
{
	this->m_messageSize += obj->m_size;
	m_object = obj;
}
