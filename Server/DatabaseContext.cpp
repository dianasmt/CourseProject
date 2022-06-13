#include "DatabaseContext.h"

Database DatabaseContext::database = make_storage(
    "CourseworkDatabase.sqlite",
    make_table("Admin_set",
        make_column("Id", &Admin::getId, &Admin::setId, autoincrement(), primary_key()),
        make_column("Login", &Admin::getLogin, &Admin::setLogin, default_value("empty")),
        make_column("Password", &Admin::getPasword, &Admin::setPassword)),
    make_table("Client_set",
        make_column("Id", &Client::getId, &Client::setId, autoincrement(), primary_key()),
        make_column("Login", &Client::getLogin, &Client::setLogin, default_value("empty")),
        make_column("Password", &Client::getPasword, &Client::setPassword)),
    make_table("Expert_set",
        make_column("Id", &Expert::getId, &Expert::setId, autoincrement(), primary_key()),
        make_column("Login", &Expert::getLogin, &Expert::setLogin, default_value("empty")),
        make_column("Password", &Expert::getPasword, &Expert::setPassword)),
    make_table("Object_set",
        make_column("Id", &Food::GetId, &Food::SetId, autoincrement(), primary_key()),
        make_column("Name", &Food::GetName, &Food::SetName, default_value("empty")),
        make_column("Type", &Food::GetType, &Food::SetType),
        make_column("First", &Food::GetCost, &Food::SetCost),
        make_column("Description", &Food::GetDescription, &Food::SetDescription),
        make_column("Mark", &Food::GetMark, &Food::SetMark)));

void DatabaseContext::runDatabase()
{
    //string str = typeid(database).name();
    database.sync_schema();
}

list<Client> DatabaseContext::findClientsWhere(function<bool(const Client&)> comparer)
{
    list<Client> sample;
    for (const auto& i : database.iterate<Client>())
    {
        if (comparer(i))
        {
            sample.push_back(i);
        }
    }
    return sample;
}

list<Admin> DatabaseContext::findAdminsWhere(function<bool(const Admin&)> comparer)
{
    list<Admin> sample;
    for (const auto& i : database.iterate<Admin>())
    {
        if (comparer(i))
        {
            sample.push_back(i);
        }
    }
    return sample;
}

list<Expert> DatabaseContext::findExpertsWhere(function<bool(const Expert&)> comparer)
{
    list<Expert> sample;
    for (const auto& i : database.iterate<Expert>())
    {
        if (comparer(i))
        {
            sample.push_back(i);
        }
    }
    return sample;
}

int DatabaseContext::createNewUser(TypeOfUser type, const string& login, const string& password)
{
    switch (type)
    {
    case TypeOfUser::ADMIN:
        return database.insert<Admin>(Admin(login, password));
    case TypeOfUser::CLIENT:
        return database.insert<Client>(Client(login, password));
    case TypeOfUser::EXPERT:
        return database.insert<Expert>(Expert(login, password));
    default:
        return 0;
    }
}

bool DatabaseContext::modifyAdmin(const Admin& newVersion)
{
    database.update<Admin>(newVersion);
    return true;
}

bool DatabaseContext::modifyClient(const Client& newVersion)
{
    database.update<Client>(newVersion);
    return true;
}

bool DatabaseContext::modifyExpert(const Expert& newVersion)
{
    database.update<Expert>(newVersion);
    return true;
}

bool DatabaseContext::deleteClientsWhere(function<bool(const Client&)> comparer)
{
    for (const auto& i : database.iterate<Client>())
    {
        if (comparer(i))
        {
            database.remove<Client>(i.getId());
        }
    }
    return true;
}

bool DatabaseContext::deleteAdminsWhere(function<bool(const Admin&)> comparer)
{
    for (const auto& i : database.iterate<Admin>())
    {
        if (comparer(i))
        {
            database.remove<Admin>(i.getId());
        }
    }
    return true;
}

bool DatabaseContext::deleteExpertsWhere(function<bool(const Expert&)> comparer)
{
    for (const auto& i : database.iterate<Expert>())
    {
        if (comparer(i))
        {
            database.remove<Expert>(i.getId());
        }
    }
    return true;
}

bool DatabaseContext::editOneObj(const Food& obj)
{
    database.update<Food>(obj);
    return true;
}

bool DatabaseContext::addOneObj(std::string name, std::string type, std::string description, double first, double mark)
{
    return database.insert<Food>(Food(name, type, description, first, mark));
}

bool DatabaseContext::deleteObjWhere(function<bool(const Food&)> comparer)
{
    for (const auto& i : database.iterate<Food>())
    {
        if (comparer(i))
        {
            database.remove<Food>(i.GetId());
        }
    }
    return true;
}

list<Food> DatabaseContext::findObjWhere(function<bool(const Food&)> comparer)
{
    list<Food> sample;
    for (const auto& i : database.iterate<Food>())
    {
        if (comparer(i))
        {
            sample.push_back(i);
        }
    }
    return sample;
}
