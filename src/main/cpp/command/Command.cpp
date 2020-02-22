#include "command/Command.h"

Command::~Command() {}

bool Command::GetIsFinished() {
	return isFinished;
}