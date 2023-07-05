#include <iostream>
#include <string>
#include "DatabaseManager.h"

using namespace std;


int main(int argc, char *argv[])
{
    
    PostgresDriver p;
    if (argc == 6 )
    {
        string db_name = argv[1];
        string username = argv[2];
        string password = argv[3];
        string host = argv[4];
        string port = argv[5];

        p.connect_to_db(db_name, username, password, host, port);
    }
    else if (argc < 6)
    {
        return -1;
    }

    cout << "get language setting: " << p.get_language_settings() << endl;

    p.update_language_settings("farsi");

    cout << "get language setting: " << p.get_language_settings() << endl;


}