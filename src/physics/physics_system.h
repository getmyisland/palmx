#ifndef PALMX_PHYSICS_SYSTEM_H
#define PALMX_PHYSICS_SYSTEM_H

namespace palmx
{
	class Scene;

	namespace physics
	{

		class PhysicsSystem
		{
		public:
			void Step(float deltaTime, Scene* scene);

		private:
			void ResolveCollisions(float deltaTime, Scene* scene);
		};
	}
}

#endif