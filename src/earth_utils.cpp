/**
 * @file earth_utils.cpp
 * @author Ryan LaVigne
 * @brief lab 10.2
 * @date 2020-11-11
 */

#include <earth_utils.h>
#include <sstream>

using namespace std;

const std::string KML_OPEN = "<?xml version=\"1.o\" encoding=\"UTF-8\"?>\n"
                              "<kml xmlns=\"http://www.opengis.net/kml/2.2\" xmlns:gx=\"http://www.google.com/kml/ext/2.2\" xmlns:kml=\"http://www.opengis.net/kml/2.2\" xmlns:atom=\"http://www.w3.org/2005/Atom\">\n"
                              "<Document>\n";

const std::string KML_CLOSE = "</Document>\n</kml>";

const std::string PLACEMARK_OPEN = "<Placemark>\n";
const std::string PLACEMARK_CLOSE = "</Placemark>\n";


const std::string NAME_OPEN = "<name>\n";
const std::string NAME_CLOSE = "</name>\n";

const std::string POINT_COORD_OPEN = "<Point><coordinates>";
const std::string POINT_COORD_CLOSE = "</coordinates></Point>\n";

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