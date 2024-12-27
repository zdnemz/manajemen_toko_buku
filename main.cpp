#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <functional>
#include <limits>

using namespace std;

void baca_data(const string filename, function<void(ifstream &)> callback)
{
    ifstream file(filename);

    if (file.is_open())
    {
        callback(file);
        file.close();
    }
}

void simpan_data(const string filename, function<void(ofstream &)> callback)
{
    ofstream file(filename);

    if (file.is_open())
    {
        callback(file);
        file.close();
    }
}

void validasi_numeric_input(function<void()> callback)
{
    if (cin.fail())
    {

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "====================================================================" << endl;
        callback();
        return;
    }

    return;
}

struct Buku
{
    string judul;
    string penulis;
    string penerbit;
    float harga;
    int tahun_terbit;
};

vector<Buku> daftar_buku;

void simpan_data_buku()
{
    simpan_data("data_buku.txt", [&](ofstream &file)
                {
                    for (int i = 0; i < daftar_buku.size(); i++)
                    {
                        file << daftar_buku[i].judul << " " << daftar_buku[i].penulis << " " << daftar_buku[i].penerbit << " " << daftar_buku[i].harga << " " << daftar_buku[i].tahun_terbit << endl;
                    } });
}

void cetak_data_buku()
{
    if (daftar_buku.empty())
    {
        cout << "|                          Data buku kosong                        |" << endl;
        cout << "====================================================================" << endl;
        return;
    }
    for (int i = 0; i < daftar_buku.size(); i++)
    {
        cout << "Index : " << i + 1 << endl;
        cout << "Judul : " << daftar_buku[i].judul << endl;
        cout << "Penulis : " << daftar_buku[i].penulis << endl;
        cout << "Penerbit : " << daftar_buku[i].penerbit << endl;
        cout << "Harga : " << daftar_buku[i].harga << endl;
        cout << "Tahun Terbit : " << daftar_buku[i].tahun_terbit << endl;
        cout << "====================================================================" << endl;
    }
}

void tambah_data_buku()
{
    Buku buku;
    cout << "Judul : ";
    cin.ignore();
    getline(cin, buku.judul);
    cout << "Penulis : ";
    getline(cin, buku.penulis);
    cout << "Penerbit : ";
    getline(cin, buku.penerbit);
    cout << "Harga : ";
    cin >> buku.harga;
    validasi_numeric_input([&]()
                           {
        cout << "Input harga tidak valid. Silakan coba lagi." << endl;
        return
        tambah_data_buku(); });
    cout << "Tahun Terbit : ";
    cin >> buku.tahun_terbit;
    validasi_numeric_input([&]()
                           {
        cout << "Input tahun tidak valid. Silakan coba lagi." << endl;
        return
        tambah_data_buku(); });

    daftar_buku.push_back(buku);
    cout << "====================================================================" << endl;
    cout << "|                     Data Buku Berhasil ditambah                  |" << endl;
    cout << "====================================================================" << endl;

    simpan_data_buku();
}

void ubah_data_buku()
{
    cetak_data_buku();

    int index;
    cout << "Masukkan index buku yang ingin diubah: ";
    cin >> index;
    validasi_numeric_input([&]()
                           {
        cout << "Input index tidak valid. Silakan coba lagi." << endl;
        return
        ubah_data_buku(); });

    if (index < 1 || index > daftar_buku.size())
    {
        cout << "Index buku tidak valid." << endl;
        return;
    }

    Buku buku;
    cout << "Judul : ";
    cin.ignore();
    getline(cin, buku.judul);
    cout << "Penulis : ";
    getline(cin, buku.penulis);
    cout << "Penerbit : ";
    getline(cin, buku.penerbit);
    cout << "Harga : ";
    cin >> buku.harga;
    validasi_numeric_input([&]()
                           {
        cout << "Input harga tidak valid. Silakan coba lagi." << endl;
        return
        ubah_data_buku(); });
    cout << "Tahun Terbit : ";
    cin >> buku.tahun_terbit;
    validasi_numeric_input([&]()
                           {
        cout << "Input tahun tidak valid. Silakan coba lagi." << endl;
        return
        ubah_data_buku(); });

    daftar_buku[index - 1] = buku;
    cout << "====================================================================" << endl;
    cout << "|                      Data Buku Berhasil Diubah                   |" << endl;
    cout << "====================================================================" << endl;

    simpan_data_buku();
}

