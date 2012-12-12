/*
 * sgu.h
 * - The Simple Graphics Utility
 */
#pragma once

#include <math.h>

#ifdef SGUTEST
typedef double SGUfloat;
#else
typedef float SGUfloat;
#endif

#ifdef __cplusplus
extern "C" {
#endif	

/* .... Types .... */
typedef union {
	struct {
		SGUfloat x;
		SGUfloat y;
	};
	struct {
		SGUfloat w;
		SGUfloat h;
	};
	SGUfloat v[2];
} vec2;

typedef union {
	struct {
		SGUfloat x;
		SGUfloat y;
		SGUfloat z;
	};
	SGUfloat v[3];
} vec3;

typedef union {
	struct {
		SGUfloat x;
		SGUfloat y;
		SGUfloat z;
		SGUfloat w;
	};
	SGUfloat v[4];
} vec4;

typedef union {
	struct {
		SGUfloat s;
		vec3  v;
	};
	struct {
		SGUfloat w;
		SGUfloat x;
		SGUfloat y;
		SGUfloat z;
	};
	SGUfloat q[4];
} quat;

typedef union {
	struct {
		vec3 r1;
		vec3 r2;
		vec3 r3;
	};
	SGUfloat m[9];
} mat3;

typedef union {
	struct {
		vec4 r1;
		vec4 r2;
		vec4 r3;
		vec4 r4;
	};
	SGUfloat m[16];
} mat4;


/* .... Functions .... */
SGUfloat len3(vec3 v);
SGUfloat len4(vec4 v);
vec3 norm3(vec3 v);
vec4 norm4(vec4 v);
vec3 abs3(vec3 v);
vec3 neg3(vec3 v);
vec3 add3(vec3 a, vec3 b);
vec3 scalar_mult3(vec3 v, SGUfloat s);
vec3 cross3(vec3 a, vec3 b);
SGUfloat dot3(vec3 a, vec3 b);
quat multQ(quat a, quat b);
vec3 rotateQ(quat q, vec3 v);
quat conjQ(quat q);
mat4 look_at(vec3 eye, vec3 center, vec3 up);
mat4 project_persp(SGUfloat fovy_rad, SGUfloat aspect, 
									 SGUfloat nearz, SGUfloat farz);

#ifdef __cplusplus
}
#endif
