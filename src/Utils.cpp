#include <streambuf>
#include "Utils.h"


using namespace std;


std::istream &getLine(std::istream &s, std::string &str)
{
    str.clear();

    istream::sentry se(s, true);
    streambuf* sb = s.rdbuf();
    while(true)
    {
        int c = sb->sbumpc();
        if (c == '\n')
        {
            return s;
        }
        else if (c == '\r')
        {
            if (sb->sgetc() == '\n')
                sb->snextc();
            return s;
        }
        else if (c == EOF)
        {
            if (str.empty())
                s.setstate(ios::eofbit);
            return s;
        }
        str += c;
    }
}
