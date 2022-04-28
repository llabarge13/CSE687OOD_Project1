#include <string>
#include <iostream>

#include <boost\filesystem.hpp>
#include <boost\log\trivial.hpp>

#include "Workflow.h"

// Constructor that creates boost::filesystem::path objects for the input directory, intermediate files directory and the output directory
Workflow::Workflow(std::string inputDir, std::string interDir, std::string outputDir)
{
	BOOST_LOG_TRIVIAL(debug) << "Debug in Workflow constructor: Entering constructor.";

	// Create boost path object for targetDir containing input files
	boost::filesystem::path input_dir(inputDir);

	// If path a is a directory, then assign the path to targetDir data member
	if (boost::filesystem::is_directory(input_dir))
	{
		this->target_dir = inputDir;
		BOOST_LOG_TRIVIAL(info) << "targetDir member has been set in Workflow constructor.";
	}

	// If path is not a directory then log the error, print error message
	if (!(boost::filesystem::is_directory(input_dir)))
	{
		// Path received in arg[1] of cmd line entry is not a directory error
		BOOST_LOG_TRIVIAL(fatal) << "Fatal in Workflow constructor: arg[1] is not a directory";
		exit(-1);
	}

	// Create boost path object for intermediateDir containing intermediate files
	boost::filesystem::path intermediate_dir(interDir);

	// If path b is a directory, then assign the path to intermediateDir data member
	if (boost::filesystem::is_directory(intermediate_dir))
	{
		this->intermediate_dir = interDir;
		BOOST_LOG_TRIVIAL(info) << "Info in Workflow constructor: intermediateDir member has been set in Workflow constructor.";
	}
	if (!(boost::filesystem::is_directory(intermediate_dir)))
	{
		// Path received in arg[2] of cmd line entry is not a directory error
		BOOST_LOG_TRIVIAL(warning) << "Warning in Workflow constructor: argv[2] is not a directory" << std::endl;
		BOOST_LOG_TRIVIAL(info) << "Info in Workflow constructor: Creating directory at " << interDir << " now...";

		// Create a directory for the intermediate files to go 
		if (!(boost::filesystem::create_directory(interDir)))
		{
			BOOST_LOG_TRIVIAL(fatal) << "Fatal in Workflow constructor: directory for intermediate files was not created.";
			exit(-1);
		}

		// Log that the directory was created 
		else
		{
			BOOST_LOG_TRIVIAL(info) << "Info in Workflow constructor: Directory for intermediate files created.";
		}
	}

	// Else log that the directory was created 
	else
	{
		BOOST_LOG_TRIVIAL(info) << "Info in Workflow constructor: Directory for intermediate files created.";
	}

	// Create boost path object for outputDir that will contain output files of workflow object
	boost::filesystem::path output_dir(outputDir);

	// If path c is a directory, then assign the path to outDir data member
	if (boost::filesystem::is_directory(output_dir))
	{
		this->out_dir = outputDir;
		BOOST_LOG_TRIVIAL(info) << "Info in Workflow constructor: outDir member has been set in Workflow constructor.";
	}
	if (!(boost::filesystem::is_directory(output_dir)))
	{
		// Path received in arg[3] of cmd line entry is not a directory error
		BOOST_LOG_TRIVIAL(warning) << "Warning in Workflow constructor: argv[3] is not a directory" << std::endl;
		BOOST_LOG_TRIVIAL(info) << "Info in Workflow constructor: Creating directory at " << interDir << " now...";
		// Create a directory for the output files to go 
		if (!(boost::filesystem::create_directory(outputDir)))
		{
			// std::cout << "Error creating directory: " << outputDir << std::endl;
			BOOST_LOG_TRIVIAL(fatal) << "Fatal in Workflow constructor: directory for output files was not created.";
			exit(-1);
		}
		// Log that the directory was 
		else
		{
			BOOST_LOG_TRIVIAL(info) << "Info in Workflow constructor: Directory for output files created.";
		}
	}

	// Else log that the directory was created 
	else
	{
		BOOST_LOG_TRIVIAL(info) << "Info in Workflow constructor: Directory for output files created.";
	}
	BOOST_LOG_TRIVIAL(debug) << "Debug in Workflow constructor: Construction is complete. Exiting constructor.";

	// Initialize map, sort and reduce objects to null pointers
	this->map = nullptr;
	this->sorter = nullptr;
	this->reduce = nullptr;
}

