//#include "State.h"
//#include "FSM.h"
//#include <iostream>
//#include <thread>
//
//namespace SSB
//{
//	class IdleState : public State
//	{
//	public:
//		void Process() override;
//	};
//	void IdleState::Process()
//	{
//		std::cout << "Idle" << std::endl;
//	}
//
//	class WalkState : public State
//	{
//	public:
//		void Process() override;
//	};
//	void WalkState::Process()
//	{
//		std::cout << "Walk" << std::endl;
//	}
//
//	class RunState : public State
//	{
//	public:
//		void Process() override;
//	};
//	void RunState::Process()
//	{
//		std::cout << "Run" << std::endl;
//	}
//
//	class DeadState : public State
//	{
//	public:
//		void Process() override;
//	};
//	void DeadState::Process()
//	{
//		std::cout << "Dead" << std::endl;
//		exit(0);
//	}
//}
//
//SSB::StateMachineEvent idleEvent = 0;
//SSB::StateMachineEvent walkEvent = 1;
//SSB::StateMachineEvent runEvent = 2;
//SSB::StateMachineEvent deadEvent = 3;
//
//void Input(SSB::FSM& fsm)
//{
//	int input;
//	do
//	{
//		std::cin >> input;
//		fsm.EventOccured(input);
//	} while (input != deadEvent);
//}
//
//int main()
//{
//	SSB::IdleState idle;
//	SSB::WalkState walk;
//	SSB::RunState run;
//	SSB::DeadState dead;
//
//	idle.AddTransition(walkEvent, &walk);
//	idle.AddTransition(runEvent, &run);
//	idle.AddTransition(deadEvent, &dead);
//
//	walk.AddTransition(idleEvent, &idle);
//	walk.AddTransition(runEvent, &run);
//	walk.AddTransition(deadEvent, &dead);
//
//	run.AddTransition(walkEvent, &walk);
//	run.AddTransition(idleEvent, &idle);
//	run.AddTransition(deadEvent, &dead);
//
//	SSB::FSM _fsm(&idle);
//	std::thread inputThread(Input, std::ref(_fsm));
//
//	while (1)
//	{
//		_fsm.Run();
//	}
//
//	inputThread.join();
//}