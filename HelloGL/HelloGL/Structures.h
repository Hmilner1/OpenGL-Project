#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

struct Vector3
{
	float x;
	float y;
	float z;
};

struct Camera
{
	Vector3 eye;
	Vector3 center;
	Vector3 up;
};

struct Color
{
	GLfloat r, g, b;
};

struct Vertex
{
	GLfloat x, y, z;
};

struct TexCoord
{	
	GLfloat u, v;

};

struct Mesh
{
	Vertex* Vertices;
	//Color* Colors;
	Vector3* Normals;
	GLushort* Indices;
	int VertexCount, NormalCount, IndexCount, TexCoordCount;
	TexCoord* TexCoords;
};

struct Vector4
{
	float x, y, z, w;
};

struct Lighting
{
	Vector4 Ambient, Diffuse, Specular; 
};

struct Material
{
	Vector4 Ambient, Diffuse, Specular;
	GLfloat Shininess;
};

struct Sphere
{
	float radius;
	Vector3 position;
};

