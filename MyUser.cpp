// MyUser.cpp: 구현 파일
//

#include "pch.h"
#include "ValueServer.h"
#include "MyUser.h"


// MyUser

MyUser::MyUser(CObList *ap_user_list)
{
	mp_user_list = ap_user_list;
}

MyUser::~MyUser()
{
}


// MyUser 멤버 함수
// 
// 상대편이 나에게 데이터를 줬을 때 발생하는 이벤트
void MyUser::OnReceive(int nErrorCode)
{
	int value;
	Receive(&value, sizeof(int));

	AfxGetMainWnd()->SetDlgItemInt(IDC_VALUE_EDIT, value);
	value = 1;
	Send(&value, sizeof(int));

	CSocket::OnReceive(nErrorCode);
}


void MyUser::OnClose(int nErrorCode)
{

	ShutDown(2);
	Close();

	MyUser* p = NULL;
	POSITION pos = mp_user_list->GetHeadPosition(), check_pos;
	while (pos != NULL)
	{
		check_pos = pos; // 현재 pos값 백업
		p = (MyUser*)mp_user_list->GetNext(pos);
		if (p == this)
		{
			mp_user_list->RemoveAt(check_pos);
			break;
		}
	}
	if (p != NULL) delete p;

	CSocket::OnClose(nErrorCode);
}
