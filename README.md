# CSE687 Project 1: Map Reduce
April 28, 2022
Authors: Todd Hricik, Lyndsay LaBarge

## Overview
The Visual Studio Solution contains two seperate projects. The MapReduce project contains the implementation of the Project 1 command line application. The UnitTests project contains our Google Unit tests.

We used C++ 17 and the boost C++ library (version 1.79). We used the boost Filesystem as opposed to implementating our own file management class.

## Build
Both projects use a properties sheet. To build the projects, you will need to change the values of the user macros BoostRoot and BoostLib in MapReduce > PropertySheet.props and UnitTests > PropertySheet.props.