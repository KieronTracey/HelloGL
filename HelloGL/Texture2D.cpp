#include "Texture2D.h"
#include <fstream>
#include <iostream>
using namespace std;

Texture2D::Texture2D()
{
}

Texture2D::~Texture2D()
{
	glDeleteTextures(1, &_ID);
}

bool Texture2D::Load(char* path, int width, int height)
{
	char* tempTextureData; int fileSize; ifstream inFile;

	_width = width; _height = height;

	inFile.open(path, ios::binary);

	if (!inFile.good())
	{

		cerr << "Can't open texture file" << path << endl;
		return false;

	}

	inFile.seekg(0, ios::end); // seek the end of the file
	fileSize = (int)inFile.tellg(); // get the current position in file - the end, this gives us total file size
	tempTextureData = new char[fileSize]; // create a new array to store data
	inFile.seekg( 0, ios::beg ); // seek back to the beginning of file
	inFile.read(tempTextureData, fileSize); // read in all the data in one go
	inFile.close(); // close the file

	cout << path << "loaded." << endl;

	glGenTextures(1, &_ID); // get next texture ID
	glBindTexture(GL_TEXTURE_2D, _ID);//bind the texture to the id
	//glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, tempTextureData);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, tempTextureData);

	delete[] tempTextureData; //clear up the data, we dont need this anymore

	return true;






}
