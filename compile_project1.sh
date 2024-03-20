#!/bin/bash

if [ ! -d "Project1/bin" ]; then
  mkdir Project1/bin
fi

cmake -S . -B cmake-build-debug

cmake --build cmake-build-debug --config Debug

mv cmake-build-debug/Computer_Architecture Project1/bin/
