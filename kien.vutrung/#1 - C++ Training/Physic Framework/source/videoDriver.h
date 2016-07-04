#ifndef __VIDEO_DRIVER_H__
#define __VIDEO_DRIVER_H__

#include <stdarg.h>
#include <openGLESv2.h>
#include <matrix.h>
#include "../glmath.h"


class VideoDriver
{
private:
	//Color
	float color[4];
	static VideoDriver* s_Instance;

	void Draw(int x, int y, int width, int height, unsigned int idTexture = 0);
	void DrawVertices(float* vertices, unsigned int numVertices, GLenum mode = GL_TRIANGLES);

public:
	// Constructor
	VideoDriver(void);

	// Destructor
	~VideoDriver(void);

	// Methods
	void Init();
	void FillRect(int x, int y, int width, int height);
	void DrawRect(int x, int y, int width, int height, int weight = 1);
	void DrawRect(vec2 position, vec2 width, vec2 height);
	void DrawCircle(float cx, float cy, float radius);
	void DrawCircle(vec2 position, float radius);
	void DrawLine(vec2 start, vec2 end);

	void SetColor(unsigned int color);

	void CleanScreen();

	static VideoDriver* GetInstance();

	// Propertices
	unsigned int program;
};

#endif