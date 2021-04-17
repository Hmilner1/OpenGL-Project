#include "Texture2D.h"
#include "structures.h"
#include <fstream>
#include <iostream>
using namespace std;

Texture2D::Texture2D()
{

}

Texture2D::~Texture2D()
{
	//removes it from memory 
	glDeleteTextures(1, &_ID);
}
//loads texture file
bool Texture2D::Load(char* path, int width, int height)
{
	char* tempTextureData; int fileSize; ifstream inFile;
	_width = width; _height = height;
	inFile.open(path, ios::binary);
	//error checking 
	if (!inFile.good())
	{
		cerr << "Can't open texture file " << path << endl;
		return false;
	}
	inFile.seekg(0, ios::end); 
	fileSize = (int)inFile.tellg(); 
	//creates an array to store the data in 
	tempTextureData = new char[fileSize]; 
	inFile.seekg(0, ios::beg); 
	//reads the data in from a file
	inFile.read(tempTextureData, fileSize); 
	inFile.close(); 

	cout << path << " loaded." << endl;

	glGenTextures(1, &_ID); 
	glBindTexture(GL_TEXTURE_2D, _ID); 
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE,tempTextureData);
	//deletes the data that is no longer being used
	delete[] tempTextureData; 
	return true;
}
