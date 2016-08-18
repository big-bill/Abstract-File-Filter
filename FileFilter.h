#ifndef FILEFILTER_H
#define FILEFILTER_H
#include <iostream>
#include <string>
#include <cctype>
#include <fstream>
#include <sstream>
/*
	I didn't include much in the FileFilter.cpp file because most of the functions here
	in the classes can simply be written as one line functions in the definitions of each class
*/


class FileFilter
{
public:
	void doFilter(std::ifstream &in, std::ofstream &out);
	virtual char transform(char ch)	const = 0;
};

class Encryption : public FileFilter
{
private: 
	int key;
public:
	Encryption(int key) { this->key = key; }
	char transform(char ch) const { return ch + key; }
};

class Decryption : public FileFilter
{
private:
	int decryptionKey;
public:
	Decryption(int decryptionKey) { this->decryptionKey = decryptionKey; }
	char transform(char ch) const { return ch - decryptionKey; }
};

class UpperCase : public FileFilter
{
public:
	char transform(char ch) const { return toupper(ch); }
};

class CopyOriginal : public FileFilter
{
public:
	char transform(char ch) const { return ch; }
};

#endif