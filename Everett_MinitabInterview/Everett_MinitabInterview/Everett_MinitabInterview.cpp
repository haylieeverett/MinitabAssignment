// Everett_MinitabInterview.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm> 
#include <istream>
#include <boost/algorithm/string.hpp>
using namespace std;

enum SortType
{
    SORTTYPE_ERROR = 0,
    SORT_ALPHA,
    SORT_NUMERIC,
    SORT_BOTH
};
SortType uSortType = SortType::SORTTYPE_ERROR;

enum SortOrder
{
    SORTORDER_ERROR = 0,
    SORT_ASC,
    SORT_DESC
};

void SortNumbers(std::vector<double> &p_vNumVector, SortOrder p_uSortOrder);
void SortStrings(std::vector<std::string>& p_vStringVector, SortOrder p_uSortOrder);

int main()
{
    
    SortType uSortType= SortType::SORTTYPE_ERROR;

    
    SortOrder uSortOrder = SortOrder::SORTORDER_ERROR;

    std::cout << "Please enter the file to read from \n";
    std::string sFileName;
    std::cin >> sFileName;
    
    std::cout << "Please enter the type to sort on: alpha, numeric or both \n";
    std::string sSortType;
    std::cin >> sSortType;
    bool bValidSortType = false;
    string sSortTypeLower = sSortType;
    boost::algorithm::to_lower(sSortTypeLower);
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

    std::cout << "Please enter the order of sorting: ascending or descending \n";
    std::string sSortOrder;
    std::cin >> sSortOrder;
    bool bValidSortOrder = false;
    string sSortOrderLower = sSortOrder;
    boost::algorithm::to_lower(sSortOrderLower);
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

    if (bValidSortOrder && bValidSortType)
    {
        std::ifstream readFile;
        std::string sFileString;
        std::string sSkip;
        std::vector<std::string> vStringValues;
        std::vector<double> vDoubleValues;

        readFile.open(sFileName, std::ios::in);

        //Read file and parse
        if (readFile.is_open())
        {
            while (std::getline(std::getline(readFile, sSkip, '"'), sFileString, '"')) //Throw away first " and then read up until right before the next "
            {
                std::stringstream streamFile(sFileString);
                std::string sStringRead;
                while (std::getline(streamFile, sStringRead, ','))
                {
                    double dVal;
                    std::istringstream in(sStringRead);
                    if (in >> dVal && in.eof())
                    {
                        //Valid double
                        std::cout << "Valid number";
                        vDoubleValues.push_back(dVal);
                    }
                    else
                    {
                        //Only a string 
                        std::cout << "Not a number";
                        vStringValues.push_back(sStringRead);
                    }

                    std::cout << sStringRead << "\n";
                }
            }
        }

        switch (uSortType)
        {
            case SortType::SORT_ALPHA:
                SortStrings(vStringValues, uSortOrder);
                break;

            case SortType::SORT_NUMERIC:
                SortNumbers(vDoubleValues, uSortOrder);
                break;

            case SortType::SORT_BOTH:
                if (uSortOrder == SortOrder::SORT_ASC)
                {
                    SortNumbers(vDoubleValues, uSortOrder);
                    SortStrings(vStringValues, uSortOrder);
                }
                else if(uSortOrder == SortOrder::SORT_DESC)
                {
                    SortStrings(vStringValues, uSortOrder);
                    SortNumbers(vDoubleValues, uSortOrder);
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


void SortNumbers(std::vector<double>& p_vNumVector, SortOrder p_uSortOrder)
{
    if (p_uSortOrder == SortOrder::SORT_DESC)
        std::sort(p_vNumVector.begin(), p_vNumVector.end(), std::greater<double>());
    else
        std::sort(p_vNumVector.begin(), p_vNumVector.end());

    for (std::vector<double>::const_iterator it = p_vNumVector.begin(); it != p_vNumVector.end(); ++it) {
        std::cout << *it << " ";
    }
}

void SortStrings(std::vector<std::string>& p_vStringVector, SortOrder p_uSortOrder)
{
    if (p_uSortOrder == SortOrder::SORT_DESC)
        std::sort(p_vStringVector.begin(), p_vStringVector.end(), std::greater<std::string>());
    else
        std::sort(p_vStringVector.begin(), p_vStringVector.end());

    for (std::vector<std::string>::const_iterator it = p_vStringVector.begin(); it != p_vStringVector.end(); ++it) {
        std::cout << *it << " ";
    }
}