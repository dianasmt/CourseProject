#define _CRT_SECURE_NO_WARNINGS
#include "Server.h"
#include "../SerializableEntities/Object.h"
#include <ctime>

std::ostream& dt(std::ostream& o)
{
	time_t now = std::time(0);
	tm* t = localtime(&now);
	o << "[" << t->tm_mday << "." << t->tm_mon << "." << t->tm_year + 1900 << " " << t->tm_hour << ":" << t->tm_min << ":" << t->tm_sec << "]";
	return o;
}

void Server::userHandler(ClientInfo* client)
{
	while (true)
	{
		client->setTypeOfUser(TypeOfUser::UNDEFINED);
		client->setClientId(0);
		client->setClientId(validation(client));
		if (client->getClientId() <= 0) { closesocket(client->getConnectionSocket()); return; }
		switch (client->getType())
		{
		case TypeOfUser::ADMIN:
		{adminHandler(client); break; }
		case TypeOfUser::CLIENT:
		{clientHandler(client); break; }
		case TypeOfUser::EXPERT:
		{expertHandler(client); break; }
		case TypeOfUser::UNDEFINED:
			return;
		default:
			break;
		}
	}
}

unsigned int Server::validation(ClientInfo* client)
{
	while (true)
	{
		switch (protocol.receiveCommand(client->getConnectionSocket()))
		{
		case CommandToServer::AUTHORIZATION:
		{
			cout << dt << " AUTHORIZATION\n";
			int id = authorization(client);
			protocol.sendTypeOfUser(client->getType(), client->getConnectionSocket());
			if (id <= 0)continue;
			else return id;
		}
		case CommandToServer::REGISTRATION:
		{

			int id = registration(client);
			if (id > 0)
			{
				protocol.sendAnswer(AnswerFromServer::SUCCESSFULLY, client->getConnectionSocket());
				cout << dt << " REGISTRATION SUCCESSFULLY\n";
				return id;
			}
			else
			{
				protocol.sendAnswer(AnswerFromServer::_ERROR, client->getConnectionSocket());
				cout << dt << " REGISTRATION ERROR\n";
				continue;
			}
		}
		case CommandToServer::RETURN_TO_PREV_ROOM:
		{
			return 0;
		}
		default:
		{
			protocol.sendAnswer(AnswerFromServer::UNKNOWN_COMMAND, client->getConnectionSocket());
			cout << dt << " UNKNOWN COMMAND\n";
			return 0;
		}
		}
	}
}

unsigned int Server::registration(ClientInfo* client)
{
	TypeOfUser type = protocol.receiveTypeOfUser(client->getConnectionSocket());
	string login = protocol.receiveLogin(client->getConnectionSocket());
	string password = protocol.receivePassword(client->getConnectionSocket());
	double rateWeight = 0;
	if (type == TypeOfUser::EXPERT)
	{
		rateWeight = atof(protocol.receiveString(client->getConnectionSocket()).c_str());
	}
	switch (type)
	{
	case TypeOfUser::ADMIN:
	{
		cout << dt << " REGISTRATION NEW ADMIN\n";
		auto id = DatabaseContext::createNewUser(TypeOfUser::ADMIN, login, password);
		if (id > 0) { client->setTypeOfUser(TypeOfUser::ADMIN); }
		return id;
	}
	case TypeOfUser::CLIENT:
	{
		cout << dt << " REGISTRATION NEW CLIENT\n";
		auto id = DatabaseContext::createNewUser(TypeOfUser::CLIENT, login, password);
		if (id > 0) { client->setTypeOfUser(TypeOfUser::CLIENT); }
		return id;
	}
	case TypeOfUser::EXPERT:
	{
		cout << dt << " REGISTRATION NEW EXPERT\n";
		auto id = DatabaseContext::createNewUser(TypeOfUser::EXPERT, login, password);
		if (id > 0) { client->setTypeOfUser(TypeOfUser::EXPERT); }
		return id;
	}
	case TypeOfUser::UNDEFINED:
		return 0;
	default:
		return 0;
	}
}

unsigned int Server::authorization(ClientInfo* user)
{
	string login = protocol.receiveLogin(user->getConnectionSocket());
	string password = protocol.receivePassword(user->getConnectionSocket());
	auto admins = DatabaseContext::findAdminsWhere([&](const Admin& admin) {return admin.getLogin() == login && admin.getPasword() == password; });
	if (admins.size() == 1) { user->setTypeOfUser(TypeOfUser::ADMIN); return  admins.front().getId(); }
	auto clients = DatabaseContext::findClientsWhere([&](const Client& client) {return client.getLogin() == login && client.getPasword() == password; });
	if (clients.size() == 1) { user->setTypeOfUser(TypeOfUser::CLIENT); return clients.front().getId(); }
	auto experts = DatabaseContext::findExpertsWhere([&](const Expert& expert) {return expert.getLogin() == login && expert.getPasword() == password; });
	if (experts.size() == 1) { user->setTypeOfUser(TypeOfUser::EXPERT); return experts.front().getId(); }
	user->setTypeOfUser(TypeOfUser::UNDEFINED);
	return 0;
}

