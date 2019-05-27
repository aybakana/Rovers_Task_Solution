#include "gtest/gtest.h"
#include "Rover.hpp"

// Cell and position are used interchangeably

// Occlusion Test
// Whether a rover occlude with another or not
// We expect that two or more Rovers can not in the same cell(position)
TEST(RoverTest, Occlusion){
	Rover::limits = Point2D(5,5);
	Rover rover1,rover2;
	rover1.setPose(Point2D(1,1),"W"); 
	rover2.setPose(Point2D(1,1),"W");
	EXPECT_FALSE(rover1.getX() == rover2.getX() && rover1.getY() == rover2.getY());
	// Clearing the last positions storage
	Rover::resetRovers();           
}



// Default Position and Heading Test 
// Whether Default Rover position and heading is correct
TEST(RoverTest, StartingPosition) {
	Rover::limits = Point2D(5,5);
	Rover rover;
	if(rover.isEmpty(Point2D(0,0))){
		EXPECT_TRUE(rover.getX() == 0 && rover.getY() == 0 && rover.getHeading() == Rover::fromHead("N"));
	}
	Rover::resetRovers(); 
}


// Limit Positive Test
// Whether the rover is goes beyond the limit of plateau
TEST(RoverTest, IsInsidePlateau_1) {
	Rover::limits = Point2D(5,5);
	Rover rover;
	rover.setPose(Point2D(7,7),"N"); 	// IsInsidePlateau_1 Test
	EXPECT_TRUE(rover.isInLimits(Point2D(rover.getX(),rover.getY())));
	Rover::resetRovers(); 
}




// Limit Positive Test
// Whether the rover is goes beyond the limit of plateau
TEST(RoverTest, IsInsidePlateau_2) { 
	Rover::limits = Point2D(5,5);
	Rover rover;
	rover.execute("MMMMMMMM");  	// IsInsidePlateau_2 Test
	EXPECT_TRUE(rover.getX() <= Rover::limits.x && rover.getX() >= 0);
	EXPECT_TRUE(rover.getY() <= Rover::limits.y && rover.getY() >= 0);
	Rover::resetRovers(); 
}


// Limit Negative Test
// Whether the rover is goes beyond the limit of plateau
TEST(RoverTest, IsInsidePlateau_3) {
	Rover::limits = Point2D(5,5);
	Rover rover(Point2D(-1,-1),"N");
	EXPECT_TRUE(rover.getX() <= Rover::limits.x && rover.getX() >= 0);
	EXPECT_TRUE(rover.getY() <= Rover::limits.y && rover.getY() >= 0);
	Rover::resetRovers(); 
}



// Limit Negative Test
// Whether the rover is goes beyond the limit of plateau
TEST(RoverTest, IsInsidePlateau_4) { 
	Rover::limits = Point2D(5,5);
	Rover rover(Point2D(0,4),"N");
	rover.execute("RRMMMMMMMM");	// IsInsidePlateau_4 Test
	EXPECT_TRUE(rover.getX() <= Rover::limits.x && rover.getX() >= 0);
	EXPECT_TRUE(rover.getY() <= Rover::limits.y && rover.getY() >= 0);
	Rover::resetRovers(); 
}



// Execute Test 1
// Whether the execution is working right or not
TEST(RoverTest, IfExampleInputWorks_1) {
	Rover::limits = Point2D(5,5);
	Rover rover;
	rover.setPose(Point2D(1,2),"N");	// IfExampleInputWorks_1 Test
	rover.execute("LMLMLMLMM");
	if(rover.isEmpty(Point2D(1,3))){
		EXPECT_TRUE(rover.getX()==1 && rover.getY()==3 && rover.getHeading()==Rover::fromHead("N"));
	}
	Rover::resetRovers(); 
}


// Execute Test 2
// Whether the execution is working right or not  
TEST(RoverTest, IfExampleInputWorks_2) {
	Rover::limits = Point2D(5,5);

	Rover rover;
	rover.setPose(Point2D(3,3),"E");	// IfExampleInputWorks_2 Test
	rover.execute("MMRMMRMRRM");
	if(rover.isEmpty(Point2D(5,1))){
		EXPECT_TRUE(rover.getX() == 5 && rover.getY() == 1 && rover.getHeading() == Rover::fromHead("E"));
	}
	Rover::resetRovers(); 
}

