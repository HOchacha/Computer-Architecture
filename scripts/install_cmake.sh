#!/bin/bash

echo "checking cmake package installed"
# Check if cmake is installed
if ! command -v cmake &> /dev/null
then
    echo "CMake could not be found"
    echo "Installing CMake..."

    # Update the package lists for upgrades and new packages
    sudo apt-get update

    # Install cmake
    sudo apt-get install -y cmake
else
    echo "CMake is already installed"
fi
