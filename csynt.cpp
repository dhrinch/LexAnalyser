#include "csynt.h"

bool isType(string lexeme);
bool isName(string lexeme);
bool isSign(string lexeme);
bool isOperation(string lexeme);
bool isValue(string lexeme);
bool isCompare(string lexeme);

int CSynt::test(const CLex* _lexs)
{
    cur = 0;
    lexs = _lexs;

    return testOperatorsList();
}

string CSynt::getCurLex()
{
    if(cur<0) return "empty";
    if(cur>lexs->getSize()) return "empty";
    return (*lexs)[cur];
}

int CSynt::testOperatorsList()
{
    while(cur < lexs->getSize()&& getCurLex()!="}")
    {
        string lex = getCurLex();
        if(lex == "{")
        {
            int err = testBlock();
            if(err) return err;
            continue;
        }
        if(lex == "for")
        {
            int err = testFor();
            if(err) return err;
            continue;
        }
        if(isType(lex))
        {
            int err = testDeclaration();
            if(err) return err;
            continue;
        }
        if(isName(lex))
        {
            int err = testAssign();
            if(err) return err;
            continue;
        }
        return cur;
    }
    return 0;
}

int CSynt::testExpression()
{
    int res = testOperand();
    if(res) return res;
    string lex = getCurLex();
    while (isOperation(lex))
    {
        cur++;
        int res = testOperand();
        if(res) return res;
        lex = getCurLex();
    }
    return 0;
}

int CSynt::testOperand()
{
    string lex = getCurLex();
    if(isSign(lex)) cur++;
    lex = getCurLex();
    if(!isValue(lex)&&!isName(lex)) return cur;
    cur++;
    return 0;
}

int CSynt::testAssign()
{
    cur++;
    string lex = getCurLex();
    if(lex!="=") return cur;
    cur++;
    int res = testExpression(); //testExpression should do cur++
    if(res) return res;
    lex = getCurLex();
    if(lex!=";") return cur;
    cur++;
    return 0;
}

int CSynt::testBlock()
{
    cur++;
    int res = testOperatorsList();
    if(res>0) return res;
    if(getCurLex() == "}")
        cur++;
    else
        return cur;
    return 0;
}

int CSynt::testDeclaration()
{
    cur++;
    string lex = getCurLex();
    if(!isName(lex)) return cur;
    cur++;
    lex = getCurLex();
    if(lex != ";") return cur;
    cur++;
    return 0;
}

int CSynt::testFor()
{
    cur++;
    string lex = getCurLex(); //(
    if(lex!="(") return cur;

    cur++;
    lex = getCurLex(); //int
    if(!isType(lex)) return cur;

    cur++;
    lex = getCurLex(); //i
    if(!isName(lex)) return cur;

    cur++;
    lex = getCurLex(); //=
    if(lex!="=") return cur;

    cur++;
    int res = testExpression(); //0
    if(res!=0) return res;

    //cur++;
    lex = getCurLex(); //;
    if(lex!=";") return cur;

    cur++;
    res = testExpression();  //i
    if(res!=0) return res;

    //cur++;
    lex = getCurLex(); //> < >= <=...
    if(!isCompare(lex)) return cur;

    cur++;
    res = testExpression();  //i
    if(res!=0) return res;

    //cur++;
    lex = getCurLex(); //;
    if(lex!=";") return cur;

    cur++;
    lex = getCurLex(); //i
    if(!isName(lex)) return cur;

    cur++;
    lex = getCurLex(); //++
    if(lex!="++") return cur;

    cur++;
    lex = getCurLex(); //)
    if(lex!=")") return cur;

    cur++;
    lex = getCurLex();
    if(lex == "{")
    {
        int err = testBlock();
        if(err)
            return err;
    }
    if(lex == "for")
    {
        int err = testFor();
        if(err)
            return err;
    }
    if(isType(lex))
    {
        int err = testDeclaration();
        if(err)
            return err;
    }
    if(isName(lex))
    {
        int err = testAssign();
        if(err)
            return err;
    }
    return 0;
}

bool isSign(string lexeme)
{
    if(lexeme == "+") return true;
    if(lexeme == "-") return true;
    return false;
}

bool isOperation(string lexeme)
{
    if(lexeme == "+") return true;
    if(lexeme == "-") return true;
    if(lexeme == "*") return true;
    if(lexeme == "/") return true;
    return false;
}

bool isValue(string lexeme)
{
    for(int i = 0; i<lexeme.size(); i++)
    {
        if(!isdigit(lexeme[i])) return false;
    }
    return true;
}

bool isType(string lexeme)
{
    if(lexeme == "int"||lexeme == "unsigned int") return true;
    return false;
}

bool isName(string lexeme)
{
    if(!isalpha(lexeme[0])) return false;
    int len = lexeme.size();

    for (int i = 1; i<len; i++)
    {
        if(!isalpha(lexeme[i])&&!isdigit(lexeme[i])) return false;
    }
    return true;
}

bool isCompare(string lexeme)
{
    if(lexeme == ">") return true;
    if(lexeme == "<") return true;
    if(lexeme == ">=") return true;
    if(lexeme == "<=") return true;
    if(lexeme == "==") return true;
    if(lexeme == "!=") return true;
    return false;
}


