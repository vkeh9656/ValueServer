#pragma once

// MyUser 명령 대상

class MyUser : public CSocket
{
private:
	CObList* mp_user_list;
	char m_is_header = 1;
	unsigned int m_data_size;

public:
	MyUser(CObList *ap_user_list);
	virtual ~MyUser();
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
};


