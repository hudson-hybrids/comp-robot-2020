#include "CommandScheduler.h"



void CommandScheduler::ClearCommandsContents() {
	if (commands != nullptr) {
		for (unsigned int i = 0; i < commands->size(); i++) {
			if ((*commands)[0] != nullptr) {
				delete (*commands)[0];
			}
			commands->erase(commands->begin());
		}
	}
}

void CommandScheduler::ClearCommands() {
	ClearCommandsContents();
	if (commands != nullptr) {
		delete commands;
	}
}

CommandScheduler::CommandScheduler(std::vector<Command*> *commands) {
	isFinished = false;
	this->commands = commands;
}

CommandScheduler::CommandScheduler() {
	isFinished = true;
}

CommandScheduler::~CommandScheduler() {
	ClearCommands();
}

void CommandScheduler::Run() {
	if (isFinished) {
		std::cout << "WARNING > CALL TO Run ON FINISHED CommandScheduler" << std::endl;
	}
	else {
		for (unsigned int i = 0; i < commands->size(); i++) {
			if ((*commands)[i] != nullptr) {
				if (!(*commands)[i]->GetIsFinished()) {
					(*commands)[i]->Run();
					return;
				}
			}
		}
		isFinished = true;
		ClearCommandsContents();
	}
}

void CommandScheduler::AddCommand(Command *command) {
	if (commands != nullptr) {
		isFinished = false;
		commands->push_back(command);
	}
}

bool CommandScheduler::GetIsFinished() {
	return isFinished;
}