#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h> 

// Kode warna dari ANSI
#define WARNA_HITAM     "\x1b[30m" // Kode warna hitam
#define WARNA_MERAH     "\x1b[31m" // Kode warna merah
#define WARNA_HIJAU   "\x1b[32m" // Kode warna hija
#define WARNA_KUNING  "\x1b[33m" // Kode warna kuning
#define WARNA_BIRU    "\x1b[34m" // Kode warna biru
#define WARNA_PATMA "\x1b[35m" // Kode warna patma
#define WARNA_SIAN    "\x1b[36m" // Kode warna siyan
#define WARNA_PUTIH "\x1b[37m" // Kode warna putih
#define LATAR_WARNA_HITAM "\x1b[40m" // Kode latar warna hitam
#define LATAR_WARNA_MERAH "\x1b[41m" // Kode latar warna merah
#define LATAR_WARNA_HIJAU "\x1b[42m" // Kode latar warna hijau
#define LATAR_WARNA_KUNING "\x1b[43m" // Kode latar warna kuning
#define LATAR_WARNA_BIRU "\x1b[44m" // Kode latar warna biru
#define LATAR_WARNA_PATMA "\x1b[45m" // Kode latar warna patma
#define LATAR_WARNA_SIAN "\x1b[46m" // Kode latar warna siyan
#define LATAR_WARNA_PUTIH "\x1b[47m" // Kode latar warna putih
#define WARNA_RESET   "\x1b[0m" // Kode untuk mereset warna

// Struktur data untuk menyimpan informasi pelanggan
typedef struct {
    int id;
    char nama[50];
    char alamat[100];
    char telepon[15];
} Pelanggan;

// Struktur data untuk menyimpan informasi pesanan laundry
typedef struct {
    int id_pelanggan;
    char jenis_cucian[20];
    int jumlah;
    float total_biaya;
    int status_selesai; // 0 untuk belum selesai, 1 untuk sudah selesai
} Pesanan;

void JudulProgram() {
    printf(WARNA_HIJAU"================================================================================\n");
printf("||" WARNA_RESET WARNA_MERAH"                      __   __                                 __   __       "WARNA_RESET WARNA_HIJAU "||\n" WARNA_RESET);
printf(WARNA_HIJAU"||" WARNA_RESET WARNA_MERAH" |     /\\  |  | |\\ | |  \\ |__) \\ /    |    |  |  |\\/| | |\\ | /  \\ /__`  /\\  "WARNA_RESET WARNA_HIJAU "||\n" WARNA_RESET);
printf(WARNA_HIJAU"||" WARNA_RESET WARNA_MERAH" |___ /~~\\ \\__/ | \\| |__/ |  \\  |     |___ \\__/  |  | | | \\| \\__/ .__/ /~~\\ "WARNA_RESET WARNA_HIJAU "||\n" WARNA_RESET);
printf(WARNA_HIJAU"================================================================================"WARNA_RESET);                                                                    
}

void JudulPesan() {
printf(WARNA_HIJAU"========================================================================\n");
printf(WARNA_HIJAU"||" WARNA_RESET WARNA_MERAH"      ___               __   ___                 __   __            "WARNA_RESET WARNA_HIJAU "||\n" WARNA_RESET);
printf(WARNA_HIJAU"||" WARNA_RESET WARNA_MERAH"|\\/| |__  |\\ | |  |    |__) |__  |     /\\  |\\ | / _` / _`  /\\  |\\ | "WARNA_RESET WARNA_HIJAU "||\n" WARNA_RESET);
printf(WARNA_HIJAU"||" WARNA_RESET WARNA_MERAH"|  | |___ | \\| \\__/    |    |___ |___ /~~\\ | \\| \\__> \\__> /~~\\ | \\| "WARNA_RESET WARNA_HIJAU "||\n" WARNA_RESET);
printf(WARNA_HIJAU"========================================================================\n"WARNA_RESET);                                         
}

void simpanData(Pelanggan pelanggan[], int jumlah_pelanggan, Pesanan pesanan[], int jumlah_pesanan) {
    FILE *file;
    file = fopen("data_laundry.txt", "w"); // Membuka file untuk ditulis (overwrite jika sudah ada)

    if (file == NULL) {
        printf("Gagal membuka file.\n");
        return;
    }

    fprintf(file, "### Data Pelanggan ###\n");
    for (int i = 0; i < jumlah_pelanggan; i++) {
        fprintf(file, "%d,%s,%s,%s\n", pelanggan[i].id, pelanggan[i].nama, pelanggan[i].alamat, pelanggan[i].telepon);
    }

    fprintf(file, "### Data Pesanan ###\n");
    for (int i = 0; i < jumlah_pesanan; i++) {
        fprintf(file, "%d,%s,%d,%.2f,%d\n", pesanan[i].id_pelanggan, pesanan[i].jenis_cucian,
                pesanan[i].jumlah, pesanan[i].total_biaya, pesanan[i].status_selesai);
    }

    fclose(file); // Menutup file setelah selesai penulisan
}

