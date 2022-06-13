#pragma once
#include"../SerializableEntities/Admin.h"
#include"../SerializableEntities/Client.h"
#include"../SerializableEntities/Expert.h"
#include"../SerializableEntities/CommandsBetweenServerAndClient.h"
#include"../SerializableEntities/Object.h"
#include<list>
#include<functional>
#include"sqlite_orm-master/include/sqlite_orm/sqlite_orm.h"
#include "DatabaseTypeDefinition.h"
using namespace std;
using namespace sqlite_orm;
//ћодуль взаимодействи€ с базой данных


class DatabaseContext
{
protected:

	static Database database;

public:

	static void runDatabase();

	static list<Client> findClientsWhere(function<bool(const Client&)> comparer);

	static list<Admin> findAdminsWhere(function<bool(const Admin&)> comparer);

	static list<Expert> findExpertsWhere(function<bool(const Expert&)> comparer);

	static int createNewUser(TypeOfUser type, const string& login, const string& password);

	static bool modifyAdmin(const Admin& newVersion);

	static bool modifyClient(const Client& newVersion);

	static bool modifyExpert(const Expert& newVersion);

	static bool deleteClientsWhere(function<bool(const Client&)> comparer);

	static bool deleteAdminsWhere(function<bool(const Admin&)> comparer);

	static bool deleteExpertsWhere(function<bool(const Expert&)> comparer);

	static bool editOneObj(const Food& obj);

	static bool addOneObj(std::string name, std::string type, std::string description, double first, double mark);

	static bool deleteObjWhere(function<bool(const Food&)> comparer);

	static list<Food> findObjWhere(function<bool(const Food&)> comparer);

};
