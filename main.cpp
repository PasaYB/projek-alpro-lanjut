#include <iostream>
#include <string>
#include "jadwal.h"

using namespace std;

const string sep = "=================================================================";

void titleScreen(string title){
    cout << sep << endl;
    cout << "           " << title << endl;
    cout << sep << endl;
}

void mainMenu(){
    int pilihan;

    do
    {
        titleScreen("Menu");
        cout << "1. Lihat Daftar Penerbangan" << endl
            << "2. Pesan Tiket" << endl
            << "3. Kelola Pesanan" << endl
            << "4. Laporan" << endl
            << "5. Keluar" << endl
            << "Pilih menu: "; cin >> pilihan;
    } while (pilihan != 5);
    
}

int main() {
    mainMenu();

    return 0;
}