#include <stdio.h>
#include <stdlib.h>
#include <glib.h>

#include "sgu.h"
#include "shapes.h"

/**
    * takes floating point rounding errors
    * into consideration
    */
#define sgu_assert_float_eq(a,b) \
    g_assert_cmpfloat(fabs((a)-(b)), <=, 1.0e-15)
#define sgu_assert_float_neq(a,b) \
    g_assert_cmpfloat(fabs((a)-(b)), >, 1.0e-15)

/**
    * sgu_rndf()
    * returns a random float ranged between 0.0 and 1.0
    */
SGUfloat sgu_rndf() {
    unsigned long r = random();
    return r / (pow(2,31)-1.0);
}

/*
 * test vec2
 */
typedef struct {
    vec2 v;
} vec2fixture;

void vec2_setup(vec2fixture *f, gconstpointer test_data) {
    f->v = (vec2){.v={sgu_rndf(),-sgu_rndf()}};
}

void vec2_teardown(vec2fixture *f, gconstpointer test_data) {
    f->v = (vec2){.v={0.0,0.0}};
}

void test_vec2_union(vec2fixture *f, gconstpointer ignored) {
    g_assert(f->v.x == f->v.w);
    g_assert(f->v.y == f->v.h);

    g_assert(f->v.w == f->v.v[0]);
    g_assert(f->v.h == f->v.v[1]);
}

/*
 * test vec3
 */
typedef struct {
    vec3 v;
    vec3 u;
    vec3 r;
} vec3fixture;

void vec3_setup(vec3fixture *f, gconstpointer test_data) {
    f->v = (vec3){.v={sgu_rndf(), -sgu_rndf(), sgu_rndf()}};
    f->u = (vec3){.v={-sgu_rndf(), sgu_rndf(), -sgu_rndf()}};
    f->r = (vec3){.v={sgu_rndf(), sgu_rndf(), -sgu_rndf()}};
}

void vec3_teardown(vec3fixture *f, gconstpointer test_data) {
    f->v = (vec3){.v={0.0,0.0,0.0}};
    f->u = (vec3){.v={0.0,0.0,0.0}};
    f->r = (vec3){.v={0.0,0.0,0.0}};
}

void test_vec3_union(vec3fixture *f, gconstpointer ignored) {
    g_assert(f->v.x == f->v.v[0]);
    g_assert(f->v.y == f->v.v[1]);
    g_assert(f->v.z == f->v.v[2]);
}

void test_vec3_norm_len(vec3fixture *f, gconstpointer ignored) {
    vec3 n = norm3(f->v);
    sgu_assert_float_eq(len3(n), 1.0);
}

void test_vec3_abs(vec3fixture *f, gconstpointer ignored) {
    f->v = (vec3){.v={-1.0, -2.0, -3.0}};
    vec3 a = abs3(f->v);
    g_assert_cmpfloat(a.x, >, 0.0);
    g_assert_cmpfloat(a.y, >, 0.0);
    g_assert_cmpfloat(a.z, >, 0.0);
}

void test_vec3_neg(vec3fixture *f, gconstpointer ignored) {
    f->v = (vec3){.v={-1.0, 2.0, -3.0}};
    vec3 n = neg3(f->v);
    g_assert_cmpfloat(n.x, ==, 1.0);
    g_assert_cmpfloat(n.y, ==, -2.0);
    g_assert_cmpfloat(n.z, ==, 3.0);
}

void test_vec3_add(vec3fixture *f, gconstpointer ignored) {
    vec3 a = add3(f->v,f->u);
    g_assert_cmpfloat(a.x, ==, f->v.x + f->u.x);
    g_assert_cmpfloat(a.y, ==, f->v.y + f->u.y);
    g_assert_cmpfloat(a.z, ==, f->v.z + f->u.z);
}

void test_vec3_scalar_mult(vec3fixture *f, gconstpointer ignored) {
    vec3 m = scalar_mult3(f->v, 0.5);
    g_assert_cmpfloat(m.x, ==, f->v.x * 0.5);
    g_assert_cmpfloat(m.y, ==, f->v.y * 0.5);
    g_assert_cmpfloat(m.z, ==, f->v.z * 0.5);
}

