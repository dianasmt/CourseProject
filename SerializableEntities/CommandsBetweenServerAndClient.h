#pragma once

/// <summary>
/// ��� ������� ������� � ������ �� ������� ��������� � ��� ��������� enum class (��������� �� 999 ������)
/// Service Commands �� �������, ������������ � ���������� ������ ������� � �������
/// </summary>

enum class CommandToServer
{
	AUTHORIZATION,
	REGISTRATION,
	RETURN_TO_PREV_ROOM,
	//Admin commands
	REGISTER_NEW_USER,
	BAN_CLIENT,
	BAN_EXPERT,
	UNBAN_CLIENT,
	UNBAN_EXPERT,
	DELETE_CLIENT,
	DELETE_EXPERT,
	FIND_CLIENT_BY_LOGIN,
	FIND_EXPERT_BY_LOGIN,
	FIND_ADMIN_BY_LOGIN,
	GET_ALL_ADMIN,
	GET_ALL_EXPERT,
	GET_ALL_CLIENT,
	EDIT_OBJECT,
	DEL_OBJECT,
	ADD_OBJECT,
	GET_ALL_OBJECT,
	DISCONNECT,
	//Expert commands
	RATE,
	//ClientCommands
	//�� ���������
};

enum class AnswerFromServer
{
	SUCCESSFULLY,
	_ERROR,
	UNKNOWN_COMMAND
};

enum class TypeOfUser
{
	UNDEFINED,
	ADMIN,
	CLIENT, 
	EXPERT,
	REGISTRATION
};

enum class ServiceCommands
{
	READY_TO_RECEIVE,
};