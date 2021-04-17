#include "Pyramid.h"
#include <iostream>
#include <fstream>

Pyramid::Pyramid(Mesh* mesh, Texture2D* texture, float x, float y, float z) : SceneObject(mesh, texture)
{
	//postion and rotation
	_position = { x, y, z };
	_rotation = 30.0f;
}

Pyramid::~Pyramid()
{

}

void Pyramid::Draw()
{
	//if the files doesnt equal null then its continues to draw the shape 
	if (_mesh->Vertices != nullptr && _mesh->Normals != nullptr && _mesh->Indices != nullptr)
	{
		//draws shape and sets its rotation and lighting from the mesh loader 
		glBindTexture(GL_TEXTURE_2D, _texture->GetID());
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnable(GL_NORMAL_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, _mesh->Vertices);
		glNormalPointer(GL_FLOAT, 0, _mesh->Normals);
		glTexCoordPointer(2, GL_FLOAT, 0, _mesh->TexCoords);
		material();
		glPushMatrix();
		glTranslatef(_position.x, _position.y, _position.z);
		glRotatef(_rotation, 0.1f, 0.1f, 0.0f);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, _mesh->Indices);
		glPopMatrix();
		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}
}

void Pyramid::Update()
{

}

void Pyramid::material()
{
	// holds all the lighting information for the pyramid 
	_material = new Material();
	_material->Ambient.x = 0.01; _material->Ambient.y = 0.01; _material->Ambient.z = 0.01;
	_material->Ambient.w = 100.0;
	_material->Diffuse.x = 0.0; _material->Diffuse.y = 0.0; _material->Diffuse.z = 0.0;
	_material->Diffuse.w = 0.0;
	_material->Specular.x = 0.0; _material->Specular.y = 0.0; _material->Specular.z = 0.0;
	_material->Specular.w = 0.0;
	_material->Shininess = 0.0;
}