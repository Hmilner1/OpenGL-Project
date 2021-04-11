#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "Structures.h"
#include "SceneObject.h"
class Pyramid : public SceneObject
{
private:
	GLfloat _rotation;
	Vector3 _position;
	Material* _material;
public:
	Pyramid(Mesh* mesh, Texture2D* texture, float x, float y, float z);
	~Pyramid();

	void Draw();
	void Update();
	void material();
};

