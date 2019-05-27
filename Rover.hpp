#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "Point2D.hpp"


using namespace std;

#define N 0 // North
#define E 1 // East
#define S 2 // South
#define W 3 // West

class Rover {
public:
	Rover();
	Rover(Point2D position,string head);
	~Rover();
	void setPose(Point2D position, string head);
	void setPosition(Point2D position);
	string getPose();
	void setX(int x);
	void setY(int y);
	void move();
	void turnLeft();
	void turnRight();
	// Save the last positions
	void saveLastPosition();
	void updateLastPosition();
	// Instructions Process Functions
	void execute_command(char command);
	void execute(string commands);
	
	bool isInLimits(Point2D position);
	bool isEmpty(Point2D position); // If the specified cell is empty or not
	Point2D findEmpty();

	// inline functions
	inline int getX(){ return this->cur_position.x; }
	inline int getY(){ return this->cur_position.y; }
	inline int getHeading(){ return this->heading; }

	// Heading Functions
	static int fromHead(string dir);
	static string toHead(int dir); 
	
	// clean static variables
	static void resetRovers();
	// Static Variables
	static Point2D limits;
	static int countRovers;  // Num of Rovers avaliable
	static vector<Point2D> last_positions; // In order to store positions of rovers and avoid occulusions
private:
	Point2D cur_position;  // current position
	int heading;
	int roverId;
};


