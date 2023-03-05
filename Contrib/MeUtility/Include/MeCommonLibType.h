#pragma once
#ifdef MECOMMON_EXPORTS
// DLL library project uses this
#define MECOMMON_ENTRY __declspec(dllexport)
#else
#ifdef MECOMMON_IMPORTS
// client of DLL uses this
#define MECOMMON_ENTRY __declspec(dllimport)
#else
// static library project uses this
#define MECOMMON_ENTRY
#endif
#endif