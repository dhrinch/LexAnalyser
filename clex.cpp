#include "clex.h"
#include <fstream>

bool isname(string s);
bool isLiteral(string s);

string code2String(char* fileName);

int CLex::getNearestDelimiterPos(string s, string& delimiter)
{
    int nearestPos = -1;
    delimiter = "";
    for(int i = 0; i<delimiters.size(); i++)
    {
        int pos = s.find(delimiters[i]);
        if (pos>=0)
        {
            if(nearestPos == -1)
            {
                nearestPos = pos;
                delimiter = delimiters[i];
            }
            else
            {
                if(pos<nearestPos)
                {
                    nearestPos = pos;
                    delimiter = delimiters[i];
                }
            }
        }
    }
    return nearestPos;
}

void CLex::parse(string s)
{
    lexemes.clear();
    int lineCnt = 0;
    while(s.size()>0)
    {
        string delimiter;
        int pos = getNearestDelimiterPos(s, delimiter);
        if(pos>0)
        {
            string lex = s.substr(0, pos);
            Lex lexStru(lineCnt, lex);
            lexemes.push_back(lexStru);
            s.erase(0, pos);
        }
        if(pos == 0)
        {
            if(delimiter == "$") {
                lineCnt++;
            }
            else if(delimiter != " ")
            {
                Lex lexStru(lineCnt, delimiter);
                lexemes.push_back(lexStru);
            }
            s.erase(0, delimiter.size());
        }
    }
}

const string CLex::operator[](int lexIdx) const
{
    if(lexIdx<0) return "";
    if(lexIdx>=lexemes.size())return "";
    return lexemes[lexIdx].lex;
}

string CLex::operator[](int lexIdx)
{
    if(lexIdx<0) return "";
    if(lexIdx>=lexemes.size())return "";
    return lexemes[lexIdx].lex;
}

CLex::CLex(char* fileName)
    :tts("tts.txt")
{
    string s = code2String(fileName);
    cout<<s<<endl;
    delimiters.push_back("==");
    delimiters.push_back("!=");
    delimiters.push_back("<=");
    delimiters.push_back(">=");
    delimiters.push_back("++");
    delimiters.push_back("--");
    delimiters.push_back("+=");
    delimiters.push_back("-=");
    delimiters.push_back("*=");
    delimiters.push_back("/=");
    delimiters.push_back("{");
    delimiters.push_back("}");
    delimiters.push_back("(");
    delimiters.push_back(")");
    delimiters.push_back("=");
    delimiters.push_back("+");
    delimiters.push_back("-");
    delimiters.push_back("*");
    delimiters.push_back("/");
    delimiters.push_back(">");
    delimiters.push_back("<");
    delimiters.push_back(";");
    delimiters.push_back(",");
    delimiters.push_back("$");
    delimiters.push_back(" ");
    parse(s);
    analyse();
}

CLex::~CLex()
{
    //dtor
}

string code2String(char* fileName)
{
    string result;
    ifstream in(fileName);
    if(in.is_open())
    {
        string s;
        //while(in>>s)
        while(getline(in, s))
        {
            result+=s;
            result+="$";
        }
    }
    else cout<<"File not found";
    for (int i = 0; i<result.size(); i++)
    {
        if(result[i]<32) result[i] = 32;
    }
    return result;
}

void CLex::analyse()
{
    for(int i = 0; i<lexemes.size(); i++)
    {
        Lex& lex = getLexByIdx(i);
        int idx = tts.indexOf(lex.lex);
        if(idx!=-1)
        {
            lex.setIdxInTable(idx);
            lex.setTable("TTS");
        }
        else if(isname(lex.lex)){
            int idx = tsi.indexOf(lex.lex);
            if(idx==-1)
            {
               tsi.addLex(lex.lex);
               idx = tsi.getSize()-1;
            }
            lex.setIdxInTable(idx);
            lex.setTable("TSI");
        }
        else if(isLiteral(lex.lex))
        {
            int idx = tl.indexOf(lex.lex);
            if(idx==-1)
            {
               tl.addLex(lex.lex);
               idx = tl.getSize()-1;
            }
            lex.setIdxInTable(idx);
            lex.setTable("TL");
        }
        else {
            cout<<"unindentifiable lexeme "<<i<<": "<<lex.lex<<endl;
        }
    }
}

bool isname(string s)
{
    if(!isalpha(s[0])) return false;
    for (int i = 0; i< s.size(); i++)
    {
        if(!isalpha(s[i])&&(!isdigit(s[i]))) return false;
    }
    return true;
}

bool isLiteral(string s)
{
    for (int i = 0; i< s.size(); i++)
    {
        if(!isdigit(s[i])) return false;
    }
    return true;
}

void CLex::show()
{
    tts.show();
    tsi.show();
    tl.show();
    cout<<endl;
    for (int i = 0; i<getLexCount(); i++)
    {
        Lex& lex = getLexByIdx(i);
        cout<<i<<"\t"<<lex.lineNum<<"\t"<<lex.lex<<"\t"<<lex.table<<"."<<lex.idxInTable<<endl;
    }
}
