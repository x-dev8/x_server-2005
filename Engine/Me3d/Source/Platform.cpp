#include "Me3d/Me3d.h"
#include "Me3d/Platform.h"
#include "FuncPerformanceLog.h"
#include "Me3d/Vector4.h"
#include "Me3d/Vector.h"

Vector4 MeMatrix::operator * (const Vector4& v) const
{
	return Vector4(
		m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3] * v.w, 
		m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3] * v.w,
		m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3] * v.w,
		m[3][0] * v.x + m[3][1] * v.y + m[3][2] * v.z + m[3][3] * v.w
		);
}

Platform *GetPlatform()
{
	static Platform Platform;
	return &Platform;
}


#define ARRAY_COUNT( array )   ( sizeof(array) / sizeof((array)[0]) )
template< class T > inline void Exchange( T& A, T& B )
{
	const T Temp = A;
	A = B;
	B = Temp;
}

typedef signed long long SQWORD;
typedef unsigned __int64 QWORD;

DWORD GPhysicalMemory;
DOUBLE GSecondsPerCycle;
DWORD GPageSize;
DWORD GProcessorCount;

BOOL GIsMMX;
BOOL GIsPentiumPro;
BOOL GIsSSE;
//
// Platform specific initialization.
//
static void DoCPUID( int i, DWORD *A, DWORD *B, DWORD *C, DWORD *D )
{
#if ASM
	__asm
	{			
		mov eax,[i]
		_emit 0x0f
			_emit 0xa2

			mov edi,[A]
		mov [edi],eax

			mov edi,[B]
		mov [edi],ebx

			mov edi,[C]
		mov [edi],ecx

			mov edi,[D]
		mov [edi],edx

			mov eax,0
			mov ebx,0
			mov ecx,0
			mov edx,0
			mov esi,0
			mov edi,0
	}
#else
	*A=*B=*C=*D=0;
#endif
}

/*****************************************************************************/
/** Constructs the platform instance.
*
* This function is the default constructor of the platform instance.
*****************************************************************************/

Platform::Platform():
MemoryLvl(eMemory_High)
{
}

/*****************************************************************************/
/** Destructs the platform instance.
*
* This function is the destructor of the platform instance.
*****************************************************************************/

Platform::~Platform()
{
}

