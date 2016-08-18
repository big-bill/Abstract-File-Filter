#include "FileFilter.h"
/*
	I would've liked to just pass the file names to the function instead of the files themselves, but the problem statement
	asked for the program to pass the ifstream and ofstream data types. 
*/
void FileFilter::doFilter(std::ifstream &inputFile, std::ofstream &outputFile)
{
	char transformChar = '\0', fileChar = '\0';

	//clears the flags
	inputFile.clear();
	outputFile.clear();

	//sets the reading position of the input file back to the start
	inputFile.seekg(0, std::ios::beg);

	inputFile.get(fileChar);

	while (!inputFile.fail())
	{
		//transforms the characters in the text file and places it in the output file
		transformChar = transform(fileChar);
		outputFile.put(transformChar);
		inputFile.get(fileChar);
	}

	//I had some problems if I didn't include this statement. It was originally going to be back in main.
	//Visual Studios didn't state what line in which the compiler error was arising, besides saying it was an external problem
	//This managed to fix it though.
	outputFile.close();
}