// 3DTrainingFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../Utilities/utilities.h"
#include "Globals.h"
#include <conio.h>


int Initialize(ESContext* esContext)
{
	return -1;
}

void Draw(ESContext* esContext)
{
	
}

void Update(ESContext* esContext, float deltaTime)
{
	
}

void TouchActionDown(ESContext* esContext, int x, int y)
{
	
}

void TouchActionUp(ESContext* esContext, int x, int y)
{
	
}

void TouchActionMove(ESContext* esContext, int x, int y)
{
	
}

void Key(ESContext* esContext, unsigned char key, bool bIsPressed)
{
	
}

void CleanUp()
{
	
}



int main(int argc, _TCHAR* argv[])
{
	ESContext esContext;

	esInitContext(&esContext);

	esCreateWindow(&esContext, "3D Training Framework", Globals::screenWidth, Globals::screenHeight, ES_WINDOW_RGB | ES_WINDOW_DEPTH);

	if (Initialize(&esContext) != 0)
		return 0;

	esRegisterDrawFunc(&esContext, Draw);
	esRegisterUpdateFunc(&esContext, Update);
	esRegisterKeyFunc(&esContext, Key);
	esRegisterMouseDownFunc(&esContext, TouchActionDown);
	esRegisterMouseUpFunc(&esContext, TouchActionUp);
	esRegisterMouseMoveFunc(&esContext, TouchActionMove);

	esMainLoop(&esContext);

	// releasing OpenGL resources
	CleanUp();

	// identifying memory leaks
	MemoryDump();
	printf("Press any key...\n");
	_getch();

	return 0;
}