void test_vec3_cross(vec3fixture *f, gconstpointer ignored)
{
    #define assert_eq3(a, b) {                          \
        for (int _i=0; _i<3; _i++)                      \
             sgu_assert_float_eq(a.v[_i], b.v[_i]);     \
    }

    // (orthagonoal unit vector identities)

    vec3 i = {.v={1.0, 0.0, 0.0}};
    vec3 j = {.v={0.0, 1.0, 0.0}};
    vec3 k = {.v={0.0, 0.0, 1.0}};

    // i x j = k
    vec3 kk = cross3(i,j);
    assert_eq3(kk,k);

    // j x k = i
    vec3 ii = cross3(j,k);
    assert_eq3(ii,i);

    // k x i = j
    vec3 jj = cross3(k,i);
    assert_eq3(jj,j);

    //j x i = -k
    vec3 nk = cross3(j,i);
    assert_eq3(nk,neg3(k));

    //k x j = -i
    vec3 ni = cross3(k,j);
    assert_eq3(ni,neg3(i));

    //i x k = -j
    vec3 nj = cross3(i,k);
    assert_eq3(nj,neg3(j));


    // the following tests may be provable from the 
    // unit vector identities, but will test anyway

    // (anticommutivity)
    // v x u = -u x v
    assert_eq3(cross3(f->v, f->u), cross3(neg3(f->u), f->v));

    // (distribution)
    // v x (u + r) = (v x u) + (v x r)
    assert_eq3(cross3(f->v, add3(f->u, f->r)), 
                         add3(cross3(f->v, f->u), 
                                cross3(f->v, f->r)));
    #undef assert_eq3
}

void test_vec3_dot(vec3fixture *f, gconstpointer ignored) {

    // (orthagonoal unit vector identities)

    vec3 i = {.v={1.0, 0.0, 0.0}};
    vec3 j = {.v={0.0, 1.0, 0.0}};

    // i . j = 0
    g_assert_cmpfloat(dot3(i,j), ==, 0.0);

    // i . i = 1
    g_assert_cmpfloat(dot3(i,i), ==, 1.0);


    // (algebraic identities)

    // (commutative)
    // v . u = u . v
    sgu_assert_float_eq(dot3(f->v,f->u), dot3(f->u,f->v));

    // (distributive)
    // v . (u + r) = (v . u) + (v . r)
    sgu_assert_float_eq(dot3(f->v, add3(f->u,f->r)),
                                          dot3(f->v,f->u) + dot3(f->v,f->r));


    // (geometric identities)

    // v . v = |v|^2
    sgu_assert_float_eq(dot3(f->v,f->v), len3(f->v)*len3(f->v));

}


/*
 * test vec4
 */

typedef struct {
    vec4 v;
    vec4 u;
    vec4 r;
} vec4fixture;

void vec4_setup(vec4fixture *f, gconstpointer test_data) {
    f->v = (vec4){.v={sgu_rndf(), -sgu_rndf(), sgu_rndf(), -sgu_rndf()}};
    f->u = (vec4){.v={sgu_rndf(), -sgu_rndf(), -sgu_rndf(), sgu_rndf()}};
    f->r = (vec4){.v={-sgu_rndf(), sgu_rndf(), -sgu_rndf(), sgu_rndf()}};
}

void vec4_teardown(vec4fixture *f, gconstpointer test_data) {
    f->v = (vec4){.v={0.0,0.0,0.0,0.0}};
    f->u = (vec4){.v={0.0,0.0,0.0,0.0}};
    f->r = (vec4){.v={0.0,0.0,0.0,0.0}};
}

void test_vec4_union(vec4fixture *f, gconstpointer ignored) {
    g_assert(f->v.x == f->v.r);
    g_assert(f->v.y == f->v.g);
    g_assert(f->v.z == f->v.b);
    g_assert(f->v.w == f->v.a);

    g_assert(f->v.x == f->v.v[0]);
    g_assert(f->v.y == f->v.v[1]);
    g_assert(f->v.z == f->v.v[2]);
    g_assert(f->v.w == f->v.v[3]);
}

