// map.h
// Lyndsay LaBarge
// CSE687 Object Oriented Design
// Project 1
// April 28, 2022
// 
// Map class definition
#include <string>
#include <array>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#pragma once

// Performs map operation on text files
// Given data from a file, outputs a separate temporary file that 
// holds (word, 1) for each occurrence of every word.
// Example:
//	std::string text = "The quick brown fox jumps over the lazy dog.";
//	std::string file = "test.txt";
//	Map m = Map(directory);
//	int success = m.map(file, text);
class Map
{

public:
	Map(const boost::filesystem::path& directory);

	// Map object must be deleted or go out of scope
	// and be destroyed on the stack, otherwise the output
	// file will not be able to be read until the Map
	// object relinquishes it .
	~Map();

	// Given data from a file, writes to a separate temporary file that 
	// holds (word, 1) for each occurrence of every word.
	// If the map operation failed (could not write to the file), 
	// returns -1.
	// If the map operation succeeded, returns 0.
	int map(const std::string& key, const std::string& value);

	// Gets the path of the most recently written to output file  
	boost::filesystem::path getOutputPath();
	// Gets the output directory path 
	boost::filesystem::path getOutputDirectory();

private:
	boost::filesystem::path output_directory_;
	boost::filesystem::path output_path_;
	boost::filesystem::ofstream* output_stream_;
	std::array<char, 2048> output_buffer_;

	// Exports word, value pair to disk
	// If the export fails, returns -1. 
	// If the export succeeds, returns 0.
	int exportToDisk(const std::string& filename, 
					const std::string& key, 
					int value);
};
