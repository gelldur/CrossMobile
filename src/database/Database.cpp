//
// Created by pingu on 1/7/16.
//

#include "Database.h"


namespace ESport
{

Database::Database(const std::string& name)
		: _database(name, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE)
{
	SQLite::Transaction transaction(_database);
	{
		_database.exec("CREATE TABLE IF NOT EXIST Favorites ()");
	}
	transaction.commit();
}

}