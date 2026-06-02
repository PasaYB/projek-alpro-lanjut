#ifndef JADWAL_H
#define JADWAL_H

#include <string>

struct Jadwal {
    std::string kode;          // contoh: "GA-101"
    std::string maskapai;      // contoh: "Garuda Indonesia"
    std::string asal;          // contoh: "Jakarta"
    std::string tujuan;        // contoh: "Bali"
    std::string tanggal;       // contoh: "2025-06-10"
    std::string jamBerangkat;  // contoh: "08:00"
    std::string jamTiba;       // contoh: "09:30"
    int totalKursi;       // total kapasitas pesawat
    int kursiTerisi;      // sudah berapa yang dipesan
    float hargaEkonomi;   // harga kelas ekonomi
    float hargaBisnis;    // harga kelas bisnis

    int sisaKursi(Jadwal f) {
        return f.totalKursi - f.kursiTerisi;
    }
};

#endif