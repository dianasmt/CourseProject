#pragma once

#include<WinSock2.h>
#pragma comment (lib, "ws2_32.lib")
#include"../SerializableEntities/CommandsBetweenServerAndClient.h"
#include"../SerializableEntities/BinaryFormatter.h"
#include<iostream>

class ServerProtocol
{
protected:

	SOCKADDR_IN serverAddress; //Сетевой адрес сервера

	SOCKET listenSocket; //Сокет прослушивания

	//Создание сокета
	SOCKET createSocket()
	{
		SOCKET l_socket = socket(AF_INET, SOCK_STREAM, NULL);
		if (l_socket == INVALID_SOCKET)
		{
			WSACleanup();
			throw "Listen socket error!";
		}
		bindSocket(l_socket, serverAddress);
		modifySocketToListen(l_socket);
		return l_socket;
	}

	//Сопряжение сокета с адресом сервера
	void bindSocket(SOCKET& socket, SOCKADDR_IN address)
	{
		int size = sizeof(address);
		const sockaddr* buf = (sockaddr*)&address;
		if (bind(socket, buf, size) == SOCKET_ERROR)
		{
			throw "Binding failed";
		}
	}

	//Модификация сокета на прослушивание
	void modifySocketToListen(SOCKET& socket)
	{
		if (listen(socket, SOMAXCONN) == SOCKET_ERROR)
		{
			closesocket(socket);
			WSACleanup();
			throw "Listening failed!";
		}
	}

	//Отправка служебной команды
	void sendServiceCommand(SOCKET destination, ServiceCommands command)
	{
		string commandBuf = to_string((int)command);
		send(destination, commandBuf.c_str(), commandBuf.size(), NULL);
	}

	//Получение служебной команды
	ServiceCommands receiveServiceCommand(SOCKET from)
	{
		char commandBuf[3];
		memset(commandBuf, '\0', sizeof(commandBuf));
		recv(from, commandBuf, sizeof(commandBuf), NULL);
		return (ServiceCommands)atoi(commandBuf);
	}

public:

	//Создание сервера с портом
	ServerProtocol(unsigned int port)
	{
		WSADATA wsaData;
		WORD dllVersion = MAKEWORD(2, 2);
		if (WSAStartup(dllVersion, &wsaData) == WSAVERNOTSUPPORTED)
		{
			throw "WSAStartup version failure!";
		}
		serverAddress.sin_addr.s_addr = INADDR_ANY;
		serverAddress.sin_port = htons(port);
		serverAddress.sin_family = AF_INET;
		listenSocket = createSocket();
	}

	SOCKET acceptConnectionRequests(string& clientIpMutable)
	{
		SOCKADDR_IN clientAdress;
		int size = sizeof(clientAdress);
		//Принятие запроса на соединение
		SOCKET newClientSocket = accept(listenSocket, (sockaddr*)&clientAdress, &size);
		clientIpMutable = inet_ntoa(clientAdress.sin_addr);
		return newClientSocket;
	}

	//Получение логина от пользователя
	string receiveLogin(SOCKET from)
	{
		char sizeBuf[50];
		memset(sizeBuf, '\0', sizeof(sizeBuf));
		sendServiceCommand(from, ServiceCommands::READY_TO_RECEIVE);
		recv(from, sizeBuf, sizeof(sizeBuf), NULL);
		int loginSize = atoi(sizeBuf);
		char* loginBuf = new char[loginSize];
		sendServiceCommand(from, ServiceCommands::READY_TO_RECEIVE);
		recv(from, loginBuf, loginSize, NULL);
		string login(loginBuf, loginSize);
		delete[] loginBuf;
		sendServiceCommand(from, ServiceCommands::READY_TO_RECEIVE);
		return login;
	}

	//Получение пароля от пользователя
	string receivePassword(SOCKET from)
	{
		char sizeBuf[50];
		memset(sizeBuf, '\0', sizeof(sizeBuf));
		sendServiceCommand(from, ServiceCommands::READY_TO_RECEIVE);
		recv(from, sizeBuf, sizeof(sizeBuf), NULL);
		int passwordSize = atoi(sizeBuf);
		char* passwordBuf = new char[passwordSize];
		sendServiceCommand(from, ServiceCommands::READY_TO_RECEIVE);
		recv(from, passwordBuf, passwordSize, NULL);
		string login(passwordBuf, passwordSize);
		delete[] passwordBuf;
		sendServiceCommand(from, ServiceCommands::READY_TO_RECEIVE);
		return login;
	}

	//Приём запроса на соединение


	//Отправление коллекции данных по сокету
	template<class SerializableType>
	void sendList(const list<SerializableType>& listToSend, SOCKET destination)
	{
		//Сериализация объкта в строку
		string serializedString = BinaryFormatter::serialize(listToSend);
		//Конвертация размера сериализованной строки в строку для отправки
		string bufStringSize = to_string(serializedString.size());
		//Принять команду о готовности к приёму от клиента
		receiveServiceCommand(destination);
		//Отправка размера сериализованной строки
		send(destination, bufStringSize.c_str(), bufStringSize.size(), NULL);
		receiveServiceCommand(destination);
		//Отправка самой сериализованной строки
		send(destination, serializedString.c_str(), serializedString.size(), NULL);
		receiveServiceCommand(destination);
	}

