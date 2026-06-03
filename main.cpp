#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include "jadwal.h"
#include "utility/utils.h"

using namespace std;

struct Pesanan {
    string namaPenumpang;
    string kodeTerbang;
    string kelasTiket; // "Ekonomi" atau "Bisnis"
    long totalBayar;
};

Pesanan daftarPesanan[100];
int jumlahPesanan = 0;

// ================================================================================================
void menuAdmin(){
    int pilihan;

    do {
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
        else if(pilihan == 6){ cout << "Keluar dari menu Admin." << endl;}
    } while (pilihan != 6);
}

// ================================================================================================
int cariJadwalBerdasarkanKode(string kodeCari) {
    for (int i = 0; i < jumlahJadwal; i++) {
        if (j[i].kode == kodeCari) { // Terhubung ke database J di jadwal.h
            return i;
        }
    }
    return -1;
}

void sortHargaTermurah() {
    for (int i = 0; i < jumlahJadwal - 1; i++) {
        for (int k = 0; k < jumlahJadwal - i - 1; k++) {
            if (j[k].hargaEkonomi > j[k+1].hargaEkonomi) {
                Jadwal temp = j[k];
                j[k] = j[k+1];
                j[k+1] = temp;
            }
        }
    }
}

void pesanTiket() {
    titleScreen("Pesan Tiket Pesawat");
    string inputKode;
    
    cout << "Masukkan Kode Penerbangan (Contoh: GA-101): ";
    cin >> inputKode;

    int index = cariJadwalBerdasarkanKode(inputKode);

    if (index == -1) {
        cout << "Penerbangan dengan kode " << inputKode << " tidak ditemukan!\n";
        return;
    }

    if (j[index].sisaKursi() <= 0) {
        cout << "Mohon maaf, kursi untuk penerbangan ini sudah penuh!\n";
        return;
    }

    Pesanan pesananBaru;
    pesananBaru.kodeTerbang = inputKode;

    cout << "Nama Penumpang: ";
    cin.ignore();
    getline(cin, pesananBaru.namaPenumpang);

    cout << "Pilih Kelas:\n";
    cout << "1. Ekonomi (Rp " << j[index].hargaEkonomi << ")\n";
    cout << "2. Bisnis (Rp " << j[index].hargaBisnis << ")\n";
    cout << "Pilihan (1/2): ";
    
    int pilKelas;
    cin >> pilKelas;

    if (pilKelas == 1) {
        pesananBaru.kelasTiket = "Ekonomi";
        pesananBaru.totalBayar = j[index].hargaEkonomi;
    } else if (pilKelas == 2) {
        pesananBaru.kelasTiket = "Bisnis";
        pesananBaru.totalBayar = j[index].hargaBisnis;
    } else {
        cout << "Pilihan kelas tidak valid! Pemesanan dibatalkan.\n";
        return;
    }

    cout << "\n--- Konfirmasi Pesanan ---\n";
    cout << "Nama       : " << pesananBaru.namaPenumpang << endl;
    cout << "Penerbangan: " << j[index].maskapai << " (" << inputKode << ")" << endl;
    cout << "Rute       : " << j[index].asal << " -> " << j[index].tujuan << endl;
    cout << "Kelas      : " << pesananBaru.kelasTiket << endl;
    cout << "Total Bayar: Rp " << pesananBaru.totalBayar << endl;
    
    char konfirmasi;
    cout << "\nLanjutkan pemesanan? (y/n): ";
    cin >> konfirmasi;

    if (konfirmasi == 'y' || konfirmasi == 'Y') {
        j[index].kursiTerisi += 1;
        
        daftarPesanan[jumlahPesanan] = pesananBaru;
        jumlahPesanan++;
        
        ofstream fileStruk;
        fileStruk.open("Riwayat_Pesanan.txt", ios::app); 
        
        if (fileStruk.is_open()) {
            fileStruk << sep2 << endl;
            fileStruk << "BUKTI PEMESANAN TIKET PESAWAT" << endl;
            fileStruk << sep2 << endl;
            fileStruk << "Nama Penumpang : " << pesananBaru.namaPenumpang << endl;
            fileStruk << "Maskapai       : " << j[index].maskapai << " (" << inputKode << ")" << endl;
            fileStruk << "Rute           : " << j[index].asal << " -> " << j[index].tujuan << endl;
            fileStruk << "Kelas          : " << pesananBaru.kelasTiket << endl;
            fileStruk << "Total Bayar    : Rp " << pesananBaru.totalBayar << endl;
            fileStruk << sep2 << endl << endl;
            
            fileStruk.close(); 
        } else {
            cout << "Gagal membuat file struk!\n";
        }
        
        cout << "Berhasil! Tiket anda telah dipesan.\n";
        cout << "[ Struk telah otomatis disimpan di 'Riwayat_Pesanan.txt' ]\n";
    } else {
        cout << "Pemesanan dibatalkan.\n";
    }
}

