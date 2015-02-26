#include "XMLParser.hpp"
#include <ExpatXMLParser\expat.h>

void XMLCALL end(void *data, const char *el);
void XMLCALL start(void *data, const char *el, const char **attr);
int Depth;




string CXMLParser::Get(string key, char *buff, int len)
{
	XML_Parser p = XML_ParserCreate(NULL);
    int depth = 0;
    XML_SetElementHandler(p, start, end);
    XML_Parse(p, buff, len, 1);
    XML_ParserFree(p);
}


void XMLCALL start(void *data, const char *el, const char **attr)
{
  int i;

  //for (i = 0; i < Depth; i++)
  //  printf("  ");

  //printf("%s", el);

  //for (i = 0; attr[i]; i += 2) {
  //  printf(" %s='%s'", attr[i], attr[i + 1]);
  //}

  //printf("\n");
  Depth++;
}

void XMLCALL end(void *data, const char *el)
{
  Depth--;
}


