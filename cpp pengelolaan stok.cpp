#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <numeric> // Untuk fungsi accumulate

using namespace std;

struct Item {
    string nama;
    string jenis; // "Bahan Baku", "Setengah Jadi", "Produk Jadi"
    int stok;
    vector<int> konsumsiHarian; // Riwayat konsumsi untuk prediksi
};

void tampilkanMenu() {
    cout << "\nMenu:\n";
    cout << "1. Tambah Barang\n";
    cout << "2. Tambah Stok\n";
    cout << "3. Kurangi Stok\n";
    cout << "4. Tampilkan Stok\n";
    cout << "5. Prediksi Kebutuhan Stok\n";
    cout << "6. Integrasi Pemasok\n";
    cout << "7. Keluar\n";
    cout << "Pilih opsi: ";
}

int prediksiKebutuhan(const vector<int>& konsumsiHarian) {
    if (konsumsiHarian.empty()) return 0;
    int total = accumulate(konsumsiHarian.begin(), konsumsiHarian.end(), 0);
    return total / konsumsiHarian.size();  // Menghitung rata-rata konsumsi
}

int main() {
    vector<Item> gudang;
    map<string, string> pemasok = {
        {"Bahan Baku", "Pemasok A"},
        {"Setengah Jadi", "Pemasok B"},
        {"Produk Jadi", "Pemasok C"}
    };
    int pilihan;

    do {
        tampilkanMenu();
        cin >> pilihan;

        if (pilihan == 1) {
            Item item;
            cout << "Masukkan nama barang: ";
            cin.ignore();  // Membersihkan buffer sebelum getline
            getline(cin, item.nama);  // Menggunakan getline untuk membaca nama dengan spasi
            cout << "Masukkan jenis barang (Bahan Baku/Setengah Jadi/Produk Jadi): ";
            cin >> item.jenis;
            item.stok = 0;
            gudang.push_back(item);
            cout << "Barang berhasil ditambahkan.\n";
        } else if (pilihan == 2) {
            string nama;
            int jumlah;
            cout << "Masukkan nama barang: ";
            cin.ignore();  // Membersihkan buffer sebelum getline
            getline(cin, nama);  // Menggunakan getline untuk membaca nama dengan spasi
            auto it = find_if(gudang.begin(), gudang.end(), [&](const Item& item) { return item.nama == nama; });
            if (it != gudang.end()) {
                cout << "Masukkan jumlah stok yang ditambahkan: ";
                cin >> jumlah;
                it->stok += jumlah;
                cout << "Stok berhasil ditambahkan.\n";
            } else {
                cout << "Barang tidak ditemukan.\n";
            }
        } else if (pilihan == 3) {
            string nama;
            int jumlah;
            cout << "Masukkan nama barang: ";
            cin.ignore();  // Membersihkan buffer sebelum getline
            getline(cin, nama);  // Menggunakan getline untuk membaca nama dengan spasi
            auto it = find_if(gudang.begin(), gudang.end(), [&](const Item& item) { return item.nama == nama; });
            if (it != gudang.end()) {
                cout << "Masukkan jumlah stok yang dikurangi: ";
                cin >> jumlah;
                if (it->stok >= jumlah) {
                    it->stok -= jumlah;
                    it->konsumsiHarian.push_back(jumlah);  // Menambahkan konsumsi harian
                    cout << "Stok berhasil dikurangi.\n";
                } else {
                    cout << "Stok tidak mencukupi.\n";
                }
            } else {
                cout << "Barang tidak ditemukan.\n";
            }
        } else if (pilihan == 4) {
            cout << "\nDaftar Stok Barang:\n";
            for (const auto& item : gudang) {
                cout << "Barang: " << item.nama << ", Jenis: " << item.jenis << ", Stok: " << item.stok << "\n";
            }
        } else if (pilihan == 5) {
            cout << "\nPrediksi Kebutuhan Stok:\n";
            for (const auto& item : gudang) {
                int prediksi = prediksiKebutuhan(item.konsumsiHarian);
                cout << "Barang: " << item.nama << ", Kebutuhan Harian (rata-rata): " << prediksi << "\n";
            }
        } else if (pilihan == 6) {
            cout << "\nIntegrasi Pemasok:\n";
            for (const auto& item : gudang) {
                if (item.stok < 10) {
                    auto pemasokIt = pemasok.find(item.jenis);
                    if (pemasokIt != pemasok.end()) {
                        cout << "Barang: " << item.nama << " memiliki stok rendah. Hubungi " 
                             << pemasokIt->second << " untuk pemesanan.\n";
                    } else {
                        cout << "Tidak ada pemasok untuk jenis barang: " << item.jenis << "\n";
                    }
                }
            }
        } else if (pilihan != 7) {
            cout << "Pilihan tidak valid.\n";
        }

    } while (pilihan != 7);

    cout << "Program selesai.\n";
    return 0;
}