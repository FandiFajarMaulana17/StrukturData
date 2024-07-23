#include <iostream>
#include <mysql/mysql.h>
using namespace std;

const char *hostname = "127.0.0.1";
const char *user = "root";
const char *pass = "p455w0rd";
const char *dbname = "toko_fandi";
unsigned int port = 33215;
const char *unixsocket = NULL;
unsigned long clientflag = 0;

MYSQL *connect_db()
{
    MYSQL *conn = mysql_init(0);
    if (conn && mysql_real_connect(conn, hostname, user, pass, dbname, port, unixsocket, clientflag))
    {
        return conn;
    }
    cerr << "Connection failed: " << mysql_error(conn) << endl;
    return nullptr;
}

bool register_user(const string &username, const string &password, const string &role)
{
    MYSQL *conn = connect_db();
    if (conn)
    {
        string query = "INSERT INTO users (username, password, role) VALUES ('" + username + "', '" + password + "', '" + role + "')";
        if (mysql_query(conn, query.c_str()))
        {
            cerr << "INSERT failed: " << mysql_error(conn) << endl;
            mysql_close(conn);
            return false;
        }
        cout << role << " Berhasil di tambahkan." << endl;
        mysql_close(conn);
        return true;
    }
    return false;
}

bool login(const string &username, const string &password, string &userRole)
{
    MYSQL *conn = connect_db();
    if (conn)
    {
        string query = "SELECT role FROM users WHERE username = '" + username + "' AND password = '" + password + "'";
        if (mysql_query(conn, query.c_str()) == 0)
        {
            MYSQL_RES *res = mysql_store_result(conn);
            if (mysql_num_rows(res) > 0)
            {
                MYSQL_ROW row = mysql_fetch_row(res);
                userRole = row[0];
                mysql_free_result(res);
                mysql_close(conn);
                return true;
            }
            mysql_free_result(res);
        }
        mysql_close(conn);
    }
    return false;
}

void create_barang(const string &nama, int jumlah, const string &harga)
{
    MYSQL *conn = connect_db();
    if (conn)
    {
        string query = "INSERT INTO barang (nama, jumlah, harga) VALUES ('" + nama + "', '" + to_string(jumlah) + "', '" + harga + "')";
        if (mysql_query(conn, query.c_str()))
        {
            cerr << "INSERT failed: " << mysql_error(conn) << endl;
        }
        else
        {
            cout << "Barang berhasil di ubah." << endl;
        }
        mysql_close(conn);
    }
}

void get_barang()
{
    MYSQL *conn = connect_db();
    if (conn)
    {
        string query = "SELECT * FROM barang";
        if (mysql_query(conn, query.c_str()) == 0)
        {
            MYSQL_RES *res = mysql_store_result(conn);
            MYSQL_ROW row;
            while ((row = mysql_fetch_row(res)) != NULL)
            {
                cout << "ID: " << row[0] << " | Nama: " << row[1] << " | Jumlah: " << row[2] << " | Harga: " << row[3] << endl;
            }
            mysql_free_result(res);
        }
        else
        {
            cerr << "SELECT failed: " << mysql_error(conn) << endl;
        }
        mysql_close(conn);
    }
}

void update_barang(int id, const string &nama, int jumlah, const string &harga)
{
    MYSQL *conn = connect_db();
    if (conn)
    {
        string query = "UPDATE barang SET nama='" + nama + "', jumlah=" + to_string(jumlah) + ", harga='" + harga + "' WHERE id=" + to_string(id);
        if (mysql_query(conn, query.c_str()))
        {
            cerr << "UPDATE failed: " << mysql_error(conn) << endl;
        }
        else
        {
            cout << "Barang berhasil ter update." << endl;
        }
        mysql_close(conn);
    }
}

void delete_barang(int id)
{
    MYSQL *conn = connect_db();
    if (conn)
    {
        string query = "DELETE FROM barang WHERE id=" + to_string(id);
        if (mysql_query(conn, query.c_str()))
        {
            cerr << "DELETE failed: " << mysql_error(conn) << endl;
        }
        else
        {
            cout << "Barang berhasil terhapus." << endl;
        }
        mysql_close(conn);
    }
}

void display_admin_menu()
{
    int choice;
    do
    {
        cout << "1. Create Barang\n2. Get Barang\n3. Update Barang\n4. Delete Barang\n5. Exit\nChoice: ";
        cin >> choice;

        if (choice == 5)
        {
            cout << "Exiting..." << endl;
            break;
        }

        switch (choice)
        {
        case 1:
        {
            string nama, harga;
            int jumlah;
            cout << "Nama Barang: ";
            cin >> nama;
            cout << "Jumlah Barang: ";
            cin >> jumlah;
            cout << "Harga Barang: ";
            cin >> harga;
            create_barang(nama, jumlah, harga);
            break;
        }
        case 2:
        {
            get_barang();
            break;
        }
        case 3:
        {
            int id, jumlah;
            string nama, harga;
            cout << "ID: ";
            cin >> id;
            cout << "Nama Barang: ";
            cin >> nama;
            cout << "Jumlah Barang: ";
            cin >> jumlah;
            cout << "Harga Barang: ";
            cin >> harga;
            update_barang(id, nama, jumlah, harga);
            break;
        }
        case 4:
        {
            int id;
            cout << "ID: ";
            cin >> id;
            delete_barang(id);
            break;
        }
        default:
            cout << "Invalid choice." << endl;
            break;
        }
    } while (choice != 5);
}

void display_user_menu()
{
    int choice;
    do
    {
        cout << "1. Get Barang\n2. Exit\nChoice: ";
        cin >> choice;

        if (choice == 2)
        {
            cout << "Exiting..." << endl;
            break;
        }

        if (choice == 1)
        {
            get_barang();
        }
        else
        {
            cout << "Invalid choice." << endl;
        }
    } while (choice != 2);
}

int main()
{
    int choice;
    do
    {
        cout << "Welcome to Toko App\n1. Register\n2. Login\n3. Exit\nChoice: ";
        cin >> choice;

        if (choice == 1)
        {
            string username, password, role;
            cout << "Username: ";
            cin >> username;
            cout << "Password: ";
            cin >> password;
            cout << "Role (admin/user): ";
            cin >> role;
            register_user(username, password, role);
        }
        else if (choice == 2)
        {
            string username, password, userRole;
            cout << "Username: ";
            cin >> username;
            cout << "Password: ";
            cin >> password;
            if (login(username, password, userRole))
            {
                cout << "Welcome, " << username << "! Role: " << userRole << endl;
                if (userRole == "admin")
                {
                    display_admin_menu();
                }
                else
                {
                    display_user_menu();
                }
            }
            else
            {
                cout << "Login failed." << endl;
            }
        }
    } while (choice != 3);

    return 0;
}