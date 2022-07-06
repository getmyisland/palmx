#include "SystemManager.h"
#include "SystemGlobals.h"
#include <iostream>
#include <chrono>
#include <Windows.h>

using namespace std::chrono_literals;

// we use a fixed timestep of 1 / (60 fps) = 16 milliseconds
constexpr std::chrono::nanoseconds timestep(16ms);

struct game_state {
	// this contains the state of your game, such as positions and velocities
};

game_state Interpolate(game_state const& current, game_state const& previous, float alpha) {
	game_state interpolated_state;

	// interpolate between previous and current by alpha here

	return interpolated_state;
}

SystemManager& SystemManager::Instance() {
	static SystemManager    instance;

	return instance;
};

void SystemManager::StartEngine(HINSTANCE hInst) {
	m_hInstance = hInst;

	InitSystems();

	GameLoop();

	ShutdownSystems();
}

void SystemManager::InitSystems() {
	System::g_InputSystem.Init();
	System::g_GraphicSystem.Init();
}

void SystemManager::GameLoop() {
	using clock = std::chrono::high_resolution_clock;

	std::chrono::nanoseconds lag(0ns);
	auto time_start = clock::now();
	bool quit_game = false;

	game_state current_state;
	game_state previous_state;

	// Main game loop
	MSG msg;
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);

		auto delta_time = clock::now() - time_start;
		time_start = clock::now();
		lag += std::chrono::duration_cast<std::chrono::nanoseconds>(delta_time);

		// update game logic as lag permits
		while (lag >= timestep) {
			lag -= timestep;

			previous_state = current_state;
			UpdateSystems(); // update at a fixed rate each time
		}

		// calculate how close or far we are from the next timestep
		auto alpha = (float)lag.count() / timestep.count();
		auto interpolated_state = Interpolate(current_state, previous_state, alpha);

		RenderSystems();
	}
}

void SystemManager::UpdateSystems() {

}

void SystemManager::RenderSystems() {

}

void SystemManager::ShutdownSystems() {
	System::g_InputSystem.Shutdown();
	System::g_GraphicSystem.Shutdown();
}

void SystemManager::SendEventToSystems(CSystemEvent p_CSystemEvent) {

}