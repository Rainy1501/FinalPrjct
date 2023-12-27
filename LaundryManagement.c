	/*
	    namaTugas : Ujian Akhir Semester
	    namaProgrammer : Fattan Naufan Islami / 23343037
	    kasus program : Manajemen Laundry
	*/
	
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <conio.h> 
	#include <windows.h>
	
	// Kode warna dari ANSI
	#define WARNA_HITAM  "\x1b[30m" // Kode warna hitam
	#define WARNA_MERAH  "\x1b[31m" // Kode warna merah
	#define WARNA_HIJAU  "\x1b[32m" // Kode warna hijau
	#define WARNA_KUNING "\x1b[33m" // Kode warna kuning
	#define WARNA_BIRU   "\x1b[34m" // Kode warna biru
	#define WARNA_PATMA  "\x1b[35m" // Kode warna patma
	#define WARNA_SIAN   "\x1b[36m" // Kode warna siyan
	#define WARNA_PUTIH  "\x1b[37m" // Kode warna putih
	#define LATAR_WARNA_ABU  "\x1b[40m" // Kode latar warna hitam
	#define LATAR_WARNA_MERAH  "\x1b[41m" // Kode latar warna merah
	#define LATAR_WARNA_HIJAU  "\x1b[42m" // Kode latar warna hijau
	#define LATAR_WARNA_KUNING "\x1b[43m" // Kode latar warna kuning
	#define LATAR_WARNA_BIRU   "\x1b[44m" // Kode latar warna biru
	#define LATAR_WARNA_PATMA  "\x1b[45m" // Kode latar warna patma
	#define LATAR_WARNA_SIAN   "\x1b[46m" // Kode latar warna siyan
	#define LATAR_WARNA_PUTIH  "\x1b[47m" // Kode latar warna putih
	#define WARNA_RESET  "\x1b[0m" // Kode untuk mereset warna
	
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
	    int status_selesai; // N.B. 0 untuk belum selesai, 1 untuk sudah selesai
	} Pesanan;
	
	// Fungsi untuk menampilkan judul program
	void JudulProgram() {
	    printf(WARNA_HIJAU"\t================================================================================\n");
	    printf("\t||" WARNA_RESET WARNA_MERAH"                      __   __                                 __   __       "WARNA_RESET WARNA_HIJAU "||\n" WARNA_RESET);
	    printf(WARNA_HIJAU"\t||" WARNA_RESET WARNA_MERAH" |     /\\  |  | |\\ | |  \\ |__) \\ /    |    |  |  |\\/| | |\\ | /  \\ /__`  /\\  "WARNA_RESET WARNA_HIJAU "||\n" WARNA_RESET);
	    printf(WARNA_HIJAU"\t||" WARNA_RESET WARNA_MERAH" |___ /~~\\ \\__/ | \\| |__/ |  \\  |     |___ \\__/  |  | | | \\| \\__/ .__/ /~~\\ "WARNA_RESET WARNA_HIJAU "||\n" WARNA_RESET);
	    printf(WARNA_HIJAU"\t================================================================================"WARNA_RESET);                                                                    
	}
	
	// Fungsi untuk menampilkan judul pesan
	void JudulPesan() {
	    printf(WARNA_HIJAU"\t=========================================================================\n");
	    printf(WARNA_HIJAU"\t||" WARNA_RESET WARNA_MERAH"       ___               __   ___                 __   __            "WARNA_RESET WARNA_HIJAU "||\n" WARNA_RESET);
	    printf(WARNA_HIJAU"\t||" WARNA_RESET WARNA_MERAH" |\\/| |__  |\\ | |  |    |__) |__  |     /\\  |\\ | / _` / _`  /\\  |\\ | "WARNA_RESET WARNA_HIJAU "||\n" WARNA_RESET);
	    printf(WARNA_HIJAU"\t||" WARNA_RESET WARNA_MERAH" |  | |___ | \\| \\__/    |    |___ |___ /~~\\ | \\| \\__> \\__> /~~\\ | \\| "WARNA_RESET WARNA_HIJAU "||\n" WARNA_RESET);
	    printf(WARNA_HIJAU"\t=========================================================================\n"WARNA_RESET);                                         
	}
	
	// Fungsi untuk menampilkan judul pesan laundry
	void JudulPesanLaundry() {
	    printf(WARNA_HIJAU"\t==========================================================================================\n");
	    printf(WARNA_HIJAU"\t||" WARNA_RESET WARNA_MERAH"       ___               __   ___  __                                    __   __      "WARNA_RESET WARNA_HIJAU "||\n" WARNA_RESET);
	    printf(WARNA_HIJAU"\t||" WARNA_RESET WARNA_MERAH" |\\/| |__  |\\ | |  |    |__) |__  /__`  /\\  |\\ |    |     /\\  |  | |\\ | |  \\ |__) \\ / "WARNA_RESET WARNA_HIJAU "||\n" WARNA_RESET);
	    printf(WARNA_HIJAU"\t||" WARNA_RESET WARNA_MERAH" |  | |___ | \\| \\__/    |    |___ .__/ /~~\\ | \\|    |___ /~~\\ \\__/ | \\| |__/ |  \\  |  "WARNA_RESET WARNA_HIJAU "||\n" WARNA_RESET);
	    printf(WARNA_HIJAU"\t==========================================================================================\n\n"WARNA_RESET);                                         
	}
	
	// Fungsi untuk menampilkan judul riwayat pesanan tertunda
	void JudulPendingOrder() {                                                                                                        
	    printf(WARNA_HIJAU"==================================================================================================================\n");
	    printf(WARNA_HIJAU"||" WARNA_RESET WARNA_MERAH"  __                       ___     __   ___  __                         ___  ___  __  ___            __       "WARNA_RESET WARNA_HIJAU "||\n" WARNA_RESET);
	    printf(WARNA_HIJAU"||" WARNA_RESET WARNA_MERAH" |__) | |  |  /\\  \\ /  /\\   |     |__) |__  /__`  /\\  |\\ |  /\\  |\\ |     |  |__  |__)  |  |  | |\\ | |  \\  /\\  "WARNA_RESET WARNA_HIJAU "||\n" WARNA_RESET);
	    printf(WARNA_HIJAU"||" WARNA_RESET WARNA_MERAH" |  \\ | |/\\| /~~\\  |  /~~\\  |     |    |___ .__/ /~~\\ | \\| /~~\\ | \\      |  |___ |  \\  |  \\__/ | \\| |__/ /~~\\ "WARNA_RESET WARNA_HIJAU "||\n" WARNA_RESET);
	    printf(WARNA_HIJAU"==================================================================================================================\n\n"WARNA_RESET);                                         
	}
	
	// Fungsi untuk menampilkan judul tandai pesanan selesai
	void JudulMarkComplete() {
	    printf(WARNA_HIJAU"\t=========================================================================================\n");
	    printf(WARNA_HIJAU"\t||" WARNA_RESET WARNA_MERAH"       ___              ___            __             __   ___       ___  __         "WARNA_RESET WARNA_HIJAU "||\n" WARNA_RESET);
	    printf(WARNA_HIJAU"\t||" WARNA_RESET WARNA_MERAH" |\\/| |__  |\\ | |  |     |   /\\  |\\ | |  \\  /\\  |    /__` |__  |    |__  /__`  /\\  | "WARNA_RESET WARNA_HIJAU "||\n" WARNA_RESET);
	    printf(WARNA_HIJAU"\t||" WARNA_RESET WARNA_MERAH" |  | |___ | \\| \\__/     |  /~~\\ | \\| |__/ /~~\\ |    .__/ |___ |___ |___ .__/ /~~\\ | "WARNA_RESET WARNA_HIJAU "||\n" WARNA_RESET);
	    printf(WARNA_HIJAU"\t=========================================================================================\n\n"WARNA_RESET);                                         
	}
	
	// Fungsi untuk menampilkan judul riwayat pesanan selesai
	void JudulCompleteOrder() {                                                                                                       
	    printf(WARNA_HIJAU"============================================================================================================\n");
	    printf(WARNA_HIJAU"||" WARNA_RESET WARNA_MERAH"  __                       ___     __   ___  __                          __   ___       ___  __         "WARNA_RESET WARNA_HIJAU "||\n" WARNA_RESET);
	    printf(WARNA_HIJAU"||" WARNA_RESET WARNA_MERAH" |__) | |  |  /\\  \\ /  /\\   |     |__) |__  /__`  /\\  |\\ |  /\\  |\\ |    /__` |__  |    |__  /__`  /\\  | "WARNA_RESET WARNA_HIJAU "||\n" WARNA_RESET);
	    printf(WARNA_HIJAU"||" WARNA_RESET WARNA_MERAH" |  \\ | |/\\| /~~\\  |  /~~\\  |     |    |___ .__/ /~~\\ | \\| /~~\\ | \\|    .__/ |___ |___ |___ .__/ /~~\\ | "WARNA_RESET WARNA_HIJAU "||\n" WARNA_RESET);
	    printf(WARNA_HIJAU"============================================================================================================\n\n"WARNA_RESET);                                         
	}
	
	// Fungsi untuk menampilkan judul cari pelanggan
	void JudulCariPelanggan() {                                                                                    
	    printf(WARNA_HIJAU"\t=============================================================================================\n");
	    printf(WARNA_HIJAU"\t||" WARNA_RESET WARNA_MERAH"       ___               __        __        __   ___                 __   __            "WARNA_RESET WARNA_HIJAU "||\n" WARNA_RESET);
	    printf(WARNA_HIJAU"\t||" WARNA_RESET WARNA_MERAH" |\\/| |__  |\\ | |  |    /  `  /\\  |__) |    |__) |__  |     /\\  |\\ | / _` / _`  /\\  |\\ | "WARNA_RESET WARNA_HIJAU "||\n" WARNA_RESET);
	    printf(WARNA_HIJAU"\t||" WARNA_RESET WARNA_MERAH" |  | |___ | \\| \\__/    \\__, /~~\\ |  \\ |    |    |___ |___ /~~\\ | \\| \\__> \\__> /~~\\ | \\| "WARNA_RESET WARNA_HIJAU "||\n" WARNA_RESET);
	    printf(WARNA_HIJAU"\t=============================================================================================\n\n"WARNA_RESET);                                         
	}
	
	// Fungsi untuk menampilkan judul urut pesanan
	void JudulSortOrder() {
	    printf(WARNA_HIJAU"\t=====================================================================================\n");
	    printf(WARNA_HIJAU"\t||" WARNA_RESET WARNA_MERAH"       ___                    __       ___     __   ___  __                      "WARNA_RESET WARNA_HIJAU "||\n" WARNA_RESET);
	    printf(WARNA_HIJAU"\t||" WARNA_RESET WARNA_MERAH" |\\/| |__  |\\ | |  |    |  | |__) |  |  |     |__) |__  /__`  /\\  |\\ |  /\\  |\\ | "WARNA_RESET WARNA_HIJAU "||\n" WARNA_RESET);
	    printf(WARNA_HIJAU"\t||" WARNA_RESET WARNA_MERAH" |  | |___ | \\| \\__/    \\__/ |  \\ \\__/  |     |    |___ .__/ /~~\\ | \\| /~~\\ | \\| "WARNA_RESET WARNA_HIJAU "||\n" WARNA_RESET);
	    printf(WARNA_HIJAU"\t=====================================================================================\n\n"WARNA_RESET);                                         
	}
	
	// Fungsi untuk menampilkan judul terima kasih
	void TerimaKasih() {
	    printf(WARNA_HIJAU"\t=========================================================\n");
	    printf(WARNA_HIJAU"\t||" WARNA_RESET WARNA_MERAH" ___  ___  __                             __         "WARNA_RESET WARNA_HIJAU "||\n" WARNA_RESET);
	    printf(WARNA_HIJAU"\t||" WARNA_RESET WARNA_MERAH"  |  |__  |__) |  |\\/|  /\\     |__/  /\\  /__` | |__| "WARNA_RESET WARNA_HIJAU "||\n" WARNA_RESET);
	    printf(WARNA_HIJAU"\t||" WARNA_RESET WARNA_MERAH"  |  |___ |  \\ |  |  | /~~\\    |  \\ /~~\\ .__/ | |  | "WARNA_RESET WARNA_HIJAU "||\n" WARNA_RESET);
	    printf(WARNA_HIJAU"\t=========================================================\n\n"WARNA_RESET);    
	}
	
	// Fungsi untuk menampilkan teks dengan delay variasi 1
	void DelayPrintExit(const char *text, int delayTime) {
	    while (*text != '\0') {
	        printf(WARNA_SIAN"%c"WARNA_RESET, *text);
	        Sleep(delayTime);
	        text++;
	    }
	}
	
	// Fungsi untuk menampilkan teks dengan delay variasi 2
	void DelayPrintPilihan(const char *text, int delayTime) {
	    while (*text != '\0') {
	        printf(WARNA_PATMA"%c"WARNA_KUNING, *text);
	        Sleep(delayTime);
	        text++;
	    }
	}
	
	// Fungsi untuk menampilkan teks dengan delay variasi 3
	void DelayPrintSalahInput(const char *text, int delayTime) {
	    while (*text != '\0') {
	        printf(WARNA_KUNING"%c"WARNA_RESET, *text);
	        Sleep(delayTime);
	        text++;
	    }
	}
	
	// Fungsi untuk menyimpan data pelanggan ke Data_Pelannggan_Laundry.txt
	void simpanDataPelanggan(Pelanggan pelanggan[], int jumlah_pelanggan) {
	    FILE *file;
	    file = fopen("Data_Pelanggan_Laundry.txt", "w"); 
	
	    if (file == NULL) {
	        printf("Gagal membuka file Data_Pelanggan_Laundry.\n");
	        return;
	    }
	
	    fprintf(file, "### Data Pelanggan ###\n");
	    for (int i = 0; i < jumlah_pelanggan; i++) {
	        fprintf(file, "%d,%s,%s,%s\n", pelanggan[i].id, pelanggan[i].nama, pelanggan[i].alamat, pelanggan[i].telepon);
	    }
	
	    fclose(file);
	}
	
	// Fungsi untuk menyimpan data pesanan ke Data_Pesanan_Laundry.txt
	void simpanDataPesanan(Pesanan pesanan[], int jumlah_pesanan) {
	    FILE *file;
	    file = fopen("Data_Pesanan_Laundry.txt", "w"); 
	
	    if (file == NULL) {
	        printf("Gagal membuka file Data_Pesanan_Laundry.\n");
	        return;
	    }
	
	    fprintf(file, "### Data Pesanan ###\n");
	    for (int i = 0; i < jumlah_pesanan; i++) {
	        fprintf(file, "%d,%s,%d,%.0f,%d\n", pesanan[i].id_pelanggan, pesanan[i].jenis_cucian,
	                pesanan[i].jumlah, pesanan[i].total_biaya, pesanan[i].status_selesai);
	    }
	
	    fclose(file);
	}
	
	// Fungsi untuk membaca data pelanggan dari Data_Pelanggan_Laundry.txt
	int bacaDataPelanggan(Pelanggan pelanggan[]) {
	    FILE *file;
	    int jumlah_pelanggan = 0;
	    char buffer[255];
	
	    file = fopen("Data_Pelanggan_Laundry.txt", "r");
	
	    if (file == NULL) {
	        printf("File Data_Pelanggan_Laundry tidak ditemukan atau kosong.\n");
	        return 0;
	    }
	
	    while (fgets(buffer, sizeof(buffer), file) != NULL) {
	        if (sscanf(buffer, "%d,%49[^,],%99[^,],%14[^\n]", &pelanggan[jumlah_pelanggan].id,
	                   pelanggan[jumlah_pelanggan].nama, pelanggan[jumlah_pelanggan].alamat,
	                   pelanggan[jumlah_pelanggan].telepon) == 4) {
	            jumlah_pelanggan++;
	        } else {
	            printf("Format data pelanggan tidak sesuai.\n");
	        }
	    }
	
	    fclose(file);
	    return jumlah_pelanggan;
	}
	
	// Fungsi untuk membaca data pesanan dari Data_Pesanan_Laundry.txt
	int bacaDataPesanan(Pesanan pesanan[]) {
	    FILE *file;
	    int jumlah_pesanan = 0;
	    char buffer[255];
	
	    file = fopen("Data_Pesanan_Laundry.txt", "r"); 
	
	    if (file == NULL) {
	        printf("File Data_Pesanan_Laundry tidak ditemukan atau kosong.\n");
	        return 0;
	    }
	
	    while (fgets(buffer, sizeof(buffer), file) != NULL) {
	        if (sscanf(buffer, "%d,%19[^,],%d,%f,%d", &pesanan[jumlah_pesanan].id_pelanggan,
	                   pesanan[jumlah_pesanan].jenis_cucian, &pesanan[jumlah_pesanan].jumlah,
	                   &pesanan[jumlah_pesanan].total_biaya, &pesanan[jumlah_pesanan].status_selesai) == 5) {
	            jumlah_pesanan++;
	        } else {
	            printf("Format data pesanan tidak sesuai.\n");
	        }
	    }
	
	    fclose(file);
	    return jumlah_pesanan;
	}
	
	// Fungsi untuk menyimpan data pelanggan dan pesanan ke file
	void simpanData(Pelanggan pelanggan[], int jumlah_pelanggan, Pesanan pesanan[], int jumlah_pesanan) {
	    simpanDataPelanggan(pelanggan, jumlah_pelanggan);
	    simpanDataPesanan(pesanan, jumlah_pesanan);
	}
	
	// Fungsi untuk menambahkan data pelanggan
	void tambahPelangganDanSimpan(Pelanggan pelanggan[], int *jumlah_pelanggan) {
	    printf(WARNA_PATMA"Masukkan nama: "WARNA_KUNING);
	    scanf(" %[^\n]s", pelanggan[*jumlah_pelanggan].nama);
	    printf(WARNA_PATMA"Masukkan alamat: "WARNA_KUNING);
	    scanf(" %[^\n]s", pelanggan[*jumlah_pelanggan].alamat);
	    printf(WARNA_PATMA"Masukkan nomor telepon: "WARNA_KUNING);
	    scanf(" %[^\n]s", pelanggan[*jumlah_pelanggan].telepon);
	
	    // Generate ID pelanggan secara otomatis
	    pelanggan[*jumlah_pelanggan].id = *jumlah_pelanggan + 1;
	
	    (*jumlah_pelanggan)++;
	    printf(WARNA_KUNING"Pelanggan berhasil ditambahkan dengan ID: %d\n", pelanggan[*jumlah_pelanggan - 1].id);
	
	
	    simpanData(pelanggan, *jumlah_pelanggan, NULL, 0);
	}
	
	// Fungsi untuk melakukan pemesanan laundry
	void pesanLaundryDanSimpan(Pelanggan pelanggan[], int jumlah_pelanggan, Pesanan pesanan[], int *jumlah_pesanan) {
	    int id_pelanggan, i;
	    printf(WARNA_PATMA"\t\t\t\tMasukkan ID pelanggan: "WARNA_KUNING);
	    scanf("%d", &id_pelanggan);
	
	    for (i = 0; i < jumlah_pelanggan; i++) {
	        if (pelanggan[i].id == id_pelanggan) {
	            printf(WARNA_SIAN"\n\t\t\t\t============================\n");
	            printf("\t\t\t\t||" WARNA_RESET WARNA_HIJAU "  Pilihan Jenis Cucian  " WARNA_RESET WARNA_SIAN  "||\n");
	            printf("\t\t\t\t============================\n");
	            printf("\t\t\t\t||" WARNA_RESET WARNA_MERAH " 1 | Baju saja          " WARNA_RESET WARNA_SIAN "||\n");
	            printf("\t\t\t\t||" WARNA_RESET WARNA_MERAH " 2 | Celana Saja        " WARNA_RESET WARNA_SIAN "||\n" );
	            printf("\t\t\t\t||" WARNA_RESET WARNA_MERAH " 3 | Baju dan Celana    " WARNA_RESET WARNA_SIAN "||\n" );
	            printf("\t\t\t\t||" WARNA_RESET WARNA_MERAH " 4 | Sepatu             " WARNA_RESET WARNA_SIAN "||\n" );
	            printf("\t\t\t\t||" WARNA_RESET WARNA_MERAH " 5 | Selimut            " WARNA_RESET WARNA_SIAN "||\n" );
	            printf("\t\t\t\t||" WARNA_RESET WARNA_MERAH " 6 | Tas                " WARNA_RESET WARNA_SIAN "||\n" );
	            printf("\t\t\t\t||" WARNA_RESET WARNA_MERAH " 7 | Kaos Kaki          " WARNA_RESET WARNA_SIAN "||\n" );
	            printf("\t\t\t\t||" WARNA_RESET WARNA_MERAH " 8 | Sarung Tangan      " WARNA_RESET WARNA_SIAN "||\n" );
	            printf("\t\t\t\t||" WARNA_RESET WARNA_MERAH " 9 | Topi               " WARNA_RESET WARNA_SIAN "||\n");
	            printf(WARNA_SIAN"\t\t\t\t============================\n");
	            printf(WARNA_PATMA"\t\t\t\tPilih jenis cucian (1-9): "WARNA_KUNING);
	            int pilihan_cucian;
	            scanf("%d", &pilihan_cucian);
	
	            float harga_per_item = 0;
	
	            switch (pilihan_cucian) {
	                case 1:
	                    strcpy(pesanan[*jumlah_pesanan].jenis_cucian, "Baju saja");
	                    harga_per_item = 8000; 
	                    break;
	                case 2:
	                    strcpy(pesanan[*jumlah_pesanan].jenis_cucian, "Celana Saja");
	                    harga_per_item = 8000; 
	                    break;
	                case 3:
	                    strcpy(pesanan[*jumlah_pesanan].jenis_cucian, "Baju dan Celana");
	                    harga_per_item = 8000; 
	                    break;
	                case 4:
	                    strcpy(pesanan[*jumlah_pesanan].jenis_cucian, "Sepatu");
	                    harga_per_item = 8000; 
	                    break;
	                case 5:
	                    strcpy(pesanan[*jumlah_pesanan].jenis_cucian, "Selimut");
	                    harga_per_item = 15000; 
	                    break;
	                case 6:
	                    strcpy(pesanan[*jumlah_pesanan].jenis_cucian, "Tas");
	                    harga_per_item = 12000; 
	                    break;
	                case 7:
	                    strcpy(pesanan[*jumlah_pesanan].jenis_cucian, "Kaos Kaki");
	                    harga_per_item = 3000; 
	                    break;
	                case 8:
	                    strcpy(pesanan[*jumlah_pesanan].jenis_cucian, "Sarung Tangan");
	                    harga_per_item = 2000; 
	                    break;
	                case 9:
	                    strcpy(pesanan[*jumlah_pesanan].jenis_cucian, "Topi");
	                    harga_per_item = 4000; 
	                    break;
	                default:
	                    DelayPrintSalahInput("Pilihan jenis cucian tidak valid...", 50);
	                    return;
	            }
	
	            printf(WARNA_PATMA"\t\t\t\tMasukkan jumlah cucian: "WARNA_KUNING);
	            scanf("%d", &pesanan[*jumlah_pesanan].jumlah);
	
	            pesanan[*jumlah_pesanan].total_biaya = pesanan[*jumlah_pesanan].jumlah * harga_per_item;
	
	            pesanan[*jumlah_pesanan].id_pelanggan = id_pelanggan;
	            pesanan[*jumlah_pesanan].status_selesai = 0; 
	
	            (*jumlah_pesanan)++;
	            printf("\t\t\t\tPesanan laundry berhasil ditambahkan.\n");
	            simpanData(pelanggan, jumlah_pelanggan, pesanan, *jumlah_pesanan); 
	            return;
	        }
	    }
	    printf("ID pelanggan tidak ditemukan.\n");
	}
	
	// Fungsi untuk menampilkan daftar pesanan yang belum selesai
	void RiwayatPesananTertunda() {
	    printf(WARNA_KUNING"Daftar Pesanan Belum Selesai:\n"WARNA_RESET);
	
	    FILE *file;
	    file = fopen("data_pesanan_laundry.txt", "r");
	
	    if (file == NULL) {
	        printf(WARNA_KUNING"File tidak ditemukan atau kosong.\n"WARNA_RESET);
	        return;
	    }
	
	    char buffer[255];
	    int flag_pesanan = 0; // Penanda untuk membaca data pesanan
	
	    while (fgets(buffer, sizeof(buffer), file) != NULL) {
	        if (strstr(buffer, "### Data Pesanan ###") != NULL) {
	            flag_pesanan = 1; 
	            continue; 
	        }
	
	        if (flag_pesanan) {
	            int id_pelanggan, jumlah, status_selesai;
	            char jenis_cucian[20];
	            float total_biaya;
	
	            if (sscanf(buffer, "%d,%19[^,],%d,%f,%d", &id_pelanggan, jenis_cucian,
	                       &jumlah, &total_biaya, &status_selesai) == 5) {
	                if (status_selesai == 0) {
	                    printf(WARNA_SIAN"ID Pelanggan: %d, Jenis Cucian: %s, Jumlah: %d, Total Biaya: Rp.%.0f\n"WARNA_RESET,
	                           id_pelanggan, jenis_cucian, jumlah, total_biaya);
	                }
	            }
	        }
	    }
	
	    fclose(file); 
	}
	
	// Fungsi untuk menandai pesanan sebagai selesai
	void pesananSelesai(Pesanan pesanan[], int jumlah_pesanan, Pelanggan pelanggan[], int jumlah_pelanggan) {
	    int id_pesanan;
	    printf(WARNA_PATMA"Masukkan ID pesanan yang sudah selesai: "WARNA_KUNING);
	    scanf("%d", &id_pesanan);
	
	    for (int i = 0; i < jumlah_pesanan; i++) {
	        if (pesanan[i].id_pelanggan == id_pesanan && pesanan[i].status_selesai == 0) {
	            pesanan[i].status_selesai = 1;
	            printf(WARNA_KUNING"Pesanan dengan ID %d telah selesai.\n"WARNA_RESET, id_pesanan);
	            simpanData(pelanggan, jumlah_pelanggan, pesanan, jumlah_pesanan); 
	            return;
	        }
	    }
	    printf(WARNA_KUNING"ID pesanan tidak ditemukan atau sudah selesai sebelumnya.\n"WARNA_RESET);
	}
	
	// Fungsi untuk menampilkan riwayat pesanan yang sudah selesai
	void RiwayatPesananSelesai() {
	    printf(WARNA_KUNING"Riwayat Pesanan Selesai:\n"WARNA_RESET);
	
	    FILE *file;
	    file = fopen("data_pesanan_laundry.txt", "r");
	
	    if (file == NULL) {
	        printf(WARNA_KUNING"File tidak ditemukan atau kosong.\n"WARNA_RESET);
	        return;
	    }
	
	    char buffer[255];
	    int flag_pesanan = 0; 
	
	    while (fgets(buffer, sizeof(buffer), file) != NULL) {
	        if (strstr(buffer, "### Data Pesanan ###") != NULL) {
	            flag_pesanan = 1; 
	            continue; 
	        }
	
	        if (flag_pesanan) {
	            int id_pelanggan, jumlah, status_selesai;
	            char jenis_cucian[20];
	            float total_biaya;
	
	            if (sscanf(buffer, "%d,%19[^,],%d,%f,%d", &id_pelanggan, jenis_cucian,
	                       &jumlah, &total_biaya, &status_selesai) == 5) {
	                if (status_selesai == 1) {
	                    printf(WARNA_SIAN"ID Pelanggan: %d, Jenis Cucian: %s, Jumlah: %d, Total Biaya: Rp.%.0f\n",
	                           id_pelanggan, jenis_cucian, jumlah, total_biaya);
	                }
	            }
	        }
	    }
	
	    fclose(file); 
	}
	
	// Fungsi pencarian pelanggan berdasarkan ID menggunakan Linear Search
	void cariPelanggan(Pelanggan pelanggan[], int jumlah_pelanggan, int idDicari) {
	    int ditemukan = 0;
	    printf(WARNA_KUNING"Hasil pencarian:\n"WARNA_RESET);
	    for (int i = 0; i < jumlah_pelanggan; i++) {
	        if (pelanggan[i].id == idDicari) {
	            printf(WARNA_SIAN"ID: %d, Nama: %s, Alamat: %s, Telepon: %s\n"WARNA_RESET,
	                   pelanggan[i].id, pelanggan[i].nama, pelanggan[i].alamat, pelanggan[i].telepon);
	            ditemukan = 1;
	            break;
	        }
	    }
	    if (!ditemukan) {
	        printf(WARNA_KUNING"Pelanggan dengan ID '%d' tidak ditemukan.\n"WARNA_RESET, idDicari);
	    }
	}
	
	// Fungsi pengurutan pesanan berdasarkan total biaya dengan metode Bubble Sort
	void urutPesanan(Pesanan pesanan[], int jumlah_pesanan, Pelanggan pelanggan[], int jumlah_pelanggan) {
	    for (int i = 0; i < jumlah_pesanan - 1; i++) {
	        for (int j = 0; j < jumlah_pesanan - i - 1; j++) {
	            if (pesanan[j].total_biaya > pesanan[j + 1].total_biaya) {
	                Pesanan temp = pesanan[j];
	                pesanan[j] = pesanan[j + 1];
	                pesanan[j + 1] = temp;
	                simpanData(pelanggan, jumlah_pelanggan, pesanan, jumlah_pesanan);
	            }
	        }
	    }
	}
	
	// Fungsi utama yang akan dijalankan pertama kali saat program dijalankan
	int main() {
	    Pelanggan data_pelanggan[100];
	    Pesanan data_pesanan[100];
	    int jumlah_pelanggan = 0;
	    int jumlah_pesanan = 0;
	    int pilihan;
	
	    jumlah_pelanggan = bacaDataPelanggan(data_pelanggan);
	    jumlah_pesanan = bacaDataPesanan(data_pesanan);
		
		system("cls");
	
	    do {
	    	JudulProgram();
	        printf(WARNA_SIAN"\n\t\t\t==============================================\n");
	        printf("\t\t\t||                MENU UTAMA                ||\n");
	        printf(WARNA_SIAN"\t\t\t==============================================\n");
	        printf("\t\t\t||" WARNA_RESET WARNA_MERAH " 1 | Tambah Pelanggan                     "WARNA_RESET WARNA_SIAN  "||\n");
	        printf("\t\t\t||" WARNA_RESET WARNA_MERAH " 2 | Pesan Laundry                        "WARNA_RESET WARNA_SIAN  "||\n");
	        printf("\t\t\t||" WARNA_RESET WARNA_MERAH " 3 | Daftar Pesanan Belum Selesai         "WARNA_RESET WARNA_SIAN  "||\n");
	        printf("\t\t\t||" WARNA_RESET WARNA_MERAH " 4 | Tandai Pesanan Selesai               "WARNA_RESET WARNA_SIAN  "||\n");
	        printf("\t\t\t||" WARNA_RESET WARNA_MERAH " 5 | Riwayat Pesanan Selesai              "WARNA_RESET WARNA_SIAN  "||\n");
	        printf("\t\t\t||" WARNA_RESET WARNA_MERAH " 6 | Cari Pelanggan                       "WARNA_RESET WARNA_SIAN  "||\n");
	        printf("\t\t\t||" WARNA_RESET WARNA_MERAH " 7 | Urut Pesanan berdasarkan total biaya "WARNA_RESET WARNA_SIAN  "||\n");
	        printf("\t\t\t||" WARNA_RESET WARNA_MERAH " 8 | Keluar                               "WARNA_RESET WARNA_SIAN  "||\n");
	        printf("\t\t\t==============================================\n");
	        printf("\t\t\t||" WARNA_PUTIH "    Dibuat Oleh : Fattan Naufan Islami    " WARNA_SIAN "||\n");
	        printf("\t\t\t==============================================\n"WARNA_RESET);
	        printf("\t\t\t\t");
	        DelayPrintPilihan("Pilihan Anda : ", 50);
	        scanf("%d", &pilihan);
	        
	
	        switch (pilihan) {
	            case 1:
	                system("cls");
	                JudulPesan();
	                printf("\n");
	                tambahPelangganDanSimpan(data_pelanggan, &jumlah_pelanggan);
	                getch();
	                system("cls");
	                break;
	            case 2:
	                system("cls");
	                JudulPesanLaundry();
	                pesanLaundryDanSimpan(data_pelanggan, jumlah_pelanggan, data_pesanan, &jumlah_pesanan);
	                getch();
	                system("cls");
	                break;
	            case 3:
	                system("cls");
	                JudulPendingOrder();
	                RiwayatPesananTertunda(); 
	                getch();
	                system("cls");	
	                break;
	            case 4:
	                system("cls");
	                JudulMarkComplete();
	                pesananSelesai(data_pesanan, jumlah_pesanan, data_pelanggan, jumlah_pelanggan);
	                getch();
	                system("cls");
	                break;
	            case 5:
	                system("cls");
	                JudulCompleteOrder();
	                RiwayatPesananSelesai();
	                getch();
	                system("cls");
	                break;
	            case 6: {
	                int idDicari;
	
	                system("cls");
	                JudulCariPelanggan();
	                printf(WARNA_PATMA"Masukkan ID pelanggan yang dicari: "WARNA_KUNING);
	                scanf("%d", &idDicari);
	                cariPelanggan(data_pelanggan, jumlah_pelanggan, idDicari);
	                getch();
	                system("cls");
	                break;
	            }
	            case 7:
	                system("cls");
	                JudulSortOrder();
	                urutPesanan(data_pesanan, jumlah_pesanan, data_pelanggan, jumlah_pelanggan);
	                DelayPrintExit("Pesanan berhasil diurutkan berdasarkan total biaya yang paling rendah ke paling besar...", 50);
	                system("cls");
	                break;
	            case 8:
	                system("cls");
	                TerimaKasih();
	                DelayPrintExit("Tekan Tombol Apapun Untuk Keluar Dari Aplikasi Ini...", 50);
	                getch();
	                break;
	            default:
	                printf("\t\t\t\t");
	                DelayPrintSalahInput("Pilihan tidak valid...", 50);
	                system("cls");
	        }
	    } while (pilihan != 8);
	
	    simpanData(data_pelanggan, jumlah_pelanggan, data_pesanan, jumlah_pesanan);
	
	    return 0;
	}
