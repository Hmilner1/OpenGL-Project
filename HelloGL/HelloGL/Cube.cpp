#include "Cube.h"
#include <iostream>
#include <fstream>

Cube::Cube(Mesh* mesh, Texture2D* texture, float x, float y, float z) : SceneObject(mesh, texture)
{
	//sets rotation and allows to change postion 
	_position = { x, y, z };
	_rotation = 0.0f;
}

Cube::~Cube()
{
	
}

void Cube::Draw()
{
	//laods in the correction information from the mesh loader and takes lighting from the metrials function to draw the cube 
	glBindTexture(GL_TEXTURE_2D, _texture->GetID());
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnable(GL_NORMAL_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, _mesh->Vertices);
	glNormalPointer(GL_FLOAT, 0, _mesh->Normals);
	glTexCoordPointer(2, GL_FLOAT, 0, _mesh->TexCoords);
	material();
	glMaterialfv(GL_FRONT, GL_AMBIENT, &(_material->Ambient.x));
	glMaterialf(GL_FRONT, GL_DIFFUSE, (_material->Diffuse.x));
	glMaterialf(GL_FRONT, GL_SPECULAR, (_material->Specular.x));
	glMaterialf(GL_FRONT, GL_SHININESS, _material->Shininess);
	glPushMatrix();
	glTranslatef(_position.x, _position.y, _position.z);
	glRotatef(_rotation, 0.1f, 1.0f, 0.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, _mesh->Indices);
	glPopMatrix();
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void Cube::Update()
{
	_rotation += 0.5f;
}

void Cube::material()
{
	//hold all of the lighting information to be used in the draw 
	_material = new Material();
	_material->Ambient.x = 0.55; _material->Ambient.y = 0.55; _material->Ambient.z = 0.55;
	_material->Ambient.w = 1.0;
	_material->Diffuse.x = 255.8; _material->Diffuse.y = 0.05; _material->Diffuse.z = 0.05;
	_material->Diffuse.w = 1.0;
	_material->Specular.x = 255.0; _material->Specular.y = 1.0; _material->Specular.z = 1.0;
	_material->Specular.w = 1.0;
	_material->Shininess = 1.0f;
}

void Cube::move(unsigned char key, int x, int y)
{
	//allows for movement to be passed from cube to the main
	if (key == 'd')
	{
		_position.x += 0.1f;
	}
	else if (key == 'a')
	{
		_position.x -= 0.1f;
	}
	else if (key == 's')
	{
		_position.z += 0.1f;
	}
}