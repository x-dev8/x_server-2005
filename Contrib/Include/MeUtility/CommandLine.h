/********************************************************************
    Filename:    CommandLine.h
    MaintenanceMan Mail: debugcommand@hotmail.com
*********************************************************************/

#ifndef __COMMON_COMMANDLINE_H__
#define __COMMON_COMMANDLINE_H__

#pragma once

#include "MeRTLibs.h"

class CommandLine
{
public:
    CommandLine();

    virtual bool Parse( int argc, char *argv[], char* szConfigFileName, const char* szExtraParms = NULL);
    virtual bool ParseEx( int argc, char *argv[], char* szConfigFileName );

    virtual void PrintUsage( const char* szProgramName, const char* szExtraParms="" );

protected:
    int GetOpt(int argc, char* const argv[], const char* ag_opts);

private:
    char* szOptArg; // ²ÎÊýÄÚÈÝ
};

#endif // __COMMON_COMMANDLINE_H__
