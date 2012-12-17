/*
 * - The Simple Graphics Utility
 * shapes.c
 */
#include <stdio.h>
#include "shapes.h"

gsu_cube make_cube(SGUfloat len) {
	/** initialize the verts and indices */
	gsu_cube _c = {
		.verts={
			{.v={-len,  len,  len}},
			{.v={ len,  len,  len}},
			{.v={ len, -len,  len}},
			{.v={-len, -len,  len}},
			{.v={-len,  len, -len}},
			{.v={ len,  len, -len}},
			{.v={ len, -len, -len}},
			{.v={-len, -len, -len}}
		},
		.vert_count = 8,
		.indices={
			0,1,2, 0,2,3,
			1,5,6, 1,6,2,
			5,4,7, 5,7,6,
			4,0,3, 4,3,7,
			3,2,6, 3,6,7,
			4,5,1, 4,1,0
		},
		.index_count = 36,
		.norms={},
		.norm_count = 36,
		// .norm_count = 8,
		.tex_coords={},
		// .tex_coord_count = 36
		.tex_coord_count = 8
	};

	/** calculate norms */
// #define v(i1,i2) add3(_c.verts[_c.indices[(i1)]], \
// 		neg3(_c.verts[_c.indices[(i2)]]))
// 	for (int i=0; i<_c.norm_count; i+=3) {
// 		_c.norms[i+0] = norm3(cross3(v(i+2,i),v(i+1,i)));
// 		_c.norms[i+1] = norm3(cross3(v(i,i+1),v(i+2,i+1)));
// 		_c.norms[i+2] = norm3(cross3(v(i+1,i+2),v(i,i+2)));
// 	}
// #undef v

	_c.norms[0] = (vec3){.v={0.0, 0.0, 1.0}};
	_c.norms[1] = (vec3){.v={0.0, 0.0, 1.0}};
	_c.norms[2] = (vec3){.v={0.0, 0.0, 1.0}};
	_c.norms[3] = (vec3){.v={0.0, 0.0, 1.0}};

	_c.norms[4] = (vec3){.v={0.0, 0.0, -1.0}};
	_c.norms[5] = (vec3){.v={0.0, 0.0, -1.0}};
	_c.norms[6] = (vec3){.v={0.0, 0.0, -1.0}};
	_c.norms[7] = (vec3){.v={0.0, 0.0, -1.0}};

	/** calculate texture coords */
	// for (int i=0; i<_c.tex_coord_count; i+=6) {
	// 	SGUfloat a = 0.0;
	// 	SGUfloat b = 1.0;

	// 	_c.tex_coords[i+0] = (vec2){.v={a, b}};
	// 	_c.tex_coords[i+1] = (vec2){.v={b, b}};
	// 	_c.tex_coords[i+2] = (vec2){.v={b, a}};

	// 	_c.tex_coords[i+3] = (vec2){.v={a, b}};
	// 	_c.tex_coords[i+4] = (vec2){.v={b, a}};
	// 	_c.tex_coords[i+5] = (vec2){.v={a, a}};
	// }

	_c.tex_coords[0] = (vec2){.v={0.0, 1.0}};
	_c.tex_coords[1] = (vec2){.v={1.0, 1.0}};
	_c.tex_coords[2] = (vec2){.v={1.0, 0.0}};
	_c.tex_coords[3] = (vec2){.v={0.0, 0.0}};

	_c.tex_coords[4] = (vec2){.v={0.0, 1.0}};
	_c.tex_coords[5] = (vec2){.v={1.0, 1.0}};
	_c.tex_coords[6] = (vec2){.v={1.0, 0.0}};
	_c.tex_coords[7] = (vec2){.v={0.0, 0.0}};

	return _c;
}
