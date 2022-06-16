#pragma once

class SingletonManager {
public:
	virtual void startUp() = 0;
	virtual void shutDown() = 0;
};