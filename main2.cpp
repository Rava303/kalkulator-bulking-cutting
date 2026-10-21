#include <iostream>
#include <string>
#include <fstream> // <-- BARU: untuk baca/tulis file
#include <iomanip>
#include <cmath>
using namespace std;

// Nama file tempat data disimpan (ada di folder yang sama dengan program dijalankan)
const string NAMA_FILE = "data_kalori.txt";

struct dataPilihan
{
    int d_dada_ayam = 0;
    int d_telur_rebus = 0;
    int d_ikan_tuna = 0;
    int d_tempe = 0;
    int d_nasi = 0;
    int d_tahu = 0;
    int berat_badan = 0;
    int tinggi_badan = 0;
    int umur = 0;
    char jenis_kelamin = ' ';
    int tingkat_aktivitas = 0;
};

struct proteinLauk
{
    float p_dada_ayam = 0.31;
    float p_telur_rebus = 0.13;
    float p_ikan_tuna = 0.23;
    float p_tempe = 0.18;
    float p_nasi = 0.026;
    float p_tahu = 0.08;
};

struct kaloriLauk
{
    float k_dada_ayam = 1.65;
    float k_telur_rebus = 1.55;
    float k_ikan_tuna = 1.32;
    float k_tempe = 1.92;
    float k_nasi = 1.30;
    float k_tahu = 0.76;
};

// ======================= FUNGSI SIMPAN & MUAT =======================

// Menulis semua isi struct ke file. Dipanggil setiap ada perubahan data.
void simpanData(const dataPilihan &p)
{
    ofstream file(NAMA_FILE); // membuka file untuk ditulis (isi lama ditimpa)
    if (!file)
    {
        cout << "Peringatan: data gagal disimpan!" << endl;
        return;
    }
    file << p.berat_badan << " "
         << p.tinggi_badan << " "
         << p.umur << " "
         << p.jenis_kelamin << " "
         << p.tingkat_aktivitas << " "
         << p.d_dada_ayam << " "
         << p.d_telur_rebus << " "
         << p.d_ikan_tuna << " "
         << p.d_tempe << " "
         << p.d_nasi << " "
         << p.d_tahu << endl;
}

// Membaca file ke struct. Mengembalikan true jika berhasil.
bool muatData(dataPilihan &p)
{
    ifstream file(NAMA_FILE); // membuka file untuk dibaca
    if (!file)
    {
        return false; // file belum ada (pertama kali menjalankan program)
    }
    // urutan membaca HARUS sama dengan urutan menulis
    file >> p.berat_badan >> p.tinggi_badan >> p.umur >> p.jenis_kelamin >> p.tingkat_aktivitas >> p.d_dada_ayam >> p.d_telur_rebus >> p.d_ikan_tuna >> p.d_tempe >> p.d_nasi >> p.d_tahu;
    return !file.fail(); // false jika isi file rusak/tidak lengkap
}

// ======================= RUMUS =======================

float hitungProtein(int berat, float proteinPerGram)
{
    return berat * proteinPerGram;
}

float hitungKalori(int berat, float kaloriPerGram)
{
    return berat * kaloriPerGram;
}

float BMR_pria(int bb, int tb, int umur)
{
    return 66.5 + (13.7 * bb) + (5 * tb) - (6.8 * umur);
}

float BMR_wanita(int bb, int tb, int umur)
{
    return 655. + (9.6 * bb) + (1.8 * tb) - (4.7 * umur);
}

float TDEE(int BMR, int tingkat_aktivitas)
{
    if (tingkat_aktivitas == 1)
        return BMR * 1.2;
    else if (tingkat_aktivitas == 2)
        return BMR * 1.375;
    else if (tingkat_aktivitas == 3)
        return BMR * 1.55;
    else if (tingkat_aktivitas == 4)
        return BMR * 1.725;
    else
        return BMR * 1.2;
}

// Input data diri dipisah jadi fungsi supaya main lebih rapi
void inputDataDiri(dataPilihan &pilihan)
{
    cout << "--------Pengambilan data diri--------" << endl;
    cout << "Berat badan (kg): ";
    cin >> pilihan.berat_badan;
    cout << "Tinggi badan (cm): ";
    cin >> pilihan.tinggi_badan;
    cout << "Umur (tahun): ";
    cin >> pilihan.umur;
    cout << "Jenis Kelamin (L/P): ";
    cin >> pilihan.jenis_kelamin;
    cout << "Seberapa aktif Anda dalam berolahraga? (1-4)" << endl;
    cout << "1. jarang olahraga" << endl;
    cout << "2. olahraga ringan (1-3 kali seminggu)" << endl;
    cout << "3. olahraga sedang (4-5 kali seminggu)" << endl;
    cout << "4. olahraga berat (6-7 kali seminggu)" << endl;
    cout << "pilihan Anda (1-4): ";
    cin >> pilihan.tingkat_aktivitas;
}

