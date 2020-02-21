#include "CommandScheduler.h"

void CommandScheduler::ClearData() {
	for (unsigned int i = 0; i < commands->size(); i++) {
		delete (*commands)[i];
	}
	delete commands;
}

CommandScheduler::CommandScheduler() {}

CommandScheduler::CommandScheduler(std::vector<Command*> *commands) {
	this->commands = commands;
}

CommandScheduler::~CommandScheduler() {
	ClearData();
}

void CommandScheduler::Run() {
	if (isFinished) {
		std::cout << "WARNING > CALL TO Run ON FINISHED CommandScheduler" << std::endl;
	}
	for (unsigned int i = 0; i < commands->size(); i++) {
		if (!(*commands)[i]->GetIsFinished()) {
			(*commands)[i]->Run();
			break;
		}
	}
	isFinished = true;
	ClearData();
}

bool CommandScheduler::GetIsFinished() {
	return isFinished;
}