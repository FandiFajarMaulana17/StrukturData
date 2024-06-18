#include <iostream>
#include <stack>
#include <string>
#include <iomanip>

using namespace std;

// Fungsi untuk menampilkan menu
void displayMenu() {
    cout << "\n===== Menu Operasi Tumpukan Buku =====\n";
    cout << "1. Tambah Buku (push)\n";
    cout << "2. Ambil Buku Teratas (pop)\n";
    cout << "3. Lihat Buku Teratas (peek)\n";
    cout << "4. Cek Apakah Tumpukan Kosong (isEmpty)\n";
    cout << "5. Lihat Jumlah Buku dalam Tumpukan (size)\n";
    cout << "6. Tampilkan Semua Buku dalam Tumpukan\n";
    cout << "7. Keluar (exit)\n";
    cout << "======================================\n";
    cout << "Pilih operasi (1-7): ";
}

// Fungsi untuk menampilkan semua buku dalam tumpukan
void displayAllBooks(stack<string> bookStack) {
    cout << "\nBuku dalam tumpukan:\n";
    if (bookStack.empty()) {
        cout << "Tumpukan kosong.\n";
    } else {
        while (!bookStack.empty()) {
            cout << "- " << bookStack.top() << "\n";
            bookStack.pop();
        }
    }
}

int main() {
    stack<string> bookStack;
    int choice;

    while (true) {
        displayMenu();
        cin >> choice;

        if (choice == 1) {
            string book;
            cout << "Masukkan nama buku: ";
            cin.ignore();
            getline(cin, book);
            bookStack.push(book);
            cout << "Buku \"" << book << "\" telah ditambahkan ke tumpukan.\n";
        } else if (choice == 2) {
            if (bookStack.empty()) {
                cout << "Tumpukan kosong. Tidak ada buku yang bisa diambil.\n";
            } else {
                cout << "Buku \"" << bookStack.top() << "\" telah diambil dari tumpukan.\n";
                bookStack.pop();
            }
        } else if (choice == 3) {
            if (bookStack.empty()) {
                cout << "Tumpukan kosong. Tidak ada buku yang bisa dilihat.\n";
            } else {
                cout << "Buku teratas di tumpukan adalah \"" << bookStack.top() << "\".\n";
            }
        } else if (choice == 4) {
            if (bookStack.empty()) {
                cout << "Tumpukan kosong.\n";
            } else {
                cout << "Tumpukan tidak kosong.\n";
            }
        } else if (choice == 5) {
            cout << "Jumlah buku dalam tumpukan: " << bookStack.size() << ".\n";
        } else if (choice == 6) {
            displayAllBooks(bookStack);
        } else if (choice == 7) {
            cout << "Keluar dari program.\n";
            break;
        } else {
            cout << "Pilihan tidak valid. Silakan coba lagi.\n";
        }
    }

    return 0;
}
