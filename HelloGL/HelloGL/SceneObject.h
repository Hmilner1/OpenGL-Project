#pragma once
#include "Structures.h"
#include "Texture2D.h"
//base class allowinf for other shapes to inherit from it 
class SceneObject
{
protected:
	Mesh* _mesh;
	Texture2D* _texture;

public:
	SceneObject(Mesh* mesh, Texture2D* texture);
	virtual  ~SceneObject();
	virtual void Update();
	virtual void Draw();
	virtual void move(unsigned char key, int x, int y);
};

