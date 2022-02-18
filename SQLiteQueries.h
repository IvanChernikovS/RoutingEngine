//
// Created by chi3hi on 18.02.22.
//

#pragma once

#include <string>
#include "sqlite3.h"

class SQLiteUserData
{
public:
    explicit SQLiteUserData();
    ~SQLiteUserData() noexcept;

    bool IsUserRegistered(const std::string& userName);

    void StoreNewUser(const std::string& userName, int userId);
    void UpdateUserId(const std::string& userName, int userId);
    void UpdateUserName(const std::string& userName, int userId);

private:
    char *mErrMsg = nullptr;
    std::string mQuery;
    sqlite3 *mSqlConnection = nullptr;

    void OpenSqlite(const std::string& pathToDb);
    void CreateTable();
    void CloseSqlite() const;
    bool SqliteExec();
};
