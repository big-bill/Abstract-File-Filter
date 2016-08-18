/*
	C++ II Project 3 - Chapter 15 Programming Challenge 5: File Filter
	Problem Statement:
	A file filter reads an input file, transforms it in some way, and writes the result to an output file.
	Write an abstract file filter class that defines a pure virtual function for transforming a character.
	Create one subclass of your file filter class the performs the encryption, another that transforms a file to all uppercase, and another that creates an unchanged copy of the original file.
	The class should have a member function
		void doFilter(ifstream &in, oftream &out)
	that is called to perform the actual filtering. The member function for transforming a single character should have the prototype
		char transform(char ch)
	The encryption class should have a constructor that takes an integer as an arguement and uses it as the encryption key.
	--End--

	Written by: Billy Matthews, March 2016
*/
#include "FileFilter.h"

void splashScreen();
void clearScreen();
void encryptFile(std::string);
void decryptFile(std::string);
void uppercaseFile(std::string);
void displayFile(std::string);
bool getFileName(std::string);

int main()
{
	std::string fileName = "", choice = "";
	bool flagForGoodFile = false;
	splashScreen();
	clearScreen();

	std::cout << "Firstly, please enter the name of the file you would like to encrypt and/or\nchange all the text to uppercase.\nEnter 'M' if you wish to go to the main menu.";
	while (true)
	{
		std::cout << "\nFile name: ";
		std::getline(std::cin, fileName);

		//if the user wants to go to the main menu, this gives the user the option to go to it
		if (fileName.length() == 1)
		{
			fileName[0] = toupper(fileName[0]);
			if (fileName[0] == 'M')
			{
				fileName = "No file chosen";
				flagForGoodFile = true;
				break;
			}
		}
		if (getFileName(fileName))
			break;
	}
	do
	{
		clearScreen();
		while (true)
		{
			std::cout << "\tFile: " << fileName << "\n\n";
			std::cout << "\n\t------------------Main Menu------------------";
			std::cout << "\n\t|                                           |";
			std::cout << "\n\t|       (E)ncrypt the text file             |";
			std::cout << "\n\t|       (D)ecrypt the text file             |";
			std::cout << "\n\t|       (U)ppercase all characters          |";
			std::cout << "\n\t|       (C)hoose a file to modify           |";
			std::cout << "\n\t|       (S)how the contents of the file     |";
			std::cout << "\n\t|       (Q)uit the program                  |";
			std::cout << "\n\t|                                           |";
			std::cout << "\n\t---------------------------------------------\n";
			std::cout << "\n\tChoice: ";
			std::getline(std::cin, choice);
			if (choice.length() == 1)
			{
				choice[0] = toupper(choice[0]);
				if (choice[0] == 'E' || choice[0] == 'U' || choice[0] == 'C' || 
					choice[0] == 'D' || choice[0] == 'S' || choice[0] == 'Q')
					break;
			}
			//Since the if statement above didn't break out of the while loop, we need display an error message.
			clearScreen();
			std::cout << "\n\n\tInvalid input! Please re-enter your choice.\n\n";
		}

		//If the user has yet to choose a file, this if statement will catch it and will limit the user's options
		//to either 'C' to choose a file or 'Q' to quit the program
		if (flagForGoodFile && choice[0] != 'C' && choice[0] != 'Q')
		{
			clearScreen();
			std::cout << "No file chosen! Press enter to return to the main menu. . .";
			std::getline(std::cin, choice);
			continue;
		}

		switch (choice[0])
		{

		case 'E':{
			clearScreen();		
			encryptFile(fileName);
			break; }

		case 'D':{
			clearScreen();
			decryptFile(fileName);
			break; }
			
		case 'U':{
			clearScreen();
			uppercaseFile(fileName);
			break; }
			
		case 'C': 
			clearScreen();
			std::cout << "Enter the file name you would like to encrypt, decrypt, and/or change to all\nuppercase."
					  << "\nEnter 'M' if you wish to go to the main menu.";
			while (true)
			{
				std::cout << "\nFile name: ";
				std::getline(std::cin, fileName);

				//if the user wants to go to the main menu, this gives the user the option to go to it
				if (fileName.length() == 1)
				{
					fileName[0] = toupper(fileName[0]);
					if (fileName[0] == 'M')
					{
						fileName = "No file chosen";
						flagForGoodFile = true;
						break;
					}
				}

				if (getFileName(fileName))
				{
					//this boolean indicates that the file chosen is a proper filename
					flagForGoodFile = false;
					break;
				}
			}
			break;
		
		case 'S': 
			clearScreen();
			displayFile(fileName);
			break;

		default:
			std::cout << "\n\nThanks for using the program! Press enter to exit. . . ";
			break;
		}

	} while (choice[0] != 'Q');

	std::cin.get();
	return 0;
}
//-----------------------------------------------------------------------------------------------------
void splashScreen()
{
	std::string tempStr;
	std::cout << "Welcome to the file filter program!"
			  << "\nThis program will allow you to encrypt a text file and/or change all the\ncharacters to uppercase form."
			  << "\nNotice: The original file will be saved to a copy so the contents will not\nbe lost."
		      << "\n\nPress enter to continue.";
	std::getline(std::cin, tempStr);
}
//-----------------------------------------------------------------------------------------------------
void clearScreen(){ std::cout << std::string(100, '\n'); }  //clears the screen
//-----------------------------------------------------------------------------------------------------
void displayFile(std::string file)
{
	//Simple enough function, opens the file and prints it onto the command line
	std::ifstream displayFile(file);
	std::string line = "";

	if (!displayFile)
	{
		std::cout << "Error opening the file: " << file << "\nPress enter to return to the main menu. . .";
		std::getline(std::cin, line);
		return;
	}
	std::cout << "Contentes of: " << file << std::endl << std::endl;
	std::getline(displayFile, line);
	while (displayFile)
	{
		std::cout << line << std::endl;
		std::getline(displayFile, line);
	}
	displayFile.close();

	std::cout << "\n\nPress enter to return to the menu. . .";
	std::getline(std::cin, line);

}
//-----------------------------------------------------------------------------------------------------
bool getFileName(std::string file)
{
	//checks if the file exists and if it contains the proper .txt extension
	std::ifstream checkFileExists(file);
	if (file.find(".txt") != std::string::npos)
		if (checkFileExists.good())
			return true;

	std::cout << "\nInvalid filename entered! Please re-enter a valid file name that exists."
			  << "\nMake sure you include the file extension.";
	return false;
}
//-----------------------------------------------------------------------------------------------------
void encryptFile(std::string file)
{
	int encryptionKey = 0;
	std::string encryptedFile = "", copyFile = "", temp = "";

	//Gets the user's encryption key, didn't know what a proper range would be so I made it 1 through 128
	//I did check out the ASCII table, 128 for a max number seemed to get the job done
	std::cout << "Enter the key for the encryption (A value between 1-128).";
	while (true)
	{
		std::cout << "\nKey: ";
		std::getline(std::cin, temp);

		std::stringstream myStream(temp);
		if (myStream >> encryptionKey && encryptionKey >= 1 && encryptionKey <= 128)
			break;
		std::cout << "\nInvalid key! Re-enter a value between 1 through 128.\n";
	}

	//Sets the new two files' base name
	copyFile = encryptedFile = file;

	//The txtPosition variable finds the position where the ".txt" file extension is, and is used as a placing position for the new file names
	int txtPosition = file.find(".txt");
	encryptedFile.insert(txtPosition, "Encrypted");
	copyFile.insert(txtPosition, "Copy");

	//Opens the original text file for input
	std::ifstream originalFile(file, std::ios::in | std::ios::beg);

	//This class encrypts the text file and outputs it to the newly named text file
	Encryption encrypt(encryptionKey);
	std::ofstream encryptFile(encryptedFile);
	//this filter function will set each character in the original text file plus whatever the encryption key value is
	encrypt.doFilter(originalFile, encryptFile);

	//creates a copy of the original text file
	CopyOriginal copyOfOrig;
	std::ofstream copyOfFile(copyFile);
	copyOfOrig.doFilter(originalFile, copyOfFile);

	originalFile.close();

	std::cout << "\nFile encrypted!\nThe encrypted file is named " << encryptedFile << "\nThe copy of the original is named " << copyFile;
	std::cout << "\nPress enter to return to the main menu. . . ";
	std::getline(std::cin, temp);
}
//-----------------------------------------------------------------------------------------------------
void decryptFile(std::string file)
{
	int decryptionKey = 0;
	std::string decryptedFile = "", copyFile = "", temp = "";

	//Decided to include the option to back out and return to the main menu
	std::cout << "Important!\nBefore you decrypt the file " << file << ", make sure the file\nhas first been encrypted and that you enter the proper encryption key.\n"
		   	  << "Are you sure you want to continue? (Y/N) ";
	do
	{
		std::getline(std::cin, temp);

		temp[0] = toupper(temp[0]);
		if (temp.length() != 1 || (temp[0] != 'Y' && temp[0] != 'N'))
		{
			std::cout << "\n\nInvalid input! Please re-enter your choice.\n'N' will bring you back to the main menu.\nChoice: ";
			continue;
		}
		else if (temp[0] == 'N')
			return;		
	} while (temp[0] != 'Y');

	copyFile = decryptedFile = file;

	//Finds the substring "Encrypted" in the encrypted text file name and replaces it with "Decrypted"
	//This isn't done with the copy because we want to have the word "Copy" at the end of Encrypted file's name
	int txtPosition = file.find("Encrypted");
	if (txtPosition == -1) {
		std::cout << "\n" << file << " is not an encrypted file.\nPress enter to return to the main menu. . .";
		std::getline(std::cin, temp);
		return;
	}
	decryptedFile.erase(txtPosition, 9);
	decryptedFile.insert(txtPosition, "Decrypted");
	copyFile.insert(txtPosition, "Copy");

	//If the text position is at -1, then the substring "Encrypted" was not found, and will return back to the main menu
	if (txtPosition == -1)
	{
		std::cout << "Error in opening the file!\nPlease make sure to next time include the word \"Encrypted\" in the file name.\n"
			      << "Press enter to return to the main menu. . . ";
		std::getline(std::cin, temp);
		return;
	}

	std::cout << "\n\nEnter the key for the decryption key (A value between 1-128).";
	while (true)
	{
		std::cout << "\nKey: ";
		std::getline(std::cin, temp);

		std::stringstream myStream(temp);
		if (myStream >> decryptionKey && decryptionKey >= 1 && decryptionKey <= 128)
			break;
		std::cout << "\nInvalid key! Re-enter a value between 1 through 128.\n";
	}

	//Opens the original text file for input
	std::ifstream originalFile(file, std::ios::in | std::ios::beg);

	//This class decrypts the text file and outputs it to the newly named text file
	Decryption decrypt(decryptionKey);
	std::ofstream decryptFile(decryptedFile);
	//this filter function will set each character in the original text file minus whatever the decryption key value is, which should find the original text
	decrypt.doFilter(originalFile, decryptFile);

	//creates a copy of the original text file
	CopyOriginal copyOfOrig;
	std::ofstream copyOfFile(copyFile);
	copyOfOrig.doFilter(originalFile, copyOfFile);

	originalFile.close();

	std::cout << "\nFile decrypted!\nThe decrypted file is named " << decryptedFile << "\nThe copy of the original is named " << copyFile;
	std::cout << "\nPress enter to return to the main menu. . . ";
	std::getline(std::cin, temp);
}
//-----------------------------------------------------------------------------------------------------
void uppercaseFile(std::string file)
{	
	/*
		Many of the same operations are performed like they were in the encryptFile() function above.
		There isn't much of a difference besides not using an encryption key and the file names.
	*/
	std::string upperCaseFileName = "", copyFile = "", temp = "";

	copyFile = upperCaseFileName = file;
	int txtPosition = upperCaseFileName.find(".txt");
	upperCaseFileName.insert(txtPosition, "UpperCase");
	copyFile.insert(txtPosition, "Copy");
	
	//Opens the original text file for input
	std::ifstream originalFile(file, std::ios::in);
	
	//This class sets each character from the original text file to uppercase
	UpperCase upperCaseTextFile;
	std::ofstream allCaps(upperCaseFileName);
	upperCaseTextFile.doFilter(originalFile, allCaps);

	//creates a copy of the original and then closes the file
	CopyOriginal copyOfOrig;
	std::ofstream copyOfFile(copyFile);
	copyOfOrig.doFilter(originalFile, copyOfFile);
		
	std::cout << "\nThe file " << file << " has been successfully converted to all uppercase text.\n" 
			  << "The all-uppercase file is named " << upperCaseFileName << "\nThe copy of the original is named " << copyFile;
	std::cout << "\nPress enter to return to the main menu. . . ";
	std::getline(std::cin, temp);
}
//-----------------------------------------------------------------------------------------------------