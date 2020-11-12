/**
 * @file logger.cpp
 * @author Ryan LaVigne
 * @brief lab 10.2
 * @date 2020-11-11
 */


#include <pwd.h>
#include <libgen.h>
#include <logger.h>
#include <unistd.h>

using namespace std;


bool log(string msg, string programName, ofstream &logFile)
{
   string timeStr;
   time_t logTime = time(0);
   timeStr = ctime(&logTime);
   pid_t pid = getpid();
   char *hostName = new char[MAX_HOSTNAME_LEN];

   gethostname(hostName, MAX_HOSTNAME_LEN);

   int tmp = timeStr.size();
   if (tmp > 0)
      timeStr[tmp - 1] = 32;

   if (logFile)
   {
      logFile << timeStr << hostName << ' ' << programName << "[" << pid << "]: " << msg << endl;

      delete[] hostName;
      return true;
   }
   else
   {

      delete[] hostName;
      return false;
   }


}