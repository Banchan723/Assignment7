#include "PJ2GameMode.h"
#include "PJ2Character.h"
#include "PJ2PlayerController.h"

APJ2GameMode::APJ2GameMode()
{
	DefaultPawnClass = APJ2Character::StaticClass();
	PlayerControllerClass = APJ2PlayerController::StaticClass();
}