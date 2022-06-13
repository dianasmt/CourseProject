#pragma once
#include"ClientProtocol.h"
#include"../SerializableEntities/Client.h"
#include"../SerializableEntities/Admin.h"
#include"../SerializableEntities/Expert.h"
#include"../SerializableEntities/Object.h"
class ClientConnectionModule
{
protected:

	ClientProtocol protocol;

public:

	ClientConnectionModule();

	ClientConnectionModule(const string& serverIP, unsigned int serverPort);

	TypeOfUser authorization(const string& login, const string& password);

	AnswerFromServer registration(TypeOfUser type, const string& login, const string& password);

	AnswerFromServer rate(CommandToServer command, double rate);

	Client findClientByLogin(string login);

	Expert findExpertByLogin(string login);

	Admin findAdminByLogin(string login);

	AnswerFromServer registerNewAdmin(string login, string password);

	AnswerFromServer registerNewClient(string login, string password);

	AnswerFromServer registerNewExpert(string login, string password, double rateWeight);

	AnswerFromServer deleteClientWith(string login);

	AnswerFromServer deleteExpertWith(string login);

	AnswerFromServer editOneObj(Food& dish);

	AnswerFromServer addOneObj(Food& dish);

	AnswerFromServer delOneObj(Food& dish);

	std::list<Food> getAllObj();

	std::list<Admin> getAllAdmin();

	std::list<Client> getAllClient();

	std::list<Expert> getAllExpert();

	void closeConnection();

};

