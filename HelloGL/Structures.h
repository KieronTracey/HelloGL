#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL/freeglut.h"



struct Vector3 { float x; float y; float z; };
struct Camera { Vector3 eye; Vector3 center; Vector3 up; };
struct Normal { GLfloat r, g, b; };
struct Vertex { GLfloat x, y, z; };

struct TexCoord
{
	GLfloat u;
	GLfloat v;



};

struct Mesh
{
	Vertex* Vertices;
	//Color* Colors;
	GLushort* Indices;
	TexCoord* TexCoords;
	int VertexCount, NormalCount, IndexCount, TexCoordCount;
	Vector3* Normals;
};

struct Vector4
{

	float x;
	float y;
	float z;
	float w;

};

struct lighting
{

	Vector4 Ambient;
	Vector4 Diffuse;
	Vector4 Specular;

};

struct Material
{

	Vector4 Ambient;
	Vector4 Diffuse;
	Vector4 Specular;
	GLfloat Shininess;

};