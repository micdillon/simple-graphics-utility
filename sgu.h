/*
 * - The Simple Graphics Utility
 *   sgu.h
 */
#pragma once

#include <math.h>

/**
 * .... Types ....
 */

#ifdef SGUTEST
typedef double SGUfloat;
#else // normal for using opengl on mobile
typedef float SGUfloat;
#define sin sinf
#define asin asinf
#define cos cosf
#define acos acosf
#define tan tanf
#define atan atanf
#endif

typedef union {
    struct {
        SGUfloat x;
        SGUfloat y;
    };
    struct {
        SGUfloat w;
        SGUfloat h;
    };
    struct {
        SGUfloat s;
        SGUfloat t;
    };
    SGUfloat v[2];
} vec2;

typedef union {
    struct {
        SGUfloat x;
        SGUfloat y;
        SGUfloat z;
    };
    struct {
        vec2 xy;
        SGUfloat zz;
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
    struct {
        SGUfloat r;
        SGUfloat g;
        SGUfloat b;
        SGUfloat a;
    };
    struct {
        vec2 xy;
        vec2 zw;
    };
    struct {
        vec3 xyz;
        SGUfloat www;
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

typedef union {
    struct {
        vec4 min;
        vec4 max;
    };
    vec4 c[2];
    SGUfloat d[8];
} bounding_box;


#ifdef __cplusplus
extern "C" {
#endif

/**
  * .... Functions ....
  */
SGUfloat len3(vec3 v);
SGUfloat len4(vec4 v);
vec3 norm3(vec3 v);
vec4 norm4(vec4 v);
vec3 abs3(vec3 v);
vec3 neg3(vec3 v);
vec3 add3(vec3 a, vec3 b);
vec3 sub3(vec3 a, vec3 b);
vec3 scalar_mult3(vec3 v, SGUfloat s);
vec3 cross3(vec3 a, vec3 b);
SGUfloat dot3(vec3 a, vec3 b);

quat multQ(quat a, quat b);
vec3 rotateQ(quat q, vec3 v);
quat conjQ(quat q);

mat3 identity_mat3();
mat4 identity_mat4();

mat4 translate_mat4(SGUfloat x, SGUfloat y, SGUfloat z);
mat4 scale_mat4(SGUfloat sx, SGUfloat sy, SGUfloat sz);
mat4 rotate_x_mat4(SGUfloat rads);
mat4 rotate_y_mat4(SGUfloat rads);
mat4 rotate_z_mat4(SGUfloat rads);

mat3 transpose_mat3(mat3 a);
mat4 transpose_mat4(mat4 a);

SGUfloat det_mat3(mat3 a);
SGUfloat det_mat4(mat4 a);

mat3 invert_mat3(mat3 a);
mat4 invert_mat4(mat4 a);

mat3 mult_mat3(mat3 a, mat3 b);
mat4 mult_mat4(mat4 a, mat4 b);

vec4 mult_mat4_vec4(mat4, vec4);

mat4 look_at(vec3 eye, vec3 center, vec3 up);
mat4 project_persp(SGUfloat fovy_rad, SGUfloat aspect,
                   SGUfloat nearz, SGUfloat farz);
mat4 project_frust(SGUfloat top, SGUfloat bottom,
                   SGUfloat left, SGUfloat right,
                   SGUfloat nearz, SGUfloat farz);

bounding_box fit_axis_aligned_bounding_box(vec4 *verts, int num_verts);

int test_intersection(vec3 eye, vec3 ray_dir, vec3 plane_point,
        vec3 plan_norm, bounding_box aabb);
int test_bounds(bounding_box bb, vec2 point);

int aabb_hit(vec2 touch_point, vec2 screen_size, SGUfloat nearz, vec3 eye,
        mat4 inv_view_proj, bounding_box aabb);

#ifdef __cplusplus
}
#endif
