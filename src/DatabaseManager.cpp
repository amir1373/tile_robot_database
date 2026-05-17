#include "DatabaseManager.h"

void PostgresDriver::create_move_table()
{
    pqxx::work worker(db_connection);
    
    string query = "CREATE TABLE move("  \
        "ID SERIAL PRIMARY KEY  NOT NULL, " \
        "NAME  CHAR(50) NOT NULL, " \
        "UNIQUE (NAME));";
    
    worker.exec(const_cast<char*>(query.c_str()));
    worker.commit();
}

void PostgresDriver::create_waypoint_table()
{
    pqxx::work worker(db_connection);
    string query = "CREATE TABLE waypoint("  \
        "ID BIGSERIAL PRIMARY KEY  NOT NULL, " \
        "MOVE_ID SERIAL REFERENCES move(id) ON DELETE CASCADE, " \
        "X_POSITION      DOUBLE PRECISION  NOT NULL, " \
        "Y_POSITION      DOUBLE PRECISION  NOT NULL, " \
        "Z_POSITION      DOUBLE PRECISION  NOT NULL, "\
        "X_ORIENTATION  DOUBLE PRECISION NULL, " \
        "Y_ORIENTATION   DOUBLE PRECISION  NOT NULL, "\
        "Z_ORIENTATION  DOUBLE PRECISION  NOT NULL, " \
        "W_ORIENTATION  DOUBLE PRECISION  NOT NULL, "\
        "RAIL_DISPLACEMENT    INTEGER NOT NULL,"\
        "RAIL_TIME            INTEGER NOT NULL,"\
        "RAIL_SPEED           INTEGER NOT NULL,"\
        "RAIL_DIRECTION BOOLEAN NOT NULL,"\
        "DISPLACEMENT_TIME_TO_NEXT_WAYPOINT      INTEGER NOT NULL);";
    worker.exec(const_cast<char*>(query.c_str()));
    worker.commit();
}

void PostgresDriver::create_log_table()
{
    pqxx::work worker(db_connection);
    string sql = "CREATE TABLE log("  \
        "ID BIGSERIAL PRIMARY KEY  NOT NULL, " \
        "ERROR_ID INTEGER NOT NULL, " \
        "DESCRIPTION TEXT NOT NULL, " \
        "DATE date NOT NULL, " \
        "TIME time NOT NULL);";

    worker.exec(const_cast<char*>(sql.c_str()));
    worker.commit();
}

void PostgresDriver::create_tile_layout_table()
{
    string query = "CREATE TABLE tile_layout("\
    "id SERIAL PRIMARY KEY NOT NULL,"\
    "style TEXT NOT NULL,"\
    "MOVE_ID SERIAL REFERENCES move(id) ON DELETE CASCADE," \
    "UNIQUE (MOVE_ID));";

    pqxx::work worker(db_connection);
    worker.exec(const_cast<char*>(query.c_str()));
    worker.commit();
}

void PostgresDriver::create_language_table()
{
    string query = "CREATE TABLE language_settings(" \
    "id SERIAL PRIMARY KEY, " \
    "language text NOT NULL DEFAULT 'english');";

    pqxx::work worker(db_connection);
    worker.exec(const_cast<char*>(query.c_str()));

    string insert_defualt_lang_query = "INSERT INTO language_settings(id, language) VALUES(1, 'english');";

    worker.exec(const_cast<char*>(insert_defualt_lang_query.c_str()));
    worker.commit();

}

void PostgresDriver::create_password_tables()
{
    string query;

    query = "CREATE TABLE passwords(" \
    "level_1 TEXT DEFAULT '0000', " \
    "level_2 TEXT DEFAULT '0000'," \
    "level_3 TEXT DEFAULT '0000')";

    pqxx::work worker(db_connection);
    worker.exec(const_cast<char*>(query.c_str()));
    worker.commit();
}

