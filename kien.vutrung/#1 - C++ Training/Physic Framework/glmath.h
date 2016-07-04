#pragma once

#define _USE_MATH_DEFINES
#include <cmath>
class vec2
{
public:
	union {
		struct { float x, y; };
		struct { float s, t; };
		struct { float r, g; };
	};
	vec2() : x(0.0f), y(0.0f) {}
	~vec2() {}
	vec2(float num) : x(num), y(num) {}
	vec2(float x, float y) : x(x), y(y) {}
	vec2(const vec2 &u) : x(u.x), y(u.y) {}
	vec2& operator = (const vec2 &u) { x = u.x; y = u.y; return *this; }
	vec2 operator - () { return vec2(-x, -y); }
	float* operator & () { return (float*)this; };
	vec2& operator += (float num) { x += num; y += num; return *this; }
	vec2& operator += (const vec2 &u) { x += u.x; y += u.y; return *this; }
	vec2& operator -= (float num) { x -= num; y -= num; return *this; }
	vec2& operator -= (const vec2 &u) { x -= u.x; y -= u.y; return *this; }
	vec2& operator *= (float num) { x *= num; y *= num; return *this; }
	vec2& operator *= (const vec2 &u) { x *= u.x; y *= u.y; return *this; }
	vec2& operator /= (float num) { x /= num; y /= num; return *this; }
	vec2& operator /= (const vec2 &u) { x /= u.x; y /= u.y; return *this; }
	friend vec2 operator + (const vec2 &u, float num) { return vec2(u.x + num, u.y + num); }
	friend vec2 operator + (float num, const vec2 &u) { return vec2(num + u.x, num + u.y); }
	friend vec2 operator + (const vec2 &u, const vec2 &v) { return vec2(u.x + v.x, u.y + v.y); }
	friend vec2 operator - (const vec2 &u, float num) { return vec2(u.x - num, u.y - num); }
	friend vec2 operator - (float num, const vec2 &u) { return vec2(num - u.x, num - u.y); }
	friend vec2 operator - (const vec2 &u, const vec2 &v) { return vec2(u.x - v.x, u.y - v.y); }
	friend vec2 operator * (const vec2 &u, float num) { return vec2(u.x * num, u.y * num); }
	friend vec2 operator * (float num, const vec2 &u) { return vec2(num * u.x, num * u.y); }
	friend vec2 operator * (const vec2 &u, const vec2 &v) { return vec2(u.x * v.x, u.y * v.y); }
	friend vec2 operator / (const vec2 &u, float num) { return vec2(u.x / num, u.y / num); }
	friend vec2 operator / (float num, const vec2 &u) { return vec2(num / u.x, num / u.y); }
	friend vec2 operator / (const vec2 &u, const vec2 &v) { return vec2(u.x / v.x, u.y / v.y); }
	friend bool operator == (const vec2 &u, const vec2 &v) { return u.x == v.x && u.y == v.y; }
	friend bool operator != (const vec2 &u, const vec2 &v) { return !(u == v); }
};

float dot(const vec2 &u, const vec2 &v);
float length(const vec2 &u);
float length2(const vec2 &u);
vec2 mix(const vec2 &u, const vec2 &v, float a);
vec2 normalize(const vec2 &u);
vec2 reflect(const vec2 &i, const vec2 &n);
vec2 refract(const vec2 &i, const vec2 &n, float eta);
vec2 rotate(const vec2 &u, float angle);

vec2 project(const vec2 &vector, const vec2 &axis);
bool isNull(const vec2 &u);