void test_vec4_norm_len(vec4fixture *f, gconstpointer ignored) {
    vec4 n = norm4(f->v);
    sgu_assert_float_eq(len4(n), 1.0);
}


/*
 * test quat
 */
typedef struct {
    quat v;
    quat u;
    quat r;
} quatfixture;

void quat_setup(quatfixture *f, gconstpointer test_data) {
    f->v = (quat){.q={sgu_rndf(), -sgu_rndf(), sgu_rndf(), -sgu_rndf()}};
    f->u = (quat){.q={sgu_rndf(), -sgu_rndf(), -sgu_rndf(), sgu_rndf()}};
    f->r = (quat){.q={-sgu_rndf(), sgu_rndf(), -sgu_rndf(), sgu_rndf()}};
}

void quat_teardown(quatfixture *f, gconstpointer test_data) {
    f->v = (quat){.q={0.0,0.0,0.0,0.0}};
    f->u = (quat){.q={0.0,0.0,0.0,0.0}};
    f->r = (quat){.q={0.0,0.0,0.0,0.0}};
}

void test_quat_union(quatfixture *f, gconstpointer ignored) {
    g_assert(f->v.s == f->v.w);
    g_assert(f->v.v.x == f->v.x);
    g_assert(f->v.v.y == f->v.y);
    g_assert(f->v.v.z == f->v.z);

    g_assert(f->v.w == f->v.q[0]);
    g_assert(f->v.x == f->v.q[1]);
    g_assert(f->v.y == f->v.q[2]);
    g_assert(f->v.z == f->v.q[3]);
}

#define assert_eqQ(a, b) {                          \
    sgu_assert_float_eq(a.s, b.s);                  \
    for (int _i=0; _i<3; _i++)                      \
        sgu_assert_float_eq(a.v.v[_i], b.v.v[_i]);  \
}

void test_quat_conjugate(quatfixture *f, gconstpointer ignored) {
    quat q = (quat){
        .s = f->v.s,
        .v = (vec3){.v={-f->v.x, -f->v.y, -f->v.z}}
    };
    assert_eqQ(q, conjQ(f->v));
}

void test_quat_mult(quatfixture *f, gconstpointer ignored) {
    quat p;
    p.s = f->v.s*f->u.s - dot3(f->v.v, f->u.v);
    p.v = add3(add3(scalar_mult3(f->u.v, f->v.s),
                    scalar_mult3(f->v.v, f->u.s)),
                    cross3(f->v.v, f->u.v));
    assert_eqQ(p, multQ(f->v,f->u));
}

#undef assert_eqQ


/*
 * test geometrical functions
 */

void test_rotateQ() {
    // test rotating 90 degrees around the y-axis
    quat q = {
        .s = cosf(M_PI/4.0),
        .v = {.v={0.0, 1.0, 0.0}}
    };
    vec3 v = {.v={1.0, 0.0, 0.0}};
    v = rotateQ(q,v);
    // sgu_assert_float_eq(v.x,0.0);
    // sgu_assert_float_eq(v.y,0.0);
    sgu_assert_float_eq(v.z,-1.0);
}

/*
 * matrix tests
 */

void test_det_mat3() {
    mat3 singular = {.m={
        1.0, -2.0, 4.0,
        0.0, 0.0, 6.0,
        0.0, 0.0, 1.0
    }};
    sgu_assert_float_eq(det_mat3(singular), 0.0);

    mat3 non_singular = {.m={
        9.0, -6.0, -1.0,
        3.0, -9.0, -8.0,
        5.0, 7.0, 1.0
    }};
    sgu_assert_float_eq(det_mat3(non_singular), 615.0);
}

