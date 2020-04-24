#include "PyramidObject.h"
#include <fstream>
#include <iostream>

//Vertex* Cube::indexedVertices = nullptr;
//
//Color* Cube::indexedColors = nullptr;
//
//GLushort* Cube::indices = nullptr;
//
//int Cube::numVertices = 0;
//int Cube::numColors = 0;
//int Cube::numIndices = 0;

PyramidObject::PyramidObject(Mesh* mesh, float x, float y, float z) : SceneObject(mesh,nullptr)
{
	_rotation = 0.0f;

	_position.x = x;
	_position.y = y;
	_position.z = z;

	_mesh = mesh;
}

PyramidObject::~PyramidObject()
{
}

void PyramidObject::Draw()
{
	if (_mesh->Vertices != nullptr && _mesh->Colors != nullptr && _mesh->Indices != nullptr)
	{
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, _mesh->Vertices);
		glColorPointer(3, GL_FLOAT, 0, _mesh->Colors);

		glTranslatef(_position.x , _position.y, _position.z);

		glRotatef(_rotation, 1.0f, 0.0f, 0.0f);

		glPushMatrix();



		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, _mesh->Indices);

		glPopMatrix();

		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
	}
}

void PyramidObject::Update()
{
	_rotation = 0.1f;

	if (_rotation >= 360.0f)
		_rotation = 0.0f;
}