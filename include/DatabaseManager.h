#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include "pqxx/pqxx"

using namespace std;

class PostgresDriver
{

    private:

        void create_move_table();
        void create_waypoint_table();
        void create_log_table();
        void create_tile_layout_table();
        void create_language_table();
        void create_password_tables();

        pqxx::connection db_connection;


    public:
        PostgresDriver(){}

        PostgresDriver(const string &db_name, const string &username,
        const string &password, const string &host = "127.0.0.1", const string &port = "5432");

        void connect_to_db(const string &db_name, const string &username,
        const string &password, const string &host = "127.0.0.1", const string &port = "5432");

        string get_language_settings();

        bool update_language_settings(const string &language);

        int insert_tile_layout(const string &style, const int &move_id);

        string get_tile_layout(const int &move_id);
    
        bool update_password(const string &old_password, const string &new_password, const string &lvl);
};

#endif