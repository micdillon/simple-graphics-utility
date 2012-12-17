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
		.norm_count = 8,
		.tex_coords={},
		.tex_coord_count = 8
	};

	/** normals */
	_c.norms[0] = (vec3){.v={0.0, 0.0, 1.0}};
	_c.norms[1] = (vec3){.v={0.0, 0.0, 1.0}};
	_c.norms[2] = (vec3){.v={0.0, 0.0, 1.0}};
	_c.norms[3] = (vec3){.v={0.0, 0.0, 1.0}};

	_c.norms[4] = (vec3){.v={0.0, 0.0, -1.0}};
	_c.norms[5] = (vec3){.v={0.0, 0.0, -1.0}};
	_c.norms[6] = (vec3){.v={0.0, 0.0, -1.0}};
	_c.norms[7] = (vec3){.v={0.0, 0.0, -1.0}};

	/** tex coords */
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
