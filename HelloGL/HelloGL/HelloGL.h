#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL/freeglut.h"
#include "Structures.h"
#include <math.h>
#include "Cube.h"
#include "Pyramid.h"
#include "GLUTCallbacks.h"
#include "MeshLoader.h"
#include <iostream>
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
//	void reshape(int w, int h);
	void Keyboard(unsigned char key, int x, int y);
	void InitObjects();
	void InitGL(int argc, char* argv[]);
	void Light();
	void DrawString(const char* text, Vector3* position, Color* color);
	float calculateDistanceSquared(Sphere s1, Sphere s2);
	void drawSpheres(float distance, bool distanceSquared);
//	void initSpheres();
	void displayTxt();
private:
	Camera* camera;  
	SceneObject* objects[1];
	SceneObject* object2[1];
	Sphere sphere1;
	Sphere sphere2;
	Vector4* _lightPosition;
	Lighting* _lightData;
	
};


