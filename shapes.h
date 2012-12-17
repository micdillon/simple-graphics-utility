/*
 * - The Simple Graphics Utility
 * shapes.h
 */
#pragma once

#include "sgu.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
	* cube
	*/
typedef struct {
	vec3 verts[8];
	int vert_count;

	unsigned int indices[36];
	int index_count;

	vec3 norms[36];
	int norm_count;

	vec2 tex_coords[36];
	int tex_coord_count;
} gsu_cube;

gsu_cube make_cube(SGUfloat side_length);

#ifdef __cplusplus
}
#endif