void Server::adminHandler(ClientInfo* client)
{
	while (true)
	{
		switch (protocol.receiveCommand(client->getConnectionSocket()))
		{
		case CommandToServer::REGISTER_NEW_USER:
		{
			cout << dt << " REGISTRATION NEW USER\n";
			auto userType = protocol.receiveTypeOfUser(client->getConnectionSocket());
			auto login = protocol.receiveLogin(client->getConnectionSocket());
			auto password = protocol.receivePassword(client->getConnectionSocket());
			double expertWeight = 0;
			if (userType == TypeOfUser::EXPERT)
			{
				expertWeight = atof(protocol.receiveString(client->getConnectionSocket()).c_str());
			}
			auto id = DatabaseContext::createNewUser(userType, login, password);
			if (id > 0) protocol.sendAnswer(AnswerFromServer::SUCCESSFULLY, client->getConnectionSocket());
			else { protocol.sendAnswer(AnswerFromServer::_ERROR, client->getConnectionSocket()); }
			break;
		}
		case CommandToServer::DELETE_CLIENT:
		{
			cout << dt << " DELETE CLIENT\n";
			auto login = protocol.receiveLogin(client->getConnectionSocket());
			if (DatabaseContext::deleteClientsWhere([&](Client client) {return client.getLogin() == login; }))
				protocol.sendAnswer(AnswerFromServer::SUCCESSFULLY, client->getConnectionSocket());
			else
				protocol.sendAnswer(AnswerFromServer::_ERROR, client->getConnectionSocket());
			break;
		}
		case CommandToServer::DELETE_EXPERT:
		{
			cout << dt << " DELETE EXPERT\n";
			auto login = protocol.receiveLogin(client->getConnectionSocket());
			if (DatabaseContext::deleteExpertsWhere([&](Expert expert) {return expert.getLogin() == login; }))
				protocol.sendAnswer(AnswerFromServer::SUCCESSFULLY, client->getConnectionSocket());
			else
				protocol.sendAnswer(AnswerFromServer::_ERROR, client->getConnectionSocket());
			break;
		}
		case CommandToServer::FIND_CLIENT_BY_LOGIN:
		{
			cout << dt << " FIND CLIENT BY LOGIN\n";
			auto login = protocol.receiveLogin(client->getConnectionSocket());
			protocol.sendList(DatabaseContext::findClientsWhere([&](Client client) {return client.getLogin() == login; }), client->getConnectionSocket());
			break;
		}
		case CommandToServer::FIND_EXPERT_BY_LOGIN:
		{
			cout << dt << " FIND EXPERT BY LOGIN\n";
			auto login = protocol.receiveLogin(client->getConnectionSocket());
			protocol.sendList(DatabaseContext::findExpertsWhere([&](Expert expert) {return expert.getLogin() == login; }), client->getConnectionSocket());
			break;
		}
		case CommandToServer::FIND_ADMIN_BY_LOGIN:
		{
			cout << dt << " FIND ADMIN BY LOGIN\n";
			auto login = protocol.receiveLogin(client->getConnectionSocket());
			protocol.sendList(DatabaseContext::findAdminsWhere([&](Admin admin) {return admin.getLogin() == login; }), client->getConnectionSocket());
			break;
		}
		case CommandToServer::GET_ALL_CLIENT:
		{
			cout << dt << " GET ALL CLIENT\n";
			protocol.sendList(DatabaseContext::findClientsWhere([&](Client client) {return true; }), client->getConnectionSocket());
			break;
		}
		case CommandToServer::GET_ALL_EXPERT:
		{
			cout << dt << " GET ALL EXPERT\n";
			protocol.sendList(DatabaseContext::findExpertsWhere([&](Expert client) {return true; }), client->getConnectionSocket());
			break;
		}
		case CommandToServer::GET_ALL_ADMIN:
		{
			cout << dt << " GET ALL ADMIN\n";
			protocol.sendList(DatabaseContext::findAdminsWhere([&](Admin client) {return true; }), client->getConnectionSocket());
			break;
		}
		case CommandToServer::GET_ALL_OBJECT:
		{
			cout << dt << " GET ALL OBJECTS\n";
			protocol.sendList(DatabaseContext::findObjWhere([&](Food obj) {return true; }), client->getConnectionSocket());
			break;
		}
		case CommandToServer::ADD_OBJECT:
		{
			cout << dt << " ADD OBJECT\n";
			auto obj = protocol.receiveObject<Food>(client->getConnectionSocket());
			double expertWeight = 0;
			auto id = DatabaseContext::addOneObj(obj.GetName(), obj.GetType(), obj.GetDescription(), obj.GetCost(), obj.GetMark());
			if (id > 0) protocol.sendAnswer(AnswerFromServer::SUCCESSFULLY, client->getConnectionSocket());
			else { protocol.sendAnswer(AnswerFromServer::_ERROR, client->getConnectionSocket()); }
			break;
		}
		case CommandToServer::DEL_OBJECT:
		{
			cout << dt << " DEL OBJECT\n";
			auto obj = protocol.receiveObject<Food>(client->getConnectionSocket());
			if (DatabaseContext::deleteObjWhere([&](Food o) {return o.GetId() == obj.GetId(); }))
				protocol.sendAnswer(AnswerFromServer::SUCCESSFULLY, client->getConnectionSocket());
			else
				protocol.sendAnswer(AnswerFromServer::_ERROR, client->getConnectionSocket());
			break;
		}
		case CommandToServer::EDIT_OBJECT:
		{
			cout << dt << " EDIT OBJECT\n";
			auto o = protocol.receiveObject<Food>(client->getConnectionSocket());
			if (DatabaseContext::editOneObj(o))
				protocol.sendAnswer(AnswerFromServer::SUCCESSFULLY, client->getConnectionSocket());
			else
				protocol.sendAnswer(AnswerFromServer::_ERROR, client->getConnectionSocket());
			break;
		}
		case CommandToServer::RETURN_TO_PREV_ROOM:
		{
			return;
		}
		default:
		{
			cout << dt << " UNKNOWN COMAND\n";
			protocol.sendAnswer(AnswerFromServer::UNKNOWN_COMMAND, client->getConnectionSocket());
			break;
		}
		}
	}
}

