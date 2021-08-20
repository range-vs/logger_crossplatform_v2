//
//  main.mm
//  test_logger_macos
//
//  Created by range on 12.08.2021.
//

#include <pch.h>

#include "helpers/StatusFunction.h"

#include <csignal>

void signal_handler(int sig);
int _test_func();

int main(int argc, const char * argv[])
{
    @autoreleasepool
    {
        // insert code here...
        //NSLog(@"Hello, World!");
    }
    
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
