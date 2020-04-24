#include "Cube.h"
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

Cube::Cube(Mesh* mesh, float x, float y, float z)
{
	_rotation = 0.0f;

	_position.x = x;
	_position.y = y;
	_position.z = z;

	_mesh = mesh;
}

Cube::~Cube()
{
}

void Cube::Draw()
{
	if (_mesh->Vertices != nullptr && _mesh->Colors != nullptr && _mesh->Indices != nullptr)
	{
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, _mesh->Vertices);
		glColorPointer(3, GL_FLOAT, 0, _mesh->Colors);

		glTranslatef(_position.x, _position.y, _position.z);

		glRotatef(_rotation, 1.0f, 0.0f, 0.0f);

		glPushMatrix();



		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, _mesh->Indices);

		glPopMatrix();

		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
	}
}

void Cube::Update()
{
	_rotation = 0.1f;

	if (_rotation >= 360.0f)
		_rotation = 0.0f;
}

/*
bool Cube::Load(char* path)
{
	std::ifstream input;
	input.open("cube.txt");
	if (!input.good())
	{
		std::cerr << "Can't open text file " << path << std::endl;
		return false;
	}

	input >> numVertices;
	indexedVertices = new Vertex[numVertices];
	for (int i = 0; i < numVertices; i++)
	{
		//TODO Use inFile to populate the indexedVertices array
		input >> indexedVertices[i].x;
		input >> indexedVertices[i].y;
		input >> indexedVertices[i].z;
	}

	input >> numColors;
	indexedColors = new Color[numColors];
	for (int i = 0; i < numColors; i++)
	{
		//TODO Use inFile to populate the indexedVertices array
		input >> indexedColors[i].r;
		input >> indexedColors[i].g;
		input >> indexedColors[i].b;

	}

	input >> numIndices;
	indices = new GLushort[numIndices];
	for (int i = 0; i < numIndices; i++)
	{
		//TODO Use inFile to populate the indexedVertices array
		input >> indices[i];

	}


	input.close();

	return true;
}
*/

