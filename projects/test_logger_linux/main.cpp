#include <pch.h>

#include "helpers/StatusFunction.h"

int _test_func()
{
    printCriticalError("sasdasda");
}

int main()
{
    logger_init("log.html");

    printMessage("cock", 33, 45.f);
    printError("sasa");
    printWarning("as", 323);

    checkError(true, "sad", 4);
    checkWarning(true, "sadas", 443);

    _test_func();
    int a = 45;
    a += 89;
    checkCriticalError(true, 332, "sadas", 5);
    checkCriticalError(true, 332, "sadas", 5);

}

// тест трассировки стека
// залить на гит
// добавить описание к проектам (кого через что собирал и тестил)