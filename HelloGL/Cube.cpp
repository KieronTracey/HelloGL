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

Cube::Cube(Mesh* mesh, Texture2D* texture, float x, float y, float z) : SceneObject(mesh)
{
	_rotation = 0.0f;

	_position.x = x;
	_position.y = y;
	_position.z = z;

	//_mesh = mesh;
}

Cube::~Cube()
{
}

void Cube::Draw()
{
	if (_mesh->Vertices != nullptr && _mesh->Normals != nullptr && _mesh->Indices != nullptr)
	{
		glBindTexture(GL_TEXTURE_2D, _texture->GetID());
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);


		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, _mesh->Vertices);
		glColorPointer(3, GL_FLOAT, 0, _mesh->Normals);

		glTranslatef(_position.x, _position.y, _position.z);

		glRotatef(_rotation, 1.0f, 0.0f, 0.0f);

		glTexCoordPointer(2, GL_FLOAT, 0, _mesh->TexCoords);

		Material();
		glMaterialfv(GL_FRONT, GL_AMBIENT, &(_material->Ambient.x));

		glMaterialf(GL_FRONT, GL_SHININESS, _material->Shininess);
		glMaterialf(GL_FRONT, GL_DIFFUSE, _material->Diffuse);
		glMaterialf(GL_FRONT, GL_SPECULAR, _material->Specular);

		glPushMatrix();



		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, _mesh->Indices);

		glPopMatrix();

		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}
}

void Cube::Update()
{
	_rotation = 0.1f;

	if (_rotation >= 360.0f)
		_rotation = 0.0f;
}

void Cube::Material()
{
//create a shiny object with high specular reflection that primarily reflects red light
	_material = new Material();
	_material->Ambient.x = 0.8; _material->Ambient.y = 0.05; _material->Ambient.z = 0.05;
	_material->Ambient.w = 1.0;
	_material->Diffuse.x = 0.8; _material->Diffuse.y = 0.05; _material->Diffuse.z = 0.05;
	_material->Diffuse.w = 1.0;
	_material->Specular.x = 1.0; _material->Specular.y = 1.0; _material->Specular.z = 1.0;
	_material->Specular.w = 1.0;
	_material->Shininess = 100.0f;

	//Ambient is the most basic. It gives a uniform sort of colour to an object, while the parts of the object that are 'sheltered' from the light. There is normally a certain intensity and colour involved. The result is a sort of matte looking object.

	//Diffuse lighting of an object approximates how photons will bounce off the object's surface in many different directions (rather than just a single reflection, which will be discussed later). Combine this with ambient light and you have a warmer looking object with a little bit more finish.

		//Specular lighting is considering the direct reflection of photons off the surface.It affects a very localized part of the object and gives it a very shiny finish.The effect from specular lighting is called a specular highlight.

}




//bool Cube::Load(char* path)
//{
//	std::ifstream input;
//	input.open("cube.txt");
//	if (!input.good())
//	{
//		std::cerr << "Can't open text file " << path << std::endl;
//		return false;
//	}
//
//	input >> numVertices;
//	indexedVertices = new Vertex[numVertices];
//	for (int i = 0; i < numVertices; i++)
//	{
//		//TODO Use inFile to populate the indexedVertices array
//		input >> indexedVertices[i].x;
//		input >> indexedVertices[i].y;
//		input >> indexedVertices[i].z;
//	}
//
//	input >> numColors;
//	indexedColors = new Color[numColors];
//	for (int i = 0; i < numColors; i++)
//	{
//		//TODO Use inFile to populate the indexedVertices array
//		input >> indexedColors[i].r;
//		input >> indexedColors[i].g;
//		input >> indexedColors[i].b;
//
//	}
//
//	input >> numIndices;
//	indices = new GLushort[numIndices];
//	for (int i = 0; i < numIndices; i++)
//	{
//		//TODO Use inFile to populate the indexedVertices array
//		input >> indices[i];
//
//	}
//
//
//	input.close();
//
//	return true;
//}


