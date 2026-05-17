#include "DatabaseManager.h"

#include <iostream>
#include <string>

int main() {
    std::cout << "Tile robot database example\n";
    std::cout << "Create a PostgresDriver with database credentials before using database calls.\n";

    // Example shape only. Fill these with real development credentials locally.
    const std::string db_name = "tile_robot";
    const std::string user = "postgres";
    const std::string password = "postgres";
    const std::string host = "127.0.0.1";
    const std::string port = "5432";

    std::cout << "postgres://" << user << "@" << host << ":" << port << "/" << db_name << "\n";
    return 0;
}