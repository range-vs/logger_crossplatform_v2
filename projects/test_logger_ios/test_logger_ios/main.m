//
//  main.m
//  test_logger_ios
//
//  Created by range on 14.08.2021.
//

#import <UIKit/UIKit.h>
#import "AppDelegate.h"

#include <pch.h>

#include "helpers/StatusFunction.h"

#include <csignal>

void signal_handler(int sig);

int main(int argc, char * argv[]) {
    NSString * appDelegateClassName;
    @autoreleasepool {
        // Setup code that might create autoreleased objects goes here.
        appDelegateClassName = NSStringFromClass([AppDelegate class]);
    }
    
    signal(SIGABRT, signal_handler);
    signal(SIGSEGV, signal_handler);
        
    const char* pathToFile = [[[NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) firstObject] stringByAppendingPathComponent:@"log.html"] UTF8String];
    NSString* _data = [[NSString alloc] initWithUTF8String:pathToFile];
    NSLog(@"[ALIEN_ENGINE] Path to log-file from iOS: %@", _data);
    logger_init(pathToFile);

    printMessage("cock", 33, 45.f);
    printError("sasa");
    printWarning("as", 323);
    
    int*b = nullptr;
    *b = 45;

    checkError(true, "sad", 4);
    checkWarning(true, "sadas", 443);

    printCriticalError("sasdasda");
    int a = 45;
    a += 89;
    checkCriticalError(true, 332, "sadas", 5);
    checkCriticalError(true, 332, "sadas", 5);
    
    return UIApplicationMain(argc, argv, nil, appDelegateClassName);
}

void signal_handler(int sig)
{
    printCriticalError("Signal: ", sig);
}
