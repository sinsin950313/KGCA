//#pragma once
//
//#define _WINSOCK_DEPRECATED_NO_WARNINGS
//
//#include "NetworkProtocol.h"
//#include <WinSock2.h>
//
//namespace SSB
//{
//	class SerialData sealed
//	{
//	private:
//		int _length;
//		Byte* _data;
//
//	private:
//		// Only make instance from Serialize() of SerializeInterface
//		SerialData(int length, Byte* data);
//
//	public:
//		SerialData(SerialData& data) = delete;
//		SerialData(SerialData&& data);
//		~SerialData();
//
//	public:
//		SerialData&& operator=(SerialData&& data);
//
//	private:
//		friend class SerializeableInterface;
//	};
//
//	class SerializeableInterface
//	{
//	public:
//		virtual SerialData Serialize() = 0;
//		virtual void DeSerialize(SerialData data) = 0;
//	};
//
//	class Socket
//	{
//	private:
//		SOCKET _socket;
//		SOCKADDR_IN _localAddress;
//		SOCKADDR_IN _remoteAddress;
//		int _socketState;
//		bool _destroyed = false;
//
//	public:
//		Socket(SOCKET socket);
//		~Socket();
//
//	public:
//		int Bind(SOCKADDR_IN localAddress);
//		Socket Accept(SOCKADDR_IN& remoteAddress, int* length);
//		int Connect(SOCKADDR_IN remoteAddress);
//		int Listen();
//
//	public:
//		void SetBlock();
//		void SetNonBlock();
//
//	public:
//		bool IsDestroyed() { return _destroyed; }
//		void GetState();
//
//	public:
//		//Return error code
//		int Read(SerializeableInterface& data);
//		int Write(ProtocolType type, SerialData data);
//	};
//
//	// Working with thread
//	class CommunicationModule
//	{
//	private:
//		WSADATA _wsa;
//
//	public:
//		CommunicationModule();
//		~CommunicationModule();
//
//	public:
//		//Return error code
//		int Read(Socket socket, SerializeableInterface& data);
//		int Write(Socket socket, ProtocolType type, SerialData data);
//	};
//}
