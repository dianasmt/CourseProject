#include <pch.h>
#include "Admin.h"

Admin::Admin()
{
	id = 0;
	login = "empty";
	password = "empty";
}

Admin::Admin(const std::string& login, const std::string& password) : Admin()
{
	setLogin(login);
	setPassword(password);
}

Admin::Admin(const Admin& other)
{
	id = other.id;
	login = other.login;
	password = other.password;
}

Admin::~Admin()
{
}

string Admin::getPasword() const
{
	return password;
}

string Admin::getLogin() const
{
	return login;
}

void Admin::setId(int id)
{
	if (id > 0)
	{
		this->id = id;
	}
}

int Admin::getId() const
{
	return id;
}

void Admin::setLogin(const string& login)
{
	if (!login.empty())
	{
		this->login = login;
	}
}

void Admin::setPassword(const string& password)
{
	if (!password.empty())
	{
		this->password = password;
	}
}
