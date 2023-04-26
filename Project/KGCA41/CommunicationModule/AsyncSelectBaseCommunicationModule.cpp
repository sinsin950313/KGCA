#include "AsyncSelectBaseCommunicationModule.h"

namespace SSB
{
    void AsyncSelectBaseCommunicationModule::SetSelectSocketId(UserID id)
    {
        _id = id;
    }
    void AsyncSelectBaseCommunicationModule::SetWindowHandle(HWND hWnd)
    {
        _hWnd = hWnd;
    }
    bool AsyncSelectBaseCommunicationModule::RegisterAsyncSelectSocket(UserID id)
    {
        int iRet = WSAAsyncSelect(_connectionData.find(id)->second->GetSocket(), _hWnd, CUSTOM_NETWORK_MESSAGE, FD_CONNECT | FD_READ | FD_WRITE | FD_CLOSE);
        if (iRet == SOCKET_ERROR)
        {
            return false;
        }
        return true;
    }
    std::map<UserID, std::unique_ptr<Session>>::iterator SSB::AsyncSelectBaseCommunicationModule::GetNext()
    {
        return _connectionData.find(_id);
    }
}
