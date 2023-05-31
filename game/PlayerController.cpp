#include "PlayerController.h"

#include <input/Input.h>
#include <logging/LogManager.h>

using namespace PalmEngine;

void PlayerController::Update()
{
	if (Input::GetKey(KEY_ARROW_UP))
	{
		PE_LOG_MANAGER->LogInfo("Hello World");
	}
}