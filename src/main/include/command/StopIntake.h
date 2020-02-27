#pragma once

#include <iostream>

#include "command/Command.h"
#include "AutoControl.h"

class StopIntake: public Command {
	public:
		void Run() override;
};