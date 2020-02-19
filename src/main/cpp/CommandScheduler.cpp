#include "CommandScheduler.h"

CommandScheduler::CommandScheduler() {}

CommandScheduler::CommandScheduler(std::vector<Command*> *commands) {
	this->commands = commands;
}

CommandScheduler::~CommandScheduler() {
	for (unsigned int i = 0; i < commands->size(); i++) {
		delete (*commands)[i];
	}
	delete commands;
}

void CommandScheduler::Run() {
	for (unsigned int i = 0; i < commands->size(); i++) {
		if (!(*commands)[i]->GetIsFinished()) {
			(*commands)[i]->Run();
			break;
		}
	}
	isFinished = true;
}

bool CommandScheduler::GetIsFinished() {
	return isFinished;
}