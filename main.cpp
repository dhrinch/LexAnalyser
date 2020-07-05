#include "clex.h"
#include "tts.h"
#include "tsi.h"
#include "tl.h"
#include "csynt.h"
#include <iostream>
#include <string>

using namespace std;

int main()
{
    CLex lex("test.cpp");
    lex.show();
    cout<<endl;
//    for (int i = 0; i<lex.getLexCount(); i++)
//    {
//        cout<<i<<" "<<lex.getLexByIdx(i).lineNum<<" "<<lex[i]<<endl;
//    }
    CSynt synt;
    cout<<endl<<synt.test(&lex)<<endl;
    return 0;
}
