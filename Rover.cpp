#include "Rover.hpp"



// Initializations
int Rover::countRovers=0;
Point2D Rover::limits= Point2D(0,0);
vector<Point2D > Rover::last_positions;

Rover::Rover(){
	if(Rover::isEmpty(Point2D(0,0))){                       // If the specified position is empty
		this->cur_position = Point2D(0,0);		
	}
	else{													// If the specified position(cell) is full
		if(countRovers < Rover::limits.x*Rover::limits.y){  // If number of rovers does not exceed maximum numbers of Rovers(area of the plateau)
			this->cur_position = Rover::findEmpty();		
		}
		else{ cout<<"There is no place to spawn the Rover "<<this->roverId<<endl; }	
	}

	this->heading = N;
	this->roverId = this->countRovers;
	cout<<"INFO: Rover "<<this->roverId<<" is spawned. "<<endl;
	this->countRovers++;
	Rover::saveLastPosition(); 								   // Save the current position as the last position
}

Rover::Rover(Point2D position, string head){
	if(Rover::isInLimits(position)){
		if(Rover::isEmpty(position)){ 						   // If the specified position is empty
			this->cur_position = position; 		   
		}
		else{ 												   // If the specified position(cell) is full
			if(countRovers < Rover::limits.x*Rover::limits.y){ // If number of rovers does not exceed maximum numbers of Rovers(area of the plateau)
				this->cur_position = Rover::findEmpty();		
			}
			else{ 											   // If number of rovers does not exceed maximum numbers of Rovers(area of the plateau)
				cout<<"There is no place to spawn Rover"<<endl; 
			}	
		}
	}
	else{
		cout<<"WARNING: Invalid position, rover will be spawned to default position"<<endl;
		this->cur_position = Rover::findEmpty();
	}
	this->heading = Rover::fromHead(head);
	cout<<"INFO: Rover "<<this->roverId<<" is spawned. "<<endl;
	this->countRovers++;
	Rover::saveLastPosition();								   // Save the current position as the last position
}
Rover::~Rover(){
}
// Set the pose(position and heading) of the Rover
void Rover::setPose(Point2D position, string head){
	if(position.x <= Rover::limits.x && position.x >= 0 && position.y <= Rover::limits.y && position.y >= 0){
		if(this->cur_position == position){ 				   // If Rover is set to same position as current position
			cout<<"WARNING: Rover is already at the specified position!"<<endl;
			this->heading = Rover::fromHead(head);
		} else if(Rover::isEmpty(position)){ 
			this->cur_position = position;
			this->heading = Rover::fromHead(head);			
		}
		else{cout<<"WARNING: Another Rover is at the specified position"<<endl;}
	}
	else{cout<<"WARNING: Invalid Position, Rover will stay in the same place "<<endl;} 
	Rover::updateLastPosition();								// Update the last position
}

// Set only the position of the Rover
void Rover::setPosition(Point2D position){
	if(position.x <= Rover::limits.x && position.x >= 0 && position.y <= Rover::limits.y && position.y >= 0){
		if(this->cur_position == position){ 			// If Rover is set to same position as current position
			cout<<"WARNING: Rover is already at the specified position!"<<endl;
		} else if(Rover::isEmpty(position)){ 
			this->cur_position = position;		
		}
		else{
			cout<<"WARNING: Another Rover is at the specified position"<<endl;
		}
	}
	else{cout<<"WARNING: Invalid Position, Rover will stay in the same place "<<endl;} 
	Rover::updateLastPosition();								// Update the last position
}

// Set only the X coordinate of the current position
void Rover::setX(int x){
	if(x <= Rover::limits.x && x >= 0){ 
		if(Rover::isEmpty(Point2D(x,this->cur_position.y))){ this->cur_position.x = x; }
		else{cout<<"WARNING: another rover is at the specified position"<<endl;}	
	}
	else{cout<<"WARNING: Invalid x position, instruction is neglected!"<<endl;}
	Rover::updateLastPosition();								// Update the last position
}
// Set only the Y coordinate of the current position
void Rover::setY(int y){
	if(y <= Rover::limits.y && y >= 0){
		if(Rover::isEmpty(Point2D(this->cur_position.x,y))){ this->cur_position.y = y; }
		else{cout<<"WARNING: Another rover is at the specified position"<<endl;}
	} 
	else{cout<<"WARNING: Invalid y position, instruction is neglected!"<<endl;}
	Rover::updateLastPosition();								// Update the last position
}
// Get Current Position as string
string Rover::getPose(){
	return to_string(this->cur_position.x)+" "+to_string(this->cur_position.y)+" "+Rover::toHead(this->heading);
}

