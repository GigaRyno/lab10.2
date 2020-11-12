/**
 * @file earth_utils.cpp
 * @author Ryan LaVigne
 * @brief lab 10.2
 * @date 2020-11-11
 */

#include <earth_utils.h>
#include <sstream>

using namespace std;

int processCSV(std::ifstream &inFile, std::string kmlFileName)
{
   string country, capital, lat, lon, strLine;
   stringstream s_stream;
   int recordCount = 0;

   if (inFile)
   {
      ofstream kmlFile(kmlFileName);
      kmlFile << KML_OPEN;

      getline(inFile, strLine);
      while (getline(inFile, strLine))
      {
         s_stream.str(strLine);
         getline(s_stream, country, ',');
         getline(s_stream, capital, ',');
         getline(s_stream, lat, ',');
         getline(s_stream, lon, ',');

         writePlacemark(kmlFile, capital + ", " + country, lat, lon);
         recordCount++;
      }
      kmlFile << KML_CLOSE;
   }
   return recordCount;
}

void writePlacemark(std::ofstream &kmlFile, std::string name, std::string latitude, std::string longitude)
{

   kmlFile << PLACEMARK_OPEN
           << NAME_OPEN << name << NAME_CLOSE
           << POINT_COORD_OPEN << longitude << "," << latitude << POINT_COORD_CLOSE
           << PLACEMARK_CLOSE;
}