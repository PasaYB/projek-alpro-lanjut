#ifndef JADWAL_H
#define JADWAL_H

#include <string>
#include <iomanip>
#include "utility/utils.h"

using namespace std;

const int MAX_MASKAPAI = 100;
int jumlahMaskapai = 5;
int jumlahJadwal = 3;

struct Jadwal {
    string kode;          // contoh: "GA-101"
    string maskapai;      // contoh: "Garuda Indonesia"
    string asal;          // contoh: "Jakarta"
    string tujuan;        // contoh: "Bali"
    string tanggal;       // contoh: "2025-06-10"
    string jamBerangkat;  // contoh: "08:00"
    string jamTiba;       // contoh: "09:30"
    int totalKursi;       // total kapasitas pesawat
    int kursiTerisi;      // sudah berapa yang dipesan
    long hargaEkonomi;   // harga kelas ekonomi
    long hargaBisnis;    // harga kelas bisnis

    int sisaKursi() {
        return totalKursi - kursiTerisi;
    }
};

Jadwal j[MAX_MASKAPAI] = {
    // DUMMY DATA MILIK TEMANMU
    {"GA-101", "Garuda Indonesia", "Jakarta", "Bali", "2025-06-10", "08:00", "09:30", 180, 45, 850000, 2100000},
    {"JT-202", "Lion Air", "Surabaya", "Makassar", "2025-06-11", "13:00", "15:10", 210, 120, 620000, 1500000},
    {"QG-303", "Citilink", "Yogyakarta", "Medan", "2025-06-12", "06:30", "09:00", 156, 0, 780000, 1800000}
};

struct Maskapai {
    string kode;  // "GA"
    string nama;  // "Garuda Indonesia"
};

Maskapai daftarMaskapai[MAX_MASKAPAI] = {
    {"GA", "Garuda Indonesia"},
    {"JT", "Lion Air"},
    {"QG", "Citilink"},
    {"ID", "Batik Air"},
    {"QZ", "AirAsia"}
};

// CREATE
void tambahJadwal(Jadwal j[]){
    int pilihanMaskapai;
    string kode;

    titleScreen("TAMBAH JADWAL");
    cout << "Maskapai Penerbangan: " << endl;
    for (int i = 0; i < jumlahMaskapai; i++)
    {
        cout << i+1 << ". " << daftarMaskapai[i].nama << endl;
    }
    cout << jumlahMaskapai+1 << ". Lainnya" << endl;
    
    cout << "Pilihan: "; cin >> pilihanMaskapai;

    if (pilihanMaskapai == jumlahMaskapai + 1) {
        cout << "Masukkan nama maskapai: ";
        cin >> daftarMaskapai[jumlahMaskapai].nama;
        cout << "Masukkan kode maskapai: ";
        cin >> daftarMaskapai[jumlahMaskapai].kode;
        jumlahMaskapai++;
        j[jumlahJadwal].maskapai = daftarMaskapai[jumlahMaskapai-1].nama;
    } else {
        j[jumlahJadwal].maskapai = daftarMaskapai[pilihanMaskapai-1].nama;
    }

    cout << "Masukkan kode: "; cin >> kode; j[jumlahJadwal].kode = daftarMaskapai[pilihanMaskapai-1].kode + "-" +  kode;
    
    cout << sep2 << endl;
    cout << "Masukkan asal: "; cin >> j[jumlahJadwal].asal;
    cout << "Masukkan tujuan: "; cin >> j[jumlahJadwal].tujuan;
    
    cout << sep2 << endl;
    cout << "Masukkan tanggal (YYYY-MM-DD): "; cin >> j[jumlahJadwal].tanggal;
    cout << "Masukkan jam berangkat (HH:MM): "; cin >> j[jumlahJadwal].jamBerangkat;
    cout << "Masukkan jam tiba (HH:MM): "; cin >> j[jumlahJadwal].jamTiba;
    
    cout << sep2 << endl;
    cout << "Masukkan total kursi: "; cin >> j[jumlahJadwal].totalKursi;
    
    cout << sep2 << endl;
    cout << "Masukkan harga Ekonomi: Rp."; cin >> j[jumlahJadwal].hargaEkonomi;
    cout << "Masukkan harga Bisnis: Rp."; cin >> j[jumlahJadwal].hargaBisnis;
    jumlahJadwal++;

    cout << sep2 << endl;
    cout << "Data berhasil ditambahkan." << endl;
}

