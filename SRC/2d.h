#ifndef _2D_H
#define _2D_H

typedef struct Vec2f
{
	float x;
	float y;

} Vec2f;

float Radiansf(float degrees);
float Degreesf(float radians);

Vec2f 	Vec2fAdd(Vec2f v, Vec2f s);
Vec2f 	Vec2fSub(Vec2f v, Vec2f s);
Vec2f 	Vec2fMul(Vec2f v, float n);
Vec2f 	Vec2fDiv(Vec2f v, float n);
Vec2f 	Vec2fNormalize(Vec2f v);
Vec2f 	Vec2fRotate(Vec2f v, Vec2f s, float angle);
float 	Vec2fLen(Vec2f v);
float 	Vec2fDot(Vec2f v, Vec2f s);
float 	Vec2fCross(Vec2f v, Vec2f s);

#endif