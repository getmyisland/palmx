#ifndef PALMX_PHYSICS_SYSTEM_H_
#define PALMX_PHYSICS_SYSTEM_H_

namespace palmx
{
	class Scene;

	class PhysicsSystem
	{
	public:
		void Step(float deltaTime, Scene* scene);

	private:
		void ResolveCollisions(float deltaTime, Scene* scene);
	};
}

#endif