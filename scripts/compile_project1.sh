#!/bin/bash
cd ..
# Check if the bin directory exists under Project1
if [ ! -d "bin" ]; then
  # If not, create the bin directory
  mkdir bin
fi

# Run CMake to compile the project
cmake -S . -B cmake-build-debug

# Build the project
cmake --build cmake-build-debug --config Debug

# Check if a name for the binary was provided
if [ -z "$1" ]; then
  echo "No binary name provided. Using default: Project1"
  binary_name="Project1"
else
  binary_name="$1"
fi

# Move the executable to the bin directory
mv "cmake-build-debug/$binary_name" Project1/bin/