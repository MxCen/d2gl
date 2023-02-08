#include "pch.h"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call) {
		case DLL_PROCESS_ATTACH: {
			d2gl::App.api = d2gl::Api::Glide3x;
			d2gl::dllAttach(hModule);
			break;
		}
		case DLL_PROCESS_DETACH: {
			d2gl::dllDetach();
			break;
		}
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
			break;
	}
	return TRUE;
}