void hapus_data_buku()
{
    cetak_data_buku();

    int index;
    cout << "Masukkan index buku yang ingin dihapus: ";
    cin >> index;
    validasi_numeric_input([&]()
                           {
        cout << "Input index tidak valid. Silakan coba lagi." << endl;
        return
        hapus_data_buku(); });

    if (index < 1 || index > daftar_buku.size())
    {
        cout << "Index buku tidak valid." << endl;
        return;
    }

    daftar_buku.erase(daftar_buku.begin() + index - 1);

    cout << "====================================================================" << endl;
    cout << "|                      Data Buku Berhasil Dihapus                  |" << endl;
    cout << "====================================================================" << endl;

    simpan_data_buku();
}

void data_buku()
{
    baca_data("data_buku.txt", [&](ifstream &file)
              {
                  Buku buku;
                  while (file >> buku.judul >> buku.penulis >> buku.penerbit >> buku.harga >> buku.tahun_terbit)
                  {
                      daftar_buku.push_back(buku);
                  } });

    do
    {

        int pilihan;

        cout << "====================================================================" << endl;
        cout << "|                       Manajemen Data Buku                        |" << endl;
        cout << "====================================================================" << endl;
        cout << "|  1. Cetak Data Buku                                              |" << endl;
        cout << "|  2. Tambah Data Buku                                             |" << endl;
        cout << "|  3. Ubah Data Buku                                               |" << endl;
        cout << "|  4. Hapus Data Buku                                              |" << endl;
        cout << "|  5. Kembali                                                      |" << endl;
        cout << "====================================================================" << endl;
        cout << "Masukkan Pilihan : ";
        cin >> pilihan;

        if (pilihan == 1)
        {
            cout << "====================================================================" << endl;
            cout << "|                             Data Buku                            |" << endl;
            cout << "====================================================================" << endl;

            cetak_data_buku();
        }
        else if (pilihan == 2)
        {
            cout << "====================================================================" << endl;
            cout << "|                          Tambah Data Buku                        |" << endl;
            cout << "====================================================================" << endl;

            tambah_data_buku();
        }
        else if (pilihan == 3)
        {
            cout << "====================================================================" << endl;
            cout << "|                            Ubah Data Buku                        |" << endl;
            cout << "====================================================================" << endl;
            ubah_data_buku();
        }
        else if (pilihan == 4)
        {
            cout << "====================================================================" << endl;
            cout << "|                            Hapus Data Buku                       |" << endl;
            cout << "====================================================================" << endl;
            hapus_data_buku();
        }
        else if (pilihan == 5)
        {
            break;
        }
        else
        {
            cout << "Pilihan Tidak Tersedia" << endl;
        }

    } while (true);
}

struct Pelanggan
{
    string nama;
    string alamat;
    string nomor_telpon;
    string email;
    string sejarah_pembelian;
};

vector<Pelanggan> daftar_pelanggan;

void simpan_data_pelanggan()
{
    simpan_data("data_pelanggan.txt", [&](ofstream &file)
                {
                    for (int i = 0; i < daftar_pelanggan.size(); i++)
                    {
                        file << daftar_pelanggan[i].nama << " " << daftar_pelanggan[i].alamat << " "
                             << daftar_pelanggan[i].nomor_telpon << " " << daftar_pelanggan[i].email << " "
                             << daftar_pelanggan[i].sejarah_pembelian << endl;
                    } });
}

void cetak_data_pelanggan()
{
    if (daftar_pelanggan.empty())
    {
        cout << "|                        Data pelanggan kosong                     |" << endl;
        cout << "====================================================================" << endl;
        return;
    }

    for (int i = 0; i < daftar_pelanggan.size(); i++)
    {
        cout << "Index : " << i + 1 << endl;
        cout << "Nama : " << daftar_pelanggan[i].nama << endl;
        cout << "Alamat : " << daftar_pelanggan[i].alamat << endl;
        cout << "Nomor Telepon : " << daftar_pelanggan[i].nomor_telpon << endl;
        cout << "Email : " << daftar_pelanggan[i].email << endl;
        cout << "Sejarah Pembelian : " << daftar_pelanggan[i].sejarah_pembelian << endl;
        cout << "====================================================================" << endl;
    }
}