// Move Forward
void Rover::move(){
	if(heading==N){
		if(isEmpty(Point2D(this->cur_position.x,this->cur_position.y+1)) && Rover::limits.y >= this->cur_position.y+1)	this->cur_position.y++;
		else{cout<<"WARNING: Rover "<<this->roverId<<" can not move forward!"<<endl;}
	} 
	if(heading==S){
		if(isEmpty(Point2D(this->cur_position.x,this->cur_position.y-1)) && 0 <= this->cur_position.y-1) this->cur_position.y--;
		else{cout<<"WARNING: Rover "<<this->roverId<<" can not move forward!"<<endl;}
	}
	if(heading==E){
		if(isEmpty(Point2D(this->cur_position.x+1,this->cur_position.y)) && Rover::limits.x >= this->cur_position.x+1)	this->cur_position.x++;
		else{cout<<"WARNING: Rover "<<this->roverId<<" can not move forward!"<<endl;}
	}
	if(heading==W){
		if(isEmpty(Point2D(this->cur_position.x-1,this->cur_position.y)) && 0 <= this->cur_position.x-1) this->cur_position.x--;
		else{cout<<"WARNING: Rover "<<this->roverId<<" can not move forward!"<<endl;}
	}
	Rover::updateLastPosition();
		
}
// Turn Left
void Rover::turnLeft(){
	this->heading = (this->heading - 1) < N ? W : this->heading - 1;
}
// Turn Right
void Rover::turnRight(){
	this->heading = (this->heading + 1) > W ? N : this->heading + 1;
}
// Execute single command
void Rover::execute_command(char command){
	if(command == 'M'){
		move();
	} else if (command == 'R') {
		turnRight();
	} else if (command == 'L'){
		turnLeft();
	}
	else{
		cout<<"WARNING: Invalid Command! No movement. "<<endl;
	}

}
// Execute commands in a string
void Rover::execute(string commands){
	for(int i=0;i<commands.length();i++){
		Rover::execute_command(commands[i]);
	}
}


// Convert String Direction to Integer Direction
// used for taking string input
int Rover::fromHead(string dir){
	if(dir=="N") return 0;
	if(dir=="E") return 1;
	if(dir=="S") return 2;
	if(dir=="W") return 3;
	return 0; // if unknown heading is given, default heading(N) is set.
}

// Convert the Integer Direction to String Direction
// Used for printing out
string Rover::toHead(int dir){
	if(dir==N) return "N";
	if(dir==E) return "E";
	if(dir==S) return "S";
	if(dir==W) return "W";
}
// Check if the specified cell is empty or not
bool Rover::isEmpty(Point2D position){
	if(Rover::last_positions.size()==0) return true;
	if(this->cur_position == position) return true;  // if current position is same as the specified position
	for(int i=0; i < last_positions.size();i++){
		if(Rover::last_positions[i]==position) return false;
	}
	return true;
}
// Check if the specified position is inside the plateau
bool Rover::isInLimits(Point2D position){
	if(position.x <= Rover::limits.x && position.x >= 0 &&  position.y <= Rover::limits.y && position.y >= 0) return true;
	return false;
}
// Find a free cell inside the plateau
Point2D Rover::findEmpty(){
	for(int i = 0;i < Rover::limits.x; i++){
		for(int j = 0;j <= Rover::limits.y; j++){
			if(isEmpty(Point2D(i,j)))return(Point2D(i,j));
		}
	}
}
// Reset the vector of last_positions, number of Rovers
void Rover::resetRovers(){
	Rover::last_positions.clear(); 
	Rover::countRovers = 0;
}
// Save the current position as the last position to the vector of last_positions
void Rover::saveLastPosition(){ 
	Rover::last_positions.push_back(Point2D(this->cur_position.x,this->cur_position.y));

}
// Update the last position in the vector of last_positions
void Rover::updateLastPosition(){
	Rover::last_positions[this->roverId] = Point2D(this->cur_position.x,this->cur_position.y);
}
