#pragma once

#include <Windows.h> // Required for openGL on windows
#include <gl/GL.h> //OpenGL
#include <gl/GLU.h> // OpenGL Utilities
#include "GL/freeglut.h" // freeglut library
#include "GLUTCallebacks.h"
#include "Structures.h"
#include "Cube.h"
#include "PyramidObject.h"

#define REFRESHRATE 16

class HelloGL
{
public:
	//constructer definition
	HelloGL(int argc, char* argv[]);

	void Display();

	//destructer
	~HelloGL(void);

	//Creating Game Loop
	void Update();

	void Keyboard(unsigned char key, int x, int y);

	void InitObjects();
	void InitGl(int argc, char* argv[]);

	void Lighting();
	
private:

	float rotation;

	Camera* camera;
	//Cube* cube[200];
	SceneObject* objects[200];

	Vector4* _lightPosition;
	lighting* _lightData;

};