// Fungsi untuk membaca data dari file
int bacaData(Pelanggan pelanggan[], Pesanan pesanan[]) {
    FILE *file;
    int jumlah_pelanggan = 0;
    int jumlah_pesanan = 0;
    char buffer[255];
    int flag_pelanggan = 0; // Penanda untuk membaca data pelanggan
    int flag_pesanan = 0; // Penanda untuk membaca data pesanan

    file = fopen("data_laundry.txt", "r"); // Membuka file untuk dibaca

    if (file == NULL) {
        printf("File tidak ditemukan atau kosong.\n");
        return 0;
    }

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        if (strstr(buffer, "### Data Pelanggan ###") != NULL) {
            flag_pelanggan = 1; // Set penanda bahwa sedang membaca data pelanggan
            flag_pesanan = 0; // Reset penanda data pesanan
            continue; // Lanjut ke iterasi berikutnya untuk membaca data pelanggan
        }

        if (flag_pelanggan && !flag_pesanan) {
            if (strstr(buffer, "### Data Pesanan ###") != NULL) {
                flag_pesanan = 1; // Set penanda bahwa akan membaca data pesanan
                flag_pelanggan = 0; // Reset penanda data pelanggan
                continue; // Lanjut ke iterasi berikutnya untuk membaca data pesanan
            }

            // Pembacaan data pelanggan
            if (jumlah_pelanggan < 100) {
                if (sscanf(buffer, "%d,%49[^,],%99[^,],%14[^\n]", &pelanggan[jumlah_pelanggan].id,
                           pelanggan[jumlah_pelanggan].nama, pelanggan[jumlah_pelanggan].alamat,
                           pelanggan[jumlah_pelanggan].telepon) == 4) {
                    jumlah_pelanggan++;
                } else {
                    printf("Format data pelanggan tidak sesuai.\n");
                }
            } else {
                printf("Kapasitas maksimum pelanggan telah tercapai.\n");
            }
        }

        if (flag_pesanan) {
            // Pembacaan data pesanan
            if (jumlah_pesanan < 100) {
                if (sscanf(buffer, "%d,%19[^,],%d,%f,%d", &pesanan[jumlah_pesanan].id_pelanggan,
                           pesanan[jumlah_pesanan].jenis_cucian, &pesanan[jumlah_pesanan].jumlah,
                           &pesanan[jumlah_pesanan].total_biaya, &pesanan[jumlah_pesanan].status_selesai) == 5) {
                    jumlah_pesanan++;
                } else {
                    printf("Format data pesanan tidak sesuai.\n");
                }
            } else {
                printf("Kapasitas maksimum pesanan telah tercapai.\n");
            }
        }
    }

    fclose(file); // Menutup file setelah selesai pembacaan
    return jumlah_pelanggan; // Mengembalikan jumlah pelanggan yang telah dibaca dari file
}
// Fungsi untuk menambahkan data pelanggan
void tambahPelangganDanSimpan(Pelanggan pelanggan[], int *jumlah_pelanggan) {
    printf("Masukkan nama: ");
    scanf(" %[^\n]s", pelanggan[*jumlah_pelanggan].nama);
    printf("Masukkan alamat: ");
    scanf(" %[^\n]s", pelanggan[*jumlah_pelanggan].alamat);
    printf("Masukkan nomor telepon: ");
    scanf(" %[^\n]s", pelanggan[*jumlah_pelanggan].telepon);

    // Generate ID pelanggan secara otomatis
    pelanggan[*jumlah_pelanggan].id = *jumlah_pelanggan + 1;

    (*jumlah_pelanggan)++;
    printf("Pelanggan berhasil ditambahkan dengan ID: %d\n", pelanggan[*jumlah_pelanggan - 1].id);

    // Simpan data pelanggan ke file setelah penambahan data baru
    simpanData(pelanggan, *jumlah_pelanggan, NULL, 0);
}

