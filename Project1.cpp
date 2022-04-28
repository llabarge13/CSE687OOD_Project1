// Project1.cpp
// Todd Hricik
// CIS 687 Object Oriented Design
////////////////////////////////////////////////////////////////////////////////////
// This program acts as executor which will intantiate a workflow object and invoke 
// the workflow's run member function
////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost\filesystem.hpp>
#include <boost\log\trivial.hpp>
#include "Executive.h"
#include "Workflow.h"

// Set the boost logging threshold to >= info
void init()
{
    boost::log::core::get()->set_filter
    (
        boost::log::trivial::severity >= boost::log::trivial::info
    );
}

int main(int argc, char* argv[])
{

    // check that comand line input is valid
    if (argc != 4)
    {
        BOOST_LOG_TRIVIAL(fatal) << "./project1 <path of dir containging input files> <path of dir for intermediate files> <path of dir for output files>.";
        return -1;
    }

    // declare strings to hold command line input values which should each be a path to a directory
    std::string targetDir = argv[1];
    std::string intermediateDir = argv[2];
    std::string outDir = argv[3];

    // Instantiate an executor
    Executive* executive = new Executive(argv[1], argv[2], argv[3]);

    // Use the executor to run the workflow
    executive->run();
}
