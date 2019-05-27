// executeInstructions.cpp
void execFile(string input_file,string output_file){
	// Open Files
	ifstream infile(input_file);
	ofstream outfile(output_file);
	string line;

	getline(infile, line);
	stringstream ss(line);
	int limit_x, limit_y;
	ss>>limit_x>>limit_y;
  	// Set Limits of Plateau
	Rover::limits=Point2D(limit_x,limit_y);
	// Clearing the last positions storage and rover count
	Rover::resetRovers();

	while (std::getline(infile, line))
	{
		Rover rover;
		// Split String by space
		stringstream ss(line);
		int x,y;string heading;
		ss>>x>>y>>heading;
	    // Set Starting Position of Rover
		rover.setPose(Point2D(x,y),heading);
		// Get Instructions String
		getline(infile, line);
		// Process Instructions
		rover.execute(line);
		// Write to file
		outfile<<rover.getPose()<<endl;
	}
	Rover::resetRovers();
	

	// Close Files
	infile.close();
	outfile.close();
}
