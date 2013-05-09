#include <iostream>
#include "sqlite3.h"
#include <string>

using namespace std;

class sqlite {
private:
    sqlite3 *database;
    const char * command;
    const char * returned;
    const char * db;
public:
    string action;
    sqlite() {
    db = "rogue.sqlite";
    }
    void dbConnect(const char * db) {
        sqlite3_open(db, &database);
    };
    void dbCommand (const char * command, string action) {
dbConnect(db);
    sqlite3_stmt *statement;
    sqlite3_prepare_v2(database, command, -1, &statement, 0);
    sqlite3_step(statement);
    if (action == "READ") {
        returned = (char *) sqlite3_column_text(statement, 0);
    }
    //
    sqlite3_finalize(statement);
    sqlite3_close(database);
    }
    string returnRead() {
        return returned;
    }
};