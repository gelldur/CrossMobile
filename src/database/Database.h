//
// Created by pingu on 1/7/16.
//

#pragma once

#include <string>
#include <SQLiteCpp/SQLiteCpp.h>

namespace ESport
{

class Database
{
public:
	Database(const std::string& name);

private:
	SQLite::Database _database;
};

}