PostgresDriver::PostgresDriver(const string &db_name, const string &username,
const string &password, const string &host, const string &port)
{
    connect_to_db(db_name, username, password, host, port);
}

void PostgresDriver::connect_to_db(const string &db_name, const string &username,
const string &password, const string &host, const string &port)
{
    string connection = "dbname = " + db_name + " user = " + username + 
    " password = " + password +" hostaddr = " + host + " port = " + port;

    db_connection = pqxx::connection(connection);
}

string PostgresDriver::get_language_settings()
{
    string query = "SELECT language FROM language_settings WHERE id = 1";

    try
    {
        pqxx::nontransaction non_tran(db_connection);
        pqxx::result result_id(non_tran.exec(const_cast<char*>(query.c_str())));
        return result_id[0][0].as<string>();
    }
    catch(const pqxx::undefined_table& e)
    {
        create_language_table();
        get_language_settings();        
    }
    catch(const std::exception)
    {
        return "";
    }
}

bool PostgresDriver::update_language_settings(const string &language)
{
    string query = "UPDATE language_settings SET language = '" + language + "' WHERE ID = 1;";

    try
    {
        pqxx::work worker(db_connection);
        worker.exec(const_cast<char*>(query.c_str()));
        worker.commit();
        return true;
    }
    catch(const pqxx::undefined_table &e)
    {
        create_language_table();
        update_language_settings(language);
    }
    catch(const std::exception &e)
    {
        return false;
    }
}

int PostgresDriver::insert_tile_layout(const string &style, const int &move_id)
{
    string query = "INSERT INTO tile_layout VALUES(DEFAULT, '" + style + "', " + to_string(move_id) + ");";

    try
    {
        pqxx::work worker(db_connection);
        worker.exec(const_cast<char*>(query.c_str()));
        worker.commit();
    }
    catch (const pqxx::undefined_table &e)
    {
        create_tile_layout_table();
        insert_tile_layout(style, move_id);
    }

    string query_id = "SELECT id FROM tile_layout WHERE move_id= " + to_string(move_id) + " ;";

    try
    {
        pqxx::nontransaction non_tran(db_connection);
        pqxx::result result_id(non_tran.exec(const_cast<char*>(query_id.c_str())));
        return result_id[0][0].as<int>();
    }
    catch (const pqxx::undefined_table &e)
    {
        create_tile_layout_table();
        insert_tile_layout(style, move_id);
    }

}

string PostgresDriver::get_tile_layout(const int &move_id)
{
    try
    {
        string query = "SELECT style FROM tile_layout WHERE move_id =  " + to_string(move_id) + ";";
        pqxx::nontransaction non_tran(db_connection);
        pqxx::result result_id(non_tran.exec(const_cast<char*>(query.c_str())));
        return result_id[0][0].as<string>();
    }
    catch(const pqxx::undefined_table &e)
    {
        create_tile_layout_table();
        get_tile_layout(move_id);
    }
    catch(const std::exception)
    {
        return "";
    }
}

bool PostgresDriver::update_password(const string &old_password, const string &new_password, const string &lvl)
{

    string query;
    if (lvl == "1")
    {
        query = "UPDATE passwords SET level_1 = '" + new_password + 
        "' WHERE level_1 = '" + old_password + "' ;";
    }
    if (lvl == "2")
    {
        query = "UPDATE passwords SET level_2 = '" + new_password + 
        "' WHERE level_2 = '" + old_password + "' ;";
    }
    if (lvl == "3")
    {
        query = "UPDATE passwords SET level_3 = '" + new_password + 
        "' WHERE level_3 = '" + old_password + "' ;";
    }
    else
        return false;

    try
    {
        pqxx::work worker(db_connection);
        worker.exec(const_cast<char*>(query.c_str()));
        worker.commit();
        return true;
    }
    catch(const pqxx::undefined_table &e)
    {
        create_password_tables();
        update_password(old_password, new_password, lvl);

    }

    return false;
}