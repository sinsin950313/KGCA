//#include "IOCPBaseCommunicationModule.h"
//#include "IOCPBaseCommunicationModule.h"
//
//namespace SSB
//{
//	bool IOCPSession::Read(Packet& packet)
//	{
//		OVERLAPPED2* ov = new OVERLAPPED2(OVERLAPPED2::MODE_RECV);
//		m_wsaRecvBuffer.buf = &m_szDataBuffer[m_iWritePos];
//		m_wsaRecvBuffer.len = g_iMaxDataBufferSize;
//		DWORD dwRecvBytes;
//		DWORD dwFlag = 0;
//		int iRet = WSARecv(m_Sock, &m_wsaRecvBuffer, 1, &dwRecvBytes, &dwFlag,
//			(OVERLAPPED*)ov, NULL);
//
//		if (iRet == SOCKET_ERROR)
//		{
//			if (WSAGetLastError() != WSA_IO_PENDING)
//			{
//				m_bDisConnect = true;
//				return -1;
//			}
//		}
//		return 1;
//	}
//	bool IOCPSession::Write(Packet& packet)
//	{
//		m_wsaSendBuffer.buf = (char*)&packet;
//		m_wsaSendBuffer.len = packet.ph.len;
//
//		OVERLAPPED2* ov = new OVERLAPPED2(OVERLAPPED2::MODE_SEND);
//
//		DWORD dwSendBytes;// = send(sock, msgSend, packet.ph.len, 0);
//		int iRet = WSASend(m_Sock, &m_wsaSendBuffer, 1, &dwSendBytes, 0,
//			(OVERLAPPED*)ov, NULL);
//
//		if (iRet == SOCKET_ERROR)
//		{
//			if (WSAGetLastError() != WSA_IO_PENDING)
//			{
//				m_bDisConnect = true;
//				return -1;
//			}
//		}
//		return 1;
//	}
//	void IOCPBaseCommunicationModule::Connect(SOCKET socket)
//	{
//		_dataUpdated = true;
//		// Need adjust polymorphism
//		_connectionData.insert(std::make_pair(socket, std::make_unique<IOCPSession>(socket, socket)));
//		_iter = _connectionData.begin();
//	}
//	unsigned WINAPI IOCPBaseCommunicationModule::WorkProc(LPVOID arg)
//	{
//		// Pass evented socket to IOCP::GetNext() queue
//
//		//TIocp* pIocp = (TIocp*)arg;
//		//DWORD dwTransfer;
//		//ULONG_PTR KeyValue;
//		//OVERLAPPED* pOV;
//		//while (1)
//		//{
//		//	DWORD dwEvent = WaitForSingleObject(pIocp->m_hEventFinish, 0);
//		//	if (dwEvent == WAIT_OBJECT_0)
//		//	{
//		//		break;
//		//	}
//		//	// 비동기 읽기 완성 여부 판단
//		//	BOOL bRet = ::GetQueuedCompletionStatus(pIocp->m_hIOCP,
//		//		&dwTransfer,
//		//		&KeyValue,
//		//		&pOV, INFINITE);
//
//		//	OVERLAPPED2* pOV2 = (OVERLAPPED2*)pOV;
//		//	TSessionUser* user = (TSessionUser*)KeyValue;
//		//	if (bRet == TRUE)
//		//	{
//		//		// 읽기 또는 쓰기 비동기 완성
//		//		if (OVERLAPPED2::MODE_RECV == pOV2->iType)
//		//		{
//		//			user->DispatchRead(dwTransfer, pOV2);
//		//			user->RecvMsg();
//		//		}
//		//		if (OVERLAPPED2::MODE_SEND == pOV2->iType)
//		//		{
//		//			user->DispatchSend(dwTransfer, pOV2);
//		//		}
//		//	}
//		//	else
//		//	{
//		//		DWORD dwError = GetLastError();
//		//		if (dwError == ERROR_NETNAME_DELETED)
//		//		{
//		//			user->m_bDisConnect = true;
//		//		}
//		//	}
//		//}
//		return 0;
//	}
//	IOCPBaseCommunicationModule::IOCPBaseCommunicationModule(int maxWorkerThreadCount) : _maxWorkerThreadCount(maxWorkerThreadCount)
//	{
//		_workerThreadArray = new unsigned long[_maxWorkerThreadCount];
//		_threadIDArray = new unsigned int[_maxWorkerThreadCount];
//
//		_iocp = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0, 0);
//		_eventHandle = ::CreateEvent(0, TRUE, FALSE, 0);
//		for (int i = 0; i < _maxWorkerThreadCount; ++i)
//		{
//			_workerThreadArray[i] = _beginthreadex(NULL, 0, WorkProc, this, 0, &_threadIDArray[i]);
//		}
//	}
//	IOCPBaseCommunicationModule::~IOCPBaseCommunicationModule()
//	{
//		CloseHandle(_iocp);
//		for (int i= 0; i< _maxWorkerThreadCount; ++i)
//		{
//			CloseHandle((HANDLE)_threadIDArray[i]);
//		}
//
//		delete[] _workerThreadArray;
//		delete[] _threadIDArray;
//	}
//
//	UserID :IOCPBaseCommunicationModule::Connect(IPAddress address, PortNumber port)
//	{
//		SOCKET SessionSocket = socket(AF_INET, SOCK_STREAM, 0);
//
//		SOCKADDR_IN sa;
//		sa.sin_family = AF_INET;
//		sa.sin_addr.s_addr = inet_addr(address.c_str());
//		sa.sin_port = htons(port);
//		{
//			int ret = connect(SessionSocket, (sockaddr*)&sa, sizeof(sa));
//			if (ret == SOCKET_ERROR)
//			{
//				int error = GetLastError();
//				return NewConnectionNotExist;
//			}
//		}
//		Connect(SessionSocket);
//
//		::CreateIoCompletionPort((HANDLE)sock, m_hIOCP, key, 0);
//
//		return SessionSocket;
//	}
//}
