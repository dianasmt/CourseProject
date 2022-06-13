#pragma once
#include"ClientProtocol.h"
class ClientConnectionModule
{
protected:

	ClientProtocol protocol;

public:

	ClientConnectionModule();

	ClientConnectionModule(const string& serverIP, unsigned int serverPort);

	TypeOfUser validation(const string& login, const string& password);

	AnswerFromServer registration(TypeOfUser type, const string& login, const string& password);

	void closeConnection();

};