// Fungsi untuk melakukan pemesanan laundry
void pesanLaundryDanSimpan(Pelanggan pelanggan[], int jumlah_pelanggan, Pesanan pesanan[], int *jumlah_pesanan) {

    int id_pelanggan, i;
    printf("Masukkan ID pelanggan: ");
    scanf("%d", &id_pelanggan);

    // Cari ID pelanggan dalam data pelanggan
    for (i = 0; i < jumlah_pelanggan; i++) {
        if (pelanggan[i].id == id_pelanggan) {
            printf("Masukkan jenis cucian: ");
            scanf(" %[^\n]s", pesanan[*jumlah_pesanan].jenis_cucian);
            printf("Masukkan jumlah cucian: ");
            scanf("%d", &pesanan[*jumlah_pesanan].jumlah);

            // (contoh perhitungan sederhana, Anda bisa menyesuaikan sesuai kebutuhan)
            pesanan[*jumlah_pesanan].total_biaya = pesanan[*jumlah_pesanan].jumlah * 10; // Harga per item

            pesanan[*jumlah_pesanan].id_pelanggan = id_pelanggan;
            pesanan[*jumlah_pesanan].status_selesai = 0; // Pesanan belum selesai

            (*jumlah_pesanan)++;
            printf("Pesanan laundry berhasil ditambahkan.\n");
            getch();
            simpanData(pelanggan, jumlah_pelanggan, pesanan, *jumlah_pesanan); // Simpan data ke file
            return;
        }
    }
    printf("ID pelanggan tidak ditemukan.\n");
}



// Fungsi untuk menandai pesanan sebagai selesai
void pesananSelesai(Pesanan pesanan[], int jumlah_pesanan, Pelanggan pelanggan[], int jumlah_pelanggan) {
    int id_pesanan;
    printf("Masukkan ID pesanan yang sudah selesai: ");
    scanf("%d", &id_pesanan);

    for (int i = 0; i < jumlah_pesanan; i++) {
        if (pesanan[i].id_pelanggan == id_pesanan && pesanan[i].status_selesai == 0) {
            pesanan[i].status_selesai = 1;
            printf("Pesanan dengan ID %d telah selesai.\n", id_pesanan);
            simpanData(pelanggan, jumlah_pelanggan, pesanan, jumlah_pesanan); // Simpan data ke file
            return;
        }
    }
    printf("ID pesanan tidak ditemukan atau sudah selesai sebelumnya.\n");
}

// Fungsi pencarian pelanggan berdasarkan nama
void cariPelanggan(Pelanggan pelanggan[], int jumlah_pelanggan, int idDicari) {
    int ditemukan = 0;
    printf("Hasil pencarian:\n");
    for (int i = 0; i < jumlah_pelanggan; i++) {
        if (pelanggan[i].id == idDicari) {
            printf("ID: %d, Nama: %s, Alamat: %s, Telepon: %s\n",
                   pelanggan[i].id, pelanggan[i].nama, pelanggan[i].alamat, pelanggan[i].telepon);
            ditemukan = 1;
            break; // Jika ID ditemukan, hentikan pencarian
        }
    }
    if (!ditemukan) {
        printf("Pelanggan dengan ID '%d' tidak ditemukan.\n", idDicari);
    }
}

// Fungsi untuk menukar data pesanan pada proses pengurutan
void tukar(Pesanan *a, Pesanan *b) {
    Pesanan temp = *a;
    *a = *b;
    *b = temp;
}

// Fungsi pengurutan pesanan berdasarkan total biaya dengan metode Bubble Sort
void urutPesanan(Pesanan pesanan[], int jumlah_pesanan, Pelanggan pelanggan[], int jumlah_pelanggan) {
    for (int i = 0; i < jumlah_pesanan - 1; i++) {
        for (int j = 0; j < jumlah_pesanan - i - 1; j++) {
            if (pesanan[j].total_biaya > pesanan[j + 1].total_biaya) {
                tukar(&pesanan[j], &pesanan[j + 1]);
                simpanData(pelanggan, jumlah_pelanggan, pesanan, jumlah_pesanan); // Simpan data ke file
            }
        }
    }
}

void RiwayatPesananTertunda() {
    printf("Daftar Pesanan Belum Selesai:\n");

    FILE *file;
    file = fopen("data_laundry.txt", "r");

    if (file == NULL) {
        printf("File tidak ditemukan atau kosong.\n");
        getch();
        return;
    }

    char buffer[255];
    int flag_pesanan = 0; // Penanda untuk membaca data pesanan

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        if (strstr(buffer, "### Data Pesanan ###") != NULL) {
            flag_pesanan = 1; // Set penanda bahwa akan membaca data pesanan
            continue; // Lanjut ke iterasi berikutnya untuk membaca data pesanan
        }

        if (flag_pesanan) {
            int id_pelanggan, jumlah, status_selesai;
            char jenis_cucian[20];
            float total_biaya;

            if (sscanf(buffer, "%d,%19[^,],%d,%f,%d", &id_pelanggan, jenis_cucian,
                       &jumlah, &total_biaya, &status_selesai) == 5) {
                if (status_selesai == 0) {
                    printf("ID Pelanggan: %d, Jenis Cucian: %s, Jumlah: %d, Total Biaya: %.2f\n",
                           id_pelanggan, jenis_cucian, jumlah, total_biaya);
                }
            }
        }
    }

    fclose(file); // Menutup file setelah selesai pembacaan
    getch();
}

