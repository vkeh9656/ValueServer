// MyServer.cpp: 구현 파일
//

#include "pch.h"
#include "ValueServer.h"
#include "MyServer.h"


// MyServer

MyServer::MyServer()
{
}

MyServer::~MyServer()
{
	MyUser* p;
	POSITION pos = m_user_list.GetHeadPosition();
	while (pos != NULL)
	{
		p = (MyUser*)m_user_list.GetNext(pos); // 현재 노드의 값은 반환해주고
												// 자기는 그 다음 노드로 이동
		delete p;		// 반환된 현재 값을 delete
	}
}


// MyServer 멤버 함수


void MyServer::OnAccept(int nErrorCode)
{
	MyUser* p_user = new MyUser(&m_user_list);
	m_user_list.AddTail(p_user);
	Accept(*p_user);

	CSocket::OnAccept(nErrorCode);
}