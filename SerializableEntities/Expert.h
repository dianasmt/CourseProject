#pragma once
#include "User.h"
using namespace std;
class Expert
{
protected:

	int id;
	std::string login;
	std::string password;

public:

	Expert();
	Expert(const string& login, const string& password);
	Expert(const Expert& other);
	virtual ~Expert();
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
