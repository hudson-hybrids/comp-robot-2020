#pragma once

class Command {
	protected:
		bool isFinished = false;

	public:
		virtual ~Command();

		bool GetIsFinished();
		virtual void Run() = 0; 
};