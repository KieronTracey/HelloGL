#include "HelloGL.h"
#include "MeshLoader.h"
/*
Vertex HelloGL::vertices[] = { 1, 1, 1,  -1, 1, 1,  -1,-1, 1,      // v0-v1-v2 (front)
				-1,-1, 1,   1,-1, 1,   1, 1, 1,      // v2-v3-v0

				1, 1, 1,   1,-1, 1,   1,-1,-1,      // v0-v3-v4 (right)
				1,-1,-1,   1, 1,-1,   1, 1, 1,      // v4-v5-v0

				1, 1, 1,   1, 1,-1,  -1, 1,-1,      // v0-v5-v6 (top)
				-1, 1,-1,  -1, 1, 1,   1, 1, 1,      // v6-v1-v0

				-1, 1, 1,  -1, 1,-1,  -1,-1,-1,      // v1-v6-v7 (left)
				-1,-1,-1,  -1,-1, 1,  -1, 1, 1,      // v7-v2-v1

				-1,-1,-1,   1,-1,-1,   1,-1, 1,      // v7-v4-v3 (bottom)
				1,-1, 1,  -1,-1, 1,  -1,-1,-1,      // v3-v2-v7

				1,-1,-1,  -1,-1,-1,  -1, 1,-1,      // v4-v7-v6 (back)
				-1, 1,-1,   1, 1,-1,   1,-1,-1 };    // v6-v5-v4

Color HelloGL::colors[] = { 1, 1, 1,   1, 1, 0,   1, 0, 0,      // v0-v1-v2 (front)
				1, 0, 0,   1, 0, 1,   1, 1, 1,      // v2-v3-v0

				1, 1, 1,   1, 0, 1,   0, 0, 1,      // v0-v3-v4 (right)
				0, 0, 1,   0, 1, 1,   1, 1, 1,      // v4-v5-v0

				1, 1, 1,   0, 1, 1,   0, 1, 0,      // v0-v5-v6 (top)
				0, 1, 0,   1, 1, 0,   1, 1, 1,      // v6-v1-v0

				1, 1, 0,   0, 1, 0,   0, 0, 0,      // v1-v6-v7 (left)
				0, 0, 0,   1, 0, 0,   1, 1, 0,      // v7-v2-v1

				0, 0, 0,   0, 0, 1,   1, 0, 1,      // v7-v4-v3 (bottom)
				1, 0, 1,   1, 0, 0,   0, 0, 0,      // v3-v2-v7

				0, 0, 1,   0, 0, 0,   0, 1, 0,      // v4-v7-v6 (back)
				0, 1, 0,   0, 1, 1,   0, 0, 1 };    // v6-v5-v4

Vertex HelloGL::indexedVertices[] = { 1, 1, 1,  -1, 1, 1,  // v0,v1,
				-1,-1, 1,   1,-1, 1,   // v2,v3
				1,-1,-1,   1, 1,-1,    // v4,v5
				-1, 1,-1,   -1,-1,-1 }; // v6,v7

Color HelloGL::indexedColors[] = { 1, 1, 1,   1, 1, 0,   // v0,v1,
				1, 0, 0,   1, 0, 1,   // v2,v3
				0, 0, 1,   0, 1, 1,   // v4,v5
				0, 1, 0,   0, 0, 0 }; //v6,v7

GLushort HelloGL::indices[] = { 0, 1, 2,  2, 3, 0,      // front
				0, 3, 4,  4, 5, 0,      // right
				0, 5, 6,  6, 1, 0,      // top
				1, 6, 7,  7, 2, 1,      // left
				7, 4, 3,  3, 2, 7,      // bottom
				4, 7, 6,  6, 5, 4 };    // back
*/




HelloGL::HelloGL(int argc, char* argv[])
{
	
	InitGl(argc, argv);
	InitObjects();

	Lighting();

	glutMainLoop();


}


HelloGL::~HelloGL()
{
	delete camera;
}




void HelloGL::Display()
{
	glClear(GL_COLOR_BUFFER_BIT); // this clears the scene

	for (int i = 0; i < 200; i++)
	{
		objects[i]->Draw();

	}

	glFlush(); // flushes the scene drawn to the graphics card

	glutSwapBuffers();
}

