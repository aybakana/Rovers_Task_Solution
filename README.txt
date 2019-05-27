# MarsRover
My Mars Rover Solution

## task.cpp 
The main C++ code where example input file(input.txt) and input with 6 rovers(input1.txt) are executed with execFile function.

## execFile.cpp
Contains the execFile function which execute commands in the input files as described in the task description.

## test.cpp
Unit testing code.

## Rover.cpp & Rover.hpp
Rover Class 
The methods are:
    setPose,
    setPosition,
    getPose,
    setX,
    setY,
    move,
    turnLeft,
    turnRight,
    execute_command,
    execute,
    toHead,
    fromHead,
    isEmpty,
    findEmpty,
    isInLimits,
    saveLastPosition,
    updateLastPosition,
    resetRovers,
    
The variables are:
    cur_position(Current Position),
    heading,
    roverId,
    limits,
    countRovers,
    last_positions