void test_det_mat4() {
    mat4 singular = {.m={
        16.0, 5.0, 9.0, 4.0,
        2.0, 11.0, 7.0, 14.0,
        3.0, 10.0, 6.0, 15.0,
        13.0, 8.0, 12.0, 1.0
    }};
    sgu_assert_float_eq(det_mat4(singular), 0.0);

    mat4 non_singular = {.m={
        1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0
    }};
    sgu_assert_float_neq(det_mat4(non_singular), 0.0);
}

void test_invert_mat3() {
    mat3 non_singular = {.m={
        9.0, -6.0, -1.0,
        3.0, -9.0, -8.0,
        5.0, 7.0, 1.0
    }};
    mat3 inv = invert_mat3(non_singular);
    sgu_assert_float_eq(inv.m[0], 47.0 / 615.0);
    sgu_assert_float_eq(inv.m[1], -1.0 / 615.0);
    sgu_assert_float_eq(inv.m[2], 39.0 / 615.0);

    sgu_assert_float_eq(inv.m[3], -43.0 / 615.0);
    sgu_assert_float_eq(inv.m[4], 14.0 / 615.0);
    sgu_assert_float_eq(inv.m[5], 69.0 / 615.0);

    sgu_assert_float_eq(inv.m[6], 66.0 / 615.0);
    sgu_assert_float_eq(inv.m[7], -93.0 / 615.0);
    sgu_assert_float_eq(inv.m[8], -63.0 / 615.0);
}

void test_invert_mat4() {
    mat4 non_singular = {.m={
        1.0, 1.0, 1.0, 1.0,
        1.0, 2.0, 1.0, 2.0,
        1.0, 1.0, 1.0, 0.0,
        1.0, 4.0, 2.0, 3.0
    }};
    mat4 inv = invert_mat4(non_singular);

    sgu_assert_float_eq(inv.m[0], -1.0);
    sgu_assert_float_eq(inv.m[1], 2.0);
    sgu_assert_float_eq(inv.m[2], 1.0);
    sgu_assert_float_eq(inv.m[3], -1.0);

    sgu_assert_float_eq(inv.m[4], -2.0);
    sgu_assert_float_eq(inv.m[5], 1.0);
    sgu_assert_float_eq(inv.m[6], 1.0);
    sgu_assert_float_eq(inv.m[7], 0.0);

    sgu_assert_float_eq(inv.m[8], 3.0);
    sgu_assert_float_eq(inv.m[9], -3.0);
    sgu_assert_float_eq(inv.m[10], -1.0);
    sgu_assert_float_eq(inv.m[11], 1.0);

    sgu_assert_float_eq(inv.m[12], 1.0);
    sgu_assert_float_eq(inv.m[13], 0.0);
    sgu_assert_float_eq(inv.m[14], -1.0);
    sgu_assert_float_eq(inv.m[15], 0.0);
}

void test_mult_mat3() {
#define assert_m3eq(a, b) {                             \
    for (int _i=0; _i<9; _i++)                          \
             sgu_assert_float_eq(a.m[_i], b.m[_i]);     \
    }

    /** check identity matrix */
    mat3 i = (mat3){.m={
        1.0, 0.0, 0.0,
        0.0, 1.0, 0.0,
        0.0, 0.0, 1.0
    }};

    mat3 b = (mat3){.m={
        sgu_rndf(), sgu_rndf(), sgu_rndf(),
        sgu_rndf(), sgu_rndf(), sgu_rndf(),
        sgu_rndf(), sgu_rndf(), sgu_rndf()
    }};

    mat3 c = mult_mat3(i, b);
    assert_m3eq(b,c);

    /**
     * check that multiplying two 180 degree rotations
     * will get us back to the identitiy matrix
     */
    mat3 a = (mat3){.m={
        cos(M_PI), -sin(M_PI), 0.0,
        sin(M_PI),  cos(M_PI), 0.0,
        0.0,        0.0,       1.0
    }};

    b = (mat3){.m={
        cos(M_PI), -sin(M_PI), 0.0,
        sin(M_PI),  cos(M_PI), 0.0,
        0.0,        0.0,       1.0,
    }};

    c = mult_mat3(a,b);
    assert_m3eq(i,c);

