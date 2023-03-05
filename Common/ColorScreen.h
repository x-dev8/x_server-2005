#ifndef  __COMMON_COLORSCREEN_H__
#define  __COMMON_COLORSCREEN_H__

#pragma once

#include "GlobalDef.h"

//std::cout; EDefColor : only( COLOR_RED COLOR_GREEN COLOR_YELLOW)
#define COLOR_MESSAGE ColoredPrintf
// Returns the character attribute for the given color.
static WORD GetColorAttribute(EDefColor color) {
    switch (color) {
    case COLOR_RED:    return FOREGROUND_RED;
    case COLOR_GREEN:  return FOREGROUND_GREEN;
    case COLOR_YELLOW: return FOREGROUND_RED | FOREGROUND_GREEN;
    default:           return 0;
    }
}

static void ColoredPrintf(EDefColor color, const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);

    const HANDLE stdout_handle = GetStdHandle(STD_OUTPUT_HANDLE);

    // Gets the current text color.
    CONSOLE_SCREEN_BUFFER_INFO buffer_info;
    GetConsoleScreenBufferInfo(stdout_handle, &buffer_info);
    const WORD old_color_attrs = buffer_info.wAttributes;

    SetConsoleTextAttribute(stdout_handle,
        GetColorAttribute(color) | FOREGROUND_INTENSITY);
    vprintf(fmt, args);

    // Restores the text color.
    SetConsoleTextAttribute(stdout_handle, old_color_attrs);
    va_end(args);
}

#endif