#include <pch.h>

#include "StatusFunction.h"

namespace stat_func
{
    bool checkExpression(bool expression)
    {
        return expression;
    }
#ifdef WIN32
    bool checkExpression(HRESULT expression)
    {
        return FAILED(expression);
    }
#endif
}
