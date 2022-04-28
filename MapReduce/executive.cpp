// executive.cpp
// Todd Hricik
// CSE687 Object Oriented Design
// Project 1
// April 28, 2022
// 
// Executive class implementation
#include <string>
#include "executive.h"
#include "workflow.h"


// Constructor
Executive::Executive(std::string input_dir_arg, std::string inter_dir_arg, std::string output_dir_arg)
{
	workflow_ = new Workflow(input_dir_arg, inter_dir_arg, output_dir_arg);
}


// Destructor
Executive::~Executive()
{
	delete workflow_;
}

// Run the executor
void Executive::run()
{
	workflow_->run();
}