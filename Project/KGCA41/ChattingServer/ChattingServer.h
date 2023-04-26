#pragma once

#include "CommonSocket.h"
#include <list>
#include <queue>

namespace SSB
{
	class ServerAction : public CommunicationTypeAction
	{
	protected:
		std::map<SSB::UserID, std::string>* _userList;
		std::queue<std::string>* _queue;

	public:
		void SetUserList(std::map<SSB::UserID, std::string>& userList);
		void SetMessageQueue(std::queue<std::string>& msgQueue);
	};

	class EnterAction : public ServerAction
	{
	private:
		UserID _enteredUserID;

	public:
		void SetEnteredUserID(UserID id);

	public:
		void operator()() override;
	};

	class MessageTransferAction : public ServerAction
	{
	private:
		std::string _str;
		UserID _chatUserId;

	public:
		void SetMessage(char* str, int length);
		void SetChattingUserID(UserID id);

	public:
		void operator()() override;
	};

	class ExitAction : public ServerAction
	{
	private:
		UserID _exitUserID;

	public:
		void SetExitUserID(UserID id);

	public:
		void operator()() override;
	};

	class ChattingServerDecoder : public Decoder
	{
	protected:
		UserID _id;
		std::map<SSB::UserID, std::string>* _userList;
		std::queue<std::string>* _queue;

	public:
		void SetUserID(UserID id);
		void SetUserList(std::map<SSB::UserID, std::string>& userList);
		void SetMessageQueue(std::queue<std::string>& msgQueue);

	public:
		CommunicationTypeAction* Decode(Packet packet) override;
	};

	class MessageContent : public PacketContent
	{
	private:
		PacketContentStruct _contentStruct;

	public:
		void SetMessage(std::string msg);

	public:
		PacketContentStruct Serialize() override;
	};
}
