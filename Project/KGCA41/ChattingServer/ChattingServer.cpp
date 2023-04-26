#include "ChattingServer.h"
#include <queue>

namespace SSB
{
	void ChattingServerDecoder::SetUserID(UserID id)
	{
		_id = id;
	}
	void ChattingServerDecoder::SetUserList(std::map<SSB::UserID, std::string>& userList)
	{
		_userList = &userList;
	}
	void ChattingServerDecoder::SetMessageQueue(std::queue<std::string>& msgQueue)
	{
		_queue = &msgQueue;
	}
	CommunicationTypeAction* ChattingServerDecoder::Decode(Packet packet)
	{
		const Byte* msg = packet.Serialize();
		HeaderStructure header;
		memcpy(&header, msg, HeaderSize);

		CommunicationTypeAction* ret = nullptr;
		switch (header.Type)
		{
		case ServerEnter:
		{
			static EnterAction action;
			action.SetUserList(*_userList);
			action.SetMessageQueue(*_queue);
			action.SetEnteredUserID(_id);
			ret = &action;
			break;
		}
		case MessageTransfer:
		{
			static MessageTransferAction action;

			Byte content[256]{ 0, };
			memcpy(content, msg + HeaderSize, header.ContentLength);
			action.SetMessage(content, header.ContentLength);
			action.SetMessageQueue(*_queue);
			action.SetChattingUserID(_id);
			ret = &action;
			break;
		}
		case ServerExit:
		{
			static ExitAction action;
			action.SetUserList(*_userList);
			action.SetMessageQueue(*_queue);
			action.SetExitUserID(_id);
			ret = &action;
			break;
		}
		}

		return ret;
	}
	void MessageContent::SetMessage(std::string msg)
	{
		_contentStruct.Size = msg.size();
		memcpy(&_contentStruct, msg.c_str(), msg.size());
	}
	PacketContentStruct MessageContent::Serialize()
	{
		return _contentStruct;
	}
	void EnterAction::SetEnteredUserID(UserID id)
	{
		_enteredUserID = id;
	}
	void EnterAction::operator()()
	{
		std::string str = " is enterted.";
		_queue->push(std::to_string(_enteredUserID) + str);

		(*_userList)[_enteredUserID] = _enteredUserID;
	}
	void MessageTransferAction::SetMessage(char* str, int length)
	{
		_str = std::string(str, length);
	}
	void MessageTransferAction::SetChattingUserID(UserID id)
	{
		_chatUserId = id;
	}
	void MessageTransferAction::operator()()
	{
		_queue->push(_str);
	}
	void ExitAction::SetExitUserID(UserID id)
	{
		_exitUserID = id;
	}
	void ExitAction::operator()()
	{
		std::string str = " is exit.";
		_queue->push(std::to_string(_exitUserID) + str);

		(*_userList).erase(_exitUserID);
	}
	void ServerAction::SetUserList(std::map<SSB::UserID, std::string>& userList)
	{
		_userList = &userList;
	}
	void ServerAction::SetMessageQueue(std::queue<std::string>& msgQueue)
	{
		_queue = &msgQueue;
	}
}
