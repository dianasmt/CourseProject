#include <pch.h>
#include "Object.h"

Food::Food()
{
	name = "";
	type = "";
	description = "";
	cost = 0;
	mark = 0;
	id = 0;
}

Food::Food(const Food& o)
{
	name = o.name;
	type = o.type;
	cost = o.cost;
	description = o.description;
	mark = o.mark;
	id = o.id;
}

Food::Food(string _name, string _type, string _description, double _cost, double _mark)
{
	name = _name;
	type = _type;
	mark = _mark;
	description = _description;
	cost = _cost;
}

void Food::SetName(const string& _name)
{
	name = _name;
}

string Food::GetName()const
{
	return name;
}

void Food::SetType(const string& _type)
{
	type = _type;
}

string Food::GetType()const
{
	return type;
}

void Food::SetMark(const double& _mark)
{
	mark = _mark;
}

const double& Food::GetMark() const
{
	return mark;
}

void Food::SetCost(const double& _cost)
{
	cost = _cost;
}

const double& Food::GetCost() const
{
	return cost;
}


void Food::SetDescription(const string& _description)
{
	description = _description;
}

string Food::GetDescription() const
{
	return description;
}

bool Food::operator==(const Food& o)
{
	return name == o.name && type == o.type;
}
