//
// Created by Dawid Drozd aka Gelldur on 7/19/16.
//

#include "Preferences.h"

#include<cstdio>

#include <Poco/Data/Session.h>
#include <Poco/Data/SQLite/Connector.h>

#include <log.h>
#include <utils/Utils.h>

Preferences::Preferences(const std::string& databaseName, const std::string& tableName)
		: TABLE_NAME(tableName)
		, DATABSE_FILE_NAME(databaseName)
{
	Poco::Data::SQLite::Connector::registerConnector();

	recreate();
}

Preferences::~Preferences()
{
	_session->close();
	Poco::Data::SQLite::Connector::unregisterConnector();
}

void Preferences::setValue(const std::string& key, const std::string& value)
{
	_cache[key] = value;

	if (_session == nullptr)
	{
		ELOG("Session not created\nNo storage");
		return;
	}

	Poco::Data::Session& session = *_session;

	Poco::Data::Statement insert(session);
	insert << "INSERT OR REPLACE INTO " << TABLE_NAME << " VALUES(?, ?)",
			Poco::Data::Keywords::useRef(key),
			Poco::Data::Keywords::useRef(value);
	DLOG("Preferences: %s\n(%s)=(%s)", insert.toString().c_str(), key.c_str(), value.c_str());

	insert.execute();
}

std::string Preferences::getValue(const std::string& key, const std::string& defaultValue)
{
	auto found = _cache.find(key);
	if (found != _cache.end())
	{
		return found->second;
	}

	if (_session == nullptr)
	{
		ELOG("Session not created\nNo storage");
		_cache[key] = defaultValue;
		return defaultValue;
	}

	std::string returnedValue = defaultValue;

	Poco::Data::Session& session = *_session;


	// a simple query
	Poco::Data::Statement select(session);
	select << "SELECT value FROM " << TABLE_NAME << " WHERE key=?",
			Poco::Data::Keywords::useRef(key),
			Poco::Data::Keywords::into(returnedValue); //  iterate over result set one row at a time

	DLOG("Select: %s\nkey:%s", select.toString().c_str(), key.c_str());
	select.execute();

	_cache[key] = returnedValue;
	return returnedValue;
}

void Preferences::clean()
{
	_cache.clear();
	if (_session == nullptr)
	{
		ELOG("Session not created\nNo storage");
		return;
	}

	_session->close();

	if (std::remove(DATABSE_FILE_NAME.c_str()) != 0)
	{
		ELOG("Can't remove database: %s", DATABSE_FILE_NAME.c_str());
	}
	recreate();
}

void Preferences::recreate()
{
	_session = std::make_unique<Poco::Data::Session>("SQLite", DATABSE_FILE_NAME.c_str());

	if (_session == nullptr)
	{
		ELOG("Session not created\nNo storage");
		return;
	}

	Poco::Data::Session& session = *_session;

	session << "CREATE TABLE IF NOT EXISTS `" << TABLE_NAME << "`("
			"`key` TEXT NOT NULL UNIQUE,"
			"`value` TEXT,"
			"PRIMARY KEY(key)"
			");", Poco::Data::Keywords::now;
}
