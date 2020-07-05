#include "tts.h"
#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;

TTS::TTS(char* fileName)
{
    lines.clear();
    ifstream f(fileName);
    if(f)
    {
        char s[200];
        while(f.getline(s, 200))
        {
            if(s == "") break;
            bool isDelimiter = false;
            if(s[0] == '@')
            {
                isDelimiter = true;
                TableLine tline(s+1, isDelimiter);
                lines.push_back(tline);
            }
            else
            {
                TableLine tline(s, isDelimiter);
                lines.push_back(tline);
            }
        }
    }
    else
    {
        cout<<"File not found: "<<fileName<<endl;
    }
}

void TTS::show() const
{
    cout<<endl<<"\tTerms Table"<<endl;
    cout<<"----+-----------+----------------"<<endl;
    cout<<"Num |\tlexeme\t|  is delimiter?"<<endl;
    cout<<"----+-----------+----------------"<<endl;
    for (int i = 0; i<lines.size(); i++)
    {
        cout<<setw(4)<<i<<"|\t"<<lines[i].lex<<"\t|\t"<<lines[i].isDelimiter<<endl;
    }
}

string TTS::getLexByIdx(int idx) const
{
    if(idx<0) return "$";
    if(idx>=lines.size()) return "$";
    return lines[idx].lex;
}

int TTS::indexOf(string lex) const
{
    for (int i = 0; i<lines.size(); i++)
    {
        if(lines[i].lex == lex) return i;
    }
    return -1;
}

bool TTS::isDelimiter(string lex) const
{
   int idx = indexOf(lex);
   if(idx == -1) return false;
   return lines[idx].isDelimiter;
}
