// reduce.h
// Lyndsay LaBarge
// CSE687 Object Oriented Design
// Project 1
// April 28, 2022
// 
// Reduce class definition
#include <vector>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#pragma once

// Performs reduce operation on intermediate results.
// Given sorted data from the intermediate file, reduces the results 
// by aggregating the values and output result to a file.
// e.g. (word, [1, 1]) -> (word, 2)
// Example:
//		boost::filesystem::path ouput_directory = boost::filesystem::path{ ".\\tem" };
//		boost::container::map<std::string, std::vector<int>> map_data;
//		std::vector<int> one{ 1 };
//		std::vector<int> two{ 1, 1 };
//		map_data["the"] = two;
//		map_data["quick"] = one;
//		map_data["brown"] = one;
//		Reduce reducer = Reduce(ouput_directory);
//		for (auto const& pair : map_data) {
//		    success = reducer->reduce(pair.first, pair.second);
//		}
class Reduce
{

public:
	Reduce(const boost::filesystem::path& directory);

	// Reduce object must be deleted or go out of scope
	// and be destroyed on the stack, otherwise the output
	// file will not be able to be read until the Reduce object
	// class relinquishes it .
	~Reduce();

	// Performs reduce operation on intermediate results.
	// Given sorted data from the intermediate file, reduces the results 
	// by aggregating the values and output result to a file.
	// e.g. (word, [1, 1]) -> (word, 2)
	// If reduce operation fails (cannot write to file), returns -1. 
	// If reduce operation succeeds, returns 0.
	int reduce(const std::string& key, const std::vector<int>& values);

	// Gets the path of the output file
	boost::filesystem::path getOutputPath();

	// Gets the path of the output directory
	boost::filesystem::path getOutputDirectory();

private:
	boost::filesystem::path output_directory_;
	boost::filesystem::path output_path_;
	boost::filesystem::ofstream* output_stream_;

	// Exports word, value pair to disk
	// If the export fails, returns -1. 
	// If the export succeeds, returns 0.
	int exportToDisk(const std::string& key, int value);
};
