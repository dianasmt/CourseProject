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

	list<ClientInfo*> clientsInfo; //Содержит сведения о подключенных клиентах
	ServerProtocol protocol; //Отвечает за посылку/прием сущностей
	const unsigned int maxAmountOfConnections = 10;

	//В этом методе происходит взаимодействие с клиентом
	void userHandler(ClientInfo* client);

	//Авторизация уже существующих пользователей

	unsigned int validation(ClientInfo* client);

	unsigned int registration(ClientInfo* client);

	unsigned int authorization(ClientInfo* client);

	void adminHandler(ClientInfo* clientInfo);

	void clientHandler(ClientInfo* clientInfo);

	void expertHandler(ClientInfo* clientInfo);

	//Инициализация сервера по стандартному порту
	Server();

public:

	//Инициализация сервера по заданному порту(лучше использовать этот конструктор)
	Server(unsigned int port);

	//Ожидание завершения потоков клиентов и удаление динамических данных
	~Server();

	//Открытие соединения после инициализации 
	void openConnection();

};
