#pragma once
#include "User.h"
class Client :
    public User
{
protected:



public:

    Client();
    Client(std::string& login, std::string& password);
    Client(const Client& other);
    virtual ~Client();
    // Унаследовано через User
    virtual void setLogin(const std::string& login) override;
    virtual void setPassword(const std::string& login) override;
};