void ubah_data_pelanggan()
{
    cetak_data_pelanggan();

    int index;
    cout << "Masukkan index pelanggan yang ingin diubah: ";
    cin >> index;
    validasi_numeric_input([&]()
                           {
        cout << "Input index tidak valid. Silakan coba lagi." << endl;
        return
        ubah_data_pelanggan(); });

    if (index < 1 || index > daftar_pelanggan.size())
    {
        cout << "Index pelanggan tidak valid." << endl;
        return;
    }

    Pelanggan pelanggan;
    cout << "Nama : ";
    cin.ignore();
    getline(cin, pelanggan.nama);
    cout << "Alamat : ";
    getline(cin, pelanggan.alamat);
    cout << "Nomor Telepon : ";
    getline(cin, pelanggan.nomor_telpon);
    cout << "Email : ";
    getline(cin, pelanggan.email);
    cout << "Sejarah Pembelian : ";
    getline(cin, pelanggan.sejarah_pembelian);

    daftar_pelanggan[index - 1] = pelanggan;
    cout << "====================================================================" << endl;
    cout << "|                     Data Pelanggan Berhasil Diubah               |" << endl;
    cout << "====================================================================" << endl;

    simpan_data_pelanggan();
}

void tambah_data_pelanggan()
{
    Pelanggan pelanggan;
    cout << "Nama : ";
    cin.ignore();
    getline(cin, pelanggan.nama);
    cout << "Alamat : ";
    getline(cin, pelanggan.alamat);
    cout << "Nomor Telepon : ";
    getline(cin, pelanggan.nomor_telpon);
    cout << "Email : ";
    getline(cin, pelanggan.email);
    cout << "Sejarah Pembelian : ";
    getline(cin, pelanggan.sejarah_pembelian);

    daftar_pelanggan.push_back(pelanggan);

    cout << "====================================================================" << endl;
    cout << "|                  Data Pelanggan Berhasil Ditambah                |" << endl;
    cout << "====================================================================" << endl;

    simpan_data_pelanggan();
}

void hapus_data_pelanggan()
{
    cetak_data_pelanggan();

    int index;
    cout << "Masukkan index pelanggan yang ingin dihapus: ";
    cin >> index;
    validasi_numeric_input([&]()
                           {
        cout << "Input index tidak valid. Silakan coba lagi." << endl;
        return
        hapus_data_pelanggan(); });

    if (index < 1 || index > daftar_pelanggan.size())
    {
        cout << "Index pelanggan tidak valid." << endl;
        return;
    }

    daftar_pelanggan.erase(daftar_pelanggan.begin() + index - 1);

    cout << "====================================================================" << endl;
    cout << "|                    Data Pelanggan Berhasil Dihapus               |" << endl;
    cout << "====================================================================" << endl;

    simpan_data_pelanggan();
}

void data_pelanggan()
{
    baca_data("data_pelanggan.txt", [&](ifstream &file)
              {
                  Pelanggan pelanggan;
                  while (file >> pelanggan.nama >> pelanggan.alamat >> pelanggan.nomor_telpon >> pelanggan.email >> pelanggan.sejarah_pembelian)
                  {
                      daftar_pelanggan.push_back(pelanggan);
                  } });

    do
    {
        int pilihan;

        cout << "====================================================================" << endl;
        cout << "|                      Manajemen Data Pelanggan                    |" << endl;
        cout << "====================================================================" << endl;
        cout << "|  1. Cetak Data Pelanggan                                         |" << endl;
        cout << "|  2. Tambah Data Pelanggan                                        |" << endl;
        cout << "|  3. Ubah Data Pelanggan                                          |" << endl;
        cout << "|  4. Hapus Data Pelanggan                                         |" << endl;
        cout << "|  5. Kembali                                                      |" << endl;
        cout << "====================================================================" << endl;
        cout << "Masukkan Pilihan : ";
        cin >> pilihan;

        if (pilihan == 1)
        {
            cout << "====================================================================" << endl;
            cout << "|                             Data Pelanggan                       |" << endl;
            cout << "====================================================================" << endl;

            cetak_data_pelanggan();
        }
        else if (pilihan == 2)
        {
            cout << "====================================================================" << endl;
            cout << "|                          Tambah Data Pelanggan                   |" << endl;
            cout << "====================================================================" << endl;
            tambah_data_pelanggan();
        }
        else if (pilihan == 3)
        {
            cout << "====================================================================" << endl;
            cout << "|                            Ubah Data Pelanggan                   |" << endl;
            cout << "====================================================================" << endl;

            ubah_data_pelanggan();
        }
        else if (pilihan == 4)
        {
            cout << "====================================================================" << endl;
            cout << "|                            Hapus Data Pelanggan                  |" << endl;
            cout << "====================================================================" << endl;
            hapus_data_pelanggan();
        }
        else if (pilihan == 5)
        {
            break;
        }
        else
        {
            cout << "Pilihan Tidak Tersedia" << endl;
        }
    } while (true);
}

