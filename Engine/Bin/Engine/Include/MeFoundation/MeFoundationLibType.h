#pragma once
#ifdef MEFOUNDATION_EXPORTS
// DLL library project uses this
#define MEFOUNDATION_ENTRY __declspec(dllexport)
#else
#ifdef MEFOUNDATION_IMPORTS
// client of DLL uses this
#define MEFOUNDATION_ENTRY __declspec(dllimport)
#else
// static library project uses this
#define MEFOUNDATION_ENTRY
#endif

#   define ME_SIMD_ALIGNMENT  16

#endif