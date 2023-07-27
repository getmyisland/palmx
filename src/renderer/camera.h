#ifndef PALMX_RENDER_CAMERA_H
#define PALMX_RENDER_CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace palmx::render
{
	struct Camera
	{
		float mZoom{ 45 };
	};
}

#endif