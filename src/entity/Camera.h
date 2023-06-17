#ifndef PALMX_CAMERA_H_
#define PALMX_CAMERA_H_

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace palmx
{
	class Camera;
	class Transform;

	struct MainCamera
	{
		MainCamera(const Camera& camera, const Transform& transform) : mCamera(&camera), mTransform(&transform) {}
		~MainCamera() {}

		const Camera* mCamera;
		const Transform* mTransform;
	};

	class Camera
	{
	public:
		Camera();
		~Camera();

		glm::mat4 GetViewMatrix(const Transform& transform) const;

		float mZoom{ 45 };
	};
}

#endif