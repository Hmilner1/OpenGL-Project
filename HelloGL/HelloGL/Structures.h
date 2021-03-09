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
	Color* Colors;
	GLushort* Indices;
	int VertexCount, ColorCount, IndexCount, TexCoordCount;
	TexCoord* TexCoords;
};
