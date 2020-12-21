// project3.cpp

#include <iostream>
#include <sstream>
#include <string>

#include "kAVLTree.h"

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: ./project3.out \"<sequence of queries>\"" << std::endl;
        return 1;
    }

    std::string queryStr = argv[1];
    std::vector<std::string> queryVect;
    std::string delim = ", ";

    std::size_t start = 0;
    std::size_t end = 0;
    while (start < queryStr.size() )
    {
        end = queryStr.find(delim, start);  // Set end position to start of next delimiter
        if (end == std::string::npos)
        {   // Final token, so break
            break;
        }

        queryVect.push_back(queryStr.substr(start, end - start) );  // Push-back the token from start to end
        start = end + delim.size();
    }

    queryVect.push_back(queryStr.substr(start) );  // Push-back the final token

    // std::cout << "Printing query vect" << std::endl;
    // for (auto e : queryVect)
    // {
    //     std::cout << e << std::endl;
    // }

    kAVLTree t(std::stoi(queryVect.at(0)) );   // Init. tree with first value

    for (int i = 1; i < queryVect.size(); i++)
    {
        std::string qry = queryVect.at(i);

        std::vector<std::string> qryParam;
        std::stringstream strm(qry);
        std::string paramStr = "";
        while (std::getline(strm, paramStr, ' ') )
        {
            qryParam.push_back(paramStr);
        }

        // for (auto e : qryParam)
        // {
        //     std::cout << e << std::endl;
        // }

        std::string qryType = qryParam.at(0);

        if (qryType == "search")
        {
            t.printSearch(std::stoi(qryParam[1]), std::stoi(qryParam[2]) );
        }

        else if (qryType == "approx_search")
        {
            t.printApproxSearch(std::stoi(qryParam[1]), std::stoi(qryParam[2]) );
        }

        else if (qryType == "insert")
        {
            t.printInsert(std::stoi(qryParam[1]), std::stoi(qryParam[2]) );
        }

        else if (qryType == "delete")
        {
            t.printDelete(std::stoi(qryParam[1]), std::stoi(qryParam[2]) );
        }

        else if (qryType == "in_order")
        {
            t.printInOrder();
        }

        else if (qryType == "pre_order")
        {
            t.printPreOrder();
        }
    }

    return 0;
}