	//Приём коллекции данных по сокету
	template<typename ReceivingType>
	list<ReceivingType> receiveList(SOCKET from)
	{
		char sizeBuf[100];
		//"Зануление буфера"
		memset(sizeBuf, '\0', sizeof(sizeBuf));
		//Отправка команды о готовности к приёму
		sendServiceCommand(from, ServiceCommands::READY_TO_RECEIVE);
		//Принятие размера сериализованной строки
		recv(from, sizeBuf, sizeof(sizeBuf), NULL);
		//конвертация размера из строки в число
		int size = atoi(sizeBuf);
		//Динамическое выделение памяти для принимаемой строки
		char* buffer = new char[size];
		sendServiceCommand(from, ServiceCommands::READY_TO_RECEIVE);
		//Приём строки 
		recv(from, buffer, size, NULL);
		sendServiceCommand(from, ServiceCommands::READY_TO_RECEIVE);
		//Конвертация char строки в string
		string serilizedString(buffer, size);
		//Очистка динамического буфера
		delete[] buffer;
		return BinaryFormatter::deserialize<ReceivingType>(serilizedString);
	}

	string receiveString(SOCKET from)
	{
		char sizeBuf[50];
		memset(sizeBuf, '\0', sizeof(sizeBuf));
		sendServiceCommand(from, ServiceCommands::READY_TO_RECEIVE);
		recv(from, sizeBuf, sizeof(sizeBuf), NULL);
		int strSize = atoi(sizeBuf);
		char* strBuf = new char[strSize];
		sendServiceCommand(from, ServiceCommands::READY_TO_RECEIVE);
		recv(from, strBuf, strSize, NULL);
		string login(strBuf, strSize);
		delete[] strBuf;
		sendServiceCommand(from, ServiceCommands::READY_TO_RECEIVE);
		return login;
	}

	void sendString(string str, SOCKET destination)
	{
		receiveServiceCommand(destination);
		string passwordSize = to_string(str.size());
		send(destination, passwordSize.c_str(), passwordSize.size(), NULL);
		receiveServiceCommand(destination);
		send(destination, str.c_str(), str.size(), NULL);
		receiveServiceCommand(destination);
	}

	//Отправка ответа клиенту
	void sendAnswer(AnswerFromServer answer, SOCKET destination)
	{
		//Конвертация ответа(число) в строку
		string buf = to_string((int)answer);
		//Отправка строки
		send(destination, buf.c_str(), buf.size(), NULL);
		receiveServiceCommand(destination);
	}

	//Приём команды от клиента
	CommandToServer receiveCommand(SOCKET from)
	{
		//Буфер приема(до 999 команд)
		char serverCommandBuf[3];
		//"Зануление"
		memset(serverCommandBuf, '\0', sizeof(serverCommandBuf));
		//Приём в буфер
		recv(from, serverCommandBuf, sizeof(serverCommandBuf), NULL);
		sendServiceCommand(from, ServiceCommands::READY_TO_RECEIVE);
		//Конвертирование в тип команды
		return (CommandToServer)atoi(serverCommandBuf);
	}

	//Отправка типа пользователя(исп. при валидации)
	void sendTypeOfUser(TypeOfUser type, SOCKET destination)
	{
		//Конвертация команды в строку
		string commandBuf = to_string((int)type);
		//Отправка
		send(destination, commandBuf.c_str(), commandBuf.size(), NULL);
	}

	//Приём типа пользователя(исп. при валидации)
	TypeOfUser receiveTypeOfUser(SOCKET from)
	{
		char commandBuf[3];
		memset(commandBuf, '\0', sizeof(commandBuf));
		recv(from, commandBuf, sizeof(commandBuf), NULL);
		return (TypeOfUser)atoi(commandBuf);
	}

	template<class SerializableType>
	SerializableType receiveObject(SOCKET from)
	{
		//Приём аналогичен приёму сервера
		char sizeBuf[100];
		memset(sizeBuf, '\0', sizeof(sizeBuf));
		sendServiceCommand(from, ServiceCommands::READY_TO_RECEIVE);
		recv(from, sizeBuf, sizeof(sizeBuf), NULL);
		int size = atoi(sizeBuf);
		char* buffer = new char[size];
		sendServiceCommand(from, ServiceCommands::READY_TO_RECEIVE);
		recv(from, buffer, size, NULL);
		sendServiceCommand(from, ServiceCommands::READY_TO_RECEIVE);
		string serilizedString(buffer, size);
		delete[] buffer;
		return BinaryFormatter::deserializeObj<SerializableType>(serilizedString);
	}

	template<class SerializableType>
	void sendObj(const SerializableType& obj, SOCKET destination)
	{
		//Отправка аналогична серверной
		string serializedString = BinaryFormatter::serialize(obj);
		string bufStringSize = to_string(serializedString.size());
		receiveServiceCommand(destination);
		send(destination, bufStringSize.c_str(), bufStringSize.size(), NULL);
		receiveServiceCommand(destination);
		send(destination, serializedString.c_str(), serializedString.size(), NULL);
		receiveServiceCommand(destination);
	}

	void closeConnection(SOCKET socket)
	{
		closesocket(socket);
	}

};
