# Banking System Project

This project is a **Banking System** written in **C++**, using the **MySQL C API** for database management. The system allows users to perform various banking operations such as account creation, balance inquiry, deposits, withdrawals, and transfers.

## Features
1. **Account Management**:
   - Create new customer accounts.
   - Manage account details and PINs.
   - Temporarily block accounts for security.

2. **Transactions**:
   - Deposit money.
   - Withdraw money.
   - Transfer money between accounts.

3. **Audit and Logs**:
   - View transaction history for deposits, withdrawals, and transfers.

4. **Database Integration**:
   - Utilizes MySQL for secure data storage.
   - Automatically creates the necessary database and tables if they do not exist.

## Prerequisites

1. **Development Environment**:
   - Visual Studio (with "Desktop Development with C++" workload installed).

2. **MySQL Server**:
   - Ensure you have a running MySQL server (local or remote).

3. **MySQL Connector/C**:
   - Install the MySQL C API (Connector/C) from [MySQL website](https://dev.mysql.com/downloads/connector/c/).

## Installation and Setup

### 1. Clone the Repository
```
git clone https://github.com/hemanthgithub642/APDBMS.git
```

### 2. Set Up MySQL Connector
- Include the MySQL Connector library and headers in your project:
  1. Add the `include` folder of the MySQL Connector to the **Additional Include Directories** in Visual Studio.
  2. Add the `lib` folder of the MySQL Connector to the **Additional Library Directories**.
  3. Link the `libmysql.lib` library in the **Linker > Input > Additional Dependencies**.

### 3. Configure Database Connection
- Update the connection details in the program:
  - Hostname
  - Username
  - Password
  - Port

### 4. Build and Run the Project
- Open the project in Visual Studio.
- Build the solution (`Ctrl + Shift + B`).
- Run the application (`Ctrl + F5`).

## How to Use
1. Launch the program.
2. Enter database connection details (hostname, username, password, port).
3. Perform the following operations:
   - **Login**: Access your account.
   - **Signup**: Create a new account.
   - **Deposit**: Add money to your account.
   - **Withdraw**: Remove money from your account.
   - **Transfer**: Transfer money to another account.
   - **View Statement**: Check transaction history.
4. Exit the application when done.

## Database Structure

The application creates the following database and tables:

- **Database**: `apdbms`
- **Tables**:
  - `apdbms_Cust`: Stores customer details (Name, Account Number).
  - `apdbms_Bal`: Stores account balances.
  - `apdbms_Acc`: Stores account PINs.
  - `apdbms_wid`: Logs withdrawal transactions.
  - `apdbms_dep`: Logs deposit transactions.
  - `apdbms_tra`: Logs transfer transactions.
  - `apdbms_blo`: Tracks blocked accounts.

## Example SQL Queries

Use these queries to manually inspect the database:
```sql
USE apdbms;

SELECT * FROM apdbms_Cust;
SELECT * FROM apdbms_Bal;
SELECT * FROM apdbms_Acc;
SELECT * FROM apdbms_wid;
SELECT * FROM apdbms_dep;
SELECT * FROM apdbms_tra;
SELECT * FROM apdbms_blo;
```

## Troubleshooting

1. **Missing DLLs**:
   - Ensure `libmysql.dll` is in the same directory as the executable.
2. **Connection Issues**:
   - Verify MySQL server is running and credentials are correct.
3. **Compilation Errors**:
   - Check Visual Studio project properties for correct library and include paths.

## Future Enhancements

1. Implement advanced security features such as encryption for PINs.
2. Add support for additional transaction types (e.g., loan processing).
3. Develop a graphical user interface (GUI).


## Acknowledgments
- **MySQL**: For providing the database management system.
- **Visual Studio**: For the development environment.

