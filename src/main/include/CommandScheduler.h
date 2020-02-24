#pragma once

#include <vector>
#include <iostream>

#include "command/Command.h"

class CommandScheduler {
	private:
		bool isFinished;
		std::vector<Command*> *commands = nullptr;

		void ClearCommandsContents();
		void ClearCommands();
		void ClearData();

	public:
		CommandScheduler();
		CommandScheduler(std::vector<Command*> *commands);
		~CommandScheduler();
		
		void Run();
		void AddCommand(Command *command);
		bool GetIsFinished();
};