#undef assert_m3eq
};


void test_mult_mat4() {
#define assert_m4eq(a, b) {                             \
    for (int _i=0; _i<16; _i++)                         \
             sgu_assert_float_eq(a.m[_i], b.m[_i]);     \
    }

    /** check identity matrix */
    mat4 i = (mat4){.m={
        1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0,
    }};

    mat4 b = (mat4){.m={
        sgu_rndf(), sgu_rndf(), sgu_rndf(), sgu_rndf(),
        sgu_rndf(), sgu_rndf(), sgu_rndf(), sgu_rndf(),
        sgu_rndf(), sgu_rndf(), sgu_rndf(), sgu_rndf(),
        sgu_rndf(), sgu_rndf(), sgu_rndf(), sgu_rndf()
    }};

    mat4 c = mult_mat4(i, b);
    assert_m4eq(b,c);

    /**
     * check that multiplying two 180 degree rotations
     * will get us back to the identitiy matrix
     */
    mat4 a = (mat4){.m={
        cos(M_PI), -sin(M_PI), 0.0, 0.0,
        sin(M_PI),  cos(M_PI), 0.0, 0.0,
        0.0,        0.0,       1.0, 0.0,
        0.0,        0.0,       0.0, 1.0
    }};

    b = (mat4){.m={
        cos(M_PI), -sin(M_PI), 0.0, 0.0,
        sin(M_PI),  cos(M_PI), 0.0, 0.0,
        0.0,        0.0,       1.0, 0.0,
        0.0,        0.0,       0.0, 1.0
    }};

    c = mult_mat4(a,b);
    assert_m4eq(i,c);

#undef assert_m4eq
};

void test_mult_mat4_vec4() {
    /**
     * Check that multiplying a unit vector by a
     * 90 degree rotation matrix works.
     */
    mat4 r90 = (mat4){.m={
        cos(M_PI/2.0), -sin(M_PI/2.0), 0.0, 0.0,
        sin(M_PI/2.0),  cos(M_PI/2.0), 0.0, 0.0,
        0.0,           0.0,            1.0, 0.0,
        0.0,           0.0,            0.0, 1.0
    }};
    vec4 x_u = (vec4){.v={1.0, 0.0, 0.0, 1.0}};
    vec4 y_u = mult_mat4_vec4(r90, x_u);

    // Should be <0,1,0,1> y-unit vector
    sgu_assert_float_eq(y_u.x, 0.0);
    sgu_assert_float_eq(y_u.y, 1.0);
    sgu_assert_float_eq(y_u.z, 0.0);
    sgu_assert_float_eq(y_u.w, 1.0);

    vec4 neg_x_u = mult_mat4_vec4(r90, y_u);

    // Should be <-1,0,0,1> negative x-unit vector
    sgu_assert_float_eq(neg_x_u.x, -1.0);
    sgu_assert_float_eq(neg_x_u.y, 0.0);
    sgu_assert_float_eq(neg_x_u.z, 0.0);
    sgu_assert_float_eq(neg_x_u.w, 1.0);
}

/*
 * test make_cube function
 */
void test_make_cube() {
    sgu_cube c = make_cube(1.0);
    g_assert(c.vert_count==8);
}

/*
 * test fit_axis_aligned_bounding_box
 */
void test_fit_axis_aligned_bounding_box() {
#define num_verts 10
    vec4 *zero_verts = calloc(num_verts, sizeof(vec4));
    for (int i=0; i<num_verts; i++) {
        zero_verts[i] = (vec4){.v={0, 0, 0, 0}};
    }

    bounding_box zero_aabb = fit_axis_aligned_bounding_box(
            zero_verts, num_verts);

    for (int i=0; i<2; i++) {
        sgu_assert_float_eq(zero_aabb.c[i].x, 0.0);
        sgu_assert_float_eq(zero_aabb.c[i].y, 0.0);
        sgu_assert_float_eq(zero_aabb.c[i].z, 0.0);
        sgu_assert_float_eq(zero_aabb.c[i].w, 1.0);
    }
#undef num_verts
}

