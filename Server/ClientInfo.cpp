#include "ClientInfo.h"

ClientInfo::ClientInfo()
{
	connectionSocket = 0;
	type = TypeOfUser::UNDEFINED;
}

ClientInfoEx::ClientInfoEx()
{
	connectionSocket = 0;
	lastIp = "";
	clientId = 0;
	type = TypeOfUser::UNDEFINED;
}

ClientInfoEx::ClientInfoEx(SOCKET connectionSocket, const string& lastIp) : ClientInfo()
{
	this->connectionSocket = connectionSocket;
	this->lastIp = lastIp;
}

void ClientInfoEx::setClientId(unsigned int clientId)
{
	if (clientId > 0)
	{
		this->clientId = clientId;
	}
}

unsigned int ClientInfoEx::getClientId() const
{
	return clientId;
}

SOCKET ClientInfo::getConnectionSocket() const
{
	return connectionSocket;
}

string ClientInfoEx::getLastIp() const
{
	return lastIp;
}

TypeOfUser ClientInfo::getType() const
{
	return type;
}

void ClientInfo::setTypeOfUser(TypeOfUser type)
{
	this->type = type;
}

bool ClientInfoEx::operator==(const ClientInfoEx& other) const
{
	return connectionSocket == other.connectionSocket && lastIp == other.lastIp;
}

bool ClientInfoEx::operator!=(const ClientInfoEx& other) const
{
	return !this->operator==(other);
}
