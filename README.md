# CSE687 Project 1: Map Reduce
April 28, 2022

Authors: Todd Hricik, Lyndsay LaBarge

## Overview
The Visual Studio Solution contains two seperate projects. The MapReduce project contains the implementation of the Project 1 command line application. The UnitTests project contains our Google Unit tests.

We used C++ 17 and the boost C++ library (version 1.79). We used the boost Filesystem as opposed to implementating our own file management class.

## Build
Both projects use a properties sheet. To build the projects, you will need to change the values of the user macros BoostRoot and BoostLib in MapReduce > PropertySheet.props, UnitTests > PropertySheet.props, and UnitTests > PropertySheetRelease.props. By default they are set to `C:\Program Files\boost\boost_1_79_0` and `C:\Program Files\boost\boost_1_79_0\stage\lib`. To build, use either the Debug or Release configuration for x64 platforms.

## Usage
```
MapReduce.exe <path of directory containging input files> <directory for intermediate files> <path of dir for output files>.
```
All command line requirements are required. 

The input directory must contain UTF-8 encoded text files. If the input directory contains a file that does not meet the requirements, that file will be skipped during processing.

If the intermediate directory or the output directory does not already exist, the application will create the directories.

## Expected Output
### Command Line
```
[2022-04-30 10:06:21.824128] [0x00008378] [info]    targetDir member has been set in Workflow constructor.
[2022-04-30 10:06:21.825128] [0x00008378] [info]    Info in Workflow constructor: intermediateDir member has been set in Workflow constructor.
[2022-04-30 10:06:21.825629] [0x00008378] [info]    Info in Workflow constructor: Directory for intermediate files created.
[2022-04-30 10:06:21.826128] [0x00008378] [info]    Info in Workflow constructor: outDir member has been set in Workflow constructor.
[2022-04-30 10:06:21.826128] [0x00008378] [info]    Info in Workflow constructor: Directory for output files created.
[2022-04-30 10:06:21.887639] [0x00008378] [info]    Info in Workflow run(): Map process completed for All'sWellThatEndsWell.txt
[2022-04-30 10:06:21.930646] [0x00008378] [info]    Info in Workflow run(): Map process completed for AMidSummerNightsDream.txt
[2022-04-30 10:06:21.971154] [0x00008378] [info]    Info in Workflow run(): Map process completed for AsYouLIkeIte.txt
[2022-04-30 10:06:22.024663] [0x00008378] [info]    Info in Workflow run(): Map process completed for Cymbeline.txt
[2022-04-30 10:06:22.075671] [0x00008378] [info]    Info in Workflow run(): Map process completed for Love'sLabourLost.txt
[2022-04-30 10:06:22.127181] [0x00008378] [info]    Info in Workflow run(): Map process completed for MeasureForMeasure.txt
[2022-04-30 10:06:22.176689] [0x00008378] [info]    Info in Workflow run(): Map process completed for MuchAdoAboutNothing.txt
[2022-04-30 10:06:22.226198] [0x00008378] [info]    Info in Workflow run(): Map process completed for PericlesPrinceOfTyre.txt
[2022-04-30 10:06:22.275706] [0x00008378] [info]    Info in Workflow run(): Map process completed for TamingOfTheShrew.txt
[2022-04-30 10:06:22.312213] [0x00008378] [info]    Info in Workflow run(): Map process completed for TheComedyOfErrors.txt
[2022-04-30 10:06:22.361221] [0x00008378] [info]    Info in Workflow run(): Map process completed for TheMerchantOfVenice.txt
[2022-04-30 10:06:22.419232] [0x00008378] [info]    Info in Workflow run(): Map process completed for TheMerryWivesOfWindsor.txt
[2022-04-30 10:06:22.458739] [0x00008378] [info]    Info in Workflow run(): Map process completed for TheTempest.txt
[2022-04-30 10:06:22.514249] [0x00008378] [info]    Info in Workflow run(): Map process completed for TheTwelthNight.txt
[2022-04-30 10:06:22.551254] [0x00008378] [info]    Info in Workflow run(): Map process completed for TheTwoGentlemenOfVerona.txt
[2022-04-30 10:06:22.600763] [0x00008378] [info]    Info in Workflow run(): Map process completed for TroilusAndCressida .txt
[2022-04-30 10:06:22.653273] [0x00008378] [info]    Info in Workflow run(): Map process completed for Winter'sTale.txt
[2022-04-30 10:06:22.654272] [0x00008378] [info]    Running sort on All'sWellThatEndsWell.txt
[2022-04-30 10:06:22.670275] [0x00008378] [info]    Running sort on AMidSummerNightsDream.txt
[2022-04-30 10:06:22.681777] [0x00008378] [info]    Running sort on AsYouLIkeIte.txt
[2022-04-30 10:06:22.696780] [0x00008378] [info]    Running sort on Cymbeline.txt
[2022-04-30 10:06:22.716284] [0x00008378] [info]    Running sort on Love'sLabourLost.txt
[2022-04-30 10:06:22.729285] [0x00008378] [info]    Running sort on MeasureForMeasure.txt
[2022-04-30 10:06:22.744788] [0x00008378] [info]    Running sort on MuchAdoAboutNothing.txt
[2022-04-30 10:06:22.757790] [0x00008378] [info]    Running sort on PericlesPrinceOfTyre.txt
[2022-04-30 10:06:22.772793] [0x00008378] [info]    Running sort on TamingOfTheShrew.txt
[2022-04-30 10:06:22.787629] [0x00008378] [info]    Running sort on TheComedyOfErrors.txt
[2022-04-30 10:06:22.797298] [0x00008378] [info]    Running sort on TheMerchantOfVenice.txt
[2022-04-30 10:06:22.809299] [0x00008378] [info]    Running sort on TheMerryWivesOfWindsor.txt
[2022-04-30 10:06:22.821801] [0x00008378] [info]    Running sort on TheTempest.txt
[2022-04-30 10:06:22.831303] [0x00008378] [info]    Running sort on TheTwelthNight.txt
[2022-04-30 10:06:22.842805] [0x00008378] [info]    Running sort on TheTwoGentlemenOfVerona.txt
[2022-04-30 10:06:22.852807] [0x00008378] [info]    Running sort on TroilusAndCressida .txt
[2022-04-30 10:06:22.872310] [0x00008378] [info]    Running sort on Winter'sTale.txt
[2022-04-30 10:06:22.889813] [0x00008378] [info]    Running reduce operation...
[2022-04-30 10:06:27.347590] [0x00008378] [info]    Writing success file...
[2022-04-30 10:06:27.348590] [0x00008378] [info]    Removing intermediate files...
[2022-04-30 10:06:27.403099] [0x00008378] [info]    Map reduce process complete.
```

