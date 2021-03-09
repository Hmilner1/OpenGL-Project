#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL/freeglut.h"
#include "Structures.h"
#include "Cube.h"
#include "Pyramid.h"
//this can be changed to 7 to run 140 fps
#define REFRESHRATE 16

class HelloGL
{
public:
	//constructor
	HelloGL(int argc, char* argv[]);
	//destructor
	~HelloGL(void);
	void Display();
	void Update();
	void Keyboard(unsigned char key, int x, int y);
	void InitObjects();
	void InitGL(int argc, char* argv[]);
private:
	Camera* camera;  
	SceneObject* objects[1000];
	
};


