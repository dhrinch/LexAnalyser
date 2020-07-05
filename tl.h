#ifndef TL_H
#define TL_H
#include <string>
#include <vector>

using namespace std;

class TL
{
    vector<string>names;
public:
    TL();
    void addLex(string lex){names.push_back(lex);}
    int getSize() const{return names.size();}
    string getLexByIdx(int idx) const;
    int indexOf(string lex) const;
    void show() const;
};

#endif // TL_H
