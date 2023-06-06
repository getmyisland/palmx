#ifndef _PALM_ENGINE_SINGLETON_H__
#define _PALM_ENGINE_SINGLETON_H__

namespace PalmEngine
{
	template <typename T> class PalmEngineSingleton
	{
	public:
#if defined(__has_attribute)
#  if __has_attribute(no_sanitize)
		// The `static_cast` happens so early in the construction of the inheriting
		// classes that the `this` pointer is still detected as the super class
		// pointer. Therefore, disabling vptr checks.
		__attribute__((no_sanitize("vptr")))
#  endif
#endif
			PalmEngineSingleton(void)
		{
			ms_Singleton = static_cast<T*>(this);
		}
		~PalmEngineSingleton(void)
		{
			ms_Singleton = 0;
		}
		// Get the singleton instance
		static T& GetSingleton(void)
		{
			return (*ms_Singleton);
		}
		// Get a pointer to the singleton instance
		static T* GetSingletonPtr(void) { return ms_Singleton; }

		PalmEngineSingleton(const PalmEngineSingleton<T>&) = delete;
		PalmEngineSingleton& operator=(const PalmEngineSingleton<T>&) = delete;

	protected:
		static T* ms_Singleton;
	};
}

#endif