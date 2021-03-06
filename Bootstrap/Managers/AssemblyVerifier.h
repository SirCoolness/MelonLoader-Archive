#pragma once
#include "Mono.h"

#ifndef __stdcall
#define __stdcall __attribute__((__stdcall__))
#endif

#ifndef __forceinline
#define __forceinline __attribute__((always_inline))
#endif

struct AssemblyVerifier {
	static void InstallHooks();
private:
	typedef Mono::Object** (*callOriginalLoadFrom_t)(Mono::String** path, int refonly, void* stackMark, void* error);
	typedef Mono::Object** (*callOriginalLoadRaw_t)(Mono::Object** appDomain, Mono::Object** bytes, Mono::Object** symbolStore, Mono::Object** evidence, int refonly, void* stackMark, void* error);

	static callOriginalLoadFrom_t callOriginalLoadFrom;
	static callOriginalLoadRaw_t callOriginalLoadRaw;

	// TODO: are mono internal calls __stdcall indeed?
	static Mono::Object** __stdcall LoadFromPatch(Mono::String** path, int refonly, void* stackMark, void* error);
	static Mono::Object** __stdcall LoadRawPatch(Mono::Object** appDomain, Mono::Object** bytes, Mono::Object** symbolStore, Mono::Object** evidence, int refonly, void* stackMark, void* error);
};

