#include <string>

#include "Executive.h"
#include "Workflow.h"


// Constructor
Executive::Executive(std::string tarDir, std::string interDir, std::string outputDir)
{
	workflow = new Workflow(tarDir, interDir, outputDir);
}

// Run the executor
void Executive::run()
{
	workflow->run();
}