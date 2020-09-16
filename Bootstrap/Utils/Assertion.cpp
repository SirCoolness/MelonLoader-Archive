#include "Assertion.h"
#include <string>
#include "../Base/Core.h"
#include "Debug.h"
#include "Logger.h"
#include "Console.h"

bool Assertion::ShouldContinue = true;

void Assertion::ThrowInternalFailure(const char* msg)
{
	if (ShouldContinue)
	{
		ShouldContinue = false;
		bool should_print_debug_info = (!Logger::LogFile.coss.is_open() || Debug::Enabled);
		Console::SetColor(Console::Color::Red);
		Logger::WriteTimestamp(Console::Color::Red);
		Logger::LogFile << "[INTERNAL FAILURE] " << msg << std::endl;
		Console::Write("[INTERNAL FAILURE] ");
		if (should_print_debug_info)
			Console::Write(msg);
		else
			Console::Write("Please Post your Latest Log File on #internal-failure in the MelonLoader Discord!");
		Console::Write("\n");
		Console::SetColor(Console::Color::Gray);
		if (should_print_debug_info)
			MessageBoxA(NULL, msg, "MelonLoader - INTERNAL FAILURE", MB_OK | MB_ICONERROR);
		else
			MessageBoxA(NULL, "Please Post your Latest Log File\non #internal-failure in the MelonLoader Discord!", "MelonLoader - INTERNAL FAILURE!", MB_OK | MB_ICONERROR);
	}
}

FARPROC Assertion::GetExport(HMODULE mod, const char* export_name)
{
	if (!ShouldContinue)
		return NULL;
	Debug::Msg(export_name);
	FARPROC returnval = GetProcAddress(mod, export_name);
	if (returnval == NULL)
		ThrowInternalFailure((std::string("Failed to GetExport ( ") + export_name + " )").c_str());
	return returnval;
}