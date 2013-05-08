#include <iostream>
#include "sqlite3.h"
#include <string>

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
        db = "rogue.sqlite";
    }
    void dbConnect() {
        sqlite3_open(db, &database);
    };
    void dbCommand (string command, string action = "") {
        dbConnect();
        sqlite3_stmt *statement;
        const char * convert = command.c_str();
        sqlite3_prepare_v2(database, convert, -1, &statement, 0);
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
