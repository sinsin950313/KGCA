//#pragma once
//
//#include "CommonSocket.h"
//#include <process.h>
//
//namespace SSB
//{
//	class IOCPSession : public Session
//	{
//	public:
//		bool Read(Packet& packet) override;
//		bool Write(Packet& packet) override;
//	};
//
//	class IOCPBaseCommunicationModule : public CommunicationModule
//	{
//	private:
//		int _maxWorkerThreadCount;
//		HANDLE  _iocp;
//		HANDLE  _eventHandle;
//		unsigned long* _workerThreadArray;
//		unsigned int*  _threadIDArray;
//
//	protected:
//		std::map<UserID, std::unique_ptr<Session>>::iterator GetNext() override;
//		void Connect(SOCKET socket) override;
//		//void DIsconnect(UserID id) override;
//
//	public:
//		static unsigned WINAPI WorkProc(LPVOID arg);
//
//	public:
//		IOCPBaseCommunicationModule(int maxWorkerThreadCount = 3);
//		~IOCPBaseCommunicationModule();
//
//	public:
//		UserID Connect(IPAddress address = TestIP, PortNumber port = TestPort) override;
//	};
//
//	class ListenWithIOCPBaseCommunicationModule : public IOCPBaseCommunicationModule, public ListenSocketInterface
//	{
//	private:
//		bool _isListenEstablished = false;
//		SOCKET _listenSocket;
//
//	public:
//		UserID Listen() override;
//	};
//}
