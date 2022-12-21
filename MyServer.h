#pragma once

#include "MyUser.h"
// MyServer 명령 대상

class MyServer : public CSocket
{
private:
	CObList m_user_list; // 부모가 CObject일때 쓰는 연결리스트
	// MyUser m_user;
public:
	MyServer();
	virtual ~MyServer();
	virtual void OnAccept(int nErrorCode);
};


