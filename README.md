# Sistem Reservasi Tiket Pesawat

Program manajemen pemesanan tiket pesawat berbasis terminal yang dibuat menggunakan bahasa C++.

---

## Fitur

### Mode Admin
| No | Menu | Keterangan |
|----|------|------------|
| 1 | Tambah Daftar Penerbangan | Menambahkan data penerbangan baru |
| 2 | Cari Daftar Penerbangan | Mencari penerbangan berdasarkan kode atau rute |
| 3 | Lihat Daftar Penerbangan | Menampilkan seluruh daftar penerbangan |
| 4 | Edit Daftar Penerbangan | Mengubah data penerbangan yang sudah ada |
| 5 | Hapus Daftar Penerbangan | Menghapus data penerbangan |

### Mode User
| No | Menu | Keterangan |
|----|------|------------|
| 1 | Lihat Daftar Penerbangan | Menampilkan penerbangan yang tersedia |
| 2 | Pesan Tiket | Melakukan pemesanan tiket |
| 3 | Kelola Pesanan | Melihat atau membatalkan pesanan |
| 4 | Laporan | Melihat riwayat dan rekap pemesanan |

---

## Struktur File

```
project/
├── main.cpp
├── jadwal.h / jadwal.cpp       # Data & logika penerbangan
├── pemesanan.h / pemesanan.cpp # Data & logika pemesanan tiket
├── maskapai.h / maskapai.cpp   # Data maskapai
└── utility/
    ├── utils.h / utils.cpp     # Fungsi bantu umum
```

---

## Cara Kompilasi & Menjalankan

```bash
g++ main.cpp jadwal.cpp pemesanan.cpp maskapai.cpp utility/utils.cpp -o reservasi

./reservasi
```

---

## Teknologi

- **Bahasa:** C++
- **Paradigma:** Procedural
- **Struktur Data:** Array of Struct
- **Algoritma:** Sequential Search, Sorting

---

## Dibuat untuk

Proyek Akhir Praktikum — Mata Kuliah Algoritma dan Pemrograman Lanjut