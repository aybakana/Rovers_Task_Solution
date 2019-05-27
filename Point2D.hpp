#pragma once


// Point2D is used to store cell position.
class Point2D {
public:
	int x;
	int y;
	Point2D(){};
	Point2D(int x_,int y_){
	this->x = x_;
	this->y = y_;
	};
	int getX(){return this->x;}
	int getY(){return this->y;}
	// Operator == overloading
	bool operator==(Point2D p1){
		if(p1.x==this->x && p1.y==this->y){	return true;}
		else{ 						 	return false;}
	}
	// Operator = overloading
	void operator=(Point2D p1){
		this->x = p1.getX();
		this->y = p1.getY();
	}


};