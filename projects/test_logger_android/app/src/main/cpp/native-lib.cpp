#include "pch.h"
#include <jni.h>
#include <string>
#include <csignal>

#include "helpers/StatusFunction.h"

void signal_handler(int sig);

extern "C" JNIEXPORT void JNICALL
Java_com_test_logger_android_MainActivity_initLogger(
        JNIEnv* env,
        jobject thiz,
        jstring pathLog,
        jobject activity)
{
    jboolean isCopy;
    std::string pathToLogFile = env->GetStringUTFChars(pathLog, &isCopy);

    signal(SIGABRT, signal_handler);
    signal(SIGSEGV, signal_handler);

    logger_init(env, activity, pathToLogFile);

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


}

void signal_handler(int sig)
{
    printCriticalError("Signal: ", sig);
}
