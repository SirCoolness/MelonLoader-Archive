#pragma once
#include "Mono.h"

class BaseAssembly
{
public:
	static char* Path;
	static char* PreloadPath;
	static bool Initialize();
	static void Preload();
	static void Start();

private:
	static Mono::Method* Mono_Start;
};