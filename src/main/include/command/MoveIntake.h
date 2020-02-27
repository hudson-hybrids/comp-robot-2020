#pragma once

#include <iostream>

#include "command/Command.h"
#include "AutoControl.h"

class MoveIntake: public Command {
	public:
		void Run() override;
};