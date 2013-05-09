/*#include <iostream>
#include "sqlite3.h"
#include <string>

using namespace std;

class sql {
private:

};

int main() {
    sqlite3 *database;
    const char * command;
    const char * returned;
    //takes in command
    command = "select * from test;";//"SELECT * FROM rogue WHERE type='table';";

    if(true) {
            sqlite3_open("rogue.sqlite", &database);
       // cout<<"DATABASE CREATED/EXISTS"<<endl;
        sqlite3_stmt *statement;
        //command = "CREATE TABLE a (b INTEGER, c INTEGER);";
        if(sqlite3_prepare_v2(database, command, -1, &statement, 0) == SQLITE_OK) {
            // if command executed
            sqlite3_step(statement);
            returned = (char *) sqlite3_column_text(statement, 0);
                cout<<returned;

        }
        // else return error and command
        //else {
        //    cout<<"\""<<command<<"\""<<" returned error.";
        //}
        sqlite3_finalize(statement);
    }
    else {
        //cout<<"DB ERROR";

    }
    // sqve and close DB
    sqlite3_close(database);


    return 0;
}
*/
