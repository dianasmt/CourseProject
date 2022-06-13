#pragma once
#include<winsock2.h>
#pragma comment (lib, "ws2_32.lib")
#include<thread>
#include<string>
#include"../SerializableEntities/CommandsBetweenServerAndClient.h"

using namespace std;
class ClientInfo
{
protected:

	SOCKET connectionSocket; //����� ���������� � ��������

	TypeOfUser type;

public:

	virtual void setClientId(unsigned int clientId) {}

	virtual unsigned int getClientId()const { return 0; }

	ClientInfo();

	TypeOfUser getType()const;

	void setTypeOfUser(TypeOfUser type);

	SOCKET getConnectionSocket() const;

};

class ClientInfoEx : public ClientInfo
{
protected:

	string lastIp; //��������� IP �������
	unsigned int clientId; //Id ������� � ���� ������
public:

	//����� �� ��������� �������� �������� ��� ���� �����
	thread* clientThread;

	void setClientId(unsigned int clientId);

	virtual unsigned int getClientId()const;

	virtual string getLastIp()const;

	bool operator == (const ClientInfoEx& other) const;

	bool operator != (const ClientInfoEx& other) const;

	ClientInfoEx(SOCKET connectionSocket, const string& lastIp);
	ClientInfoEx();
};