// Destructor
Workflow::~Workflow()
{
	/////////// Clean up //////////////
	boost::filesystem::remove_all(this->intermediate_dir);
	delete sorter;
	delete reduce;
}
// Getters and setters
boost::filesystem::path Workflow::getTargetDir()
{
	// This function returns the boost::filesystem::path object private data member targetDir
	return this->target_dir;
}
boost::filesystem::path Workflow::getIntermediateDir()
{
	// This function returns the boost::filesystem::path object private data member intermediateDir
	return this->intermediate_dir;
}
boost::filesystem::path Workflow::getOutDir()
{
	// This function returns the boost::filesystem::path object private data member outDir
	return this->out_dir;
}

// Run a workflow
void Workflow::run()
{

	boost::filesystem::ifstream input_stream;
	std::string key;
	std::string value;
	
	int success = 0;
	int line_count = 0;

	////////////// Map ////////////////////
	// For each file in the target directory which contains the files to be processed
	boost::filesystem::directory_iterator end_itr;
	for (boost::filesystem::directory_iterator itr(this->target_dir); itr != end_itr; ++itr)
	{
		if (boost::filesystem::is_regular_file(itr->path()))
		{
			// Set the key to the current filename
			key = itr->path().filename().string();

			// Open a file input stream for the text contained within the file
			input_stream.open(itr->path());
			
			// If ifstream did not open, log and break
			if (input_stream.fail() == 1)
			{
				BOOST_LOG_TRIVIAL(fatal) << "Fatal in Workflow run(): ifstream could not be opened for " << key;
				break;
			}
	
			// Instantiate Map object on heap
			this->map = new Map(this->intermediate_dir);

			// Process all lines of the file via map
			while (std::getline(input_stream, value))
			{
				// Increment the line count and call the map object to map the key and the value
				line_count++;
				success = this->map->map(itr->path().filename().string(), value);

				// If the map member function of the map object does not return zero (which is a success), then log and break
				if (success != 0)
				{
					BOOST_LOG_TRIVIAL(error) << "Error in Workflow run(): Map did not successfully process entire file at line " << line_count << " of " << key;
				}
			}
			
			// Log map process has completed for the current file
			BOOST_LOG_TRIVIAL(info) << "Info in Workflow run(): Map process completed for " << key;
			

			// Close the current input stream
			input_stream.close();

			// Delete the map object on the heap
			delete this->map;
			this->map = nullptr;

			// Reset the line counter to zer0
			line_count = 0;
		}
		else
		{
			// Log that a non regular file was encountered and ignored
			BOOST_LOG_TRIVIAL(info) << "Info in Workflow::run(): Non regular file: " << itr->path() << " detected and ignored.";
		}

	}
	/////////// SORT ///////////////////
	// Initialize a sorting object
	this->sorter = new Sorting();
	for (boost::filesystem::directory_iterator itr(this->intermediate_dir); itr != end_itr; ++itr)
	{
		BOOST_LOG_TRIVIAL(info) << "Running sort on " << itr->path().filename().string();
		success = this->sorter->sort(itr->path());

		if (success != 0) {
			BOOST_LOG_TRIVIAL(fatal) << "Failed to process " << itr->path().filename().string() << " with sort.";
			exit(1);
		}
	}

	/////////// REDUCE ////////////////
	const boost::container::map<std::string, std::vector<int>>& aggregateData = sorter->getAggregateData();
	reduce = new Reduce(this->out_dir);
	for (auto const& pair : aggregateData) {
		success = this->reduce->reduce(pair.first, pair.second);

		if (success != 0) {
			BOOST_LOG_TRIVIAL(fatal) << "Failed to export to " << reduce->getOutputPath().string() << " with reduce.";
			exit(1);
		}
	}

}