### File Output
Assuming the application completed with no errors, the results of the map reduce operation are located in the specified output directory. It will output 2 files.

`reduce.txt` - file containing the map reduce output

`SUCCESS` - file indicating the operation completed successfully


## Unit Test Results
The unit tests are defined in UnitTests\tests.cpp. There are unit tests for the Map, Sort, Reduce, and Workflow calsses. 

```
Running main() from c:\a\1\s\thirdparty\googletest\googletest\src\gtest_main.cc
[==========] Running 12 tests from 4 test cases.
[----------] Global test environment set-up.
[----------] 3 tests from mapTest
[ RUN      ] mapTest.checkOutputPath
[       OK ] mapTest.checkOutputPath (3 ms)
[ RUN      ] mapTest.checkMapResult
[       OK ] mapTest.checkMapResult (3 ms)
[ RUN      ] mapTest.badOutputDirectory
[       OK ] mapTest.badOutputDirectory (1 ms)
[----------] 3 tests from mapTest (7 ms total)

[----------] 3 tests from sortTest
[ RUN      ] sortTest.checkSortOutput
[       OK ] sortTest.checkSortOutput (0 ms)
[ RUN      ] sortTest.badInputFilePath
[       OK ] sortTest.badInputFilePath (0 ms)
[ RUN      ] sortTest.badInputFileFormat
[       OK ] sortTest.badInputFileFormat (3 ms)
[----------] 3 tests from sortTest (5 ms total)

[----------] 4 tests from reduceTest
[ RUN      ] reduceTest.checkOutputDirectory
[       OK ] reduceTest.checkOutputDirectory (1 ms)
[ RUN      ] reduceTest.checkOutputPath
[       OK ] reduceTest.checkOutputPath (1 ms)
[ RUN      ] reduceTest.checkBadDirectory
[       OK ] reduceTest.checkBadDirectory (1 ms)
[ RUN      ] reduceTest.checkReduceOutput
[       OK ] reduceTest.checkReduceOutput (5 ms)
[----------] 4 tests from reduceTest (9 ms total)

[----------] 2 tests from WorkflowTest
[ RUN      ] WorkflowTest.testConstructor
[2022-04-30 09:19:34.662754] [0x000077c4] [debug]   Debug in Workflow constructor: Entering constructor.
[2022-04-30 09:19:34.662754] [0x000077c4] [info]    targetDir member has been set in Workflow constructor.
[2022-04-30 09:19:34.662754] [0x000077c4] [info]    Info in Workflow constructor: intermediateDir member has been set in Workflow constructor.
[2022-04-30 09:19:34.663254] [0x000077c4] [info]    Info in Workflow constructor: Directory for intermediate files created.
[2022-04-30 09:19:34.663755] [0x000077c4] [info]    Info in Workflow constructor: outDir member has been set in Workflow constructor.
[2022-04-30 09:19:34.663755] [0x000077c4] [info]    Info in Workflow constructor: Directory for output files created.
[2022-04-30 09:19:34.664255] [0x000077c4] [debug]   Debug in Workflow constructor: Construction is complete. Exiting constructor.
[       OK ] WorkflowTest.testConstructor (2 ms)
[ RUN      ] WorkflowTest.testRun
[2022-04-30 09:19:34.667756] [0x000077c4] [debug]   Debug in Workflow constructor: Entering constructor.
[2022-04-30 09:19:34.668254] [0x000077c4] [info]    targetDir member has been set in Workflow constructor.
[2022-04-30 09:19:34.668754] [0x000077c4] [info]    Info in Workflow constructor: intermediateDir member has been set in Workflow constructor.
[2022-04-30 09:19:34.668754] [0x000077c4] [info]    Info in Workflow constructor: Directory for intermediate files created.
[2022-04-30 09:19:34.669254] [0x000077c4] [info]    Info in Workflow constructor: outDir member has been set in Workflow constructor.
[2022-04-30 09:19:34.669254] [0x000077c4] [info]    Info in Workflow constructor: Directory for output files created.
[2022-04-30 09:19:34.669756] [0x000077c4] [debug]   Debug in Workflow constructor: Construction is complete. Exiting constructor.
[2022-04-30 09:19:35.551908] [0x000077c4] [info]    Info in Workflow run(): Map process completed for All'sWellThatEndsWell.txt
[2022-04-30 09:19:35.553408] [0x000077c4] [info]    Running sort on All'sWellThatEndsWell.txt
[2022-04-30 09:19:36.174517] [0x000077c4] [info]    Running reduce operation...
[2022-04-30 09:19:37.280209] [0x000077c4] [info]    Writing success file...
[2022-04-30 09:19:37.281709] [0x000077c4] [info]    Removing intermediate files...
[       OK ] WorkflowTest.testRun (2619 ms)
[----------] 2 tests from WorkflowTest (2626 ms total)

[----------] Global test environment tear-down
[==========] 12 tests from 4 test cases ran. (2650 ms total)
[  PASSED  ] 12 tests.
```