// Test for Setting the position to the current position again 
// Whether specified position is set even if it is same as the current position
TEST(RoverTest, setPoseAgain) {
	Rover::limits = Point2D(5,5);
	Rover rover(Point2D(1,1),"N");
	rover.setPose(Point2D(1,1),"W");
	EXPECT_TRUE(Point2D(rover.getX(),rover.getY()) == Point2D(1,1) && rover.getHeading() == Rover::fromHead("W"));
	Rover::resetRovers(); 
}


// Turning to Left Test
// Whether turnRight Function works or not 
TEST(RoverTest, TurnLeft) {
	Rover::limits = Point2D(5,5);
	Rover rover;
	rover.setPose(Point2D(0,0),"N");	// TurnLeft Test
	rover.turnLeft();
	EXPECT_EQ(rover.getHeading(),Rover::fromHead("W"));
	Rover::resetRovers(); 
}


// Turning to Right Test 
// Whether turnLeft Function works or not 
TEST(RoverTest, TurnRight) { 
	Rover::limits = Point2D(5,5);
	Rover rover;
	rover.setPose(Point2D(1,5),"W");	// TurnRight Test
	rover.turnRight();
	EXPECT_EQ(rover.getHeading(),Rover::fromHead("N"));
	Rover::resetRovers(); 
}




// Execute Test 3
// Whether the execution is working right or not  
TEST(RoverTest, IfExampleInputWorks_3) {
	Rover::limits = Point2D(5,5);
	Rover rover;
	rover.execute("MMMMMRMMMMM");	// IfExampleInputWorks_3 Test
	if(rover.isEmpty(Point2D(5,5))){
		EXPECT_TRUE(rover.getX() == 5 && rover.getY() == 5 && rover.getHeading() == Rover::fromHead("E"));
	}
	Rover::resetRovers(); 
}




// Moving to North Test 
// Whether move function works in North Direction
TEST(MoveTest, North) {
	Rover::limits = Point2D(5,5);
	Rover rover;
	int start_x = 1, start_y = 1;
	rover.setPose(Point2D(start_x,start_y),"N"); 
	rover.move();
	if(rover.isInLimits(Point2D(start_x,start_y+1)) && rover.isEmpty(Point2D(start_x,start_y+1))){
		EXPECT_TRUE(rover.getX() == start_x && rover.getY() == start_y+1);
	}
	Rover::resetRovers(); 
}
// Moving to East Test 
// Whether move function works in East Direction
TEST(MoveTest, East) {
	Rover::limits = Point2D(5,5);
	Rover rover;
	int start_x = 1, start_y = 1;
	rover.setPose(Point2D(start_x,start_y),"E");
	rover.move();
	if(rover.isInLimits(Point2D(start_x+1,start_y)) && rover.isEmpty(Point2D(start_x+1,start_y))){
		EXPECT_TRUE(rover.getX() == start_x+1 && rover.getY() == start_y);
	}
	Rover::resetRovers(); 
}
// Moving to South Test 
// Whether move function works in South Direction
TEST(MoveTest, South) {
	Rover::limits = Point2D(5,5);
	Rover rover;
	int start_x = 1, start_y = 1;
	rover.setPose(Point2D(start_x,start_y),"S");
	rover.move();
	if(rover.isInLimits(Point2D(start_x,start_y-1)) && rover.isEmpty(Point2D(start_x,start_y-1))){
		EXPECT_TRUE(rover.getX() == start_x && rover.getY() == start_y-1);
	}
	Rover::resetRovers(); 
}
// Moving to West Test 
// Whether move function works in West Direction
TEST(MoveTest, West) { 
	Rover::limits = Point2D(5,5);
	Rover rover;
	int start_x = 1, start_y = 1;
	rover.setPose(Point2D(start_x,start_y),"W");
	rover.move();
	if(rover.isInLimits(Point2D(start_x-1,start_y)) && rover.isEmpty(Point2D(start_x-1,start_y))){
		EXPECT_TRUE(rover.getX() == start_x-1 && rover.getY() == start_y);
	}
	Rover::resetRovers(); 
}

// Test for Giving an invalid command(other than M, R, or L)
TEST(MoveTest, InvalidCommand) { 
	Rover::limits = Point2D(5,5);
	Rover rover(Point2D(0,0),"N");
	rover.execute_command('S');
	// We expect that position does not change with the invalid command
	EXPECT_TRUE(Point2D(rover.getX(),rover.getY()) == Point2D(0,0));
	Rover::resetRovers(); 
}
