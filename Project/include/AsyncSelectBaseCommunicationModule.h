#pragma once

#include "CommonSocket.h"
#include <queue>

#define CUSTOM_NETWORK_MESSAGE WM_USER+100

namespace SSB
{
	class AsyncSelectBaseCommunicationModule : public CommunicationModule
	{
	private:
		HWND _hWnd;
		UserID _id;

	public:
		void SetSelectSocketId(UserID id);
		void SetWindowHandle(HWND hWnd);
		bool RegisterAsyncSelectSocket(UserID id);

	protected:
		std::map<UserID, std::unique_ptr<Session>>::iterator GetNext() override;
	};
}
