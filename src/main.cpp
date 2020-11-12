/**
 * @file main.cpp
 * @author Ryan LaVigne
 * @brief lab 10.2
 * @date 2020-11-11
 *
 */


#include <iostream>
#include <libgen.h>
#include <pwd.h>
#include <unistd.h>
#include <logger.h>
#include <earth_utils.h>

using namespace std;

int main(int argc, char **argv)
{
   int opt;
   bool countFlag = false;
   bool logFlag = 0;
   string logValue;
   string kmlValue;
   bool optErr = true;

   while ((opt = getopt(argc, argv, "k:l:")) != EOF)
   {
      switch (opt)
      {
      case 'k':
         countFlag = true;
         kmlValue = optarg;
         break;

      case 'l':
         logFlag = true;
         logValue = optarg;
         break;

      default:
         optErr = true;
         break;
      }
   }


   if(countFlag && logFlag){
      cout << "flags set!\n";
      if (logValue.empty() || kmlValue.empty())
      {
         optErr = true;
         cout << "option arguments are not set\n";
      }
      else
      {
        ofstream flog;
        flog.open(logValue, ios_base::app);
        if(flog)
        {
          std::string programName = basename(argv[0]);
          std::string msg = "The kmlfile is: " + kmlValue + " and logfile is: " + logValue;
          log("The kmlfile is: " +kmlValue+"  and logfile is: " +logValue, programName, flog);
          optErr = false;
          flog.close();
          ifstream inFile;
          inFile.open(kmlValue);
          if(inFile)
          {
              int recordCount = processCSV(inFile, kmlValue + ".kml");
              inFile.close();
              if(recordCount)
              {
                   cout << recordCount << " records processed\n";
                  optErr = false;
              }
                else
                {
                    optErr = true;
                }
          }
          else
          {
              cout << "Couldn't Open" << logValue << endl;
              optErr = true;
          }
        }
      }
   } 
    else
   {
      cout << "error - arguments are not set!\n";
      optErr = true;
   }

   if(optErr)
   {
       return EXIT_FAILURE;
   }

   cout << "The kml file is: " << kmlValue << " and logfile is: " << logValue << endl;
   cout << "optErr: " << optErr << endl;

   return optErr;
}