struct Penjualan
{
    string nama_barang;
    float harga_barang;
    int jumlah_barang;
    float total_harga;
    string tanggal_penjualan;
};

vector<Penjualan> daftar_penjualan;

void simpan_data_penjualan()
{
    simpan_data("data_penjualan.txt", [&](ofstream &file)
                {
                    for (int i = 0; i < daftar_penjualan.size(); i++)
                    {
                        file << daftar_penjualan[i].nama_barang << " " << daftar_penjualan[i].harga_barang << " "
                             << daftar_penjualan[i].jumlah_barang << " " << daftar_penjualan[i].total_harga << " "
                             << daftar_penjualan[i].tanggal_penjualan << endl;
                    } });
}

void cetak_data_penjualan()
{
    if (daftar_penjualan.empty())
    {
        cout << "|                        Data penjualan kosong                     |" << endl;
        cout << "====================================================================" << endl;
        return;
    }

    for (int i = 0; i < daftar_penjualan.size(); i++)
    {
        cout << "Index : " << i + 1 << endl;
        cout << "Nama Barang : " << daftar_penjualan[i].nama_barang << endl;
        cout << "Harga Barang : " << daftar_penjualan[i].harga_barang << endl;
        cout << "Jumlah Barang : " << daftar_penjualan[i].jumlah_barang << endl;
        cout << "Total Harga : " << daftar_penjualan[i].total_harga << endl;
        cout << "Tanggal Penjualan : " << daftar_penjualan[i].tanggal_penjualan << endl;
        cout << "====================================================================" << endl;
    }
}

void ubah_data_penjualan()
{
    cetak_data_penjualan();

    int index;
    cout << "Masukkan index penjualan yang ingin diubah: ";
    cin >> index;
    validasi_numeric_input([&]()
                           {
        cout << "Input index tidak valid. Silakan coba lagi." << endl;
        return
        ubah_data_penjualan(); });

    if (index < 1 || index > daftar_penjualan.size())
    {
        cout << "Index penjualan tidak valid." << endl;
        return;
    }

    Penjualan penjualan;
    cout << "Nama Barang : ";
    cin.ignore();
    getline(cin, penjualan.nama_barang);

    cout << "Harga Barang : ";
    cin >> penjualan.harga_barang;
    validasi_numeric_input([&]()
                           {
        cout << "Input harga tidak valid. Silakan coba lagi." << endl;
        return
        ubah_data_penjualan(); });

    cout << "Jumlah Barang : ";
    cin >> penjualan.jumlah_barang;
    validasi_numeric_input([&]()
                           {
        cout << "Input jumlah tidak valid. Silakan coba lagi." << endl;
        return
        ubah_data_penjualan(); });

    cout << "Tanggal Penjualan : ";
    cin.ignore();
    getline(cin, penjualan.tanggal_penjualan);

    penjualan.total_harga = penjualan.harga_barang * penjualan.jumlah_barang;

    daftar_penjualan[index - 1] = penjualan;
    cout << "====================================================================" << endl;
    cout << "|                     Data Penjualan Berhasil Diubah               |" << endl;
    cout << "====================================================================" << endl;

    simpan_data_penjualan();
}

void tambah_data_penjualan()
{
    Penjualan penjualan;
    cout << "Nama Barang : ";
    cin.ignore();
    getline(cin, penjualan.nama_barang);

    cout << "Harga Barang : ";
    cin >> penjualan.harga_barang;
    validasi_numeric_input([&]()
                           {
        cout << "Input harga tidak valid. Silakan coba lagi." << endl;
        return
        tambah_data_penjualan(); });

    cout << "Jumlah Barang : ";
    cin >> penjualan.jumlah_barang;
    validasi_numeric_input([&]()
                           {
        cout << "Input jumlah tidak valid. Silakan coba lagi." << endl;
        return
        tambah_data_penjualan(); });

    cout << "Tanggal Penjualan : ";
    cin.ignore();
    getline(cin, penjualan.tanggal_penjualan);

    penjualan.total_harga = penjualan.harga_barang * penjualan.jumlah_barang;

    daftar_penjualan.push_back(penjualan);
    simpan_data_penjualan();

    cout << "====================================================================" << endl;
    cout << "|                 Data Penjualan Berhasil Ditambah                 |" << endl;
    cout << "====================================================================" << endl;
}

