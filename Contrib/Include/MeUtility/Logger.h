/********************************************************************
    Filename:    Logger.h
    MaintenanceMan Mail: debugcommand@hotmail.com
*********************************************************************/

#ifndef __UTILITY_LOGGER_H__
#define __UTILITY_LOGGER_H__

#include "XMLParser.h"
#include "IOXMLObject.h"

#define deleteObject(A){ if(A){ delete   A; A = NULL; } }
#define deleteArray(A) { if(A){ delete[] A; A = NULL; } }

#define MAX_TEX_UNITS 8

class Logger
{
  public:
    static void writeImmidiateInfoLog(const string &info);
    static void writeFatalErrorLog(const string &logString);
    static bool writeErrorLog(const string &error);
    static void writeInfoLog(const string &info);
    static void initialize(const char* logfilename = NULL);
    static void flush();

  private:
    static vector<string> logStrings;
    static string         logPath; 
};


#define LOGINFO(str) Logger::writeInfoLog(str); Logger::flush();
#define LOGERROR(str) Logger::writeErrorLog( str ); Logger::flush();
#define LOGSAVE			

#endif // __UTILITY_LOGGER_H__
