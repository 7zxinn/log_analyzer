# Log Analyzer

A lightweight C++ command-line tool analyzing log files.

This project was developed to practice C++ programming, CMake-based builds, automated testing, and Git version control.

## Features
- Count the total number of log lines.
- Search for a keyword and record matching lines.
- Count ERROR,INFO,WARNING entries.
- Calculate the error rate.
- Record the line number of the first error.
- Handle empty files and missing files.

## Requirements
- A C++ compiler that supports C++ 11.
- CMake 3.10 or late.
- GoogleTest for running unit tests.

## Installation
On ubuntu,install the required tools and libraries:

  sudo apt update
  sudo apt install build-essential cmake libgtest-dev

## Build
Clone the repository and navigate to the project directory:

  git clone <repository-url>
  cd log_analyzer

Configure and build the project:

  cmake -S . -B build 
  cmake --build build

## Usage
Run the program with a log file path and a keyword:

  ./build/log_analyzer <log-file-path> <keyword>

Example:

  ./build/log_analyzer tests/sample.log ERROR

The program analyzes the specified log file, counts log levels, calculates the error rate, and dispalays lines matching the specified keyword.

## Testing
This project usus GoogleTest for unit testing.

Run the following commands from the project root directory:

  ctest --test-dir build --output-on-failure

The test suite covers:
- Log line and log level counting.
- Keyword macthing and matching line recording.
- Empty log files.
- Missing log files.
- First error line detection. 