//****************************************************************************//
VOID Platform::Init()
{
	guardfunc;
	
	CHAR szBuffer[256] = {0};
	// Identity.
	//debugf( NAME_Init, TEXT("Computer: %s"), appComputerName() );
	//debugf( NAME_Init, TEXT("User: %s"), appUserName() );

	// Get memory.
	guard(GetMemory);
	MEMORYSTATUS M;
	GlobalMemoryStatus(&M);
	GPhysicalMemory=M.dwTotalPhys;
	sprintf( szBuffer, "Memory total: Phys=%iK Pagef=%iK Virt=%iK\n", M.dwTotalPhys/1024, M.dwTotalPageFile/1024, M.dwTotalVirtual/1024 );
	OutputDebugString( szBuffer );
	unguard;

	// Working set.
	guard(GetWorkingSet);
	DWORD WsMin=0, WsMax=0;
	GetProcessWorkingSetSize( GetCurrentProcess(), &WsMin, &WsMax );
	sprintf( szBuffer, "Working set: %X / %X\n", WsMin, WsMax );
	OutputDebugString( szBuffer );
	unguard;

	// CPU speed.
	guard(CheckCpuSpeed);
	try
	{
		LARGE_INTEGER lFreq;
		QueryPerformanceFrequency(&lFreq);
		DOUBLE Frequency = (DOUBLE)(SQWORD)(((QWORD)lFreq.LowPart) + ((QWORD)lFreq.HighPart<<32));

// 		DOUBLE S[3];
// 		for( INT i=0; i<ARRAY_COUNT(S); i++ )
// 		{
// 			INT Cycles=0;
// 			LARGE_INTEGER I1, I2;
// 			QueryPerformanceCounter(&I1);
// 
// 			DWORD StartMsec = timeGetTime();
// 			while( timeGetTime()-StartMsec < 10 );
// 			QueryPerformanceCounter(&I2);
// 
// 			DOUBLE T1 = (DOUBLE)(SQWORD)((QWORD)I1.LowPart + (((QWORD)I1.HighPart)<<32)) / Frequency;
// 			DOUBLE T2 = (DOUBLE)(SQWORD)((QWORD)I2.LowPart + (((QWORD)I2.HighPart)<<32)) / Frequency;
// 			S[i]      = (T2-T1) / (DOUBLE)Cycles;
// 			for( INT j=0; j<i-1; j++ )
// 				if( S[j]>S[i] )
// 				{
// 					Exchange( S[j], S[i] );
// 				}
// 		}
// 		GSecondsPerCycle = S[1];
// 
// 		sprintf( szBuffer, "CPU Speed=%f MHz\n", 0.000001 / GSecondsPerCycle );
// 		OutputDebugString( szBuffer );
	}
	catch( ... )
	{
		//debugf( NAME_Init, TEXT("Timestamp not supported (Possibly 486 or Cyrix processor)") );
		GSecondsPerCycle = 1;
	}
//	if( Parse(appCmdLine(),TEXT("CPUSPEED="),CpuSpeed) )
//	{
//		GSecondsPerCycle = 0.000001/CpuSpeed;
//		//debugf( NAME_Init, TEXT("CPU Speed Overridden=%f MHz"), 0.000001 / GSecondsPerCycle );
//	}
	unguard;

	// Get CPU info.
	guard(GetCpuInfo);
	SYSTEM_INFO SI;
	GetSystemInfo(&SI);
	GPageSize = SI.dwPageSize;
//	check(!(GPageSize&(GPageSize-1)));
	GProcessorCount=SI.dwNumberOfProcessors;

	sprintf( szBuffer, "CPU Page size=%i, Processors=%i\n", SI.dwPageSize, SI.dwNumberOfProcessors );
	OutputDebugString( szBuffer );
	unguard;

	// Check processor version with CPUID.
	try
	{
		DWORD A=0, B=0, C=0, D=0;
		DoCPUID(0,&A,&B,&C,&D);
		TCHAR Brand[13], *Model, FeatStr[256]=TEXT("");
		Brand[ 0] = (CHAR)(B);
		Brand[ 1] = (CHAR)(B>>8);
		Brand[ 2] = (CHAR)(B>>16);
		Brand[ 3] = (CHAR)(B>>24);
		Brand[ 4] = (CHAR)(D);
		Brand[ 5] = (CHAR)(D>>8);
		Brand[ 6] = (CHAR)(D>>16);
		Brand[ 7] = (CHAR)(D>>24);
		Brand[ 8] = (CHAR)(C);
		Brand[ 9] = (CHAR)(C>>8);
		Brand[10] = (CHAR)(C>>16);
		Brand[11] = (CHAR)(C>>24);
		Brand[12] = (CHAR)(0);
		DoCPUID( 1, &A, &B, &C, &D );
		switch( (A>>8) & 0x000f )
		{
		case 4:  Model=TEXT("486-class processor");        break;
		case 5:  Model=TEXT("Pentium-class processor");    break;
		case 6:  Model=TEXT("PentiumPro-class processor"); break;
		case 7:  Model=TEXT("P7-class processor");         break;
		default: Model=TEXT("Unknown processor");          break;
		}
		if( (D & 0x00008000) ) {strcat( FeatStr, (" CMov") ); GIsPentiumPro=1; }
		if( (D & 0x00000001) ) {strcat( FeatStr, (" FPU") );}
		if( (D & 0x00000010) ) {strcat( FeatStr, (" RDTSC") );}
		if( (D & 0x00000040) ) {strcat( FeatStr, (" PAE") );}
		//if( (D & 0x00800000) && !ParseParam(appCmdLine(),TEXT("NOMMX")) ) {appStrcat( FeatStr, TEXT(" MMX") ); GIsMMX=1;}
		//if( (D & 0x02000000) && !ParseParam(appCmdLine(),TEXT("NOSSE")) ) {appStrcat( FeatStr, TEXT(" SSE") ); GIsSSE=1;}


		// Print features.
		sprintf( szBuffer, "CPU Detected: %s (%s)\n", Model, Brand );
		OutputDebugString( szBuffer );
		// Print features.
		sprintf( szBuffer, "CPU Features:%s\n", FeatStr );
		OutputDebugString( szBuffer );
	}
	catch( ... )
	{
		//debugf( NAME_Init, TEXT("Couldn't detect CPU: Probably 486 or non-Intel processor") );
	}

	//ÆÀ¶¨
	DWORD dwMemory = GetPhysicalMemory();	
	DWORD dwMemoryM = dwMemory/(1024*1024);
	if( dwMemoryM < 256 )
	{
		MemoryLvl = eMemory_Low;
	}
	else
	{
		MemoryLvl =  eMemory_High;
	}

	unguard;
}


