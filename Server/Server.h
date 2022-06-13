#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <string>
#include<thread>
#include<list>
#include"ClientInfo.h"
#include"ServerProtocol.h"
#include"DatabaseContext.h"
#include"../SerializableEntities/BinaryFormatter.h"


class Server
{
protected:

	list<ClientInfo*> clientsInfo; //�������� �������� � ������������ ��������
	ServerProtocol protocol; //�������� �� �������/����� ���������
	const unsigned int maxAmountOfConnections = 10;

	//� ���� ������ ���������� �������������� � ��������
	void userHandler(ClientInfo* client);

	//����������� ��� ������������ �������������

	unsigned int validation(ClientInfo* client);

	unsigned int registration(ClientInfo* client);

	unsigned int authorization(ClientInfo* client);

	void adminHandler(ClientInfo* clientInfo);

	void clientHandler(ClientInfo* clientInfo);

	void expertHandler(ClientInfo* clientInfo);

	//������������� ������� �� ������������ �����
	Server();

public:

	//������������� ������� �� ��������� �����(����� ������������ ���� �����������)
	Server(unsigned int port);

	//�������� ���������� ������� �������� � �������� ������������ ������
	~Server();

	//�������� ���������� ����� ������������� 
	void openConnection();

};
