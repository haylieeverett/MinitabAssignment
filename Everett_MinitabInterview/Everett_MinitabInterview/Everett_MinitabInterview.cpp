// Everett_MinitabInterview.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm> 
#include <istream>
#include <map>
#include <boost/algorithm/string.hpp>
using namespace std;

//An enum of the different types of sorts that the class can do.
enum SortType
{
    SORTTYPE_ERROR = 0,
    SORT_ALPHA,
    SORT_NUMERIC,
    SORT_BOTH
};

//An enum of the different types of sort orders that the class can do.
enum SortOrder
{
    SORTORDER_ERROR = 0,
    SORT_ASC,
    SORT_DESC
};

//Forward declarations
void SortNumbers(std::vector<double> &p_vNumVector, SortOrder p_uSortOrder);
void SortStrings(std::map<std::string, std::string> p_mStringMap, SortOrder p_uSortOrder);

//Main program that holds the majority of the code. The purpose of the program is to take in a file, parse the file, determine the type and then sort based off of the parameters passed in.

int main(int argc, char**argv)
{
    if (argc == 4) //Ensure there are the correct number of arguments being passed in.
    {  
        //Default values
        SortType uSortType = SortType::SORTTYPE_ERROR;
        SortOrder uSortOrder = SortOrder::SORTORDER_ERROR;

        std::string sFileName = argv[1];

        std::string sSortType = argv[2];
        bool bValidSortType = false;
        string sSortTypeLower = sSortType;
        boost::algorithm::to_lower(sSortTypeLower);

        //Compare the string to the expected values. Convert value read in to all lower case so the value is not case sensitive
        if (sSortTypeLower == "alpha")
        {
            uSortType = SortType::SORT_ALPHA;
            bValidSortType = true;
        }
        else if (sSortTypeLower == "numeric")
        {
            uSortType = SortType::SORT_NUMERIC;
            bValidSortType = true;
        }
        else if (sSortTypeLower == "both")
        {
            uSortType = SortType::SORT_BOTH;
            bValidSortType = true;
        }

        std::string sSortOrder = argv[3];
        bool bValidSortOrder = false;
        string sSortOrderLower = sSortOrder;
        boost::algorithm::to_lower(sSortOrderLower);

        //Compare the string to the expected values. Convert value read in to all lower case so the value is not case sensitive
        if (sSortOrderLower == "ascending")
        {
            uSortOrder = SortOrder::SORT_ASC;
            bValidSortOrder = true;
        }
        else if (sSortOrderLower == "descending")
        {
            uSortOrder = SortOrder::SORT_DESC;
            bValidSortOrder = true;
        }

        //Only start sorting if the arguments passed in are valid. 
        if (bValidSortOrder && bValidSortType)
        {
            std::ifstream readFile; //Helps to read in the contents of the file
            std::string sFileString; //Will holds the contents of each value when parsed.
            std::map<std::string, std::string> mStringMap; // A map to hold the value with no leading quotes as a key to its original value.
            std::vector<double> vDoubleValues; // A vector to hold the doubles found in the file.

            readFile.open(sFileName, std::ios::in);

            //Read file and parse
            if (readFile.is_open())
            {
                while (std::getline(readFile, sFileString))
                {
                    //Throw away first " and last " if there                                                                                    
                    if (boost::starts_with(sFileString, "\""))
                        sFileString.erase(0, 1);
                    if (boost::ends_with(sFileString, "\""))
                        sFileString.erase(0, 1);

                    std::stringstream streamFile(sFileString);
                    std::string sStringRead;
                    while (std::getline(streamFile, sStringRead, ','))
                    {
                        double dVal;
                        std::istringstream in(sStringRead); 
                        if (in >> dVal && in.eof())
                        {
                            //Valid double
                            vDoubleValues.push_back(dVal);
                        }
                        else
                        {
                            //Only a string 
                            std::string sKeyValue = sStringRead;
                            boost::trim(sKeyValue);
                            if (boost::starts_with(sKeyValue, "\'")) //Erase the first single quote to help with sorting
                            {
                                sKeyValue.erase(0, 1);
                            }
                            mStringMap.insert(std::pair<std::string, std::string>(sKeyValue, sStringRead));
                        }
                    }
                }
            }

            switch (uSortType)
            {
                case SortType::SORT_ALPHA:
                    SortStrings(mStringMap, uSortOrder);
                    break;

                case SortType::SORT_NUMERIC:
                    SortNumbers(vDoubleValues, uSortOrder);
                    break;

                case SortType::SORT_BOTH:
                    if (uSortOrder == SortOrder::SORT_ASC)
                    {
                        //Sorting by ascending will have the numbers printed first and then the strings. Call the functions in that order.
                        SortNumbers(vDoubleValues, uSortOrder);
                        if (mStringMap.size() > 0)
                        {
                            if(vDoubleValues.size() > 0)
                                cout << ", "; //Adds the extra , in between the two list types
                            SortStrings(mStringMap, uSortOrder);
                        }
                    }
                    else if (uSortOrder == SortOrder::SORT_DESC)
                    {
                        //Sorting by descending will have the strings printed first and then the numbers. Call the functions in that order.
                        SortStrings(mStringMap, uSortOrder);
                        if (vDoubleValues.size() > 0)
                        {
                            if( mStringMap.size() > 0)
                                cout << ", "; //Adds the extra , in between the two list types
                            SortNumbers(vDoubleValues, uSortOrder);
                        }
                    }
                    break;

                default:
                    cout << "Error reading sort type. Please try again";
            }

        }
        else
        {
            cout << "Error. Please enter valid inputs";
        }                                                                          
    }
    else
    {
    cout << "Error. Invalid number of arguments passed in. Please pass in the file name, sort type, and sort order in that order.";
    }
}

/*
* If sorting by ascending call the sort function as normal, else if by descending add additional parameter to
* do the reverse sort.                      
*/
void SortNumbers(std::vector<double>& p_vNumVector, SortOrder p_uSortOrder)
{
    if (p_uSortOrder == SortOrder::SORT_DESC)
        std::sort(p_vNumVector.begin(), p_vNumVector.end(), std::greater<double>());
    else
        std::sort(p_vNumVector.begin(), p_vNumVector.end());

    for (std::vector<double>::const_iterator it = p_vNumVector.begin(); it != p_vNumVector.end(); ++it) {
        std::cout << *it;
        if (it + 1 != p_vNumVector.end())
            cout << ", ";
    }
}

/*
* Prints out the map depending on the sort order. If sort by ascending print the map out in the normal order. If sorting
* descending, iterate over the map backwards.
*/
void SortStrings(std::map<std::string, std::string> p_mStringMap, SortOrder p_uSortOrder)
{
    if (p_uSortOrder == SortOrder::SORT_ASC)
    {
        std::map<std::string, std::string>::iterator it;
        // Iterate over the map.
        for (it = p_mStringMap.begin(); it != p_mStringMap.end(); ++it)
        {
            std::cout << it->second;                                                           
            if (std::next(it,1) != p_mStringMap.end())
                cout << ", ";
        }
    }  
    else
    {
        std::map<std::string, std::string>::reverse_iterator it;
        // Iterate over the map in reverse order.
        for (it = p_mStringMap.rbegin(); it != p_mStringMap.rend(); ++it)
        {
            std::cout << it->second; 
            if (std::next(it,1) != p_mStringMap.rend())
                cout << ", ";
        }
    }
}