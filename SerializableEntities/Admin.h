#pragma once
#include<string>
using namespace std;
class Admin
{
protected:

	int id;
	string login;
	string password;

public:

	Admin();
	Admin(const string& login, const std::string& password);
	Admin(const Admin& other);
	virtual ~Admin();
	void setId(int id);
	int getId()const;
	void setLogin(const string& login);
	void setPassword(const string& password);
	string getPasword()const;
	string getLogin()const;

	template<class Archive>
	void serialize(Archive& ar, unsigned int version)
	{
		ar& id;
		ar& login;
		ar& password;
	}
};
