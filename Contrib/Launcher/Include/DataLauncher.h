#ifndef _DATA_LAUNCHER_H_
#define _DATA_LAUNCHER_H_
#ifdef DATA_LAUNCHER
#define fopen swFileOpen
#define fopen_s swFileOpen_s
#ifdef fseek
#undef fseek
#endif
#define fseek swFileSeek
#ifdef ftell
#undef ftell
#endif
#define ftell swGetFileSize
#ifdef rewind
#undef rewind
#endif
#define rewind swRewind
#define fclose swFileClose
#ifdef FindFirstFile
#undef FindFirstFile
#endif
#define FindFirstFile swFindFirstFile

#ifdef FindNextFile
#undef FindNextFile
#endif
#define FindNextFile swFindNextFile

#ifdef FindClose
#undef FindClose
#endif
#define FindClose swFindClose
extern FILE *swFileOpen( 
						const char *filename,
						const char *mode 
						);
extern errno_t swFileOpen_s(FILE** pFile,
							const char *filename,
							const char *mode 
							);
extern int swFileSeek( FILE * _File,  long _Offset,  int _Origin);
extern long swGetFileSize(FILE* pFile);
extern void swRewind(FILE* pFile);
extern int swFileClose( 
					   FILE *stream 
					   );
void* swFindFirstFile(  const char * lpFileName, void* lpFindFileData );
bool swFindNextFile( void* hFindFile,  void* lpFindFileData );
bool swFindClose( void* pHandle);
extern bool g_DirectReadInPackage;

void SetFlushTmpToDisk(bool bValue);

bool swIsFileExist(const char* lpFileName);
#endif


#endif
