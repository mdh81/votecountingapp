This is a C++ application that implements a preferred voting system. 

![Supported Use Cases](https://github.com/mdh81/votecountingapp/blob/master/votecountingapp_usage.gif)


#### Build

CMake is required to build this application. Do the following on the command line to build it:

    $ mkdir <build_directory>
    $ cd <build_directory>
    $ cmake ../
    $ cmake --build .

#### Execute

The build step will create an executable called `votingcountingapp` in the <build_directory>. Run the executable and you'll
be entered into a command prompt. Type help at the prompt to see supported commands and their usage

#### Test

Google tests are used for unit testing. Each sub-directory contains tests for every method or for every important functional piece in the implementation classes. The build step above will fetch google test and will build all tests. To run all tests do the following:

    $ mkdir <build_directory>
    $ ctest .


#### Contents

##### Design
This sub-directory contains design documents. 

* Design.md: Top-level design document. This document has the following:
  * Use Case Diagram
  * Activity Diagrams 
  * Class Diagram
* \*.txt files containing UML descriptions for the above diagrams
* \*.png files PlantUML renderings of the above diagrams

##### Parser
Implementation and tests for the parser service. This service implements file parsers that are necessary for the app's execution

##### CommandProcessor
Implementation and tests for the command processor service. This services implements a command loop, a command catalog, and a series of commands that the user can enter on the app's command prompt

##### VoteCounter
Implementation for the main service for this app.

