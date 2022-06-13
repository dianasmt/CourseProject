#include <pch.h>
#include "Expert.h"

Expert::Expert()
{
	id = 0;
	login = "empty";
	password = "empty";
}

Expert::Expert(const string& login, const string& password) : Expert()
{
	setLogin(login);
	setPassword(password);
}

Expert::Expert(const Expert& other)
{
	id = other.id;
	login = other.login;
	password = other.password;
}

Expert::~Expert()
{
}
string Expert::getPasword() const
{
	return password;
}

string Expert::getLogin() const
{
	return login;
}

void Expert::setId(int id)
{
	if (id > 0)
	{
		this->id = id;
	}
}

int Expert::getId() const
{
	return id;
}

void Expert::setLogin(const string& login)
{
	if (!login.empty())
	{
		this->login = login;
	}
}

void Expert::setPassword(const string& password)
{
	if (!password.empty())
	{
		this->password = password;
	}
}
