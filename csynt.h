#ifndef CSYNT_H
#define CSYNT_H
#include "clex.h"

class CSynt
{
    int cur;
    const CLex* lexs;
    int testOperatorsList();
    int testBlock();
    int testDeclaration();
    int testAssign();
    int testExpression();
    int testOperand();
    int testFor();
    string getCurLex();
public:
    int test(const CLex* _lexs);
};

#endif // CSYNT_H
