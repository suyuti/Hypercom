#ifndef _XML_PARSER_HPP_
#define _XML_PARSER_HPP_

#include <string>
using namespace std;

class CXMLParser
{
public:
    CXMLParser() {};
    virtual ~CXMLParser() {};
    static string Get(string key, char *buff, int len); 
};
#endif