void lihatDaftarPenerbangan() {
    titleScreen("Daftar Penerbangan Tersedia");
    
    int opsiSort;
    cout << "Opsi Tampilan:\n";
    cout << "1. Tampilkan Default\n";
    cout << "2. Urutkan berdasarkan Harga Ekonomi (Termurah)\n";
    cout << "Pilih (1/2): ";
    cin >> opsiSort;

    if (opsiSort == 2) {
        sortHargaTermurah();
        cout << "\n[ Data telah diurutkan dari harga termurah ]\n";
    } else {
        cout << "\n[ Menampilkan data bawaan ]\n";
    }

    cout << sep2 << endl;
    cout << left << setw(10) << "KODE" 
         << setw(20) << "MASKAPAI" 
         << setw(22) << "RUTE" 
         << setw(15) << "WAKTU" 
         << setw(15) << "HARGA EKO" 
         << "SISA KURSI" << endl;
    cout << sep2 << endl;

    for (int i = 0; i < jumlahJadwal; i++) {
        string rute = j[i].asal + "-" + j[i].tujuan;
        string waktu = j[i].jamBerangkat + "-" + j[i].jamTiba;
        
        cout << left << setw(10) << j[i].kode
             << setw(20) << j[i].maskapai
             << setw(22) << rute
             << setw(15) << waktu
             << "Rp " << setw(12) << j[i].hargaEkonomi
             << j[i].sisaKursi() << endl;
    }
    cout << sep2 << endl;
    
    cout << "\nTekan Enter untuk kembali ke menu utama...";
    cin.ignore();
    cin.get(); 
}

void laporanPesanan() {
    titleScreen("Laporan Pemesanan Tiket");

    ifstream fileBaca("Riwayat_Pesanan.txt");
    string barisTeks;

    if (fileBaca.is_open()) {
        cout << "[ Menampilkan riwayat dari file penyimpanan permanen ]\n\n";
        while (getline(fileBaca, barisTeks)) {
            cout << barisTeks << endl;
        }
        fileBaca.close();
    } else {
        cout << "Belum ada riwayat tiket yang dipesan.\n";
    }

    cout << "\nTekan Enter untuk kembali ke menu utama...";
    cin.ignore();
    cin.get();
}

// ================================================================================================

void mainMenu(){
    int pilihan;
    do
    {
        titleScreen("Menu Sistem Reservasi User");
        cout << "1. Lihat Daftar Penerbangan" << endl
             << "2. Pesan Tiket" << endl
             << "3. Laporan Pemesanan" << endl
             << "4. Keluar" << endl
             << "Pilih menu: "; 
        cin >> pilihan;

        switch (pilihan) {
            case 1: lihatDaftarPenerbangan(); break;
            case 2: pesanTiket(); break;
            case 3: laporanPesanan(); break;
            case 4: cout << "Keluar dari menu user.\n"; break;
            default: cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 4);
}

// ================================================================================================ 
void login(){
    int pilihan, chance = 0;
    string user_name, user_pw, admin_pw, admin_name;

    do {
        titleScreen("GERBANG UTAMA");
        cout << "1. Login sebagai Admin" << endl
             << "2. Login sebagai User" << endl
             << "3. Keluar Aplikasi" << endl
             << "Pilih menu: "; cin >> pilihan;
            
        if(pilihan == 1){
            do {
                titleScreen("LOGIN ADMIN");
                cout << "Masukkan nama Admin: "; cin >> admin_name;
                cout << "Masukkan password: "; cin >> admin_pw;

                if(admin_name == "admin" && admin_pw == "123"){
                    menuAdmin();
                    break;
                } else {
                    chance++;
                    cout << "Login Gagal. Kesempatan tersisa: " << 3 - chance << endl;
                }
            } while(chance < 3);
            chance = 0;

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
                    cout << "Login Gagal. Kesempatan tersisa: " << 3 - chance << endl;
                }
            } while (chance < 3);
            chance = 0;
        }
    } while (pilihan != 3);

    cout << "Terima Kasih!\n";
}

int main() {
    login();
    return 0;
}