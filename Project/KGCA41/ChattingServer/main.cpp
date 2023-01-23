#define _WINSOCK_DEPRECATED_NO_WARNINGS

#pragma comment (lib, "CommunicationModule.lib")

#include "SelectBaseCommunicationModule.h"
#include "EventSelectBaseCommunicationModule.h"
#include "ChattingServer.h"
#include <map>
#include <queue>
#include "NetworkProtocol.h"

int main()
{
	//SSB::ListenWithSelectBaseCommunicationModule cm;
	SSB::ListenWithEventSelectBaseCommunicationModule cm;
	SSB::ChattingServerDecoder decoder;

	std::map<SSB::UserID, std::string> userList;
	std::queue<std::string> message;
	decoder.SetUserList(userList);
	decoder.SetMessageQueue(message);

	while (1)
	{
		{
			SSB::UserID id = cm.Listen();
			if (id != NewConnectionNotExist)
			{
				userList.insert(std::make_pair(id, ""));
			}
		}

		{
			SSB::UserID id;
			SSB::Packet recvPacket;
			if (cm.Read(&id, recvPacket))
			{
				decoder.SetUserID(id);
				SSB::ServerAction* action = (SSB::ServerAction*)decoder.Decode(recvPacket);
				(*action)();
			}
		}

		while(!message.empty())
		{
			std::string msg = message.front();
			for (auto iter : userList)
			{
				SSB::MessageContent content;
				content.SetMessage(msg);
				cm.Write(iter.first, SSB::Packet(MessageTransfer, content));
			}
			message.pop();
		}
	}
}