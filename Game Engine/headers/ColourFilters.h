#ifndef COLOUR_FILTERS_H
#define COLOUR_FILTERS_H


#include <glm/glm.hpp>
using glm::mat3;


static const mat3 SEPIA_FILTER = mat3(0.393, 0.769, 0.189,
0.349, 0.686, 0.168,
0.272, 0.534, 0.131);

static const mat3 BLACK_AND_WHITE_FILTER = mat3(-0.7, 2.0, -0.3,
	-0.7, 2.0, -0.3,
	-0.7, 2.0, -0.3);

#endif