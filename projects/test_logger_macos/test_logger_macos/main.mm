//
//  main.mm
//  test_logger_macos
//
//  Created by range on 12.08.2021.
//

#include <pch.h>

#include "helpers/StatusFunction.h"

int _test_func()
{
    printCriticalError("sasdasda");
}

int main(int argc, const char * argv[])
{
    @autoreleasepool
    {
        // insert code here...
        //NSLog(@"Hello, World!");
    }
    
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
