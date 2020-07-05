#ifndef TTS_H
#define TTS_H
#include <vector>
#include <string>

using namespace std;

class TTS
{
    struct TableLine
    {
        string lex;
        bool isDelimiter;
        TableLine(string _lex = "lex", bool _delimit = false)
        {
            lex = _lex;
            isDelimiter = _delimit;
        }
    };
    vector<TableLine> lines;
public:
    TTS(char* fileName);
    void show() const;
    int getSize() const{return lines.size();}
    string getLexByIdx(int idx) const;
    int indexOf(string lex) const;
    bool isDelimiter(string lex) const;
};



#endif // TTS_H
