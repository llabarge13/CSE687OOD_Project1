// test.cpp
// Lyndsay LaBarge
// CSE687 Object Oriented Design
// Project 1
// April 28, 2022
// 
// Test run for basic MapReduce process
#include <string>
#include <iostream>
#include <boost/filesystem.hpp>
#include "map.h"
#include "sorting.h"
#include "reduce.h"

int main() {
    // Input, temp, output directories
    boost::filesystem::path temp_path = boost::filesystem::path{ ".\\temp" };
    boost::filesystem::path input_path = boost::filesystem::path{ ".\\shakespeare" };
    boost::filesystem::path output_path = boost::filesystem::path{ ".\\output" };

    Map* map = new Map(temp_path);

    std::string line;
    int success;
    boost::filesystem::ifstream input_stream;
    boost::filesystem::directory_iterator end_itr;


    // Run map on all the files in the input directory
    for (boost::filesystem::directory_iterator itr(input_path); 
        itr != end_itr; 
        ++itr) {
        input_stream.open(itr->path());

        std::cout << "Running map on " << itr->path().filename().string();
        std::cout << "..." << std::endl;
        while(getline(input_stream, line)) {
            success = map->map(itr->path().filename().string(), line);
            
            if (success != 0) {
                std::cout << "Failed to process " << itr->path().filename().string() 
                    << " with map." << std::endl;
                exit(1);
            }
        }
        input_stream.close();
    }
    delete map;

    // Sort all the intermediate files
    Sorting sorter = Sorting();
    for (boost::filesystem::directory_iterator itr(temp_path); itr != end_itr; ++itr) {
        std::cout << "Running sort on " << itr->path().filename().string() 
            << "..." << std::endl;
        success = sorter.sort(itr->path());

        if (success != 0) {
            std::cout << "Failed to process " << itr->path().filename().string() 
                << " with sort." << std::endl;
            exit(1);
        }
    }

    // Run reduce
    const boost::container::map<std::string, 
    std::vector<int>>& aggregate_data = sorter.getAggregateData();
    Reduce* reducer = new Reduce(output_path);
    std::cout << "Running reducer.." << std::endl;
    for (auto const& pair : aggregate_data) {
        success = reducer->reduce(pair.first, pair.second);

        if (success != 0) {
            std::cout << "Failed to export to " << reducer->getOutputPath().string() 
                << " with reduce." << std::endl;
            exit(1);
        }
    }
    delete reducer;
}
