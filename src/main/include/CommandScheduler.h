#pragma once

#include <vector>
#include <iostream>

#include "command/Command.h"

class CommandScheduler {
	private:
		bool isFinished = false;
		std::vector<Command*> *commands = nullptr;

		void ClearData();

	public:
		CommandScheduler();
		CommandScheduler(std::vector<Command*> *commands);
		~CommandScheduler();
		
		void Run();
		bool GetIsFinished();
};