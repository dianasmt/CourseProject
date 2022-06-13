#pragma once
#include <pch.h>
#include <iostream>

using namespace std;

class Food
{
	string name;
	string type;
	string description;
	double cost;
	double mark;
	int id;

public:
	Food();
	Food(const Food& o);
	Food(string _name, string _type, string _description, double _cost, double _mark);

	void SetName(const string& _name);
	string GetName() const;

	void SetType(const string& _type);
	string GetType() const;

	void SetMark(const double& _mark);
	const double& GetMark() const;

	void SetCost(const double& _cost);
	const double& GetCost() const;

	void SetDescription(const string& _description);
	string GetDescription() const;

	void SetId(const int i) { id = i; }
	int GetId()const { return id; }

	bool operator==(const Food& o);

	template<class Archive>
	void serialize(Archive& ar, unsigned int version)
	{
		ar& name;
		ar& type;
		ar& description;
		ar& cost;
		ar& mark;
		ar& id;
	}
};

