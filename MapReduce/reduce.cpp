// reduce.cpp
// Lyndsay LaBarge
// CSE687 Object Oriented Design
// Project 1
// April 28, 2022
// 
// Reduce class implementation
#include <execution>
#include <iostream>
#include <boost/random.hpp>
#include "reduce.h"

Reduce::Reduce(const boost::filesystem::path& directory)
{
	output_directory_ = directory;
	output_path_ = boost::filesystem::path { 
		output_directory_.string() + "\\reduce.txt"
	};
	output_stream_ = new boost::filesystem::ofstream{output_path_};
}

// Reduce object must be deleted or go out of scope
// and be destroyed on the stack, otherwise the output
// file will not be able to be read until the Reduce object
// class relinquishes it .
Reduce::~Reduce()
{
	// Flush & close the file stream
	if (output_stream_->is_open()) {
		output_stream_->close();
	}
	delete output_stream_;
}

// Performs reduce operation on intermediate results.
// Given sorted data from the intermediate file, reduces the results 
// by aggregating the values and output result to a file.
// e.g. (word, [1, 1]) -> (word, 2)
// If reduce operation fails (cannot write to file), returns -1. 
// If reduce operation succeeds, returns 0.
int Reduce::reduce(const std::string& key, const std::vector<int>& values)
{
	// Run reduce
	int result = std::reduce(std::execution::seq, values.begin(), values.end());
	// Write reduced value
	return exportToDisk(key, result);
}

// Gets the path of the output file
boost::filesystem::path Reduce::getOutputPath()
{
	return output_path_;
}

// Gets the path of the output directory
boost::filesystem::path Reduce::getOutputDirectory()
{
	return output_directory_;
}

// Exports word, value pair to disk
// If the export fails, returns -1. 
// If the export succeeds, returns 0.
int Reduce::exportToDisk(const std::string& key, int value)
{
	if (!output_stream_->is_open()) {
		output_stream_->open(output_path_, std::ios_base::app);
	}

	if (!output_stream_->fail()) {
		// Write result to disk 
		*(output_stream_) << "(" + key + ", " + std::to_string(value) << ")\n";
		output_stream_->close();
		return 0;
	}
	else {
		return -1;
	}
}
