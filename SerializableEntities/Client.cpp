#include <pch.h>
#include "Client.h"

Client::Client()
{
	id = 0;
	login = "empty";
	password = "empty";
}

Client::Client(const string& login, const string& password) : Client()
{
	setLogin(login);
	setPassword(password);
}

Client::Client(const Client& other)
{
	id = other.id;
	login = other.login;
	password = other.password;
}

Client::~Client()
{
}

string Client::getPasword() const
{
	return password;
}

string Client::getLogin() const
{
	return login;
}

void Client::setId(int id)
{
	if (id > 0)
	{
		this->id = id;
	}
}

int Client::getId() const
{
	return id;
}

void Client::setLogin(const string& login)
{
	if (!login.empty())
	{
		this->login = login;
	}
}

void Client::setPassword(const string& password)
{
	if (!password.empty())
	{
		this->password = password;
	}
}
