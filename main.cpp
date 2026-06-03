#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include "jadwal.h"

using namespace std;

const string sep = "=================================================================";
const string sep2 = "--------------------------------------------------------------------------------------------------";

struct Pesanan {
    string namaPenumpang;
    string kodeTerbang;
    string kelasTiket; // "Ekonomi" atau "Bisnis"
    long long totalBayar;
};

Jadwal daftarJadwal[100];
int jumlahJadwal = 0;

Pesanan daftarPesanan[100];
int jumlahPesanan = 0;

void titleScreen(string title){
    cout << "\n" << sep << endl;
    cout << "           " << title << endl;
    cout << sep << endl;
}

void DataDummy() {
    daftarJadwal[0] = {"GA-101", "Garuda Indonesia", "Jakarta", "Bali", "2025-06-10", "08:00", "09:30", 150, 148, 1500000, 3500000};
    daftarJadwal[1] = {"JT-202", "Lion Air", "Surabaya", "Jakarta", "2025-06-11", "10:00", "11:30", 200, 50, 800000, 1800000};
    jumlahJadwal = 2;
}

int cariJadwalBerdasarkanKode(string kodeCari) {
    for (int i = 0; i < jumlahJadwal; i++) {
        if (daftarJadwal[i].kode == kodeCari) {
            return i;
        }
    }
    return -1;
}

void sortHargaTermurah() {
    for (int i = 0; i < jumlahJadwal - 1; i++) {
        for (int j = 0; j < jumlahJadwal - i - 1; j++) {
            if (daftarJadwal[j].hargaEkonomi > daftarJadwal[j+1].hargaEkonomi) {
                Jadwal temp = daftarJadwal[j];
                daftarJadwal[j] = daftarJadwal[j+1];
                daftarJadwal[j+1] = temp;
            }
        }
    }
}

void pesanTiket() {
    titleScreen("Pesan Tiket Pesawat");
    string inputKode;
    
    cout << "Masukkan Kode Penerbangan (Contoh: GA-101): ";
    cin >> inputKode;

    // Memanggil fungsi searching (15% Komponen Penilaian)
    int index = cariJadwalBerdasarkanKode(inputKode);

    if (index == -1) {
        cout << "Penerbangan dengan kode " << inputKode << " tidak ditemukan!\n";
        return;
    }

    // Mengecek ketersediaan kursi menggunakan method dari struct Jadwal
    if (daftarJadwal[index].sisaKursi() <= 0) {
        cout << "Mohon maaf, kursi untuk penerbangan ini sudah penuh!\n";
        return;
    }

    Pesanan pesananBaru;
    pesananBaru.kodeTerbang = inputKode;

    cout << "Nama Penumpang: ";
    cin.ignore();
    getline(cin, pesananBaru.namaPenumpang);

    cout << "Pilih Kelas:\n";
    cout << "1. Ekonomi (Rp " << daftarJadwal[index].hargaEkonomi << ")\n";
    cout << "2. Bisnis (Rp " << daftarJadwal[index].hargaBisnis << ")\n";
    cout << "Pilihan (1/2): ";
    
    int pilKelas;
    cin >> pilKelas;

    if (pilKelas == 1) {
        pesananBaru.kelasTiket = "Ekonomi";
        pesananBaru.totalBayar = daftarJadwal[index].hargaEkonomi;
    } else if (pilKelas == 2) {
        pesananBaru.kelasTiket = "Bisnis";
        pesananBaru.totalBayar = daftarJadwal[index].hargaBisnis;
    } else {
        cout << "Pilihan kelas tidak valid! Pemesanan dibatalkan.\n";
        return;
    }

    cout << "\n--- Konfirmasi Pesanan ---\n";
    cout << "Nama       : " << pesananBaru.namaPenumpang << endl;
    cout << "Penerbangan: " << daftarJadwal[index].maskapai << " (" << inputKode << ")" << endl;
    cout << "Rute       : " << daftarJadwal[index].asal << " -> " << daftarJadwal[index].tujuan << endl;
    cout << "Kelas      : " << pesananBaru.kelasTiket << endl;
    cout << "Total Bayar: Rp " << pesananBaru.totalBayar << endl;
    
    char konfirmasi;
    cout << "\nLanjutkan pemesanan? (y/n): ";
    cin >> konfirmasi;

    if (konfirmasi == 'y' || konfirmasi == 'Y') {
        daftarJadwal[index].kursiTerisi += 1;
        
        daftarPesanan[jumlahPesanan] = pesananBaru;
        jumlahPesanan++;
        
        ofstream fileStruk;
        fileStruk.open("Riwayat_Pesanan.txt", ios::app); 
        
        if (fileStruk.is_open()) {
            fileStruk << sep2 << endl;
            fileStruk << "BUKTI PEMESANAN TIKET PESAWAT" << endl;
            fileStruk << sep2 << endl;
            fileStruk << "Nama Penumpang : " << pesananBaru.namaPenumpang << endl;
            fileStruk << "Maskapai       : " << daftarJadwal[index].maskapai << " (" << inputKode << ")" << endl;
            fileStruk << "Rute           : " << daftarJadwal[index].asal << " -> " << daftarJadwal[index].tujuan << endl;
            fileStruk << "Kelas          : " << pesananBaru.kelasTiket << endl;
            fileStruk << "Total Bayar    : Rp " << pesananBaru.totalBayar << endl;
            fileStruk << sep2 << endl;
            
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
        string rute = daftarJadwal[i].asal + "-" + daftarJadwal[i].tujuan;
        string waktu = daftarJadwal[i].jamBerangkat + "-" + daftarJadwal[i].jamTiba;
        
        cout << left << setw(10) << daftarJadwal[i].kode
             << setw(20) << daftarJadwal[i].maskapai
             << setw(22) << rute
             << setw(15) << waktu
             << "Rp " << setw(12) << daftarJadwal[i].hargaEkonomi
             << daftarJadwal[i].sisaKursi() << endl;
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

void mainMenu(){
    int pilihan;
    do
    {
        titleScreen("Menu Sistem Reservasi");
        cout << "1. Lihat Daftar Penerbangan" << endl
             << "2. Pesan Tiket" << endl
             << "3. Kelola Pesanan" << endl
             << "4. Keluar" << endl
             << "Pilih menu: "; 
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                lihatDaftarPenerbangan();
                break;
            case 2:
                pesanTiket();
                break;
            case 3:
                laporanPesanan();
                break;
            case 4:
                cout << "Keluar dari program. Terima kasih!\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 4);
}

int main() {
    DataDummy();
    mainMenu();
    return 0;
}