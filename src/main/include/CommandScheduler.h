#pragma once

#include <vector>

#include "command/Command.h"

class CommandScheduler {
	private:
		bool isFinished = false;
		std::vector<Command*> *commands = nullptr;

	public:
		CommandScheduler();
		CommandScheduler(std::vector<Command*> *commands);
		~CommandScheduler();
		
		void Run();
		bool GetIsFinished();
};