//
//  ViewController.m
//  test_logger_ios
//
//  Created by range on 14.08.2021.
//

#import "ViewController.h"

#include <pch.h>

#include "helpers/StatusFunction.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
        
    const char* pathToFile = [[[NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) firstObject] stringByAppendingPathComponent:@"log.html"] UTF8String];
    NSString* _data = [[NSString alloc] initWithUTF8String:pathToFile];
    NSLog(@"[ALIEN_ENGINE] Path to log-file from iOS: %@", _data);
    logger_init(pathToFile);

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


@end
