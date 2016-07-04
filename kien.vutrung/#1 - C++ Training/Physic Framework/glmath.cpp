#include "glmath.h"


float dot(const vec2 &u, const vec2 &v)
{
	return u.x * v.x + u.y * v.y;
}

float length(const vec2 &u)
{
	return sqrt(u.x * u.x + u.y * u.y);
}

float length2(const vec2 &u)
{
	return u.x * u.x + u.y * u.y;
}

vec2 mix(const vec2 &u, const vec2 &v, float a)
{
	return u * (1.0f - a) + v * a;
}

vec2 normalize(const vec2 &u)
{
	return u / sqrt(u.x * u.x + u.y * u.y);
}

vec2 reflect(const vec2 &i, const vec2 &n)
{
	return i - 2.0f * dot(n, i) * n;
}

vec2 refract(const vec2 &i, const vec2 &n, float eta)
{
	vec2 r;

	float ndoti = dot(n, i), k = 1.0f - eta * eta * (1.0f - ndoti * ndoti);

	if (k >= 0.0f)
	{
		r = eta * i - n * (eta * ndoti + sqrt(k));
	}

	return r;
}

vec2 rotate(const vec2 &u, float angle)
{
	angle = angle / 180.0f * (float)M_PI;

	float c = cos(angle), s = sin(angle);

	return vec2(u.x * c - u.y * s, u.x * s + u.y * c);
}

vec2 project(const vec2 & vector, const vec2 & axis)
{
	return dot(vector, axis) * axis / length2(axis);
}

bool isNull(const vec2 & u)
{
	return u.x == 0 && u.y == 0;
}

