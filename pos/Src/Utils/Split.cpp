#include <string>
#include <vector>
using namespace std;

int split(const char* str, const char* delim, 
     vector<string>& results, bool empties = true)
{
  char* pstr = const_cast<char*>(str);
  char* r = NULL;
  r = strstr(pstr, delim);
  int dlen = strlen(delim);
  while( r != NULL )
  {
    char* cp = new char[(r-pstr)+1];
    memcpy(cp, pstr, (r-pstr));
    cp[(r-pstr)] = '\0';
    if( strlen(cp) > 0 || empties )
    {
      string s(cp);
      results.push_back(s);
    }
    delete[] cp;
    pstr = r + dlen;
    r = strstr(pstr, delim);
  }
  if( strlen(pstr) > 0 || empties )
  {
    results.push_back(string(pstr));
  }
  return results.size();
}
