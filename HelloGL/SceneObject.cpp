#include "SceneObject.h"

SceneObject::SceneObject(Mesh* mesh)
{
	_mesh = mesh;
}

SceneObject::~SceneObject()
{
}

void SceneObject::Update()
{
}

void SceneObject::Draw()
{
}

SceneObject::SceneObject(Mesh* mesh, Texture2D* texture)
{
}
