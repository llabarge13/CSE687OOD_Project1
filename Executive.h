#ifndef __EXECUTOR_H__
#define __EXECUTOR_H__

#include <string>
#include "Workflow.h"

class Executive
{
	public:
		// Public member functions
		Executive(std::string target_dir, std::string intermediate_dir, std::string out_dir);		// Constructor takes input directory, dir for intermediate files and output directory as args
		void run();																				// Calls workflow to run

	private:
		// Private data members
		Workflow* workflow;
};

#endif