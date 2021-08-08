#pragma once

#ifdef __ANDROID__ 

#include "BaseOutput.h"

#include <jni.h>

class AndroidToastOutput : public BaseOutput
{
	JNIEnv* env;
	jobject activity;

public:
	void setJNIEnv(JNIEnv* env);
	void setActivity(jobject activity);
	void init(const std::string& nameGame, const std::string& versionGame) override;
	void init(const std::wstring& nameGame, const std::wstring& versionGame) override;
	void message(const LogType& lt, const std::string& str) override;
	void message(const LogType& lt, const std::wstring& str) override;
	OutputType getOutputType() const override;
	~AndroidToastOutput()override;
};
#endif
