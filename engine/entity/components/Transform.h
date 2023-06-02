#ifndef _PE_TRANSFORM_H__
#define _PE_TRANSFORM_H__

#include <glm/vec3.hpp>

namespace PalmEngine
{
	//template<typename T>
	//class AssignmentHook {
	//public:
	//	typedef void (hook_t)(const T& newValue);

	//	AssignmentHook(T& value, hook_t hook) : _ref(value), _hook(hook) {}

	//	T& operator=(const T& rhs)
	//	{
	//		_hook(rhs);
	//		_ref = rhs;
	//	}
	//private:
	//	// I'd rather not want to think about copying this
	//	AssignmentHook(const AssignmentHook&);
	//	void operator=(const AssignmentHook&);

	//	T& _ref;
	//	hook_t _hook;
	//};

	class Transform
	{
	public:
		Transform();

		glm::vec3 mPosition = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 mRotation = glm::vec3(0.0f, 0.0f, 0.0f); // Pitch, Yaw, Roll
		glm::vec3 mScale = glm::vec3(1.0f, 1.0f, 1.0f);

		glm::vec3 mForward;
		glm::vec3 mRight;
		glm::vec3 mUp;

	private:
		// AssignmentHook<glm::vec3> _rotationChangeHook;

		void UpdateDirectionVectors(const glm::vec3& newValue);
	};
}

#endif