void RiwayatPesananSelesai() {
    printf("Riwayat Pesanan Selesai:\n");

    FILE *file;
    file = fopen("data_laundry.txt", "r");

    if (file == NULL) {
        printf("File tidak ditemukan atau kosong.\n");
        getch();
        return;
    }

    char buffer[255];
    int flag_pesanan = 0; // Penanda untuk membaca data pesanan

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        if (strstr(buffer, "### Data Pesanan ###") != NULL) {
            flag_pesanan = 1; // Set penanda bahwa akan membaca data pesanan
            continue; // Lanjut ke iterasi berikutnya untuk membaca data pesanan
        }

        if (flag_pesanan) {
            int id_pelanggan, jumlah, status_selesai;
            char jenis_cucian[20];
            float total_biaya;

            if (sscanf(buffer, "%d,%19[^,],%d,%f,%d", &id_pelanggan, jenis_cucian,
                       &jumlah, &total_biaya, &status_selesai) == 5) {
                if (status_selesai == 1) {
                    printf("ID Pelanggan: %d, Jenis Cucian: %s, Jumlah: %d, Total Biaya: %.2f\n",
                           id_pelanggan, jenis_cucian, jumlah, total_biaya);
                }
            }
        }
    }

    fclose(file); // Menutup file setelah selesai pembacaan
}

int main() {
    Pelanggan data_pelanggan[100];
    Pesanan data_pesanan[100];
    int jumlah_pelanggan = 0;
    int jumlah_pesanan = 0;
    int pilihan;

    jumlah_pelanggan = bacaData(data_pelanggan, data_pesanan);
	
	system("cls");

    do {
    	JudulProgram();
        printf(WARNA_SIAN"\n\t\t\t=============== Menu ===============\n");
        printf("\t\t\t| 1. Tambah Pelanggan              |\n");
        printf("\t\t\t| 2. Pesan Laundry                 |\n");
        printf("\t\t\t| 3. Daftar Pesanan Belum Selesai  |\n");
        printf("\t\t\t| 4. Tandai Pesanan Selesai        |\n");
        printf("\t\t\t| 5. Riwayat Pesanan Selesai       |\n");
        printf("\t\t\t| 6. Cari Pelanggan                |\n");
        printf("\t\t\t| 7. Urut Pesanan                  |\n");
        printf("\t\t\t| 8. Keluar                        |\n");
        printf("\t\t\t====================================\n"WARNA_RESET);
        printf(WARNA_PATMA"\t\t\t\tPilihan Anda : "WARNA_RESET);
        scanf("%d", &pilihan);
        system("cls");
        

        switch (pilihan) {
            case 1:
                JudulPesan();
                printf("\n");
                tambahPelangganDanSimpan(data_pelanggan, &jumlah_pelanggan);
                system("cls");
                break;
            case 2:
                pesanLaundryDanSimpan(data_pelanggan, jumlah_pelanggan, data_pesanan, &jumlah_pesanan);
                system("cls");
                break;
            case 3:
                RiwayatPesananTertunda(); 
                getch();
                system("cls");
                break;
            case 4:
                pesananSelesai(data_pesanan, jumlah_pesanan, data_pelanggan, jumlah_pelanggan);
                system("cls");
                break;
            case 5:
                RiwayatPesananSelesai();
                getch();
                system("cls");
                break;
            case 6: {
                int idDicari;
                printf("Masukkan ID pelanggan yang dicari: ");
                scanf("%d", &idDicari);
                cariPelanggan(data_pelanggan, jumlah_pelanggan, idDicari);
                system("cls");
                break;
            }
            case 7:
                urutPesanan(data_pesanan, jumlah_pesanan, data_pelanggan, jumlah_pelanggan);
                printf("Pesanan berhasil diurutkan berdasarkan total biaya.\n");
                getch();
                system("cls");
                break;
            case 8:
                printf("Terima kasih!\n");
                break;
            default:
                printf("Pilihan tidak valid.\n");
                getch();
                system("cls");
                
        }
    } while (pilihan != 8);

    simpanData(data_pelanggan, jumlah_pelanggan, data_pesanan, jumlah_pesanan);

    return 0;
}
