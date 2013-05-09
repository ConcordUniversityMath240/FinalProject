/************************************************
sql.cpp - database methods
      - dbConnect()
        connects to database
      - dbCommand(string, string)
        takes in commands for the database if second argument
        is read then it passes values to returned
      - returnRead()
      - convertInt()

Author: iOAN

Purpose: DB and shit :P
*************************************************/


#include <iostream>
#include "sqlite3.h"
#include <string>
#include <sstream>

using namespace std;

class sqlite {
private:
    sqlite3 *database;
    string command;
    const char * db;
    string returned;
public:
    string action;
    sqlite() {
        // database name; it will create it if it does not exist
        db = "rogue.sqlite";
    }
    // connect to database
    void dbConnect() {
        sqlite3_open(db, &database);
    };
    // pass in any command for the database
    void dbCommand (string command, string action = "") {
        dbConnect();
        sqlite3_stmt *statement;
        // converts string to char const array; it sqlite only allows const char as commands
        const char * convert = command.c_str();
        sqlite3_prepare_v2(database, convert, -1, &statement, 0);
        sqlite3_step(statement);
        // make return hold the select statement's value
        if (action == "READ") {
            returned = (char *) sqlite3_column_text(statement, 0);
        }
        sqlite3_finalize(statement);
        sqlite3_close(database);
    }
    // return if anything selected
    string returnRead() {
        return returned;
    }
    string convertInt(int number) {
        stringstream ss;
        ss << number;
        return ss.str();
    }
};
