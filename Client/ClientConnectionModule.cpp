#pragma once
#include "pch.h"
#include "ClientConnectionModule.h"


ClientConnectionModule::ClientConnectionModule()
    : protocol("127.0.0.1", 15000)
{
    protocol.establishConection();
}

ClientConnectionModule::ClientConnectionModule(const string& serverIP, unsigned int serverPort)
    : protocol(serverIP, serverPort)
{
    protocol.establishConection();
}

TypeOfUser ClientConnectionModule::authorization(const string& login, const string& password)
{
    protocol.sendCommand(CommandToServer::AUTHORIZATION);
    protocol.sendLogin(login);
    protocol.sendPassword(password);
    return protocol.receiveTypeOfUser();
}

AnswerFromServer ClientConnectionModule::registration(TypeOfUser type, const string& login, const string& password)
{
    protocol.sendCommand(CommandToServer::REGISTRATION);
    protocol.sendTypeOfUser(type);
    protocol.sendLogin(login);
    protocol.sendPassword(password);
    return protocol.receiveAnswer();

}

AnswerFromServer ClientConnectionModule::rate(CommandToServer command, double rate)
{
    protocol.sendCommand(command);
    protocol.sendString(to_string(rate));
    return protocol.receiveAnswer();
}

Client ClientConnectionModule::findClientByLogin(string login)
{
    protocol.sendCommand(CommandToServer::FIND_CLIENT_BY_LOGIN);
    protocol.sendLogin(login);
    return protocol.receiveObject<Client>();
}

Expert ClientConnectionModule::findExpertByLogin(string login)
{
    protocol.sendCommand(CommandToServer::FIND_EXPERT_BY_LOGIN);
    protocol.sendLogin(login);
    return protocol.receiveObject<Expert>();
}

Admin ClientConnectionModule::findAdminByLogin(string login)
{
    protocol.sendCommand(CommandToServer::FIND_ADMIN_BY_LOGIN);
    protocol.sendLogin(login);
    return protocol.receiveObject<Admin>();
}

AnswerFromServer ClientConnectionModule::registerNewAdmin(string login, string password)
{
    protocol.sendCommand(CommandToServer::REGISTER_NEW_USER);
    protocol.sendTypeOfUser(TypeOfUser::ADMIN);
    protocol.sendLogin(login);
    protocol.sendPassword(password);
    return protocol.receiveAnswer();
}

AnswerFromServer ClientConnectionModule::registerNewClient(string login, string password)
{
    protocol.sendCommand(CommandToServer::REGISTER_NEW_USER);
    protocol.sendTypeOfUser(TypeOfUser::CLIENT);
    protocol.sendLogin(login);
    protocol.sendPassword(password);
    return protocol.receiveAnswer();
}

AnswerFromServer ClientConnectionModule::registerNewExpert(string login, string password, double expertRate)
{
    protocol.sendCommand(CommandToServer::REGISTER_NEW_USER);
    protocol.sendTypeOfUser(TypeOfUser::EXPERT);
    protocol.sendLogin(login);
    protocol.sendPassword(password);
    protocol.sendString(to_string(expertRate));
    return protocol.receiveAnswer();
}

AnswerFromServer ClientConnectionModule::deleteClientWith(string login)
{
    protocol.sendCommand(CommandToServer::DELETE_CLIENT);
    protocol.sendLogin(login);
    return protocol.receiveAnswer();
}

AnswerFromServer ClientConnectionModule::deleteExpertWith(string login)
{
    protocol.sendCommand(CommandToServer::DELETE_EXPERT);
    protocol.sendLogin(login);
    return protocol.receiveAnswer();
}

void ClientConnectionModule::closeConnection()
{
    protocol.sendCommand(CommandToServer::DISCONNECT);
    protocol.closeConnection();
}

AnswerFromServer ClientConnectionModule::editOneObj(Food& dish)
{
    protocol.sendCommand(CommandToServer::EDIT_OBJECT);
    protocol.sendObj(dish);
    return protocol.receiveAnswer();
}

AnswerFromServer ClientConnectionModule::addOneObj(Food& dish)
{
    protocol.sendCommand(CommandToServer::ADD_OBJECT);
    protocol.sendObj(dish);
    return protocol.receiveAnswer();
}

AnswerFromServer ClientConnectionModule::delOneObj(Food& dish)
{
    protocol.sendCommand(CommandToServer::DEL_OBJECT);
    protocol.sendObj(dish);
    return protocol.receiveAnswer();
}

std::list<Food> ClientConnectionModule::getAllObj()
{
    protocol.sendCommand(CommandToServer::GET_ALL_OBJECT);
    return protocol.receiveList<Food>();
}

std::list<Admin> ClientConnectionModule::getAllAdmin()
{
    protocol.sendCommand(CommandToServer::GET_ALL_ADMIN);
    return protocol.receiveList<Admin>();
}

std::list<Client> ClientConnectionModule::getAllClient()
{
    protocol.sendCommand(CommandToServer::GET_ALL_CLIENT);
    return protocol.receiveList<Client>();
}

std::list<Expert> ClientConnectionModule::getAllExpert()
{
    protocol.sendCommand(CommandToServer::GET_ALL_EXPERT);
    return protocol.receiveList<Expert>();
}


#include "pch.h"