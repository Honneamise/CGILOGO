#include "2d.h"
#include "math.h"

/**********/
float Radiansf(float degrees)
{
	return (float)(degrees * (float)M_PI / 180.0f);
}

/**********/
float Degreesf(float radians)
{
	return (float)(radians * 180.0f / (float)M_PI);
}

/**********/
Vec2f Vec2fAdd(Vec2f v, Vec2f s)
{
	return (Vec2f){v.x+s.x, v.y+s.y}; 
}

/**********/
Vec2f Vec2fSub(Vec2f v, Vec2f s)
{
	return (Vec2f){v.x-s.x, v.y-s.y}; 
}

/**********/
Vec2f Vec2fMul(Vec2f v, float n)
{
	return (Vec2f){v.x*n, v.y*n};
}

/**********/
Vec2f Vec2fDiv(Vec2f v, float n)
{
	return (Vec2f){v.x/n, v.y/n};
}

/**********/
Vec2f Vec2fNormalize(Vec2f v)
{
	float m = Vec2fLen(v);

	if (m != 0.0f) { return Vec2fDiv(v, m); };

	return (Vec2f){0.0f,0.0f};
}

/**********/
Vec2f Vec2fRotate(Vec2f v, Vec2f s, float angle)
{
	float x = v.x - s.x;
	float y = v.y - s.y;
	float radians = Radiansf(angle);

	float _x = s.x + x * cosf(radians) - y * sinf(radians);
	float _y = s.y + x * sinf(radians) + y * cosf(radians);

	return (Vec2f){_x,_y};
}

/**********/
float Vec2fLen(Vec2f v)
{
	float val = (v.x * v.x) + (v.y * v.y);

	return (float)sqrt(val);
}

/**********/
float Vec2fDot(Vec2f v, Vec2f s)
{
	return (v.x * s.x) + (v.y * s.y);
}

/**********/
float Vec2fCross(Vec2f v, Vec2f s)
{
	return (v.x * s.y) - (v.y * s.x);
}