void Server::clientHandler(ClientInfo* client)
{
	while (true)
	{
		switch (protocol.receiveCommand(client->getConnectionSocket()))
		{
		case CommandToServer::RETURN_TO_PREV_ROOM:
		{
			return;
		}
		case CommandToServer::GET_ALL_OBJECT:
		{
			cout << dt << " GET ALL OBJECT\n";
			protocol.sendList(DatabaseContext::findObjWhere([&](Food obj) {return true; }), client->getConnectionSocket());
			break;
		}
		default:
		{
			protocol.sendAnswer(AnswerFromServer::UNKNOWN_COMMAND, client->getConnectionSocket());
			break;
		}
		}
	}
}

void Server::expertHandler(ClientInfo* client)
{
	while (true)
	{
		switch (protocol.receiveCommand(client->getConnectionSocket()))
		{
		case CommandToServer::RETURN_TO_PREV_ROOM:
		{
			return;
		}
		case CommandToServer::GET_ALL_OBJECT:
		{
			cout << dt << " GET ALL OBJECT\n";
			protocol.sendList(DatabaseContext::findObjWhere([&](Food obj) {return true; }), client->getConnectionSocket());
			break;
		}
		case CommandToServer::EDIT_OBJECT:
		{
			cout << dt << " EDIT OBJECT\n";
			auto obj = protocol.receiveObject<Food>(client->getConnectionSocket());
			if (DatabaseContext::editOneObj(obj))
				protocol.sendAnswer(AnswerFromServer::SUCCESSFULLY, client->getConnectionSocket());
			else
				protocol.sendAnswer(AnswerFromServer::_ERROR, client->getConnectionSocket());
			break;
		}
		default:
		{
			protocol.sendAnswer(AnswerFromServer::UNKNOWN_COMMAND, client->getConnectionSocket());
			break;
		}
		}
	}
}

Server::Server()
	: protocol(15000)
{
	DatabaseContext::runDatabase();
}

Server::Server(unsigned int port)
	: protocol(port)
{
	DatabaseContext::runDatabase();
}

Server::~Server()
{
	for (auto& i : clientsInfo)
	{
		auto obj = (ClientInfoEx*)(i);

		obj->clientThread->join();
		delete obj->clientThread;
	}
}

void Server::openConnection()
{
	for (size_t i = 0; i < maxAmountOfConnections; i++)
	{
		string newClientIp;
		//Копирование сокета нового клиета 
		SOCKET newClientSocket = protocol.acceptConnectionRequests(newClientIp);
		//Вывод IP нового клиета
		std::cout << dt << " Client connected with IP: " << newClientIp << std::endl;
		//Создание объекта клиента
		ClientInfoEx newClient(newClientSocket, newClientIp);
		thread* newClientThread = new thread([&]()
			{
				userHandler(&newClient);
				cout << dt << " Client disconnected" << endl;
			});
		newClient.clientThread = newClientThread;
		newClientThread->detach();
		clientsInfo.push_back(&newClient);
	}

}
