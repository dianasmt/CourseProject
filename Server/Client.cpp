#include "Client.h"

Client::Client() 
	: User()
{
}

Client::Client(std::string& login, std::string& password)
	: User(login, password)
{
}

Client::Client(const Client& other)
	: User(other)
{
}

Client::~Client()
{
}

void Client::setLogin(const std::string& login)
{
}

void Client::setPassword(const std::string& login)
{
}
