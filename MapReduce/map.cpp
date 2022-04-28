// map.cpp
// Lyndsay LaBarge
// CSE687 Object Oriented Design
// Project 1
// April 28, 2022
// 
// Map class implementation
#include <iostream>
#include <string>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>
#include "map.h"

Map::Map(const boost::filesystem::path& directory) {
	output_directory_ = directory;
	output_stream_ = new boost::filesystem::ofstream{};
	output_stream_->rdbuf()->pubsetbuf(&output_buffer_.front(), 
									output_buffer_.size());
}

// Map object must be deleted or go out of scope
// and be destroyed on the stack, otherwise the output
// file will not be able to be read until the Map
// object relinquishes it .
Map::~Map()
{
	// Flush & close the file stream
	if (output_stream_->is_open()) {
		output_stream_->close();
	}
	delete output_stream_;
}

// Given data from a file, writes to a separate temporary file that 
// holds (word, 1) for each occurrence of every word.
// If the map operation failed (could not write to the file), 
// returns -1.
// If the map operation succeeded, returns 0.
int Map::map(const std::string& key, const std::string& value)
{
	int export_success;
	boost::tokenizer<> tok(value);
	// Tokenize text
	for (boost::tokenizer<>::iterator beg = tok.begin(); 
		beg != tok.end(); 
		++beg) {
		// Normalize text (remove capitalization)
		std::string token = *beg;
		boost::algorithm::to_lower(token);
		// Export token
		export_success = exportToDisk(key, token, 1);

		// Export failed
		if (export_success != 0) {
			return -1;
		}
	}
	// Map success
	return 0;
}

// Gets the path of the most recently written to output file
boost::filesystem::path Map::getOutputPath()
{
	return output_path_;
}

// Gets the output directory path
boost::filesystem::path Map::getOutputDirectory()
{
	return output_directory_;
}

// Exports word, value pair to disk
// If the export fails, returns -1. 
// If the export succeeds, returns 0.
int Map::exportToDisk(const std::string& filename, 
					  const std::string& key, 
					  int value)
{
	boost::filesystem::path filePath = boost::filesystem::path { 
		output_directory_.string() + "\\" + filename 
	};

	// Started to process a new file
	if (output_path_.compare(filePath) != 0) {
		// Flush & close the old file stream and start a new one
		if (output_stream_->is_open()) {
			output_stream_->close();
		}
		output_path_ = filePath;
		output_stream_->open(output_path_);
	}

	// There is a problem with the output file
	if (output_stream_->fail()) {
		return -1;
	}
	else {
		// Write to the file stream 
		*(output_stream_) << "(" + key + ", " + std::to_string(value) << ")\n";
		return 0;
	}
}
