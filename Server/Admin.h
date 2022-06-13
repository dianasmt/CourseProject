#pragma once
#include "User.h"
class Admin :
    public User
{
    // Унаследовано через User
    virtual void setLogin(const std::string& login) override;
    virtual void setPassword(const std::string& login) override;
};

