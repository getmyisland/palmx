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
			void Step(float delta_time, Scene* scene);

		private:
			void ResolveCollisions(float delta_time, Scene* scene);
		};
	}
}

#endif