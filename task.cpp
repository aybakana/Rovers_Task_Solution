#include <iostream>
#include <fstream>
#include <sstream>
#include "gtest/gtest.h"
#include "Rover.hpp"
#include "test.cpp"
#include "execFile.cpp"


int main(int argc, char **argv)  {
	// Execute Input Files 
	execFile("input.txt","output.txt");   // example input
	execFile("input1.txt","output1.txt"); // input with 6 rovers
	execFile("input2.txt","output2.txt"); // input with 11 rovers
	// Unit Tests
	cout<<"INFO: Unit Tests are starting ..."<<endl;
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}



