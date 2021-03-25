#include "Cube.h"
#include <iostream>
#include <fstream>

Cube::Cube(Mesh* mesh, Texture2D* texture, float x, float y, float z) : SceneObject(mesh, texture)
{
	_position = { x, y, z };
	_rotation = 0.0f;
	
}

Cube::~Cube()
{
	
}

void Cube::Draw()
{
	glBindTexture(GL_TEXTURE_2D, _texture->GetID());
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	//glEnableClientState(GL_COLOR_ARRAY);
	glEnable(GL_NORMAL_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, _mesh->Vertices);
	//glColorPointer(3, GL_FLOAT, 0, _mesh->Colors);
	glNormalPointer(GL_FLOAT, 0, _mesh->Normals);
	glTexCoordPointer(2, GL_FLOAT, 0, _mesh->TexCoords);
	material();
	glMaterialfv(GL_FRONT, GL_AMBIENT, &(_material->Ambient.x));
	glMaterialf(GL_FRONT, GL_DIFFUSE, (_material->Diffuse.x));
	glMaterialf(GL_FRONT, GL_SPECULAR, (_material->Specular.x));
	glMaterialf(GL_FRONT, GL_SHININESS, _material->Shininess);
	glPushMatrix();
	glTranslatef(_position.x, _position.y, _position.z);
//	glRotatef(_rotation, 1.0f, 0.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, _mesh->Indices);
	glPopMatrix();
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void Cube::Update()
{
	_rotation += 1.1f;
}


void Cube::material()
{
	_material = new Material();
	_material->Ambient.x = 0.8; _material->Ambient.y = 0.05; _material->Ambient.z = 0.05;
	_material->Ambient.w = 1.0;
	_material->Diffuse.x = 0.8; _material->Diffuse.y = 0.05; _material->Diffuse.z = 0.05;
	_material->Diffuse.w = 1.0;
	_material->Specular.x = 1.0; _material->Specular.y = 1.0; _material->Specular.z = 1.0;
	_material->Specular.w = 1.0;
	_material->Shininess = 100.0f;
}