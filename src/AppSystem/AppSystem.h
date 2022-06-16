#pragma once

#include "../InputSystem/InputListener.h"

class AppSystem : public InputListener {
public:
	static inline AppSystem& GetInstance();

	inline void Init();
	inline void Update();

	// InputListener
	inline virtual void OnKeyDown(int key) override;
	inline virtual void OnKeyUp(int key) override;

private:
	AppSystem() {};

public:
	AppSystem(AppSystem const&) = delete;
	void operator=(AppSystem const&) = delete;
};