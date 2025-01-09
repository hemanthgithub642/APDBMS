#include <iostream>
#include <mysql/mysql.h>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <stdexcept>

using namespace std;

void clearConsole() {
    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #else
        system("clear");
    #endif
}

void animate(const string& message) {
    const vector<char> spinner = {'|', '/', '-', '\\'};
    for (int i = 0; i < 20; ++i) {
        for (char c : spinner) {
            cout << "\r" << message << " " << c;
            cout.flush();
            this_thread::sleep_for(chrono::milliseconds(100));
        }
    }
    cout << "\r" << string(message.size() + 2, ' ') << "\r";
}

void connectToDatabase(MYSQL* conn, const string& host, const string& user, const string& pass, const unsigned int port) {
    if (!mysql_real_connect(conn, host.c_str(), user.c_str(), pass.c_str(), nullptr, port, nullptr, 0)) {
        throw runtime_error("Failed to connect to MySQL: " + string(mysql_error(conn)));
    }
}

void createDatabaseAndTables(MYSQL* conn) {
    const char* queries[] = {
        "CREATE DATABASE IF NOT EXISTS apdbms;",
        "USE apdbms;",
        "CREATE TABLE IF NOT EXISTS apdbms_Cust(Name VARCHAR(20), ACCOUNT_NO INT PRIMARY KEY);",
        "CREATE TABLE IF NOT EXISTS apdbms_Bal(ACCOUNT_NO INT, Balance INT, FOREIGN KEY(ACCOUNT_NO) REFERENCES apdbms_Cust(ACCOUNT_NO) ON DELETE CASCADE);",
        "CREATE TABLE IF NOT EXISTS apdbms_Acc(ACCOUNT_NO INT, PIN VARCHAR(10), FOREIGN KEY(ACCOUNT_NO) REFERENCES apdbms_Cust(ACCOUNT_NO) ON DELETE CASCADE);",
        "CREATE TABLE IF NOT EXISTS apdbms_wid(Date TIMESTAMP DEFAULT CURRENT_TIMESTAMP, ACCOUNT_NO INT, Amount INT, FOREIGN KEY(ACCOUNT_NO) REFERENCES apdbms_Cust(ACCOUNT_NO) ON DELETE CASCADE);",
        "CREATE TABLE IF NOT EXISTS apdbms_dep(Date TIMESTAMP DEFAULT CURRENT_TIMESTAMP, ACCOUNT_NO INT, Amount INT, FOREIGN KEY(ACCOUNT_NO) REFERENCES apdbms_Cust(ACCOUNT_NO) ON DELETE CASCADE);",
        "CREATE TABLE IF NOT EXISTS apdbms_tra(Date TIMESTAMP DEFAULT CURRENT_TIMESTAMP, ACCOUNT_NO INT, To_ACCOUNT INT, Amount INT, FOREIGN KEY(ACCOUNT_NO) REFERENCES apdbms_Cust(ACCOUNT_NO) ON DELETE CASCADE);",
        "CREATE TABLE IF NOT EXISTS apdbms_blo(ACCOUNT_NO INT, FOREIGN KEY(ACCOUNT_NO) REFERENCES apdbms_Cust(ACCOUNT_NO) ON DELETE CASCADE);"
    };

    for (const char* query : queries) {
        if (mysql_query(conn, query)) {
            throw runtime_error("Failed to execute query: " + string(query) + ", Error: " + string(mysql_error(conn)));
        }
    }
}

int main() {
    MYSQL* conn = mysql_init(nullptr);

    if (!conn) {
        cerr << "MySQL initialization failed!" << endl;
        return EXIT_FAILURE;
    }

    string host, user, pass;
    unsigned int port;

    while (true) {
        try {
            cout << "Enter the Host Name: ";
            cin >> host;
            cout << "Enter the User Name: ";
            cin >> user;
            cout << "Enter the password: ";
            cin >> pass;
            cout << "Enter port Number (Default - 3306): ";
            cin >> port;

            connectToDatabase(conn, host, user, pass, port);
            createDatabaseAndTables(conn);

            cout << "Database and tables set up successfully!" << endl;
            break;
        } catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
            cout << "Retrying connection..." << endl;
        }
    }

    mysql_close(conn);
    return 0;
}
