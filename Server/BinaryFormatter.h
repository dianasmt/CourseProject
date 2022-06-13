#pragma once
#include<list>
#include<string>
#include"boost/archive/binary_iarchive.hpp"
#include"boost/archive/binary_oarchive.hpp"
#include"boost/iostreams/device/back_inserter.hpp"
#include"boost/iostreams/stream.hpp"
#include"boost/serialization/list.hpp"

using namespace std;

//Сериализация с помощью библиотеки boost

class BinaryFormatter
{
public:

	template<class SerializableType>
	static string serialize(const list<SerializableType>& listOfObjects);

	template<class SerializableType>
	static list<SerializableType> deserialize(const string& serialString);

};

template<class SerializableType>
inline string BinaryFormatter::serialize(const list<SerializableType>& listOfObjects)
{
	string serial_str;
	boost::iostreams::back_insert_device<string> inserter(serial_str);
	boost::iostreams::stream<boost::iostreams::back_insert_device<string>> s(inserter);
	boost::archive::binary_oarchive oa(s);
	oa << listOfObjects;
	s.flush();
	return serial_str;
}

template<class SerializableType>
inline list<SerializableType> BinaryFormatter::deserialize(const string& serialString)
{
	boost::iostreams::basic_array_source<char> device(serialString.data(), serialString.size());
	boost::iostreams::stream<boost::iostreams::basic_array_source<char>> streamArrayWrapper(device);
	boost::archive::binary_iarchive inputArchive(streamArrayWrapper);
	list<SerializableType> list;
	inputArchive >> list;
	return list;
}
