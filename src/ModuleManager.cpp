#include "ModuleManager.h"
#include "Modules.h"
#include <iostream>
#include <chrono>
#include <Windows.h>

using namespace std::chrono_literals;

// we use a fixed timestep of 1 / (60 fps) = 16 milliseconds
constexpr std::chrono::nanoseconds timestep(16ms);

struct game_state
{
	// this contains the state of your game, such as positions and velocities
};

game_state Interpolate(game_state const& current, game_state const& previous, float alpha)
{
	game_state interpolated_state;

	// interpolate between previous and current by alpha here

	return interpolated_state;
}

ModuleManager& ModuleManager::Instance()
{
	static ModuleManager    instance;

	return instance;
};

void ModuleManager::StartEngine(HINSTANCE hInst)
{
	m_hInstance = hInst;

	InitSystems();

	GameLoop();

	ShutdownSystems();
}

void ModuleManager::InitSystems()
{
	Module::g_InputSystem.Init();
	Module::g_GraphicSystem.Init();
}

void ModuleManager::GameLoop()
{
	using clock = std::chrono::high_resolution_clock;

	std::chrono::nanoseconds lag(0ns);
	auto time_start = clock::now();
	bool quit_game = false;

	game_state current_state;
	game_state previous_state;

	while (game_running)
	{
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

void ModuleManager::UpdateSystems()
{

}

void ModuleManager::RenderSystems()
{
	Module::g_GraphicSystem.Update();
}

void ModuleManager::ShutdownSystems()
{
	Module::g_InputSystem.Shutdown();
	Module::g_GraphicSystem.Shutdown();
}

void ModuleManager::SendEventToSystems(C_ModuleEvent p_CSystemEvent)
{

}

void ModuleManager::KillGameLoop()
{
	game_running = false;
}