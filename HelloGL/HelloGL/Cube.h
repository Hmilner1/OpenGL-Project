#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "Structures.h"
#include "SceneObject.h"
class Cube : public SceneObject
{
private:
	Material* _material;
	
public:
	Cube(Mesh* mesh, Texture2D* texture,float x, float y, float z);
	~Cube();

	void Draw();
	void Update();
	void material();
	//Vector3 _position;
	GLfloat _rotation;
};


