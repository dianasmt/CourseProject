#include "ClientConnectionModule.h"

ClientConnectionModule::ClientConnectionModule()
    : protocol("127.0.0.1", 1111)
{
    protocol.establishConection();
}

ClientConnectionModule::ClientConnectionModule(const string& serverIP, unsigned int serverPort)
    : protocol(serverIP, serverPort)
{
    protocol.establishConection();
}

TypeOfUser ClientConnectionModule::validation(const string& login, const string& password)
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

void ClientConnectionModule::closeConnection()
{
    protocol.closeConnection();
}