void test_aabb_hit() {
    bounding_box box = {
        .min={.v={-1, -1, -1, 1}},
        .max={.v={ 1,  1,  1, 1}}
    };

    // inverse view
    mat4 view = look_at(
            (vec3){.v={100, 0, 0}}, // eye
            (vec3){.v={0, 0, 0}}, // center
            (vec3){.v={0, 1, 0}} // up
            );
    mat4 inv_view = invert_mat4(view);

    // inverse projection
    mat4 proj = project_persp(30.0, 1, 1.0, 10000.0);
    mat4 inv_proj = invert_mat4(proj);

    // TODO: Improve this test...
    int res = aabb_hit(
            (vec2){.v={0,0}}, // touch point
            (vec2){.v={50,50}}, // screen size
            inv_view, inv_proj, box);
    g_assert(res == 1);
}

/*
 * main()
 * run the tests
 */
int main(int argc, char *argv[])
{
    srandomdev();
    g_test_init(&argc, &argv, NULL);

    g_test_add("/vec2/union test", vec2fixture, NULL,
                         vec2_setup, test_vec2_union, vec2_teardown);

    g_test_add("/vec3/union test", vec3fixture, NULL,
                         vec3_setup, test_vec3_union, vec3_teardown);
    g_test_add("/vec3/norm_len test", vec3fixture, NULL,
                         vec3_setup, test_vec3_norm_len, vec3_teardown);
    g_test_add("/vec3/abs test", vec3fixture, NULL,
                         vec3_setup, test_vec3_abs, vec3_teardown);
    g_test_add("/vec3/neg test", vec3fixture, NULL,
                         vec3_setup, test_vec3_neg, vec3_teardown);
    g_test_add("/vec3/add test", vec3fixture, NULL,
                         vec3_setup, test_vec3_add, vec3_teardown);
    g_test_add("/vec3/scalar_mult test", vec3fixture, NULL,
                         vec3_setup, test_vec3_scalar_mult, vec3_teardown);
    g_test_add("/vec3/cross test", vec3fixture, NULL,
                         vec3_setup, test_vec3_cross, vec3_teardown);
    g_test_add("/vec3/dot test", vec3fixture, NULL,
                         vec3_setup, test_vec3_dot, vec3_teardown);

    g_test_add("/vec4/union test", vec4fixture, NULL,
                         vec4_setup, test_vec4_union, vec4_teardown);
    g_test_add("/vec4/norm_len test", vec4fixture, NULL,
                         vec4_setup, test_vec4_norm_len, vec4_teardown);

    g_test_add("/quat/union test", quatfixture, NULL,
                         quat_setup, test_quat_union, quat_teardown);
    g_test_add("/quat/conjugate test", quatfixture, NULL,
                         quat_setup, test_quat_conjugate, quat_teardown);
    g_test_add("/quat/mult test", quatfixture, NULL,
                         quat_setup, test_quat_mult, quat_teardown);

    g_test_add_func("/geom/rotateQ test", test_rotateQ);

    g_test_add_func("/mat3/det_mat3 test", test_det_mat3);
    g_test_add_func("/mat3/det_mat4 test", test_det_mat4);

    g_test_add_func("/mat3/invert_mat3 test", test_invert_mat3);
    g_test_add_func("/mat3/invert_mat4 test", test_invert_mat4);

    g_test_add_func("/mat3/mult_mat3 test", test_mult_mat3);
    g_test_add_func("/mat4/mult_mat4 test", test_mult_mat4);
    g_test_add_func("/mat4/mult_mat4_vec4 test", test_mult_mat4_vec4);

    g_test_add_func("/shapes/make_cube test", test_make_cube);

    g_test_add_func("/shapes/fit_axis_aligned_bounding_box test",
            test_fit_axis_aligned_bounding_box);

    g_test_add_func("/shapes/aabb_hit test", test_aabb_hit);

    return g_test_run();
}
