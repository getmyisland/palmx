#include "Transform.h"

namespace PalmEngine
{
	glm::vec3 Transform::GetLocalPosition() const
	{
		return _localPosition;
	}

	void Transform::SetLocalPosition(glm::vec3 localPosition)
	{
		_localPosition = localPosition;
	}

	glm::vec3 Transform::GetLocalScale() const
	{
		return _localScale;
	}

	void Transform::SetLocalScale(glm::vec3 localScale)
	{
		_localScale = localScale;
	}
}