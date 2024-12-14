// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        // Perform initialization specific to the process
        DisableThreadLibraryCalls(hModule);
        break;

    case DLL_THREAD_ATTACH:
        // Handle thread-specific initialization (if needed)
        break;

    case DLL_THREAD_DETACH:
        // Handle thread-specific cleanup
        break;

    case DLL_PROCESS_DETACH:
        // Perform cleanup specific to the process
        if (lpReserved == NULL) {
            // Cleanup for normal process termination
        }
        else {
            // Cleanup for FreeLibrary
        }
        break;
    }
    return TRUE;
}

