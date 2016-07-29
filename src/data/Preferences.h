//
// Created by Dawid Drozd aka Gelldur on 7/19/16.
//

#pragma once

#include <fstream>
#include <map>
#include <memory>
#include <string>

#include <Poco/Data/Session.h>

class Preferences
{
public:
	Preferences(const std::string& databaseFileName, const std::string& tableName = "KeyValue");
	~Preferences();

	void setValue(const std::string& key, const std::string& value);

	std::string getValue(const std::string& key, const std::string& defaultValue);

	void clean();

private:
	const std::string TABLE_NAME;
	const std::string DATABSE_FILE_NAME;

	std::map<std::string, std::string> _cache;
	std::unique_ptr<Poco::Data::Session> _session;

	void recreate();
};


