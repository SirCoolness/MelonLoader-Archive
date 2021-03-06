#pragma once
#ifdef _WIN32
#include <Windows.h>
#elif defined(__ANDROID__)
#include <jni.h>
#endif
#include <chrono>

class Core
{
public:
#ifdef _WIN32
	static HINSTANCE Bootstrap;
#elif defined(__ANDROID__)
	static JavaVM* Bootstrap;
	static JNIEnv* Env;
#endif

	static char* Path;
	static const char* Version;
	static const char* ReleaseType;
	static bool QuitFix;
	// Android: Starts when application first loads. This means that some functionality wont be available until a context is created.
	// Windows: Runs first during initialization
	static bool Inject();
	static bool Initialize();
	static void ApplyHooks();
	static bool DirectoryExists(const char* path);
	static bool FileExists(const char* path);
	static void GetLocalTime(std::chrono::system_clock::time_point* now, std::chrono::milliseconds* ms, std::tm* bt);
	static void WelcomeMessage();
	static void KillCurrentProcess();
	static const char* GetFileInfoProductName(const char* path);
	static const char* GetFileInfoProductVersion(const char* path);

private:
	static const char* GetOSVersion();
	static bool OSVersionCheck();
};