// SHOW
void lihatJadwal(Jadwal j[]){
    titleScreen("DAFTAR PENERBANGAN");
    cout << left 
         << setw(20) << "Maskapai" 
         << setw(10) << "Kode" 
         << setw(15) << "Asal" 
         << setw(15) << "Tujuan" 
         << setw(15) << "Jam Berangkat" 
         << setw(12) << "Jam Tiba" << endl;

    for (int i = 0; i < jumlahJadwal; i++)
    {
        cout << left 
        << setw(20) << j[i].maskapai 
        << setw(10) << j[i].kode 
        << setw(15) << j[i].asal 
        << setw(15) << j[i].tujuan 
        << setw(15) << j[i].jamBerangkat 
        << setw(12) << j[i].jamTiba << endl;
    };
}

// UPDATE 
void editJadwal(Jadwal j[]){
    string kode;
    int indexTarget = -1, pilihan;
    
    titleScreen("EDIT DATA PENERBANGAN");
    cout << "Masukkan kode penerbangan: "; cin >> kode;
    
    for (int i = 0; i < jumlahJadwal; i++) {
        if (j[i].kode == kode) {
            indexTarget = i;
            break;
        }
    }

    if (indexTarget == -1) {
        cout << "Data dengan kode " << kode << " tidak ditemukan." << endl;
    } else {
        Jadwal &target = j[indexTarget];
        do 
        {
            cout << "\n--- Data Saat Ini ---" << endl;
            cout << "1. Kode         : " << target.kode << endl;
            cout << "2. Maskapai     : " << target.maskapai << endl;
            cout << "3. Asal         : " << target.asal << endl;
            cout << "4. Tujuan       : " << target.tujuan << endl;
            cout << "5. Tanggal      : " << target.tanggal << endl;
            cout << "6. Jam Berangkat: " << target.jamBerangkat << endl;
            cout << "7. Jam Tiba     : " << target.jamTiba << endl;
            cout << "8. Harga Ekonomi: Rp." << target.hargaEkonomi << endl;
            cout << "9. Harga Bisnis : Rp." << target.hargaBisnis << endl;
            cout << "0. Selesai" << endl;
            cout << "Pilih field yang ingin diubah: ";
            cin >> pilihan;

            switch (pilihan) {
                case 1: cout << "Kode baru: ";          cin >> target.kode; break;
                case 2: cout << "Maskapai baru: ";       cin >> target.maskapai; break;
                case 3: cout << "Asal baru: ";           cin >> target.asal; break;
                case 4: cout << "Tujuan baru: ";         cin >> target.tujuan; break;
                case 5: cout << "Tanggal baru: ";        cin >> target.tanggal; break;
                case 6: cout << "Jam berangkat baru: ";  cin >> target.jamBerangkat; break;
                case 7: cout << "Jam tiba baru: ";       cin >> target.jamTiba; break;
                case 8: cout << "Harga ekonomi baru: Rp.";  cin >> target.hargaEkonomi; break;
                case 9: cout << "Harga bisnis baru: Rp.";   cin >> target.hargaBisnis; break;
                case 0: cout << "Update selesai." << endl; break;
                default: cout << "Pilihan tidak valid." << endl;
            }
        } while (pilihan != 0);
    }
}

// DELETE
void hapusJadwal(Jadwal j[]){
    string kode;

    titleScreen("HAPUS DATA PENERBANGAN");
    cout << "Masukkan kode penerbangan: "; cin >> kode;

    int indexTarget = -1;
    
    for (int i = 0; i < jumlahJadwal; i++) {
        if (j[i].kode == kode) {
            indexTarget = i;
            break;
        }
    }

    if (indexTarget == -1) {
        cout << "Data dengan kode " << kode << " tidak ditemukan." << endl;
    } else {
        for (int i = indexTarget; i < jumlahJadwal - 1; i++) {
            j[i] = j[i + 1];
        }
    
        jumlahJadwal--;
        cout << "Data berhasil dihapus." << endl;
    }
}

// SEARCH
void cariJadwal(Jadwal j[]){
    string kode;
    int hasilSearch = -1;
    
    titleScreen("CARI DATA PENERBANGAN");
    cout << "Masukkan kode penerbangan: "; cin >> kode;

    for (int i = 0; i < jumlahJadwal; i++)
    {
        if(j[i].kode == kode){
            hasilSearch = i;
        }
    }

    if(hasilSearch != -1){
        cout << endl << sep2 << endl;

        cout << left 
             << setw(20) << "Maskapai" 
             << setw(10) << "Kode" 
             << setw(15) << "Asal" 
             << setw(15) << "Tujuan" 
             << setw(15) << "Jam Berangkat" 
             << setw(12) << "Jam Tiba" << endl;

        cout << left 
        << setw(20) << j[hasilSearch].maskapai 
        << setw(10) << j[hasilSearch].kode 
        << setw(15) << j[hasilSearch].asal 
        << setw(15) << j[hasilSearch].tujuan 
        << setw(15) << j[hasilSearch].jamBerangkat 
        << setw(12) << j[hasilSearch].jamTiba << endl;
    } else {
        cout << "Data tidak ditemukan!" << endl;
    }
}
#endif