//
// Created by chi3hi on 18.02.22.
//

#include <iostream>
#include "SQLiteQueries.h"

//TODO
char callbackReturn = -1;
int logQuery(void*, int argc, char **argv, char **azColName)
{
    for(int i = 0; i < argc; i++)
    {
        std::cout << *azColName << " = " << *argv[i] << std::endl;
        callbackReturn = *argv[0];
    }

    return 0;
}

SQLiteUserData::SQLiteUserData()
{
    OpenSqlite("/home/chi3hi/CLionProjects/CommunicationHub/userData.db");
    CreateTable();
}

SQLiteUserData::~SQLiteUserData() noexcept
{
    CloseSqlite();
    delete[] mErrMsg;
}

bool SQLiteUserData::IsUserRegistered(const std::string& userName)
{
    mQuery = "SELECT EXISTS(SELECT * FROM USER_DATA WHERE NAME = '" + userName + "');";

    SqliteExec();
    if(callbackReturn == '0')
    {
        std::cout << "User not found" << std::endl;
        return false;
    }
    else if(callbackReturn == '1')
    {
        std::cout << "User had been found" << std::endl;
        return true;
    }

    std::cout << "User selection from DB went wrong" << std::endl;
    return false;
}

void SQLiteUserData::StoreNewUser(const std::string& userName, int userId)
{
    mQuery = "INSERT INTO USER_DATA (USER_ID,NAME)"  \
            "VALUES (" + std::to_string(userId) + ", '" + userName + "');";

    if(SqliteExec())
        std::cout << "New user had been inserted successfully" << std::endl;
}

void SQLiteUserData::UpdateUserId(const std::string& userName, int userId)
{
    mQuery = "UPDATE USER_DATA SET USER_ID = " + std::to_string(userId) + " WHERE NAME = " + userName + ";";
    if(SqliteExec())
        std::cout << "User ID had been updated successfully" << std::endl;
}

void SQLiteUserData::UpdateUserName(const std::string& userName, int userId)
{
    mQuery = "UPDATE USER_DATA SET NAME = " + userName + " WHERE USER_ID = " + std::to_string(userId) + ";";
    if(SqliteExec())
        std::cout << "User NAME had been updated successfully" << std::endl;
}

void SQLiteUserData::OpenSqlite(const std::string& pathToDb)
{
    if(sqlite3_open(pathToDb.data(), &mSqlConnection) == SQLITE_OK)
        std::cout << "Opened database successfully" << std::endl;
    else
        std::cout << "Can't open database: " << sqlite3_errmsg(mSqlConnection) << std::endl;
}

void SQLiteUserData::CreateTable()
{
    mQuery = "CREATE TABLE IF NOT EXISTS USER_DATA("    \
      "USER_ID KEY  NOT NULL,"                          \
      "NAME    TEXT NOT NULL);";

    if(SqliteExec())
        std::cout << "Table created if not exists successfully" << std::endl;
}

void SQLiteUserData::CloseSqlite() const
{
    if(!mSqlConnection)
    {
        std::cout << "SQLite already closed" << std::endl;
        return;
    }

    if(sqlite3_close(mSqlConnection) == SQLITE_OK)
        std::cout << "SQLite successfully closed" << std::endl;
    else
        std::cout << "Something went wrong while the sqlite was being closed" << std::endl;
}

bool SQLiteUserData::SqliteExec()
{
    if(sqlite3_exec(mSqlConnection, mQuery.data(), logQuery, nullptr, &mErrMsg) != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", mErrMsg);
        return false;
    }
    return true;
}