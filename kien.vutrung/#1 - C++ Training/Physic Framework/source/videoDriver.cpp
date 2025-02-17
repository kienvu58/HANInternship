#include <videoDriver.h>
#include <shaderManager.h>

VideoDriver* VideoDriver::s_Instance = NULL;

VideoDriver::VideoDriver(void)
{
	this->Init();
}

VideoDriver* VideoDriver::GetInstance()
{
	if (!s_Instance)
		s_Instance = new VideoDriver();
	return s_Instance;
}

void VideoDriver::Init()
{
	const char* vShader_Color =
		"attribute vec2 a_Position;\n"
		"void main()\n"
		"{\n"
		"gl_Position = vec4(a_Position, 1.0, 1.0);\n"	
		"}\n";

	const char* fShader_Color = "precision mediump float;\n"
		"uniform vec4 u_Color;\n"
		"void main()\n"
		"{\n"
		"gl_FragColor = u_Color;\n"
		"}\n";

	program = ShaderManager::GetInstance()->CreateProgram(vShader_Color, fShader_Color);
	if (!program)
	{
		LOGE("Cannot create program COLOR\n");
		exit(0);
	}

	// Set color default: red
	color[0] = 1.0f;
	color[1] = 0.0f;
	color[2] = 0.0f;
	color[3] = 1.0f;
}

void VideoDriver::Draw(int x, int y, int width, int height, unsigned int idTexture)
{
	// Compute vertices array
	float vertices[] =	{
		X2GAME(x), Y2GAME(y),
		X2GAME(x), Y2GAME(y + height),
		X2GAME(x + width), Y2GAME(y + height),
		X2GAME(x), Y2GAME(y),
		X2GAME(x + width), Y2GAME(y + height),
		X2GAME(x + width), Y2GAME(y)
	};

	Matrix maWorld;
	Matrix maProjection;
	Matrix maView;

	maWorld.MakeIdentity();
	maProjection.MakeIdentity();
	maView.MakeIdentity();

	Matrix maMVP =  maProjection * maView * maWorld;
	maMVP.MakeTranspose();

	// 2. Transfer data to mvp matrix
	// Use program
	glUseProgram(program);

	// Transfer data to verties
	int locs = glGetAttribLocation(program, "a_Position");
	if (locs != -1)
	{
		glVertexAttribPointer(ATT_POSITION, 2, GL_FLOAT, GL_FALSE, 0, vertices);
		glEnableVertexAttribArray(ATT_POSITION);
	}

	locs = glGetUniformLocation(program, "u_Color");
	if (locs != -1)
	{
		glUniform4fv(locs, 1, &color[0]);
	}

	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void VideoDriver::DrawVertices(float* vertices, unsigned int numVertices, GLenum mode)
{
	glUseProgram(program);

	Matrix maWorld;
	Matrix maProjection;
	Matrix maView;

	maWorld.MakeIdentity();
	maProjection.MakeIdentity();
	maView.MakeIdentity();

	Matrix maMVP =  maProjection * maView * maWorld;
	maMVP.MakeTranspose();


	// Transfer data to verties
	int locs = glGetAttribLocation(program, "a_Position");
	if (locs != -1)
	{
		glVertexAttribPointer(ATT_POSITION, 2, GL_FLOAT, GL_FALSE, 0, vertices);
		glEnableVertexAttribArray(ATT_POSITION);
	}

	locs = glGetUniformLocation(program, "u_Color");
	if (locs != -1)
	{
		glUniform4fv(locs, 1, &color[0]);
	}

	glDrawArrays(mode, 0, numVertices);
}

void VideoDriver::FillRect(int x, int y, int width, int height)
{
	Draw(x, y, width, height);
}

void VideoDriver::DrawRect(int x, int y, int width, int height, int weight)
{
	//Top
	FillRect(x, y, width, weight);
	//Bottom
	FillRect(x, y + height - weight, width, weight);
	//Left
	FillRect(x, y + weight, weight, height - (weight<<1));
	//Right
	FillRect(x + width - weight, y + weight, weight, height - (weight<<1));

}


void VideoDriver::DrawRect(vec2 position, vec2 width, vec2 height)
{
	//Top
	DrawLine(position, position + width);
	//Bottom
	DrawLine(position + height, height + width + position);
	//Left
	DrawLine(position, position + height);
	//Right
	DrawLine(position + width, width + height + position);
}


void VideoDriver::DrawCircle(float cx, float cy, float radius)
{
	float x = (float)cx;
	float y = (float)cy;

	const int SEGMENTS = 32;
	const float INCREMENT = 2.0f*(float)PI/SEGMENTS;
	float theta = 0.0f;
	float* vertices = new float[SEGMENTS*2];

	for (int i = 0; i < SEGMENTS; ++i)
	{
		vertices[i*2] = X2GAME(x + (radius)*cosf(theta));
		vertices[i*2 + 1] = Y2GAME(y + (radius)*sinf(theta));
		theta += INCREMENT;
	}

	DrawVertices(vertices, SEGMENTS, GL_LINE_LOOP);
	SAFE_DEL(vertices);
};

void VideoDriver::DrawCircle(vec2 position, float radius)
{
	DrawCircle(position.x, position.y, radius);
}

void VideoDriver::DrawLine(vec2 start, vec2 end)
{
	float* vertices = new float[4];
	vertices[0] = X2GAME(start.x);
	vertices[1] = Y2GAME(start.y);
	vertices[2] = X2GAME(end.x);
	vertices[3] = Y2GAME(end.y);

	DrawVertices(vertices, 2, GL_LINES);
}

void VideoDriver::SetColor(unsigned int _color)
{
	color[0] = ((_color >> 16) & 0xFF)/255.0f;
	color[1] = ((_color >> 8) & 0xFF)/255.0f;
	color[2] = ((_color) & 0xFF)/255.0f;

	color[3] = ((_color >> 24)/255.0f);
	if (color[3] == 0.0f)
		color[3] = 1.0f;
}

//Image VideoDriver::CreateImage(const char* imgPath)
//{
//	Image image;
//	bool isAlpha = false;
//	const char data = VideoDriver::ImageDecoding(imgPath, &image.width, &image.height, &isAlpha);
//	glGenTextures(1, &image.textureID);
//	glBindTexture(GL_TEXTURE_2D, image.textureID);
//	glTexImage2D(GL_TEXTURE_2D, 0, (GL_RGB + isAlpha), image.width, image.height, 0, (GL_RGB + isAlpha), GL_UNSIGNED_BYTE, data);
//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//	SAFE_DEL(data);
//	return image;
//}

void VideoDriver::CleanScreen()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}

//void VideoDriver::DestroyImage(Image* image)
//{
//	if (image->textureID != 0)
//		glDeleteTextures(1, &image->textureID);
//}

VideoDriver::~VideoDriver(void)
{
}