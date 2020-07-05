#ifndef TSI_H
#define TSI_H
#include <string>
#include <vector>

using namespace std;

class TSI
{
    vector<string>names;
public:
    TSI();
    void addLex(string lex){names.push_back(lex);}
    int getSize() const{return names.size();}
    string getLexByIdx(int idx) const;
    int indexOf(string lex) const;
    void show() const;
};

#endif // TSI_H
