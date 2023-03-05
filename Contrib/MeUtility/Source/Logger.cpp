#include "Logger.h"

vector<string> Logger::logStrings;
string         Logger::logPath; 

void Logger::initialize(const char* logfilename)
{
  //logPath     = !logfilename ? ".\\Log\\Log.txt" : logfilename;
  //ofstream logFile(logPath.c_str());
  //logFile.close();
}

void Logger::flush()
{
  //if(!logPath.size() || !logStrings.size())
  //  return;
 
  //ofstream logFile(logPath.c_str(), ios::app);

  //for(size_t t = 0; t < logStrings.size(); t++)
  //  logFile << logStrings[t];

  //logStrings.clear();
  //logFile.close();
}

void Logger::writeImmidiateInfoLog(const string &info)
{
  //if(info.size())
  //{
  //  logStrings.push_back(string("<+>") + info + "\n");
  //  flush();
  //}
}

void Logger::writeInfoLog(const string &info)
{
  //logStrings.push_back(string("<Info>") + info + "</Info>\n");
  //if(logStrings.size() >= 10)
  //  flush();
}

bool Logger::writeErrorLog(const string &info)
{
  //if(info.size())
  //{
  //  logStrings.push_back(string("<!>") + info + "\n");
  //  flush();
  //}
  return false;
}

void Logger::writeFatalErrorLog(const string &info)
{
  //if(info.size())
  //{
  // logStrings.push_back(string("<X>") + info + "\n");

  //  flush();
  //}
  //exit(1);
}