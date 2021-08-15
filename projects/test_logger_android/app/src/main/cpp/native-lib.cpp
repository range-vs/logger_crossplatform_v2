#include "pch.h"
#include <jni.h>
#include <string>

#include "helpers/StatusFunction.h"

void _logger_init(JNIEnv *pEnv, jobject pJobject, std::string basicString);

extern "C" JNIEXPORT void JNICALL
Java_com_test_logger_android_MainActivity_initLogger(
        JNIEnv* env,
        jobject thiz,
        jstring pathLog,
        jobject activity)
{
    jboolean isCopy;
    std::string convertedValue = env->GetStringUTFChars(pathLog, &isCopy);

    logger_init(env, activity, convertedValue);

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