void HelloGL::Update()
{
	glLoadIdentity();

	gluLookAt(camera->eye.x, camera->eye.y, camera->eye.z, camera->center.x, camera->center.y, camera->center.z, camera->up.x, camera->up.y, camera->up.z);

	

	for (int i = 0; i < 200; i++)
	{
		objects[i]->Update();

	}

	glLightfv(GL_LIGHT0, GL_AMBIENT, &(_lightData->Ambient.x));
	glLightfv(GL_LIGHT0, GL_DIFFUSE, &(_lightData->Diffuse.x));
	glLightfv(GL_LIGHT0, GL_SPECULAR, &(_lightData->Specular.x));

	glLightfv(GL_LIGHT0, GL_POSITION, &(_lightPosition->x));

	glutPostRedisplay();

	//Cube::Load((char*)"cube.txt");
	
}



void HelloGL::Keyboard(unsigned char key, int x, int y)
{
	if (key == 'd')
		rotation += 0.5f;

	if (key == 'a')
		rotation -= 0.5f;

	if (key == 'w')
		camera->eye.z += 0.1f;

	if (key == 's')
		camera->eye.z -= 0.1f;
}

void HelloGL::InitObjects()
{

	// set the viewport to be the entire window
	glViewport(0, 0, 800, 800);

	// set the correct perspective
	gluPerspective(45, 1, 0.1, 1000);

	glMatrixMode(GL_MODELVIEW);

	// setting up camera
	camera = new Camera();

	//setting up cube
	
	Mesh* cubeMesh = MeshLoader::Load((char*)"cube.txt");

	Texture2D* texture = new Texture2D();
	texture->Load((char*)"penguins.raw", 512, 512);

	for (int i = 0; i < 100; i++)
	{
		objects[i] = new Cube(cubeMesh, texture,((rand() % 400) / 10.0f) - 20.0f, ((rand() % 200) / 10.0f) - 10.0f, -(rand() % 1000) / 10.0f);

	}

	//setting up pyramids

	//Mesh* pyramidMesh = MeshLoader::Load((char*)"pyramid.txt");

	//for (int i = 100; i < 200; i++)
	//{
	//	objects[i] = new PyramidObject(pyramidMesh, ((rand() % 400) / 10.0f) - 20.0f, ((rand() % 200) / 10.0f) - 10.0f, -(rand() % 1000) / 10.0f);

	//}

	

	camera->eye.x = 0.0f; camera->eye.y = 0.0f; camera->eye.z = 1.0f;
	//camera->eye.x = 5.0f; camera->eye.y = 5.0f; camera->eye.z = -5.0f;

	camera->center.x = 0.0f; camera->center.y = 0.0f; camera->center.z = 0.0f;
	camera->up.x = 0.0f; camera->up.y = 1.0f; camera->up.z = 0.0f;

}

