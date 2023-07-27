#ifndef PALMX_SINGLETON_H
#define PALMX_SINGLETON_H

namespace palmx
{
	// Special singleton that needs to be initialized before it can be used
	template <typename T> class Singleton
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
			Singleton(void)
		{
			msSingleton = static_cast<T*>(this);
		}
		~Singleton(void)
		{
			msSingleton = 0;
		}

		// Get the singleton instance
		static T& GetSingleton(void)
		{
			return (*msSingleton);
		}

		// Get a pointer to the singleton instance
		static T* GetSingletonPtr(void)
		{
			return msSingleton;
		}

		Singleton(const Singleton<T>&) = delete;
		Singleton& operator=(const Singleton<T>&) = delete;

	protected:
		static T* msSingleton;
	};
}

#endif