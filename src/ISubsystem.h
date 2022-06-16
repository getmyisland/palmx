#pragma once

class ISubsystem {
public:
	virtual void init() = 0;
	virtual void update() = 0;
	virtual void shutDown() = 0;
};