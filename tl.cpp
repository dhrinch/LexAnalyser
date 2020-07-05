#include "tl.h"
#include <iostream>
#include <iomanip>

TL::TL()
{
    //ctor
}

string TL::getLexByIdx(int idx) const
{
    if(idx<0) return "$";
    if(idx>=names.size()) return "$";
    return names[idx];
}

int TL::indexOf(string lex) const
{
    for(int i = 0; i<names.size(); i++)
    {
        if(names[i] == lex) return i;
    }
    return -1;
}

void TL::show() const
{
    cout<<endl<<"\tLiterals Table"<<endl;
    cout<<"----+---------------+"<<endl;
    cout<<"Num |    literal    |"<<endl;
    cout<<"----+---------------+"<<endl;
    for (int i = 0; i<names.size(); i++)
    {
        cout<<setw(4)<<i<<"|\t"<<names[i]<<endl;
    }
}
