#ifndef CLEX_H
#define CLEX_H
#include <string>
#include <iostream>
#include <vector>
#include "tsi.h"
#include "tts.h"
#include "tl.h"

using namespace std;

class CLex
{
    struct Lex{
        int lineNum;
        string lex;
        string table;
        int idxInTable;
        Lex(int lNum = 0, string _lex = "lex")
        {
            lineNum = lNum;
            table = "???";
            idxInTable = -1;
            lex = _lex;
        }
        void setTable(string table)
        {
            this->table = table;
        }
        void setIdxInTable(int idx)
        {
            idxInTable = idx;
        }
    };
    vector<string> delimiters;
    vector<Lex> lexemes;
    int getNearestDelimiterPos(string s, string& delimiter);
    void parse(string s);
    void analyse();
    TTS tts;
    TL tl;
    TSI tsi;
public:
    CLex(char* fileName);
    virtual ~CLex();
    int getLexCount() const {return lexemes.size();}
    const string operator[](int lexIdx) const;
    string operator[](int lexIdx);
    Lex& getLexByIdx(int lexIdx) {return lexemes[lexIdx];}
    int getSize() const {return lexemes.size();}
    void show();
};

#endif // CLEX_H
