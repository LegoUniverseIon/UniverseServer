#pragma once

#include <string>
#include <unordered_map>

#include <my_global.h> // If you have included MySQL in Project Settings
#include <mysql.h> // If you have included MySQL in Project Settings

// This is a MySQL Exception subclasses from std::exception
class MySqlException : public std::exception {
	public:
	MySqlException() : std::exception("mysql error") {}
	MySqlException(const std::string& msg) : std::exception(msg.c_str()) {}
};

enum MYSQL_STATUS : unsigned int{
	SUCESS = 0,
	NOT_ENOUGH_MEMORY = 1,
};

template <typename T>
struct compare{
	T left; //Current state
	T right; //System state
};

// This is the declaration for methods that will be used to connect to
// MySQL database
class Database {
	private:
		static MYSQL * _con; // This is the MySQL Connection

		static std::string host;
		static std::string database;
		static std::string username;
		static std::string password;
		Database() {} // Private Database initializer
	public:
		// Initialize connection.
		// This takes the host, the database, the DB username, and the DB password as strings and connects the server to
		// the MySQL database
		static void Init(const std::string& host, const std::string& database, const std::string& username, const std::string& password);
		static unsigned int Connect();
		static void Close();
		// Query the MySQL database and return results
		static MYSQL_RES * Query(const std::string & query); 
		static MYSQL * getConnection();
};