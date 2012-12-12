/*
 * sgu.c
 * - The Simple Graphics Utility
 */
#include "sgu.h"

SGUfloat len3(vec3 v) {
	return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}

SGUfloat len4(vec4 v) {
	return sqrt(v.x*v.x + v.y*v.y + v.z*v.z + v.w*v.w);
}

vec3 norm3(vec3 v) {
	SGUfloat scale = 1.0 / len3(v);
	vec3 _v = (vec3){.v={v.x*scale, v.y*scale, v.z*scale }};
	return _v;
}

vec4 norm4(vec4 v) {
	SGUfloat scale = 1.0 / len4(v);
	vec4 _v = {.v={v.x*scale, v.y*scale, v.z*scale, v.w*scale}};
	return _v;
}

vec3 abs3(vec3 v) {
	vec3 _v = {.v={fabsf(v.x), fabsf(v.y), fabsf(v.z)}};
	return _v;
}

vec3 neg3(vec3 v) {
	vec3 _v = {.v={-v.x, -v.y, -v.z }};
	return _v;
}

vec3 add3(vec3 a, vec3 b) {
	vec3 _v = {.v={a.x+b.x, a.y+b.y, a.z+b.z}};
	return _v;
}

vec3 scalar_mult3(vec3 v, SGUfloat s) {
	vec3 _v = {.v={v.x*s, v.y*s, v.z*s}};
	return _v;
}

vec3 cross3(vec3 a, vec3 b) {
	vec3 _v = {.v={a.y*b.z - a.z*b.y,
					 			 a.z*b.x - a.x*b.z,
					 			 a.x*b.y - a.y*b.x}};
	return _v;
}

SGUfloat dot3(vec3 a, vec3 b) {
	return a.x*b.x + a.y*b.y + a.z*b.z;
}


quat conjQ(quat q) {
	quat _q;
	_q.s = q.s;
	_q.v = scalar_mult3(q.v, -1.);
	return _q;
}

quat multQ(quat a, quat b) {
	quat _q = {.q={
		b.q[0]*a.q[0] - b.q[1]*a.q[1] - b.q[2]*a.q[2] - b.q[3]*a.q[3],
		b.q[0]*a.q[1] + b.q[1]*a.q[0] - b.q[2]*a.q[3] + b.q[3]*a.q[2],
		b.q[0]*a.q[2] + b.q[1]*a.q[3] + b.q[2]*a.q[0] - b.q[3]*a.q[1],
		b.q[0]*a.q[3] - b.q[1]*a.q[2] + b.q[2]*a.q[1] + b.q[3]*a.q[0]
	}};
	return _q;
}

vec3 rotateQ(quat q, vec3 v) {
	SGUfloat a = 2.0 * acosf(q.s);
	SGUfloat c = cosf(a);
	SGUfloat s = sinf(a);
	vec3 u = norm3(q.v);

	vec3 _v = add3(scalar_mult3(v, c), 
								 add3(scalar_mult3(cross3(u, v), s),
										  scalar_mult3(u, dot3(u, v)*(1.0-c))));
	return _v;
}

mat4 look_at(vec3 eye, vec3 center, vec3 up) {
	vec3 n = norm3(add3(eye, neg3(center)));
	vec3 u = norm3(cross3(up, n));
	vec3 v = cross3(n, u);
	mat4 _m = {.m={u.x, v.x, n.x, 0.0,
								 u.y, v.y, n.y, 0.0,
								 u.z, v.z, n.z, 0.0,
								 dot3(neg3(u), eye),
								 dot3(neg3(v), eye),
								 dot3(neg3(n), eye),
								 1.0}};
	return _m;
}

mat4 project_persp(SGUfloat fovy_rad, SGUfloat aspect, 
									 SGUfloat nearz, SGUfloat farz) {
	SGUfloat cotan = 1.0 / tanf(fovy_rad / 2.0);
	mat4 _m = {.m={cotan / aspect, 0.0, 0.0, 0.0,
								 0.0, cotan, 0.0, 0.0,
								 0.0, 0.0, (nearz+farz)/(nearz-farz), -1.0,
								 0.0, 0.0, (2.0*farz*nearz)/(nearz-farz), 0.0}};
	return _m;
}

// #ifdef SGUTEST
// 	#include "sgutest.c"
// #endif

