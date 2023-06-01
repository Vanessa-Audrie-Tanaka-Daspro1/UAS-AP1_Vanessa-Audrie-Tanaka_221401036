/*Program ini dapat membuat catatan baru, melihat semua judul catatan yang ada beserta waktu pembuatannya, melihat isi dari suatu catatan, mengubah catatan,
serta menghapus catatan yang ada berdasarkan inputan dari user*/

#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <limits>

using namespace std;

//fungsi tambahan untuk merapikan tampilan terminal
void drawLine(int n) {
    for (int i=0; i<n; i++)
        cout << "-";
    cout << "\n";
}

//kita buat class Catatan yang di dalam kelas public yang berisis struct, karena akan dipakai oleh class lain
class Catatan {
public:
    string judul;
    string isi;
    time_t waktuDibuat;
};

//kita buat class baru untuk untuk Note
class Note {
//kita buat vector struct baru sebagai private agar tidak bisa diakses kelas lain, karena berisi data data catatan
private:
    vector<Catatan> daftarCatatan;

//fungsi fungsi kita buat sebagai public untuk diakses secara universal
public:
  //Menampilkan daftar catatan
  void tampilkanListCatatan(){
    cout << "[List Catatan Anda]"<< endl;
    for (size_t i = 0; i < daftarCatatan.size(); ++i) {
        cout << i + 1 << ". " << daftarCatatan[i].judul << endl;
        cout << "Dibuat pada: " << asctime(localtime(&daftarCatatan[i].waktuDibuat)) << endl;
    }     
  }

//fungsi untuk menampilkan catatan, di mana akan menampilkan data data dari vektor penyimpanan
void tampilkanCatatan() {
    int nomorCatatan;
    tampilkanListCatatan();
    cout << "Pilih catatan untuk ditampilkan: ";
    cin >> nomorCatatan;
    drawLine(40);

    //Cek apakah nomornya valid atau tidak
    if (nomorCatatan <= 0 || nomorCatatan > daftarCatatan.size()) {
        cout << "Nomor catatan tidak valid. Operasi dibatalkan." << endl;
        return;
    }

    //Menampilkan catatan yg dipilih
    cout << daftarCatatan[nomorCatatan - 1].judul << endl;
    cout << "Dibuat pada: " << asctime(localtime(&daftarCatatan[nomorCatatan - 1].waktuDibuat)) << '\n'
         << daftarCatatan[nomorCatatan - 1].isi << endl;
}

//fungsi untuk menambah catatan, menambahkan sebuah struct baru ke dalam vector setiap kali funsgi ini dipanggil
void tambahCatatan() {
        string judulCatatan, isiCatatan;
        cout << "Masukkan Judul Catatan Baru: ";
        cin.ignore();  //gunakan cin.ignore biar tidak ke samping
        getline(cin, judulCatatan);
        cout << "Masukkan Isi Catatan: \n";
        getline(cin, isiCatatan);
        daftarCatatan.push_back(Catatan{ judulCatatan, isiCatatan, time(nullptr) });
        cout << endl;
        cout << " [catatan ditambahkan]" << endl;
    }

//fungsi untuk mengubah catatan, kalau ini dipanggil akan diminta nomor catatannya, lalu dari nomor tersebut akan diubah struct isi nya
void ubahCatatan() {
        int nomorCatatan;
        string isiBaru;
        tampilkanListCatatan();
        
        cout << "Masukkan nomor catatan yang ingin diubah: ";
        cin >> nomorCatatan;
            
        // Jika nomorCatatan tidak valid, operasi dibatalkan
         if (nomorCatatan <= 0 || nomorCatatan > daftarCatatan.size()) {
            cout << "Nomor catatan tidak valid. Operasi dibatalkan." << endl;
            return;
            }

        cout << "Masukkan isi baru catatan ke-" << nomorCatatan << " : \n";
        cin.ignore();
        getline(cin, isiBaru);
        daftarCatatan[nomorCatatan - 1].isi = isiBaru;
        cout << endl;
        cout << "[catatan telah diubah]" << endl;
        
}

//fungsi untuk hapus catatan, user memasukkan nomor catatannya, lalu struct nya yang ada dalam vector kita hapus
void hapusCatatan() {
    int nomorCatatan;
    char konfirmasi;
    tampilkanListCatatan();
    cout << "Masukkan nomor catatan yang ingin dihapus: ";
    cin >> nomorCatatan;

    if (nomorCatatan <= 0 || nomorCatatan > daftarCatatan.size()) {
        cout << "Nomor catatan tidak valid. Operasi dibatalkan." << endl;
        return;
    }

    cout << "Anda yakin ingin menghapus catatan nomor " << nomorCatatan <<"? (y/n): ";
    cin >> konfirmasi;

    if (konfirmasi == 'y' || konfirmasi == 'Y') {
        daftarCatatan.erase(daftarCatatan.begin() + nomorCatatan - 1);
        cout << "Catatan anda telah terhapus" << endl;
    } else {
        cout << "Operasi dibatalkan." << endl;
    }
}
};

int main() {
    Note notes;
    int opsi;
    bool loop = true;

    while (loop == true) {
        drawLine(40);
        cout << "          MENU UTAMA CATATAN\n";
        drawLine(40);
        cout << "\n1. Tambah Catatan\n";
        cout << "2. Lihat Catatan\n";
        cout << "3. Ubah Catatan\n";
        cout << "4. Hapus Catatan\n";
        cout << "5. Keluar\n\n";
        cout << "Masukkan Nomor : ";
        cin >> opsi;

        // Jika inputan error, kita akan menghentikan program agar tidak loop terus menerus menggunakan header <limits>
        if (cin.fail()) {
            // Hapus state error
            cin.clear();
            // Kita ignore seluruh yang diinputkan
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            // Kemudian kita kirim pesan ke user
            cout << "\nInput Error! Masukkan nomor yang valid!\n";
            continue;
        }

        cout<< "\n";

        switch (opsi) {
            case 1: {
                notes.tambahCatatan();
                break;
            }

            case 2: {
                notes.tampilkanCatatan();
                break;
            }

            case 3: {
                notes.ubahCatatan();
                break;
            }

            case 4: {
                notes.hapusCatatan();
                break;
            }

            case 5: {
                drawLine(45);
                cout << "Terima kasih telah menggunakan program ini!"<<endl;
                drawLine(45);
                loop = false;
                break;
            }
            default:
                cout << "Masukkan nomor yang valid!\n";
        }
    }

    return 0;
}