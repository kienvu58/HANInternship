#pragma once
#include "Math.h"
#include "../Utilities/Math.h"

struct Vertex 
{
	Vector3 pos;
	Vector3 norm;
	Vector3 binorm;
	Vector3 tgt;
	Vector2 uv;
};


#define POS_OFFSET		0
#define NORM_OFFSET		12
#define BINORM_OFFSET	24
#define TGT_OFFSET		36
#define UV_OFFSET		48