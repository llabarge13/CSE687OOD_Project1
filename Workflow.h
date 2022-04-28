#pragma once
#include "boost\filesystem.hpp"

#include "map.h"
#include "sorting.h"
#include "reduce.h"

class Workflow
{
	public:
		// Public member functions
		Workflow(std::string targetDir, std::string intermediateDir, std::string outDir);		// constructor
		~Workflow();																			// destructor
		boost::filesystem::path getTargetDir();													// directory containing files to be fed to Map
		boost::filesystem::path getIntermediateDir();											// directory containing intermediate files from Map
		boost::filesystem::path getOutDir();													// directory containing output file(s) from reduce
		void run();																				// Runs the map sort reduce workflow

		// Public data members

	private:
		// Private member functions


		// Private data members
		boost::filesystem::path target_dir;
		boost::filesystem::path intermediate_dir;
		boost::filesystem::path out_dir;

		Map* map;																				// Map is aggregated by Workflow
		Sorting* sorter;																		// Sorting is aggregated by Workflow
		Reduce* reduce;																			// Reduce is aggregated by Workflow
};

