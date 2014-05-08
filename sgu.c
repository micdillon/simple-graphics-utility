/*
 * - The Simple Graphics Utility
 * sgu.c
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
    vec3 _v = {.v={fabs(v.x), fabs(v.y), fabs(v.z)}};
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

vec3 sub3(vec3 a, vec3 b) {
    vec3 _v = {.v={a.x-b.x, a.y-b.y, a.z-b.z}};
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
    SGUfloat a = 2.0 * acos(q.s);
    SGUfloat c = cos(a);
    SGUfloat s = sin(a);
    vec3 u = norm3(q.v);

    vec3 _v = add3(scalar_mult3(v, c),
                   add3(scalar_mult3(cross3(u, v), s),
                   scalar_mult3(u, dot3(u, v)*(1.0-c))));
    return _v;
}

mat3 identity_mat3() {
    return (mat3){.m={
        1.0, 0.0, 0.0,
        0.0, 1.0, 0.0,
        0.0, 0.0, 1.0
    }};
}

mat4 identity_mat4() {
    return (mat4){.m={
        1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0
    }};
}

mat4 translate_mat4(SGUfloat x, SGUfloat y, SGUfloat z) {
    return (mat4){.m={
        1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        x  , y  , z  , 1.0
    }};
}

mat4 scale_mat4(SGUfloat sx, SGUfloat sy, SGUfloat sz) {
    return (mat4){.m={
        sx , 0.0, 0.0, 0.0,
        0.0, sy , 0.0, 0.0,
        0.0, 0.0, sz , 0.0,
        0.0, 0.0, 0.0, 1.0
    }};
}

mat4 rotate_x_mat4(SGUfloat r) {
    return (mat4){.m={
        1.0, 0.0, 0.0, 0.0,
        0.0, cos(r), sin(r), 0.0,
        0.0, -sin(r), cos(r), 0.0,
        0.0, 0.0, 0.0, 1.0
    }};
}

mat4 rotate_y_mat4(SGUfloat r) {
    return (mat4){.m={
        cos(r), 0.0, -sin(r), 0.0,
        0.0   , 1.0, 0.0    , 0.0,
        sin(r), 0.0, cos(r) , 0.0,
        0.0   , 0.0, 0.0    , 1.0
    }};
}

mat4 rotate_z_mat4(SGUfloat r) {
    return (mat4){.m={
        cos(r) , sin(r), 0.0, 0.0,
        -sin(r), cos(r), 0.0, 0.0,
        0.0    , 0.0   , 1.0, 0.0,
        0.0    , 0.0   , 0.0, 1.0
    }};
}

mat3 transpose_mat3(mat3 a) {
#define a(i,j) a.m[3*i+j]
    return (mat3){.m={
        a(0,0), a(1,0), a(2,0),
        a(0,1), a(1,1), a(2,1),
        a(0,2), a(1,2), a(2,2),
    }};
#undef a
}

mat4 transpose_mat4(mat4 a) {
#define a(i,j) a.m[4*i+j]
    return (mat4){.m={
        a(0,0), a(1,0), a(2,0), a(3,0),
        a(0,1), a(1,1), a(2,1), a(3,1),
        a(0,2), a(1,2), a(2,2), a(3,2),
        a(0,3), a(1,3), a(2,3), a(3,3),
    }};
#undef a
}


SGUfloat det_mat3(mat3 a) {
#define a(i,j) a.m[3*i+j]
    return a(0,0)*a(1,1)*a(2,2) + a(1,0)*a(2,1)*a(0,2) +
        a(2,0)*a(0,1)*a(1,2) - a(0,0)*a(2,1)*a(1,2) - a(2,0)*a(1,1)*a(0,2) -
        a(1,0)*a(0,1)*a(2,2);
#undef a
}

SGUfloat det_mat4(mat4 a) {
#define a(i,j) a.m[4*i+j]
    return  a(0,0)*a(1,1)*a(2,2)*a(3,3) + a(0,0)*a(1,2)*a(2,3)*a(3,1) +
            a(0,0)*a(1,3)*a(2,1)*a(3,2) + a(0,1)*a(1,0)*a(2,3)*a(3,2) +
            a(0,1)*a(1,2)*a(2,0)*a(3,3) + a(0,1)*a(1,3)*a(2,2)*a(3,0) +
            a(0,2)*a(1,0)*a(2,1)*a(3,3) + a(0,2)*a(1,1)*a(2,3)*a(3,0) +
            a(0,2)*a(1,3)*a(2,0)*a(3,1) + a(0,3)*a(1,0)*a(2,2)*a(3,1) +
            a(0,3)*a(1,1)*a(2,0)*a(3,2) + a(0,3)*a(1,2)*a(2,1)*a(3,0) -
            a(0,0)*a(1,1)*a(2,3)*a(3,2) - a(0,0)*a(1,2)*a(2,1)*a(3,3) -
            a(0,0)*a(1,3)*a(2,2)*a(3,1) - a(0,1)*a(1,0)*a(2,2)*a(3,3) -
            a(0,1)*a(1,2)*a(2,3)*a(3,0) - a(0,1)*a(1,3)*a(2,0)*a(3,2) -
            a(0,2)*a(1,0)*a(2,3)*a(3,1) - a(0,2)*a(1,1)*a(2,0)*a(3,3) -
            a(0,2)*a(1,3)*a(2,1)*a(3,0) - a(0,3)*a(1,0)*a(2,1)*a(3,2) -
            a(0,3)*a(1,1)*a(2,2)*a(3,0) - a(0,3)*a(1,2)*a(2,0)*a(3,1);
#undef a
}

mat3 invert_mat3(mat3 a) {
#define a(i,j) a.m[3*i+j]
    SGUfloat s = 1.0 / det_mat3(a);
    return (mat3) {.m={
                (a(1,1)*a(2,2) - a(1,2)*a(2,1)) * s,
                (a(0,2)*a(2,1) - a(0,1)*a(2,2)) * s,
                (a(0,1)*a(1,2) - a(0,2)*a(1,1)) * s,

                (a(1,2)*a(2,0) - a(1,0)*a(2,2)) * s,
                (a(0,0)*a(2,2) - a(0,2)*a(2,0)) * s,
                (a(0,2)*a(1,0) - a(0,0)*a(1,2)) * s,

                (a(1,0)*a(2,1) - a(1,1)*a(2,0)) * s,
                (a(0,1)*a(2,0) - a(0,0)*a(2,1)) * s,
                (a(0,0)*a(1,1) - a(0,1)*a(1,0)) * s
            }};
#undef a
}

mat4 invert_mat4(mat4 a) {
#define a(i,j) a.m[4*i+j]
    SGUfloat s = 1.0 / det_mat4(a);

    SGUfloat m0 =
        a(1,1)*a(2,2)*a(3,3) + a(1,2)*a(2,3)*a(3,1) + a(1,3)*a(2,1)*a(3,2) -
        a(1,1)*a(2,3)*a(3,2) - a(1,2)*a(2,1)*a(3,3) - a(1,3)*a(2,2)*a(3,1);
    SGUfloat m1 =
        a(0,1)*a(2,3)*a(3,2) + a(0,2)*a(2,1)*a(3,3) + a(0,3)*a(2,2)*a(3,1) -
        a(0,1)*a(2,2)*a(3,3) - a(0,2)*a(2,3)*a(3,1) - a(0,3)*a(2,1)*a(3,2);
    SGUfloat m2 =
        a(0,1)*a(1,2)*a(3,3) + a(0,2)*a(1,3)*a(3,1) + a(0,3)*a(1,1)*a(3,2) -
        a(0,1)*a(1,3)*a(3,2) - a(0,2)*a(1,1)*a(3,3) - a(0,3)*a(1,2)*a(3,1);
    SGUfloat m3 =
        a(0,1)*a(1,3)*a(2,2) + a(0,2)*a(1,1)*a(2,3) + a(0,3)*a(1,2)*a(2,1) -
        a(0,1)*a(1,2)*a(2,3) - a(0,2)*a(1,3)*a(2,1) - a(0,3)*a(1,1)*a(2,2);

    SGUfloat m4 =
        a(1,0)*a(2,3)*a(3,2) + a(1,2)*a(2,0)*a(3,3) + a(1,3)*a(2,2)*a(3,0) -
        a(1,0)*a(2,2)*a(3,3) - a(1,2)*a(2,3)*a(3,0) - a(1,3)*a(2,0)*a(3,2);
    SGUfloat m5 =
        a(0,0)*a(2,2)*a(3,3) + a(0,2)*a(2,3)*a(3,0) + a(0,3)*a(2,0)*a(3,2) -
        a(0,0)*a(2,3)*a(3,2) - a(0,2)*a(2,0)*a(3,3) - a(0,3)*a(2,2)*a(3,0);
    SGUfloat m6 =
        a(0,0)*a(1,3)*a(3,2) + a(0,2)*a(1,0)*a(3,3) + a(0,3)*a(1,2)*a(3,0) -
        a(0,0)*a(1,2)*a(3,3) - a(0,2)*a(1,3)*a(3,0) - a(0,3)*a(1,0)*a(3,2);
    SGUfloat m7 =
        a(0,0)*a(1,2)*a(2,3) + a(0,2)*a(1,3)*a(2,0) + a(0,3)*a(1,0)*a(2,2) -
        a(0,0)*a(1,3)*a(2,2) - a(0,2)*a(1,0)*a(2,3) - a(0,3)*a(1,2)*a(2,0);

    SGUfloat m8 =
        a(1,0)*a(2,1)*a(3,3) + a(1,1)*a(2,3)*a(3,0) + a(1,3)*a(2,0)*a(3,1) -
        a(1,0)*a(2,3)*a(3,1) - a(1,1)*a(2,0)*a(3,3) - a(1,3)*a(2,1)*a(3,0);
    SGUfloat m9 =
        a(0,0)*a(2,3)*a(3,1) + a(0,1)*a(2,0)*a(3,3) + a(0,3)*a(2,1)*a(3,0) -
        a(0,0)*a(2,1)*a(3,3) - a(0,1)*a(2,3)*a(3,0) - a(0,3)*a(2,0)*a(3,1);
    SGUfloat m10 =
        a(0,0)*a(1,1)*a(3,3) + a(1,0)*a(1,3)*a(3,0) + a(0,3)*a(1,0)*a(3,1) -
        a(0,0)*a(1,3)*a(3,1) - a(0,1)*a(1,0)*a(3,3) - a(0,3)*a(1,1)*a(3,0);
    SGUfloat m11 =
        a(0,0)*a(1,3)*a(2,1) + a(0,1)*a(1,0)*a(2,3) + a(0,3)*a(1,1)*a(2,0) -
        a(0,0)*a(1,1)*a(2,3) - a(0,1)*a(1,3)*a(2,0) - a(0,3)*a(1,0)*a(2,1);

    SGUfloat m12 =
        a(1,0)*a(2,2)*a(3,1) + a(1,1)*a(2,0)*a(3,2) + a(1,2)*a(2,1)*a(3,0) -
        a(1,0)*a(2,1)*a(3,2) - a(1,1)*a(2,2)*a(3,0) - a(1,2)*a(2,0)*a(3,1);
    SGUfloat m13 =
        a(0,0)*a(2,1)*a(3,2) + a(0,1)*a(2,2)*a(3,0) + a(0,2)*a(2,0)*a(3,1) -
        a(0,0)*a(2,2)*a(3,1) - a(0,1)*a(2,0)*a(3,2) - a(0,2)*a(2,1)*a(3,0);
    SGUfloat m14 =
        a(0,0)*a(1,2)*a(3,1) + a(0,1)*a(1,0)*a(3,2) + a(0,2)*a(1,1)*a(3,0) -
        a(0,0)*a(1,1)*a(3,2) - a(0,1)*a(1,2)*a(3,0) - a(0,2)*a(1,0)*a(3,1);
    SGUfloat m15 =
        a(0,0)*a(1,1)*a(2,2) + a(0,1)*a(1,2)*a(2,0) + a(0,2)*a(1,0)*a(2,1) -
        a(0,0)*a(1,2)*a(2,1) - a(0,1)*a(1,0)*a(2,2) - a(0,2)*a(1,1)*a(2,0);

    return (mat4) {.m={
                m0*s, m1*s, m2*s, m3*s,
                m4*s, m5*s, m6*s, m7*s,
                m8*s, m9*s, m10*s, m11*s,
                m12*s, m13*s, m14*s, m15*s,
            }};
#undef a
}

mat3 mult_mat3(mat3 a, mat3 b) {
#define a(i,j) a.m[3*i+j]
#define b(i,j) b.m[3*i+j]
#define val(i,j) \
    a(i,0)*b(0,j)+a(i,1)*b(1,j)+a(i,2)*b(2,j)
    return (mat3){.m={
        val(0,0), val(0,1), val(0,2),
        val(1,0), val(1,1), val(1,2),
        val(2,0), val(2,1), val(2,2)
    }};
#undef a
#undef b
#undef val
}

mat4 mult_mat4(mat4 a, mat4 b) {
#define a(i,j) a.m[4*i+j]
#define b(i,j) b.m[4*i+j]
#define val(i,j) \
    a(i,0)*b(0,j)+a(i,1)*b(1,j)+a(i,2)*b(2,j)+a(i,3)*b(3,j)
    return (mat4){.m={
        val(0,0), val(0,1), val(0,2), val(0,3),
        val(1,0), val(1,1), val(1,2), val(1,3),
        val(2,0), val(2,1), val(2,2), val(2,3),
        val(3,0), val(3,1), val(3,2), val(3,3)
    }};
#undef a
#undef b
#undef val
}

vec4 mult_mat4_vec4(mat4 mat, vec4 v) {
#define mval(i,j) mat.m[4*i+j]
#define val(i) \
    mval(i,0)*v.x + mval(i,1)*v.y + mval(i,2)*v.z + mval(i,3)*v.w
    return (vec4){.v={val(0), val(1), val(2), val(3)}};
#undef mv
#undef val
}

mat4 look_at(vec3 eye, vec3 center, vec3 up) {
    vec3 n = norm3(add3(eye, neg3(center)));
    vec3 u = norm3(cross3(up, n));
    vec3 v = cross3(n, u);
    mat4 _m = {.m={
        u.x, v.x, n.x, 0.0,
        u.y, v.y, n.y, 0.0,
        u.z, v.z, n.z, 0.0,
        dot3(neg3(u), eye), dot3(neg3(v), eye), dot3(neg3(n), eye), 1.0}};
    return _m;
}


mat4 project_persp(SGUfloat fovy_rad, SGUfloat aspect,
                   SGUfloat nearz, SGUfloat farz) {
    SGUfloat cotan = 1.0 / tan(fovy_rad / 2.0);
    mat4 _m = {.m={
        cotan / aspect, 0.0, 0.0, 0.0,
        0.0, cotan, 0.0, 0.0,
        0.0, 0.0, -(nearz+farz)/(farz-nearz), -1.0,
        0.0, 0.0, (-2.0*farz*nearz)/(farz-nearz), 0.0}};
    return _m;
}

mat4 project_frust(SGUfloat left, SGUfloat right,
                   SGUfloat top, SGUfloat bottom,
                   SGUfloat near, SGUfloat far) {
    mat4 _m = {.m={
        2.0*near/(right-left), 0.0, 0.0, 0.0,
        0.0, 2.0*near/(top-bottom), 0.0, 0.0,
        (right+left)/(right-left), (top+bottom)/(top-bottom),
            -(far+near) / (far-near), -1.0,
        0.0, 0.0, (-2.0*far*near)/(far-near), 0.0}};
    return _m;
}

bounding_box fit_axis_aligned_bounding_box(vec4 *verts, int num_verts) {
#define start_max_val -100000.0
#define start_min_val 100000.0
    SGUfloat max_x = start_max_val,
             max_y = start_max_val,
             max_z = start_max_val;
    SGUfloat min_x = start_min_val,
             min_y = start_min_val,
             min_z = start_min_val;

    for (int i=0; i<num_verts; i++) {
        vec4 v = verts[i];
        if (v.x > max_x) max_x = v.x;
        if (v.x < min_x) min_x = v.x;
        if (v.y > max_y) max_y = v.y;
        if (v.y < min_y) min_y = v.y;
        if (v.z > max_z) max_z = v.z;
        if (v.z < min_z) min_z = v.z;
    }

    bounding_box _aabb = {
        .min={.v={min_x, min_y, min_z, 1.0}},
        .max={.v={max_x, max_y, max_z, 1.0}},
    };
    return _aabb;
#undef MAX_VAL
#undef MIN_VAL
}

int test_intersection(vec3 eye, vec3 ray_dir,
        vec3 plane_point, vec3 plane_norm, bounding_box aabb)
{
    SGUfloat t = dot3(sub3(plane_point, eye), plane_norm) /
            dot3(ray_dir, plane_norm);
    vec3 intersection_point = scalar_mult3(ray_dir, t);
    return test_bounds(aabb, intersection_point.xy);
}

int test_bounds(bounding_box bb, vec2 point)
{
    if (point.x > bb.min.x && point.x < bb.max.x &&
            point.y > bb.min.y && point.y < bb.max.y) {
        return 1;
    }
    return 0;
}

int aabb_hit(vec2 touch_point, vec2 screen_size, SGUfloat nearz, vec3 eye,
        mat4 inv_view_proj, bounding_box aabb)
{
    vec4 touch = {.v={
        (2.0 * touch_point.x) / screen_size.w - 1.0,
        1.0 - (2.0 * touch_point.y) / screen_size.h,
        -1.0, 1.0
    }};
    vec4 dir = mult_mat4_vec4(inv_view_proj, touch);

    vec3 front_norm = {.v={0.0, 0.0, 1.0}};
    int front_hit = test_intersection(eye, dir.xyz, aabb.max.xyz,
            front_norm, aabb);

    vec3 top_norm   = {.v={0.0, 1.0, 0.0}};
    int top_hit = test_intersection(eye, dir.xyz, aabb.max.xyz,
            top_norm, aabb);

    vec3 back_norm  = {.v={0.0, 0.0, -1.0}};
    int back_hit = test_intersection(eye, dir.xyz, aabb.min.xyz,
            back_norm, aabb);

    vec3 under_norm = {.v={0.0, -1.0, 0.0}};
    int under_hit = test_intersection(eye, dir.xyz, aabb.min.xyz,
            under_norm, aabb);

    vec3 left_norm  = {.v={-1.0, 0.0, 0.0}};
    int left_hit = test_intersection(eye, dir.xyz, aabb.min.xyz,
            left_norm, aabb);

    vec3 right_norm = {.v={1.0, 0.0, 0.0}};
    int right_hit = test_intersection(eye, dir.xyz, aabb.max.xyz,
            right_norm, aabb);

    return front_hit || top_hit || back_hit || under_hit
            || left_hit || right_hit;
}
