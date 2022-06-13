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

	SOCKET connectionSocket; //—окет соединени€ с клиентом

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

	string lastIp; //ѕоследний IP клиента
	unsigned int clientId; //Id клиента в базе данных
public:

	// ласс не выполн€ет никакого контрол€ над этим полем
	thread* clientThread;

	void setClientId(unsigned int clientId);

	virtual unsigned int getClientId()const;

	virtual string getLastIp()const;

	bool operator == (const ClientInfoEx& other) const;

	bool operator != (const ClientInfoEx& other) const;

	ClientInfoEx(SOCKET connectionSocket, const string& lastIp);
	ClientInfoEx();
};