void hapus_data_penjualan()
{
    cetak_data_penjualan();

    int index;
    cout << "Masukkan index penjualan yang ingin dihapus: ";
    cin >> index;
    validasi_numeric_input([&]()
                           {
        cout << "Input index tidak valid. Silakan coba lagi." << endl;
        return
        hapus_data_penjualan(); });

    if (index < 1 || index > daftar_penjualan.size())
    {
        cout << "Index penjualan tidak valid." << endl;
        return;
    }

    daftar_penjualan.erase(daftar_penjualan.begin() + index - 1);

    cout << "====================================================================" << endl;
    cout << "|                    Data Penjualan Berhasil Dihapus               |" << endl;
    cout << "====================================================================" << endl;

    simpan_data_penjualan();
}

void data_penjualan()
{
    baca_data("data_penjualan.txt", [&](ifstream &file)
              {
                  Penjualan penjualan;
                  while (file >> penjualan.nama_barang >> penjualan.harga_barang >> penjualan.jumlah_barang >> penjualan.total_harga >> penjualan.tanggal_penjualan)
                  {
                      daftar_penjualan.push_back(penjualan);
                  } });

    do
    {
        int pilihan;

        cout << "====================================================================" << endl;
        cout << "|                      Manajemen Data Penjualan                    |" << endl;
        cout << "====================================================================" << endl;
        cout << "|  1. Cetak Data Penjualan                                         |" << endl;
        cout << "|  2. Tambah Data Penjualan                                        |" << endl;
        cout << "|  3. Ubah Data Penjualan                                          |" << endl;
        cout << "|  4. Hapus Data Penjualan                                         |" << endl;
        cout << "|  5. Kembali                                                      |" << endl;
        cout << "====================================================================" << endl;
        cout << "Masukkan Pilihan : ";
        cin >> pilihan;

        if (pilihan == 1)
        {
            cout << "====================================================================" << endl;
            cout << "|                             Data Penjualan                       |" << endl;
            cout << "====================================================================" << endl;

            cetak_data_penjualan();
        }
        else if (pilihan == 2)
        {
            cout << "====================================================================" << endl;
            cout << "|                          Tambah Data Penjualan                   |" << endl;
            cout << "====================================================================" << endl;
            tambah_data_penjualan();
        }
        else if (pilihan == 3)
        {
            cout << "====================================================================" << endl;
            cout << "|                            Ubah Data Penjualan                   |" << endl;
            cout << "====================================================================" << endl;

            ubah_data_penjualan();
        }
        else if (pilihan == 4)
        {
            cout << "====================================================================" << endl;
            cout << "|                            Hapus Data Pelanggan                  |" << endl;
            cout << "====================================================================" << endl;
            hapus_data_penjualan();
        }
        else if (pilihan == 5)
        {
            break;
        }
        else
        {
            cout << "Pilihan Tidak Tersedia" << endl;
        }
    } while (true);
}

int main()
{
    do
    {
        daftar_buku.clear();
        daftar_pelanggan.clear();
        daftar_penjualan.clear();

        int pilihan;
        string lanjut;

        cout << "====================================================================" << endl;
        cout << "|                  Projek Manajemen Data Toko Buku                 |" << endl;
        cout << "====================================================================" << endl;
        cout << "|  1. Data Buku                                                    |" << endl;
        cout << "|  2. Data Pelanggan                                               |" << endl;
        cout << "|  3. Data Penjualan                                               |" << endl;
        cout << "|  4. Data Penerbit                                                |" << endl;
        cout << "====================================================================" << endl;
        cout << "Masukkan Pilihan : ";
        cin >> pilihan;

        if (pilihan == 1)
        {
            data_buku();
        }
        else if (pilihan == 2)
        {
            data_pelanggan();
        }
        else if (pilihan == 3)
        {
            data_penjualan();
        }
        else if (pilihan == 4)
        {
            cout << "Data Penerbit" << endl;
        }
        else
        {
            cout << "Pilihan Tidak Tersedia" << endl;
        }

        cout << "====================================================================" << endl;
        cout << "Lanjutkan? (y/n): ";
        cin >> lanjut;

        if (lanjut == "n" || lanjut == "N")
        {
            cout << "====================================================================" << endl;
            break;
        }

    } while (true);

    return 0;
}