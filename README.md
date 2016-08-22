# Abstract-File-Filter
### Project 3 for COP 2228

I really liked this project. The abstract file filter class was simple to make and I never really had any issues. I also included a decryption subclass (might as well if there's an encryption one) that will decipher encrypted files. Nothing extraordinary. Only thing I would have done differently was probably make the naming of the file names shorter and maybe add exception handling in places. The problem statement asked for a copy of the original to always be made, so the directory can become cluttered after a few uses. 

Project 3 description:

A file filter reads an input file, transforms it in some way, and writes the result to an output file.
Write an abstract file filter class that defines a pure virtual function for transforming a character.
Create one subclass of your file filter class the performs the encryption, another that transforms a file to all uppercase, and another that creates an unchanged copy of the original file.

The class should have a member function

#### void doFilter(ifstream &in, oftream &out)
that is called to perform the actual filtering. The member function for transforming a single character should have the prototype
	
#### char transform(char ch)
The encryption class should have a constructor that takes an integer as an arguement and uses it as the encryption key.
