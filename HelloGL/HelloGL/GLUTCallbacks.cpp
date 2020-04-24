//includes
#include "GLUTCallebacks.h"
#include "HelloGL.h"

//namespace implementation
namespace GLUTCallbacks
{
	namespace
	{
		//initialise to a null pointer before we do anything
		HelloGL* helloGL = nullptr;
	}

	void Init(HelloGL *gl)
	{
		helloGL = gl;
	}

	void Display()
	{
		if (helloGL != nullptr)
		{
			helloGL->Display();
		}
	}

	void Timer(int preferredRefresh)
	{

		int updateTime = glutGet(GLUT_ELAPSED_TIME);
		helloGL->Update();
		updateTime = glutGet(GLUT_ELAPSED_TIME) - updateTime;

		glutTimerFunc(preferredRefresh - updateTime, GLUTCallbacks::Timer, preferredRefresh);
	}

	void Keyboard(unsigned char key, int x, int y)
	{
		helloGL->Keyboard(key, x, y);
	}
}