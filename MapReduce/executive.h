// executive.h
// Todd Hricik
// CSE687 Object Oriented Design
// Project 1
// April 28, 2022
// 
// Executive class definition
#include <string>
#include "workflow.h"
#pragma once

class Executive
{
	public:
		// Public member functions
		Executive(std::string target_dir, std::string intermediate_dir, std::string out_dir);		// Constructor takes input directory, dir for intermediate files and output directory as args
		~Executive();
		void run();																				// Calls workflow to run

	private:
		// Private data members
		Workflow* workflow_;
};
