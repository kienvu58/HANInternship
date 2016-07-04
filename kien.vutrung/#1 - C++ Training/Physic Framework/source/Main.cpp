#include <stdio.h>
#include "esUtil.h"
#include "Define.h"
#include "VideoDriver.h"
#include "../SceneManager.h"
#include "../CollisionManager.h"

void PaintObject()
{
	// Limit FPS
	DWORD start, end;
	start = GetTickCount();

	// Clean the screen each render
	VideoDriver::GetInstance()->CleanScreen();

	// Render something here
	// VideoDriver::GetInstance()->DrawCircle(100.0f, 100.0f, 100.0f);
	// VideoDriver::GetInstance()->FillRect(0, 0, 100, 100);
	SceneManager::GetInstance()->Render();

	// Limit FPS
	end = GetTickCount();
	DWORD deltaTime = end - start;
	if (deltaTime < 1000.0/LIMIT_FPS)
		Sleep(1000/LIMIT_FPS - deltaTime);
}

bool InitGraphics(int w, int h)
{
	glViewport(0, 0, w, h);
	return true;
}

void TouchActionDown(ESContext *esContext,int x, int y)
{
	SceneManager::GetInstance()->PickObject(x, y);
}

void TouchActionUp(ESContext *esContext,int x, int y)
{
	SceneManager::GetInstance()->ReleaseObject();
}

void TouchActionMove(ESContext *esContext,int x, int y)
{
	SceneManager::GetInstance()->DragObject(x, y);
}

void KeyDown(ESContext *esContext, unsigned char keyCode, int x, int y)
{
	switch (keyCode)
	{
	case 'W':case 'w':
		break;
	case 'S':case 's':
		break;
	case 'A':case 'a':
		break;
	case 'D':case 'd':
		break;
	}
}

void KeyUp(ESContext *esContext, unsigned char keyCode, int x, int y)
{
	switch (keyCode)
	{
	case 'W':case 'w':
		break;
	case 'S':case 's':
		break;
	case 'A':case 'a':
		break;
	case 'D':case 'd':
		break;
	}
}

void GameUpdate ( ESContext *esContext, float deltaTime )
{
	if (deltaTime)
	{
		SceneManager::GetInstance()->Update(deltaTime);
		CollisionManager::GetInstance()->ResolveAllCollisions(deltaTime);
	}
}

void GameDraw ( ESContext *esContext )
{
	PaintObject();
	eglSwapBuffers ( esContext->eglDisplay, esContext->eglSurface );
}

int main ( int argc, char *argv[] )
{
	ESContext esContext;
	esInitContext ( &esContext );

	esCreateWindow ( &esContext, "Framework", (int)SCREEN_W, (int)SCREEN_H, ES_WINDOW_RGB );
	if ( !InitGraphics ((int)SCREEN_W, (int)SCREEN_H) )
		return 0;
	;

	SceneManager::GetInstance()->Init("InitObjects.txt");

	esRegisterDrawFunc(&esContext, GameDraw );
	esRegisterKeyDownFunc(&esContext, KeyDown );
	esRegisterKeyUpFunc(&esContext, KeyUp );
	esRegisterUpdateFunc(&esContext, GameUpdate);
	esRegisterMouseDownFunc(&esContext, TouchActionDown);
	esRegisterMouseUpFunc(&esContext, TouchActionUp);
	esRegisterMouseMoveFunc(&esContext, TouchActionMove);
	esMainLoop ( &esContext );
}