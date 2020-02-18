class Command {
	private:
		bool isFinished = false;

	public:
		bool GetIsFinished();
		virtual void Run() = 0; 
};