IPC - interprocess communication. Base project for Richard.

## Requirements
- cmake (>= 3.16)
- visual studio 2022, c++ >= 17

## Setup
In order to setup the project follow the steps:
- Clone the repo to your local machine
- Go to the root folder of the project
- Open PowerShell in the root of the project
- use `./generate -install`

After these steps you should see new generated folder: '_solutions' and 'build'. You Visual Studio solution is located inside of the '_solutions' folder.

## Generate script
This script will only work for Windows, you will have to write a custom bash script for Linux. Inside of this script there are several function to make your life easier:
- generateSolution: creates a folder '_solutions' and calls cmake function to generate a project;
- installResources: copies all files from 'dlls' and 'resources' folders into your output folder;
- compileProject: compiles your Debug and Release targets (can be useful for automation tests or for ci/cd pipeline)
- clearPrevious: cleans the project

Every time you add or remove new files, you should run 'generateSolution'. In order to do so you can just run `./generate` without any additional arguments.

## Structure
This project uses several libraries: boost and SDL. There are two executables in the end, but they are using the same components. In order to make it easier to develop the project is separated into several smaller projects:
- Boost: has boost library, easy to plug-in and plug-out
- Common: has all common components, such as managing of the Window
- Host: host .exe program
- Client: client .exe program