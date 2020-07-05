#include "tsi.h"
//#include <algorithm>
#include <iostream>
#include <iomanip>

TSI::TSI()
{
    //ctor
}

string TSI::getLexByIdx(int idx) const
{
    if(idx<0) return "$";
    if(idx>=names.size()) return "$";
    return names[idx];
}

int TSI::indexOf(string lex) const
{
    for(int i = 0; i<names.size(); i++)
    {
        if(names[i] == lex) return i;
    }
    return -1;
}

void TSI::show() const
{
    cout<<endl<<"\tNames Table"<<endl;
    cout<<"----+---------------+"<<endl;
    cout<<"Num |\t   name\t    |"<<endl;
    cout<<"----+---------------+"<<endl;
    for (int i = 0; i<names.size(); i++)
    {
        cout<<setw(4)<<i<<"|\t"<<names[i]<<endl;
    }
}
