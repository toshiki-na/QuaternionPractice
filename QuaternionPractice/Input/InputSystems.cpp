#include "InputSystems.h"
#include "MouseInput.h"
#include "KeyBoardInput.h"
#include "GamePadInput.h"

//XV
void InputSystems::Update()
{
	mouse.Update();
	keyboard.Update();
	gamepad.Update();
}