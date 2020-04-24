#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "Structures.h"
#include"SceneObject.h"

class PyramidObject : public SceneObject
{
private:
	//static Vertex* indexedVertices;
	//static Color* indexedColors;
	//static GLushort* indices;
	//Mesh* _mesh;

	static int numVertices, numColors, numIndices;

	GLfloat _rotation;

	Vector3 _position;

public:
	PyramidObject(Mesh* mesh, float x, float y, float z);
	~PyramidObject();

	void Draw();
	void Update();

	//static bool Load(char* path);
};
