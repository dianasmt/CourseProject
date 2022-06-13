#pragma once

/// <summary>
/// Все команды серверу и ответы от сервера размещать в уже созданные enum class (поддержка до 999 команд)
/// Service Commands не трогать, используются в протоколах работы сервера и клиента
/// </summary>

enum class CommandToServer
{
	AUTHORIZATION,
	REGISTRATION,
	CLOSE_CONNECTION
};

enum class AnswerFromServer
{
	SUCCESSFULLY,
	VALIDATION_ERROR,
	REGISTRATION_ERROR
};

enum class TypeOfUser
{
	UNDEFINED,
	ADMIN,
	CLIENT, 
	EXPERT
};

enum class ServiceCommands
{
	READY_TO_RECEIVE,
};