void HelloGL::InitGl(int argc, char* argv[])
{
	GLUTCallbacks::Init(this);
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Simple OpenGL Program");
	glutKeyboardFunc(GLUTCallbacks::Keyboard);
	glutDisplayFunc(GLUTCallbacks::Display);
	glutTimerFunc(REFRESHRATE, GLUTCallbacks::Timer, REFRESHRATE);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glEnable(GL_TEXTURE_2D); // without this you will just get white boxes
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

void HelloGL::Lighting()
{
	_lightPosition = new Vector4();
	_lightPosition->x = 0.0;
	_lightPosition->y = 0.0;
	_lightPosition->z = 1.0;
	_lightPosition->w = 0.0;

	_lightData = new Lighting();
	_lightData->Ambient.x = 0.2;
	_lightData->Ambient.y = 0.2;
	_lightData->Ambient.z = 0.2;
	_lightData->Ambient.w = 1.0;
	_lightData->Diffuse.x = 0.8;
	_lightData->Diffuse.y = 0.8;
	_lightData->Diffuse.z = 0.8;
	_lightData->Diffuse.w = 1.0;
	_lightData->Specular.x = 0.2;
	_lightData->Specular.y = 0.2;
	_lightData->Specular.z = 0.2;
	_lightData->Specular.w = 1.0;

}





//void HelloGL::DrawPolygon()
//{
//	glPushMatrix();
//	glTranslatef(0.0f, 0.0f, -5.0f);
//	glRotatef(rotation, 1.0f, 0.0f, 0.0f);
//
//	glutWireDodecahedron();
//
//	/*glBegin(GL_POLYGON); //starts to draw a polygon
//	{
//		glColor4f(1.0f, 0.0f, 0.0f, 0.0f);
//		glVertex2f(-0.75, 0.5); //define the first point og the polygon, top left
//		glColor4f(1.0f, 1.0f, 0.0f, 0.0f);
//		glVertex2f(0.0, 0.5); // next point, top right
//		glVertex2f(0.0, -0.0); // bottom right
//		glVertex2f(-0.75, 0.0); // last point, bottom left
//		glEnd(); // defines the end of the draw
//	}
//	*/
//
//	glPopMatrix();
//
//	
//	glPushMatrix();
//	glTranslatef(0.0f, 0.0f, -5.0f);
//	glRotatef(rotation, 10.0f, 5.0f, 5.0f);
//
//	glutWireOctahedron();
//
//	/*
//	glBegin(GL_POLYGON); //starts to draw a polygon
//	{
//		glColor4f(1.0f, 0.0f, 0.0f, 0.0f);
//		glVertex2f(1.0, 0.5); //define the first point og the polygon, top left
//		glColor4f(1.0f, 1.0f, 0.0f, 0.0f);
//		glVertex2f(0.0, 0.0); // next point, top right
//		glVertex2f(0.3, 0.0); // last point, bottom left
//		glEnd(); // defines the end of the draw
//	}
//	*/
//
//	glPopMatrix();
//	
//}

//void HelloGL::DrawCube()
//{
//	glRotatef(rotation, 10.0f, 5.0f, 5.0f);
//
//	glBegin(GL_TRIANGLES);
//	// face v0-v1-v2
//	glColor3f(1, 1, 1);
//	glVertex3f(1, 1, 1);
//	glColor3f(1, 1, 0);
//	glVertex3f(-1, 1, 1);
//	glColor3f(1, 0, 0);
//	glVertex3f(-1, -1, 1);
//	// face v2-v3-v0
//	glColor3f(1, 0, 0);
//	glVertex3f(-1, -1, 1);
//	glColor3f(1, 0, 1);
//	glVertex3f(1, -1, 1);
//	glColor3f(1, 1, 1);
//	glVertex3f(1, 1, 1);
//
//	// face v0-v3-v4
//	glColor3f(1, 1, 1);
//	glVertex3f(1, 1, 1);
//	glColor3f(1, 0, 1);
//	glVertex3f(1, -1, 1);
//	glColor3f(0, 0, 1);
//	glVertex3f(1, -1, -1);
//	// face v4-v5-v0
//	glColor3f(0, 0, 1);
//	glVertex3f(1, -1, -1);
//	glColor3f(0, 1, 1);
//	glVertex3f(1, 1, -1);
//	glColor3f(1, 1, 1);
//	glVertex3f(1, 1, 1);
//
//	// face v0-v5-v6
//	glColor3f(1, 1, 1);
//	glVertex3f(1, 1, 1);
//	glColor3f(0, 1, 1);
//	glVertex3f(1, 1, -1);
//	glColor3f(0, 1, 0);
//	glVertex3f(-1, 1, -1);
//	// face v6-v1-v0
//	glColor3f(0, 1, 0);
//	glVertex3f(-1, 1, -1);
//	glColor3f(1, 1, 0);
//	glVertex3f(-1, 1, 1);
//	glColor3f(1, 1, 1);
//	glVertex3f(1, 1, 1);
//
//	// face  v1-v6-v7
//	glColor3f(1, 1, 0);
//	glVertex3f(-1, 1, 1);
//	glColor3f(0, 1, 0);
//	glVertex3f(-1, 1, -1);
//	glColor3f(0, 0, 0);
//	glVertex3f(-1, -1, -1);
//	// face v7-v2-v1
//	glColor3f(0, 0, 0);
//	glVertex3f(-1, -1, -1);
//	glColor3f(1, 0, 0);
//	glVertex3f(-1, -1, 1);
//	glColor3f(1, 1, 0);
//	glVertex3f(-1, 1, 1);
//
//	// face v7-v4-v3
//	glColor3f(0, 0, 0);
//	glVertex3f(-1, -1, -1);
//	glColor3f(0, 0, 1);
//	glVertex3f(1, -1, -1);
//	glColor3f(1, 0, 1);
//	glVertex3f(1, -1, 1);
//	// face v3-v2-v7
//	glColor3f(1, 0, 1);
//	glVertex3f(1, -1, 1);
//	glColor3f(1, 0, 0);
//	glVertex3f(-1, -1, 1);
//	glColor3f(0, 0, 0);
//	glVertex3f(-1, -1, -1);
//
//	// face v4-v7-v6
//	glColor3f(0, 0, 1);
//	glVertex3f(1, -1, -1);
//	glColor3f(0, 0, 0);
//	glVertex3f(-1, -1, -1);
//	glColor3f(0, 1, 0);
//	glVertex3f(-1, 1, -1);
//	// face v6-v5-v4
//	glColor3f(0, 1, 0);
//	glVertex3f(-1, 1, -1);
//	glColor3f(0, 1, 1);
//	glVertex3f(1, 1, -1);
//	glColor3f(0, 0, 1);
//	glVertex3f(1, -1, -1);
//
//	glEnd();
//}

//void HelloGL::DrawCubeArray()
//{
//
//	//glPushMatrix();
//
//	//glRotatef(rotation, 10.0f, 5.0f, 5.0f);
//
//	//glBegin(GL_TRIANGLES);
//	//for (int i = 0; i < 36; i++)
//	//{
//	//	//Implement draw code here
//	//	/*
//	//	glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);
//	//	glColor3f(colors[i].r, colors[i].g, colors[i].b);
//	//	*/
//
//	//	glColor3fv(&colors[i].r);
//	//	glVertex3fv(&vertices[i].x);
//
//	//}
//	//glEnd();
//
//	//glPopMatrix();
//}

//void HelloGL::DrawCubeIndexed()
//{
//
//		//glPushMatrix();
//
//		//glRotatef(rotation, 10.0f, 5.0f, 5.0f);
//
//		//glBegin(GL_TRIANGLES);
//		//for (int i = 0; i < 36; i++)
//		//{
//		//	//Implement draw code here
//		//	glColor3f(indexedColors[indices[i]].r, indexedColors[indices[i]].g, indexedColors[indices[i]].b);
//		//	glVertex3f(indexedVertices[indices[i]].x, indexedVertices[indices[i]].y, indexedVertices[indices[i]].z);
//		//	
//		//
//	
//		//}
//		//glEnd();
//
//		//glPopMatrix();
//
//
//
//}

//void HelloGL::DrawCubeArrayAlt()
//{
//	glEnableClientState(GL_VERTEX_ARRAY);
//	glEnableClientState(GL_COLOR_ARRAY);
//	glVertexPointer(3, GL_FLOAT, 0, vertices);
//	glColorPointer(3, GL_FLOAT, 0, colors);
//
//	glPushMatrix();
//	glRotatef(rotation, 10.0f, 5.0f, 5.0f);
//
//	glDrawArrays(GL_TRIANGLES, 0, 36);
//
//	glPopMatrix();
//
//	glDisableClientState(GL_COLOR_ARRAY);
//	glDisableClientState(GL_VERTEX_ARRAY);
//}

////void HelloGL::DrawIndexedCubeAlt()
////{
////	//glEnableClientState(GL_VERTEX_ARRAY);
////	//glEnableClientState(GL_COLOR_ARRAY);
////	//glVertexPointer(3, GL_FLOAT, 0, indexedVertices);
////	//glColorPointer(3, GL_FLOAT, 0, indexedColors);
////
////	//glPushMatrix();
////	//glRotatef(rotation, 10.0f, 5.0f, 5.0f);
////
////	//glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, indices);
////
////	//glPopMatrix();
////
////	//glDisableClientState(GL_COLOR_ARRAY);
////	//glDisableClientState(GL_VERTEX_ARRAY);
//}
