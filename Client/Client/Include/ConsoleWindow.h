#pragma once
#include <fcntl.h>

class CustomConsole
{
public:
    static void RedirectIoToConsole()
    {
        AllocConsole();

		// 去除MFC依赖后，这行编译不过，暂时去掉，QL，2009/06/02
        //ShowWindow(GetConsoleWindow(), SW_SHOWMAXIMIZED);

        // set the screen buffer to be big enough to let us scroll text
        CONSOLE_SCREEN_BUFFER_INFO coninfo;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &coninfo);

        coninfo.dwSize.Y = 4096; // MAX_CONSOLE_LINE
        SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), coninfo.dwSize);

        // redirect unbuffered STDOUT to the console
        intptr_t lStdHandle = (intptr_t)GetStdHandle(STD_OUTPUT_HANDLE);
        int hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
        *stdout = *_fdopen(hConHandle, "w");
        setvbuf(stdout, NULL, _IONBF, 0);

        // redirect unbuffered STDIN to the console
        lStdHandle = (intptr_t)GetStdHandle(STD_INPUT_HANDLE);
        hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
        *stdin = *_fdopen(hConHandle, "r");
        setvbuf(stdin, NULL, _IONBF, 0);

        // redirect unbuffered STDERR to the console
        lStdHandle = (intptr_t)GetStdHandle(STD_ERROR_HANDLE);
        hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
        *stderr = *_fdopen(hConHandle, "w");
        setvbuf(stderr, NULL, _IONBF, 0);

        // make cout, wcout, cin, wcin, wcerr, cerr, wclog and clog 
        // point to console as well
        std::ios::sync_with_stdio();
    }
};