int main()
{
    dataPilihan pilihan;
    proteinLauk protein;
    kaloriLauk kalori;
    int pilih;

    cout << "==============================================================================" << endl;
    cout << "Selamat datang di program perhitungan protein dan kalori!" << endl;
    cout << "==============================================================================" << endl;

    // ---- Cek apakah ada data tersimpan dari sesi sebelumnya ----
    bool adaData = muatData(pilihan);
    if (adaData)
    {
        cout << endl;
        cout << "Data tersimpan ditemukan:" << endl;
        cout << "BB " << pilihan.berat_badan << " kg, TB " << pilihan.tinggi_badan
             << " cm, umur " << pilihan.umur << ", jenis kelamin " << pilihan.jenis_kelamin << endl;
        cout << "Makanan tercatat (gram): ayam " << pilihan.d_dada_ayam
             << ", telur " << pilihan.d_telur_rebus
             << ", tuna " << pilihan.d_ikan_tuna
             << ", tempe " << pilihan.d_tempe
             << ", nasi " << pilihan.d_nasi
             << ", tahu " << pilihan.d_tahu << endl;
        cout << endl;
        cout << "1. Lanjutkan (tambah makanan ke data sebelumnya)" << endl;
        cout << "2. Mulai baru (hapus semua data)" << endl;
        cout << "Pilihan Anda: ";
        int mulai;
        cin >> mulai;
        if (mulai == 2)
        {
            pilihan = dataPilihan(); // reset semua ke nilai awal
            adaData = false;
        }
    }

    if (!adaData)
    {
        inputDataDiri(pilihan);
        simpanData(pilihan);
    }

    do
    {
        cout << endl;
        cout << "--------Makanan yang dikonsumsi--------" << endl;
        cout << endl;

        cout << "Pilih lauk yang ingin ditambahkan (1-6):" << endl;
        cout << "1. Dada Ayam" << endl;
        cout << "2. Telur Rebus" << endl;
        cout << "3. Ikan Tuna" << endl;
        cout << "4. Tempe" << endl;
        cout << "5. Nasi" << endl;
        cout << "6. Tahu" << endl;
        cout << "7. Hitung total protein dan kalori dari pilihan Anda." << endl;
        cout << "Masukkan pilihan Anda: ";
        cin >> pilih;

        int gram = 0;

        // Perhatikan: memakai += (bukan =) supaya berat BERTAMBAH,
        // bukan menimpa nilai sebelumnya.
        switch (pilih)
        {
        case 1:
            cout << "Masukkan berat dada ayam (gram): ";
            cin >> gram;
            pilihan.d_dada_ayam += gram;
            break;
        case 2:
            cout << "Masukkan berat telur rebus (gram): ";
            cin >> gram;
            pilihan.d_telur_rebus += gram;
            break;
        case 3:
            cout << "Masukkan berat ikan tuna (gram): ";
            cin >> gram;
            pilihan.d_ikan_tuna += gram;
            break;
        case 4:
            cout << "Masukkan berat tempe (gram): ";
            cin >> gram;
            pilihan.d_tempe += gram;
            break;
        case 5:
            cout << "Masukkan berat nasi (gram): ";
            cin >> gram;
            pilihan.d_nasi += gram;
            break;
        case 6:
            cout << "Masukkan berat tahu (gram): ";
            cin >> gram;
            pilihan.d_tahu += gram;
            break;
        }

        // Simpan setiap kali ada penambahan, jadi kalau program tertutup
        // mendadak data tetap aman.
        if (pilih >= 1 && pilih <= 6)
        {
            simpanData(pilihan);
            cout << "(data tersimpan)" << endl;
        }
    } while (pilih != 7);

    float totalProtein = hitungProtein(pilihan.d_dada_ayam, protein.p_dada_ayam) +
                         hitungProtein(pilihan.d_telur_rebus, protein.p_telur_rebus) +
                         hitungProtein(pilihan.d_ikan_tuna, protein.p_ikan_tuna) +
                         hitungProtein(pilihan.d_tempe, protein.p_tempe) +
                         hitungProtein(pilihan.d_nasi, protein.p_nasi) +
                         hitungProtein(pilihan.d_tahu, protein.p_tahu);

    float totalKalori = hitungKalori(pilihan.d_dada_ayam, kalori.k_dada_ayam) +
                        hitungKalori(pilihan.d_telur_rebus, kalori.k_telur_rebus) +
                        hitungKalori(pilihan.d_ikan_tuna, kalori.k_ikan_tuna) +
                        hitungKalori(pilihan.d_tempe, kalori.k_tempe) +
                        hitungKalori(pilihan.d_nasi, kalori.k_nasi) +
                        hitungKalori(pilihan.d_tahu, kalori.k_tahu);

    cout << "--------TOTAL KALORI DAN PROTEIN--------" << endl;
    cout << endl;
    cout << "Total protein dan kalori dari pilihan Anda adalah:" << endl;
    if (pilihan.d_dada_ayam > 0)
        cout << "dada ayam: " << hitungProtein(pilihan.d_dada_ayam, protein.p_dada_ayam) << " gram protein, " << hitungKalori(pilihan.d_dada_ayam, kalori.k_dada_ayam) << " kalori" << endl;
    if (pilihan.d_telur_rebus > 0)
        cout << "telur rebus: " << hitungProtein(pilihan.d_telur_rebus, protein.p_telur_rebus) << " gram protein, " << hitungKalori(pilihan.d_telur_rebus, kalori.k_telur_rebus) << " kalori" << endl;
    if (pilihan.d_ikan_tuna > 0)
        cout << "ikan tuna: " << hitungProtein(pilihan.d_ikan_tuna, protein.p_ikan_tuna) << " gram protein, " << hitungKalori(pilihan.d_ikan_tuna, kalori.k_ikan_tuna) << " kalori" << endl;
    if (pilihan.d_tempe > 0)
        cout << "tempe: " << hitungProtein(pilihan.d_tempe, protein.p_tempe) << " gram protein, " << hitungKalori(pilihan.d_tempe, kalori.k_tempe) << " kalori" << endl;
    if (pilihan.d_nasi > 0)
        cout << "nasi: " << hitungProtein(pilihan.d_nasi, protein.p_nasi) << " gram protein, " << hitungKalori(pilihan.d_nasi, kalori.k_nasi) << " kalori" << endl;
    if (pilihan.d_tahu > 0)
        cout << "tahu: " << hitungProtein(pilihan.d_tahu, protein.p_tahu) << " gram protein, " << hitungKalori(pilihan.d_tahu, kalori.k_tahu) << " kalori" << endl;

    cout << endl;
    cout << "Total protein: " << totalProtein << " gram" << endl;
    cout << "Total kalori: " << totalKalori << " kalori" << endl;

    cout << endl;
    cout << "------Perhitungan protein dan kalori harian anda------" << endl;
    cout << endl;

    bool pria = (pilihan.jenis_kelamin == 'L' || pilihan.jenis_kelamin == 'l');
    float bmr = pria ? BMR_pria(pilihan.berat_badan, pilihan.tinggi_badan, pilihan.umur)
                     : BMR_wanita(pilihan.berat_badan, pilihan.tinggi_badan, pilihan.umur);
    int tdee = TDEE(bmr, pilihan.tingkat_aktivitas);

    cout << "BMR Anda (tanpa aktivitas): " << bmr << " kalori" << endl;
    cout << "Karena tingkat aktivitas anda adalah " << pilihan.tingkat_aktivitas << ", maka total kebutuhan kalori harian Anda adalah: " << tdee << " kalori" << endl;
    cout << "Jika ingin Bulking, maka kebutuhan kalori dan Protein Anda adalah: " << tdee + 300 << " - " << tdee + 500 << " kalori"
         << " Dan " << pilihan.berat_badan * 1.6 << " gram protein" << endl;
    cout << "Bulking : Anda kekurangan kalori dan protein sebesar: " << tdee + 300 - totalKalori << " kalori" << " dan " << pilihan.berat_badan * 1.6 - totalProtein << " gram protein" << endl;
    cout << "Jika ingin Cutting, maka kebutuhan kalori dan Protein Anda adalah: " << tdee - 300 << " - " << tdee - 500 << " kalori"
         << " Dan " << pilihan.berat_badan * 1.8 << " gram protein" << endl;
    cout << "Cutting : Anda kelebihan kalori dan protein sebesar: " << totalKalori - (tdee - 300) << " kalori" << " dan " << totalProtein - (pilihan.berat_badan * 1.8) << " gram protein" << endl;

    return 0;
}