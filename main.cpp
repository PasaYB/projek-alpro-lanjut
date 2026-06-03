#include <iostream>
#include <string>
#include "utility/utils.h"
#include "jadwal.h"
#include "pesanan.h"

using namespace std;

// Menu Admin
void menuAdmin(){
    int pilihan;

    do
    {
        titleScreen("DASHBOARD ADMIN");
        cout << "1. Tambah Daftar Penerbangan" << endl
            << "2. Cari Daftar Penerbangan" << endl
            << "3. Lihat Daftar Penerbangan" << endl
            << "4. Edit Daftar Penerbangan" << endl
            << "5. Hapus Daftar Penerbangan" << endl
            << "6. Keluar" << endl
            << "Pilih menu: "; cin >> pilihan;

            if(pilihan == 1){ tambahJadwal(j); }
            else if(pilihan == 2){ cariJadwal(j); }
            else if(pilihan == 3){ lihatJadwal(j); }
            else if(pilihan == 4){ editJadwal(j); }
            else if(pilihan == 5){ hapusJadwal(j); }
            else if(pilihan == 6){ cout << "Terima gaji" << endl;}
    } while (pilihan != 6);
}
// ================================================================================================

// User
void mainMenu(){
    int pilihan;
    do
    {
        titleScreen("Menu Sistem Reservasi User");
        cout << "1. Lihat Daftar Penerbangan" << endl
            << "2. Pesan Tiket" << endl
            << "3. Kelola Pesanan" << endl
            << "4. Laporan" << endl
            << "5. Keluar" << endl
            << "Pilih menu: "; cin >> pilihan;

            if(pilihan == 1){ lihatDaftarPenerbangan(); }
            else if(pilihan == 2){ pesanTiket(j); }
            else if(pilihan == 3){ laporanPesanan(); }
            else if(pilihan == 4){ cout << "Keluar dari menu user.\n"; }
    } while (pilihan != 4);
}
// ================================================================================================

void login(){
    int pilihan, chance = 0;
    string user_name, user_pw, admin_pw, admin_name;

    do
    {
        titleScreen("LOGIN");
        cout << "1. Login sebagai Admin" << endl
            << "2. Login sebagai User" << endl
            << "3. Keluar" << endl
            << "Pilih menu: "; cin >> pilihan;
            
        if(pilihan == 1){
            do {
                titleScreen("LOGIN ADMIN");
                cout << "Masukkan nama Admin: "; cin >> admin_name;
                cout << "Masukkan password: "; cin >> admin_pw;

                stoi(admin_pw);
                
                if(admin_name == "admin" && admin_pw == "123"){
                    menuAdmin();
                    break;
                } else {
                    chance++;
                }

                cout << "Kesempatan Habis" << endl;
            } while(chance < 3);
        } else if (pilihan == 2) {
            do {
                titleScreen("LOGIN USER");
                cout << "Masukkan nama User: "; cin >> user_name;
                cout << "Masukkan password: "; cin >> user_pw;

                if(user_name == "user" && user_pw == "123"){
                    mainMenu();
                    break;
                } else {
                    chance++;
                }

                cout << "Kesempatan Habis" << endl;
            } while (chance < 3);
            
        }
    } while (pilihan != 3);

    cout << "Terima Kasih!" << endl;
}

int main() {

    login();

    return 0;
}
