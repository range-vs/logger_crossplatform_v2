#include "pch.h"
#include <string>

#include "helpers/StatusFunction.h"

int main()
{
    // аллоцируем консоль для теста
    AllocConsole();
    FILE* stream;
    errno_t err;
    err = freopen_s(&stream, "CONOUT$", "w", stdout);
    //

    logger_init("log.html");

    printMessage("cock", 33, 45.f);
    printError("sasa");
    printWarning("as", 323);

    checkError(true, "sad", 4);
    checkWarning(true, "sadas", 443);

    printCriticalError("sasdasda");
    int a = 45;
    a += 89;
    checkCriticalError(true, 332, "sadas", 5);
    checkCriticalError(true, 332, "sadas", 5);

}