// NewTrainingFramework.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "Vertex.h"
#include "Shaders.h"
#include "Globals.h"
#include <conio.h>
#include "Texture.h"
#include "Model.h"
#include "SceneManager.h"
#include <iostream>


Shaders* g_pObjectShader = new Shaders();
Shaders* g_pSkyBoxShader = new Shaders();

int Initialize(ESContext* esContext)
{
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

	int objectShaderInit = g_pObjectShader->Init("../Resources/Shaders/TriangleShaderVS.vs", "../Resources/Shaders/TriangleShaderFS.fs");
	int skyBoxShaderInit = g_pSkyBoxShader->Init("../Resources/Shaders/SkyShaderVS.vs", "../Resources/Shaders/SkyShaderFS.fs");

	Matrix matModel, matView, matProjection;
	Matrix matTranslation, matRotation, matScale;

	matProjection.SetPerspective(1.0, Globals::screenWidth / Globals::screenHeight, 1.0f, 400.0f);
	matView.SetIdentity();

	// Initialize objects
	matRotation.SetRotationY(Radians(-45.0f));
	matTranslation.SetTranslation(4.0f, -1.0f, 0.0f);
	matModel = matRotation * matTranslation;
	const char* woman1Model = "../Resources/Models/Woman1.nfg";
	const char* woman1Texture = "../Resources/Textures/Woman1.tga";
	Object* woman1 = new Object(new Model(woman1Model), new Texture(woman1Texture), g_pObjectShader, matModel, matView, matProjection);
	SceneManager::GetInstance()->AddObject(woman1);

	matRotation.SetRotationY(Radians(-135.0f));
	matTranslation.SetTranslation(4.0f, -1.0f, 2.0f);
	matModel = matRotation * matTranslation;
	const char* woman2Model = "../Resources/Models/Woman2.nfg";
	const char* woman2Texture = "../Resources/Textures/Woman2.tga";
	Object* woman2 = new Object(new Model(woman2Model), new Texture(woman2Texture), g_pObjectShader, matModel, matView, matProjection);
	SceneManager::GetInstance()->AddObject(woman2);

	// Initialize skyBox
	matScale.SetScale(100.0f);
	matRotation.SetRotationZ(Radians(180.0f));
	matModel = matScale * matRotation;
	const char* skyBoxModel = "../Resources/Models/SkyBox.nfg";
	std::vector<const char *> faces;
	faces.push_back("../Resources/Skybox Textures/left.tga");
	faces.push_back("../Resources/Skybox Textures/right.tga");
	faces.push_back("../Resources/Skybox Textures/bottom.tga");
	faces.push_back("../Resources/Skybox Textures/top.tga");
	faces.push_back("../Resources/Skybox Textures/front.tga");
	faces.push_back("../Resources/Skybox Textures/back.tga");
	Object* skyBox = new Object(new Model(skyBoxModel), new Texture(faces), g_pSkyBoxShader, matModel, matView, matProjection);
	faces.clear();
	SceneManager::GetInstance()->AddObject(skyBox);

	glEnable(GL_DEPTH_TEST);
	return objectShaderInit || skyBoxShaderInit;
}

void Draw(ESContext* esContext)
{
	glClear(GL_COLOR_BUFFER_BIT);
	SceneManager::GetInstance()->Draw();
	eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);
}

void Update(ESContext* esContext, float deltaTime)
{
	if (deltaTime)
	{
		SceneManager::GetInstance()->Update(deltaTime);
	}
}

void TouchActionDown(ESContext* esContext, int x, int y)
{
	SceneManager::GetInstance()->SetMousePosition(0, x, y);
	SceneManager::GetInstance()->SetMousePosition(1, x, y);
}

void TouchActionUp(ESContext* esContext, int x, int y)
{
	SceneManager::GetInstance()->SetMousePosition(0, x, y);
	SceneManager::GetInstance()->SetMousePosition(1, x, y);
}

void TouchActionMove(ESContext* esContext, int x, int y)
{
	SceneManager::GetInstance()->SetMousePosition(1, x, y);
}

void Key(ESContext* esContext, unsigned char key, bool bIsPressed)
{
	switch (key)
	{
	case 'W': case 'w':
		SceneManager::GetInstance()->SetKeyEvent(Forward, bIsPressed);
		break;
	case 'A': case 'a':
		SceneManager::GetInstance()->SetKeyEvent(Left, bIsPressed);
		break;
	case 'S': case 's':
		SceneManager::GetInstance()->SetKeyEvent(Backward, bIsPressed);
		break;
	case 'D': case 'd':
		SceneManager::GetInstance()->SetKeyEvent(Right, bIsPressed);
		break;
	case 'Q': case 'q':
		SceneManager::GetInstance()->SetKeyEvent(Up, bIsPressed);
		break;
	case 'E': case 'e':
		SceneManager::GetInstance()->SetKeyEvent(Down, bIsPressed);
		break;
	case 'R': case 'r':
		SceneManager::GetInstance()->SetKeyEvent(Reset, bIsPressed);
		break;
	}
}


void CleanUp()
{
	delete SceneManager::GetInstance();
}

int _tmain(int argc, _TCHAR* argv[])
{
	ESContext esContext;

	esInitContext(&esContext);

	esCreateWindow(&esContext, "Hello Triangle", Globals::screenWidth, Globals::screenHeight, ES_WINDOW_RGB | ES_WINDOW_DEPTH);

	if (Initialize(&esContext) != 0)
		return 0;

	esRegisterDrawFunc(&esContext, Draw);
	esRegisterUpdateFunc(&esContext, Update);
	esRegisterKeyFunc(&esContext, Key);
	esRegisterMouseDownFunc(&esContext, TouchActionDown);
	esRegisterMouseUpFunc(&esContext, TouchActionUp);
	esRegisterMouseMoveFunc(&esContext, TouchActionMove);

	esMainLoop(&esContext);

	//releasing OpenGL resources
	CleanUp();

	//identifying memory leaks
	MemoryDump();
	printf("Press any key...\n");
	_getch();

	return 0;
}
