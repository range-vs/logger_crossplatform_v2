#include <pch.h>

#include "helpers/StatusFunction.h"

#include <csignal>

int _test_func();
void signal_handler(int sig);


int main()
{
    signal(SIGABRT, signal_handler);
    signal(SIGSEGV, signal_handler);

    logger_init("log.html");

    printMessage("cock", 33, 45.f);
    printError("sasa");
    printWarning("as", 323);

    int*b = nullptr;
    *b = 45;

    checkError(true, "sad", 4);
    checkWarning(true, "sadas", 443);

    _test_func();
    int a = 45;
    a += 89;
    checkCriticalError(true, 332, "sadas", 5);
    checkCriticalError(true, 332, "sadas", 5);

}

int _test_func()
{
    printCriticalError("sasdasda");
}

void signal_handler(int sig)
{
    printCriticalError("Signal: ", sig);
}