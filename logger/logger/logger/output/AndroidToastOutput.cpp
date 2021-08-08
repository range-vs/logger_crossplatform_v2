#include <pch.h>
#include "AndroidToastOutput.h"

#ifdef __ANDROID__ 

#include <android/log.h>

#include "../helpers/time_utils.h"

#include "factory_messages/TerminalFactory.h"

constexpr const char* LogCatAppName = "LOGGER_OUTPUT";
constexpr const char* ClassToast = "android/widget/Toast";
constexpr const char* ClassToastStaticMethodMakeText = "makeText";
constexpr const char* ClassToastStaticMethodMakeTextSignature = "(Landroid/content/Context;Ljava/lang/CharSequence;I)Landroid/widget/Toast;";
constexpr const char* ClassToastStaticMethodShow = "show";
constexpr const char* ClassToastStaticMethodShowSignature = "()V";
constexpr const char* ClassActivity = "android/app/Activity";
constexpr const char* ClassActivityMethodFinish = "finish";
constexpr const char* ClassActivityMethodFinishSignature = "()V";

void AndroidToastOutput::setJNIEnv(JNIEnv* env)
{
	this->env = env;
}

void AndroidToastOutput::setActivity(jobject activity)
{
	this->activity = activity;
}

void AndroidToastOutput::init(const std::string& nameGame, const std::string& versionGame)
{
	
}

void AndroidToastOutput::init(const std::wstring& nameGame, const std::wstring& versionGame)
{
	assert(false && "wide char functional not implemented!");
}

void AndroidToastOutput::message(const LogType& lt, const std::string & str)
{
	if (lt == LogType::LOG_CRITICAL_ERROR)
	{
		auto messageBuilder(CreatorMessagesTerminalOutput::create(lt));
		auto msg(messageBuilder->createMessage(str));

		jclass toast = env->FindClass(ClassToast);
		assert(toast);

		jmethodID methodMakeText = env->GetStaticMethodID(toast, ClassToastStaticMethodMakeText, ClassToastStaticMethodMakeTextSignature);
		assert(methodMakeText);

		jobject toastobj = env->CallStaticObjectMethod(toast, methodMakeText, activity, env->NewStringUTF(msg.c_str()), 1);
		assert(toastobj);

		jmethodID methodShow = env->GetMethodID(toast, ClassToastStaticMethodShow, ClassToastStaticMethodShowSignature);
		assert(methodShow);

		env->CallVoidMethod(toastobj, methodShow);

		jclass _activity = env->FindClass(ClassActivity);
		assert(_activity);

		jmethodID methodFinish = env->GetMethodID(_activity, ClassActivityMethodFinish, ClassActivityMethodFinishSignature);
		assert(methodFinish);

		env->CallVoidMethod(activity, methodFinish);

	}
}

void AndroidToastOutput::message(const LogType& lt, const std::wstring& str)
{
	assert(false && "wide char functional not implemented!");
}

OutputType AndroidToastOutput::getOutputType() const
{
	return OutputType::ANDROID_TOAST;
}

AndroidToastOutput::~AndroidToastOutput()
{

}

#endif

