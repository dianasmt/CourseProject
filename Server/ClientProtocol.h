#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include"BinaryFormatter.h"
#include"CommandsBetweenServerAndClient.h"
#include<string>
#include<winsock2.h>
#pragma comment (lib, "ws2_32.lib")

using namespace std;

class ClientProtocol
{
protected:

	SOCKADDR_IN serverAddress;

	SOCKET connectionSocket;

	ClientProtocol()
	{
		connectionSocket = 0;
	}

	void sendServiceCommand(ServiceCommands command)
	{
		//Конвертация команды в строку
		string commandBuf = to_string((int)command);
		//Отправка
		send(connectionSocket, commandBuf.c_str(), commandBuf.size(), NULL);
	}

	ServiceCommands receiveServiceCommand()
	{
		char commandBuf[3];
		memset(commandBuf, '\0', sizeof(commandBuf));
		recv(connectionSocket, commandBuf, sizeof(commandBuf), NULL);
		return (ServiceCommands)atoi(commandBuf);
	}

	void createSocket()
	{
		connectionSocket = socket(AF_INET, SOCK_STREAM, NULL);
	}

public:

	ClientProtocol(const string& serverIp, unsigned int serverPort)
	{
		WSADATA wsaData;
		WORD dllVersion = MAKEWORD(2, 2);
		if (WSAStartup(dllVersion, &wsaData) == WSAVERNOTSUPPORTED)
		{
			throw "WSAStartup version failure!";
		}
		serverAddress.sin_addr.s_addr = inet_addr(serverIp.c_str());
		serverAddress.sin_port = htons(serverPort);
		serverAddress.sin_family = AF_INET;
	}

	void establishConection()
	{
		createSocket();
		if (connect(connectionSocket, (sockaddr*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR)
		{
			throw "Connection error!";
		}
	}

	void sendLogin(const string& login)
	{
		receiveServiceCommand();
		string loginSize = to_string(login.size());
		send(connectionSocket, loginSize.c_str(), loginSize.size(), NULL);
		receiveServiceCommand();
		send(connectionSocket, login.c_str(), login.size(), NULL);
		receiveServiceCommand();
	}

	void sendPassword(const string& password)
	{
		receiveServiceCommand();
		string passwordSize = to_string(password.size());
		send(connectionSocket, passwordSize.c_str(), passwordSize.size(), NULL);
		receiveServiceCommand();
		send(connectionSocket, password.c_str(), password.size(), NULL);
		receiveServiceCommand();
	}

	template<class SerializableType>
	void sendList(const list<SerializableType>& listToSend)
	{
		//Отправка аналогична серверной
		string serializedString = BinaryFormatter::serialize(listToSend);
		string bufStringSize = to_string(serializedString.size());
		receiveServiceCommand();
		send(connectionSocket, bufStringSize.c_str(), bufStringSize.size(), NULL);
		receiveServiceCommand();
		send(connectionSocket, serializedString.c_str(), serializedString.size(), NULL);
		receiveServiceCommand();
	}

	template<typename ReceivingType>
	list<ReceivingType> receiveList()
	{
		//Приём аналогичен приёму сервера
		char sizeBuf[100];
		memset(sizeBuf, '\0', sizeof(sizeBuf));
		sendServiceCommand(ServiceCommands::READY_TO_RECEIVE);
		recv(connectionSocket, sizeBuf, sizeof(sizeBuf), NULL);
		int size = atoi(sizeBuf);
		char* buffer = new char[size];
		sendServiceCommand(ServiceCommands::READY_TO_RECEIVE);
		recv(connectionSocket, buffer, size, NULL);
		sendServiceCommand(ServiceCommands::READY_TO_RECEIVE);
		string serilizedString(buffer, size);
		delete[] buffer;
		return BinaryFormatter::deserialize<ReceivingType>(serilizedString);
	}

	void sendCommand(CommandToServer command)
	{
		string str = to_string((int)command);
		send(connectionSocket, str.c_str(), str.size(), NULL);
		receiveServiceCommand();
	}

	AnswerFromServer receiveAnswer()
	{
		char serverAnswerBuf[3];
		memset(serverAnswerBuf, '\0', sizeof(serverAnswerBuf));
		recv(connectionSocket, serverAnswerBuf, sizeof(serverAnswerBuf), NULL);
		sendServiceCommand(ServiceCommands::READY_TO_RECEIVE);
		return (AnswerFromServer)atoi(serverAnswerBuf);
	}

	TypeOfUser receiveTypeOfUser()
	{
		char commandBuf[3];
		memset(commandBuf, '\0', sizeof(commandBuf));
		recv(connectionSocket, commandBuf, sizeof(commandBuf), NULL);
		return (TypeOfUser)atoi(commandBuf);
	}

	void sendTypeOfUser(TypeOfUser type)
	{
		//Конвертация команды в строку
		string commandBuf = to_string((int)type);
		//Отправка
		send(connectionSocket, commandBuf.c_str(), commandBuf.size(), NULL);
	}

	void closeConnection()
	{
		sendCommand(CommandToServer::CLOSE_CONNECTION);
		closesocket(connectionSocket);
		WSACleanup();
	}

};