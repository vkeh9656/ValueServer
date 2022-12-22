// MyUser.cpp: 구현 파일
//

#include "pch.h"
#include "ValueServer.h"
#include "MyUser.h"
#include "ValueServerDlg.h"

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
	DWORD temp_size;
	if (IOCtl(FIONREAD, &temp_size))	// 실제 수신버퍼에 데이터가 얼마나 들어있는지 확인하는 함수
	{

		if (m_is_header)	// header 작업
		{
			if (temp_size >= sizeof(unsigned int))	// 4바이트 크기인지 체크해서 보냄
			{
				Receive(&m_data_size, sizeof(int));
				m_is_header = !m_is_header;
			}
			
		}
		else                 // body작업
		{
			if (temp_size >= m_data_size)
			{
				char* pString = new char[m_data_size + sizeof(unsigned int)];
				*(int*)pString = m_data_size;

				Receive(pString + sizeof(unsigned int), m_data_size);

				((CValueServerDlg*)AfxGetMainWnd())->AddEventString((wchar_t*)(pString + sizeof(unsigned int)));
				
				MyUser* p = NULL;
				POSITION pos = mp_user_list->GetHeadPosition();
				while (pos != NULL)
				{
					p = (MyUser*)mp_user_list->GetNext(pos);
					p->Send(pString, m_data_size + sizeof(unsigned int));
				}

				delete[] pString;
				m_is_header = !m_is_header;
			}
		}
	}
	else
	{
		((CValueServerDlg*)AfxGetMainWnd())->AddEventString(L"수신에 문제가 있습니다.");
	}

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
