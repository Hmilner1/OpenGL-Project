#include "Pyramid.h"
#include <iostream>
#include <fstream>

Pyramid::Pyramid(Mesh* mesh, Texture2D* texture, float x, float y, float z) : SceneObject(mesh, texture)
{
	_position = { x, y, z };
	_rotation = 0.0f;
}

Pyramid::~Pyramid()
{

}

void Pyramid::Draw()
{
	if (_mesh->Vertices != nullptr && _mesh->Normals != nullptr && _mesh->Indices != nullptr)
	{
		glBindTexture(GL_TEXTURE_2D, _texture->GetID());
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnable(GL_NORMAL_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, _mesh->Vertices);
		glNormalPointer(GL_FLOAT, 0, _mesh->Normals);
		glTexCoordPointer(2, GL_FLOAT, 0, _mesh->TexCoords);
		material();
		//glMaterialf(GL_FRONT, GL_SHININESS, _material->Shininess);
		glPushMatrix();
		glTranslatef(_position.x, _position.y, _position.z);
		glRotatef(_rotation, 0.0f, 1.0f, 0.0f);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, _mesh->Indices);
		glPopMatrix();
		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}
}

void Pyramid::Update()
{
	_rotation += 0.4f;
}

void Pyramid::material()
{
	_material = new Material();
	_material->Ambient.x = 0.0; _material->Ambient.y = 0.0; _material->Ambient.z = 0.0;
	_material->Ambient.w = 1.0;
	_material->Diffuse.x = 0.0; _material->Diffuse.y = 0.0; _material->Diffuse.z = 0.0;
	_material->Diffuse.w = 0.0;
	_material->Specular.x = 0.0; _material->Specular.y = 0.0; _material->Specular.z = 0.0;
	_material->Specular.w = 0.0;
	_material->Shininess = 0.0;
}