#ifndef PESANAN_H
#define PESANAN_H
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include "utility/utils.h"
#include "jadwal.h"

using namespace std;

struct Pesanan {
    string namaPenumpang;
    string kodeTerbang;
    string kelasTiket; // "Ekonomi" atau "Bisnis"
    long totalBayar;
};

Pesanan daftarPesanan[100];
int jumlahPesanan = 0;

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

void pesanTiket(Jadwal j[]) {
    titleScreen("Pesan Tiket Pesawat");
    string inputKode;
    
    cout << "Masukkan Kode Penerbangan (Contoh: GA-101): ";
    cin >> inputKode;

    int index = cariJadwalBerdasarkanKode(inputKode);

    if (index == -1) {
        cout << "Penerbangan dengan kode " << inputKode << " tidak ditemukan!\n";
        return;
    }

    int sisa = j[index].sisaKursi(j[index]);

    if (sisa <= 0) {
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
             << j[i].sisaKursi(j[i]) << endl;
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

#endif