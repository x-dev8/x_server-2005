#include "CommandLine.h"

CommandLine::CommandLine()
{
    szOptArg = NULL;
}

int CommandLine::GetOpt(int argc, char* const argv[], const char* szAgrOpts)
{
	static int optopt;
	static int sp = 1;
	register int c;
	register const char *cp;
    static int AgOptind = 1;

	if (sp == 1) 
    {
		if (AgOptind >= argc) 
        {
			return EOF;
		}
		if (argv[AgOptind][0] != '-' || argv[AgOptind][1] == '\0') {
			return EOF;
		}
	}
	else if (!strcmp(argv[AgOptind], "--")) 
    {	
		AgOptind++;
		return EOF;
	}

	optopt = c = argv[AgOptind][sp];
	
	if (c == ':' || (cp = strchr(szAgrOpts, c)) == NULL) 
    {
		fprintf(stderr, "%s: illegal option -- %c\n", argv[0], c);
		if (argv[AgOptind][++sp] == '\0') 
        {
			AgOptind++;
			sp = 1;
		}

		return '?';
	}

	if (*++cp == ':') 
    {
		if (argv[AgOptind][sp + 1] != '\0') 
        {
			szOptArg = &argv[AgOptind++][sp + 1];
		}
		else if (++AgOptind >= argc) 
        {
			fprintf(stderr,
					"%s: option requires an argument -- %c\n", argv[0], c);
			sp = 1;
			return '?';
		}
		else 
        {
			szOptArg = argv[AgOptind++];
		}
		sp = 1;
	}
	else 
    {
		if (argv[AgOptind][++sp] == '\0') 
        {
			sp = 1;
			AgOptind++;
		}
		szOptArg = NULL;
	}

	return c;
}

void CommandLine::PrintUsage(const char* szProgramName, const char* szExtraParms)
{
    if ( szExtraParms == NULL )
    {
        std::cout << "Usage: " << szProgramName << " [-f ConfigFile]" << std::endl;
    }
    else
    {
        std::cout << "Usage: " << szProgramName << " [-f ConfigFile]" << szExtraParms << std::endl;
    }
	
	std::cout << std::endl;
}

bool CommandLine::Parse(int argc, char *argv[], char* szConfigFileName, const char* szExtraParms)
{
	if (argc <= 1) 
    {
		std::cerr << "[Error] 启动无参数" << '!' << std::endl;
		return false;
	}

    bool bOk = false;
	int ch;
    while ((ch = GetOpt(argc, argv, "c:D")) != EOF) 
    {
		switch (ch) 
        {
			case 'c':
                {
                    sprintf_s( szConfigFileName, MAX_PATH, "Setting-%s.config", szOptArg );
                    bOk = true;
                }
                break;            
			default:
                {
                    break;
                }
		}
	}

    if ( !bOk )
    {
        std::cerr << "[Error] 启动无配置文件 = "<< szConfigFileName << '!' << std::endl;
        return false;
    }

	return true;
}

#define NEXT_ARG ((((*Argv)[2])==TEXT('\0'))?(--Argc,*++Argv):(*Argv)+2)

bool CommandLine::ParseEx( int argc, char *argv[], char* szConfigFileName )
{
    uint32 Argc = 0;
    LPTSTR * Argv;

    //转换命令行参数
#ifdef UNICODE
    Argv = CommandLineToArgvW(GetCommandLineW(), (int*)&Argc );
#else
    Argc = (uint32) argc;
    Argv = argv;
#endif

    bool bOk = false;
    //解析参数
    while( ++Argv, --Argc )
    {
        if( Argv[0][0] == TEXT('-') )
        {
            switch( Argv[0][1] )
            {
            case TEXT('c'):
                {
                    sprintf_s( szConfigFileName, MAX_PATH, "%s", NEXT_ARG );
                    bOk = true;
                }
            }
        }
    }

    return bOk;
}
