#pragma once
#include<string>
#include"UserStatus.h"
//Базовый класс для всех учётных записей
class User
{
protected:

	int id;
	std::string login;
	std::string password;

public:

	User();
	User(const std::string& login, const std::string& password);
	User(const User& other);
	virtual ~User();
	virtual void setId(unsigned int id);
	virtual unsigned int getId()const;
	virtual void setLogin(const std::string& login) { this->login = login; };
	virtual void setPassword(const std::string& password) { this->password = password; };
	virtual std::string getPasword()const;
	virtual std::string getLogin()const;

	template<class Archive>
	void serialize(Archive& ar, unsigned int version)
	{
		ar& id;
		ar& login;
		ar& password;
	}
};

