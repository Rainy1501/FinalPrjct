/*
Nama  : Fattan Naufan Islami
NIM   : 23343037
Prodi : Informatika
*/

#include <stdio.h>
#include <conio.h> 
#include <windows.h>
#include <time.h>
#include <string.h>

#define UKURAN 10 // Ukuran dari maze
#define JMLH_LVL 5 // Jumlah dari level di game
#define SKORPemain 20 // Jumlah maksimum dari pemain di papan skor

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

typedef struct { // Struktur data untuk menyimpan nama pemain dan skor pemain
	char NamaPemain [30]; // Variabel untuk menyimpan nama pemain
	int skor; // Variabel untuk menyimpan skor pemain
} Pemain; // Nama dari struktur data

// Fungsi membuat Tampilan Utama dari Permainan
void TampilanUtama() {
    system("cls"); // Membersihkan konsol atau tampilan Command Promt (CMD)
    printf(WARNA_SIAN"=====================================\n");
    printf("|              MAZE GAME            |\n"); 
    printf("=====================================\n");
    printf("|1. Mulai Permainan                 |\n"); 
    printf("|2. Liat Papan Peringkat            |\n"); 
    printf("|3. Keluar                          |\n" ); 
    printf("=====================================\n");
    printf("|"WARNA_RESET);
	printf(WARNA_MERAH"Dibuat oleh: Fattan Naufan Islami  "WARNA_RESET);
	printf(WARNA_SIAN"|\n");
    printf("=====================================\n\n"WARNA_RESET);
    
}

// Sebuah fungsi untuk membuat maze dengan keterbatasan penglihatan
void TampilanMaze(int maze[UKURAN][UKURAN], int PemainX, int PemainY, int skor, clock_t WaktuMulai) { // Mengambil maze, posisi pemain, skor, dan waktu mulai sebagai parameter
    system("cls"); // Membersihkan konsol atau tampilan Command Promt (CMD)
    clock_t WaktuSekarang = clock(); // Mengambil waktu saat ini
    double WaktuBerlalu = ((double)(WaktuSekarang - WaktuMulai)) / CLOCKS_PER_SEC; // Menghitung waktu yang telah berlalu

    // Membuat batasan bagian atas dari kotak
    printf(WARNA_MERAH "+" WARNA_RESET); // Bagian batasan kiri dari kotak
    for (int i = 0; i < UKURAN * 2; i++) { // Looping untuk membuat batasan atas dari kotak
        printf(WARNA_HIJAU"-" WARNA_RESET); // Bagian batasan atas dari kotak
    }
    printf(WARNA_MERAH"+" WARNA_RESET); // Bagian batasan kanan dari kotak
    printf(WARNA_SIAN " Skor: %d" WARNA_RESET, skor); // Menampilkan skor

    // Membuat maze dan pemain di sekitar kotak
    for (int i = 0; i < UKURAN; i++) { // Looping untuk membuat maze dan pemain
        printf("\n" WARNA_HIJAU "|" WARNA_RESET); // Bagian batasan kiri dari kotak
        for (int j = 0; j < UKURAN; j++) { // Looping untuk membuat maze dan pemain
            int Jarak = abs(PemainX - j) + abs(PemainY - i); // Menghitung jarak antara pemain dan dinding
            if (Jarak == 0 || Jarak <= 4) { // Jika jarak antara pemain dan dinding adalah 0 atau kurang dari sama dengan 4
                if (i == PemainY && j == PemainX) { // Jika posisi pemain sama dengan posisi dinding
                    printf(WARNA_KUNING "P " WARNA_RESET); // Wujud dari pemain
                } else if (maze[i][j] == 1) { // Jika posisi dinding sama dengan 1
                    printf(WARNA_SIAN"# "WARNA_RESET); // Dinding yang bakal ditampilin ketika berada di jangkauan yang bisa dilihat
                } else { // Jika posisi dinding sama dengan 0
                    printf("  "); // Ruang kosong
                } 
            } else { // Jika jarak antara pemain dan dinding lebih dari 4
                printf("  "); // Menyembunyikan dinding yang berada diluar jangkauan penglihatan
            }
        }
        printf(WARNA_HIJAU "|" WARNA_RESET); // Bagian batasan kanan dari kotak
    }

    // Bagian batasan bawah dari kotak
    printf("\n" WARNA_MERAH "+" WARNA_RESET); // Bagian batasan kiri dari kotak
    for (int i = 0; i < UKURAN * 2; i++) { // Looping untuk membuat batasan bawah dari kotak
        printf(WARNA_HIJAU"-"WARNA_RESET); // Bagian batasan bawah dari kotak
    }
    printf(WARNA_MERAH"+" WARNA_RESET); // Bagian batasan kanan dari kotak
    printf(WARNA_SIAN " \nWaktu: %.2f Detik" WARNA_RESET, WaktuBerlalu); // Menampilkan waktu yang telah berlalu di bawah layar permainan

    // Menampilkan instruksi cara bermain di bawah layar permainan
    printf(WARNA_PATMA "\n\nCara Bermain:\n"); 
    printf("W - Maju keatas\n");
    printf("S - Maju Kebawah\n");
    printf("A - Maju kekiri\n");
    printf("D - Maju kekanan\n");
    printf("K - Keluar\n\n" WARNA_RESET);\
}

// Fungsi untuk bermain game
void PermainanMaze(int level[JMLH_LVL][UKURAN][UKURAN], int* totalskor, Pemain papanperingkat[]) { // Mengambil level array, skor total, dan papan peringkat sebagai parameter
    int skor = 0; // Inisiialisasi skor untuk level saat ini
    clock_t WaktuMulai, endTime; // Inisiialisasi waktu mulai dan waktu selesai
    double WaktuBerlalu; // Inisialisasi waktu yang dibutuhkan untuk menyelesaikan level saat ini

    for (int level = 0; level < JMLH_LVL; level++) { // Looping untuk setiap level
        int PemainX = 0, PemainY = 0; // Inisialisasi posisi pemain
        int KeluarX = UKURAN - 1, KeluarY = UKURAN - 1; // Inisiialisasi posisi Keluar
        int Gerakan = 0; // Variabel untuk menghitung gerakan pemain
        clock_t WaktuMulai = clock(); // Memulai waktu untuk level

        while (PemainX != KeluarX || PemainY != KeluarY) { // Looping untuk setiap gerakan pemain
            TampilanMaze(level[level], PemainX, PemainY, *totalskor, WaktuMulai); // Menampilkan maze, pemain, dan skor
        	char Gerak = getch(); // Mengambil input dari user berdasarkan tombol yang ditekan
            int PosisiX = PemainX, PosisiY = PemainY; // Inisiialisasi posisi baru pemain

            switch (Gerak) { // Switch case untuk setiap gerakan pemain
                case 'W':
                case 'w':
                    PosisiY--;
                    break;
                case 'S':
                case 's':
                    PosisiY++;
                    break;
                case 'A':
                case 'a':
                    PosisiX--;
                    break;
                case 'D':
                case 'd':
                    PosisiX++; 
                    break;
                case 'K':
                case 'k':
                    printf(WARNA_PATMA"Mengakhiri Permainan...\n"WARNA_RESET); 
                    getch();
                    return;
                default:
                    continue;
            }

            if (PosisiX >= 0 && PosisiX < UKURAN && PosisiY >= 0 && PosisiY < UKURAN && level[level][PosisiY][PosisiX] == 0) {  // Jika gerakan pemain valid
                PemainX = PosisiX;  // Memindahkan pemain ke posisi baru
                PemainY = PosisiY;  // Memindahkan pemain ke posisi baru
                Gerakan++; // Menambahkan hitungan gerakan yang valid
            }
        }

        clock_t endTime = clock(); // Menghentikan waktu untuk level
        WaktuBerlalu = ((double)(endTime - WaktuMulai)) / CLOCKS_PER_SEC; // Kalkulasikan waktu yang dibutuhkan untuk menyelesaikan level

        // Mengkalkulasi skor berdasarkan waktu dan gerakan (rumus sederhana)
        skor = 1000 - (Gerakan * 10) - (int)(WaktuBerlalu * 10);
        if (skor < 0) { // Jika skor negatif
            skor = 0; // Memastiin skor tidak negatif
        }

        // Menambah skor pemain saat ini ke skor total
        *totalskor += skor;

        // Mengoper skor ke fungsi TampilanMaze
        TampilanMaze(level[level], PemainX, PemainY, *totalskor, WaktuMulai);
    
        printf(WARNA_KUNING "Selamat! Kamu sudah mencapai jalan keluar dari level %d!\n" WARNA_RESET, level + 1); // Menampilkan pesan saat menyelesaikan level saat ini
        printf(WARNA_SIAN"Jumlah Gerakan : %d\n", Gerakan); // Menampilkan jumlah gerakan yang dibutuhkan untuk menyelesaikan level saat ini
        printf("Waktu dibutuhkan : %.2f seconds\n", WaktuBerlalu); // Menampilkan waktu yang dibutuhkan untuk menyelesaikan level saat ini
        printf("Skor kamu di level %d ialah : %d\n"WARNA_RESET, level + 1, skor); // Menampilkan skor pemain saat ini
        printf(WARNA_HIJAU"Tekan tombol apapun untuk melanjutkan ke level selanjutnya...\n"WARNA_RESET); // Menampilkan pesan untuk melanjutkan ke level selanjutnya
        getch();

        system("cls");
    }

    printf(WARNA_SIAN "Selamat! Kamu sudah menamatkan semua tantangan\n" WARNA_RESET);
    printf("Total skor dari semua level : %d\n", *totalskor); // Menampilkan skor total
    PlaySound(TEXT("Welldone.wav"), NULL, SND_FILENAME); // Memainkan suara saat menyelesaikan permainan
    PlaySound(TEXT("Victory.wav"), NULL, SND_FILENAME); // Memainkan suara saat menyelesaikan permainan

    printf("Masukkan namamu yang akan ditampilkan di papan peringkat: "); // Meminta nama pemain
    char NamaPemain[50]; // Inisiialisasi nama pemain
    fgets(NamaPemain, sizeof(NamaPemain), stdin); // Mengambil input nama pemain
    NamaPemain[strcspn(NamaPemain, "\n")] = '\0'; // Membuang karakter newline dari NamaPemain

    // Cari posisi untuk memasukkan skor pemain saat ini
    int SelipanPosisi = -1; // Inisiialisasi posisi untuk memasukkan skor pemain saat ini
    for (int i = SKORPemain - 1; i >= 0; i--) { // Looping untuk mencari posisi untuk memasukkan skor pemain saat ini
        if (*totalskor > papanperingkat[i].skor) { // Jika skor pemain saat ini lebih besar dari skor pemain di posisi i
            SelipanPosisi = i; // Mengatur posisi untuk memasukkan skor pemain saat ini
        }
    }

    // Geser skor yang ada untuk memberi ruang bagi skor pemain saat ini
    if (SelipanPosisi != -1) { // Jika posisi untuk memasukkan skor pemain saat ini tidak sama dengan -1
        for (int i = SKORPemain - 1; i > SelipanPosisi; i--) { // Looping untuk menggeser skor yang ada untuk memberi ruang bagi skor pemain saat ini
            strcpy(papanperingkat[i].NamaPemain, papanperingkat[i - 1].NamaPemain); // Menggeser nama pemain
            papanperingkat[i].skor = papanperingkat[i - 1].skor; // Menggeser skor pemain
        }
        strcpy(papanperingkat[SelipanPosisi].NamaPemain, NamaPemain); // Memasukkan nama pemain saat ini ke papanperingkat
        papanperingkat[SelipanPosisi].skor = *totalskor; // Memasukkan skor pemain saat ini ke papanperingkat
    }

}

// Fungsi untuk menampilkan papan peringkat
void TampilanPapanPeringkat(Pemain papanperingkat[]) { // Mengambil papan peringkat sebagai parameter
    system("cls"); // Membersihkan konsol atau tampilan Command Promt (CMD)
    printf(WARNA_KUNING "\t*** Papan Peringkat ***\n\n"); // Menampilkan judul papan peringkat
    printf("Peringkat\tNama Pemain\tSkor\n"); // Menampilkan header papan peringkat

    for (int i = 0; i < SKORPemain; i++) { // Looping untuk menampilkan papan peringkat
        printf("%d.\t\t%s\t\t%d\n", i + 1, papanperingkat[i].NamaPemain, papanperingkat[i].skor); // Menampilkan papan peringkat
    }
}

// Fungsi untuk menyimpan papan peringkat ke file
void SimpanPapanPeringkat(Pemain papanperingkat[]) { // Mengambil papan peringkat sebagai parameter
    FILE *file; // Inisiialisasi file
    file = fopen("papanperingkat.txt", "w"); // Membuka file untuk menyimpan data papan peringkat
    if (file != NULL) { // Jika file tidak sama dengan NULL
        for (int i = 0; i < SKORPemain; i++) { // Looping untuk menyimpan data papan peringkat ke file
            fprintf(file, "%s %d\n", papanperingkat[i].NamaPemain, papanperingkat[i].skor); // Menyimpan data papan peringkat ke file
        }
        fclose(file); // Menutup file
    } else { // Jika file tidak ada
        printf("Gagal membuka file untuk menyimpan data papan peringkat\n"); // Menampilkan pesan error
        printf("Coba buat file papanperingkat.txt di direktori yang sama dengan program MazeInd.exe\n"); // Menampilkan pesan error
        getch(); // Menunggu user untuk menekan tombol apapun
    }
}

// Fungsi untuk memuat papan peringkat dari file
void MemuatPapanPeringkat(Pemain papanperingkat[]) { // Mengambil papan peringkat sebagai parameter
    FILE *file; // Inisiialisasi file
    file = fopen("papanperingkat.txt", "r"); // Membuka file untuk memuat data papan peringkat
    if (file != NULL) { // Jika file ada
        for (int i = 0; i < SKORPemain; i++) { // Looping untuk memuat data papan peringkat dari file
            fscanf(file, "%s %d\n", papanperingkat[i].NamaPemain, &papanperingkat[i].skor); // Memuat data papan peringkat dari file
        }
        fclose(file);  // Menutup file
    } else { // Jika file tidak ada
        printf("File tidak ada atau tidak bisa dibuka\n"); // Menampilkan pesan error
    }
}


int main() { // Fungsi utama
	int totalskor = 0; // Inisiialisasi skor total
	Pemain papanperingkat[SKORPemain] = { 0 }; // Inisiialisasi papan peringkat
	MemuatPapanPeringkat(papanperingkat); // Memuat papan peringkat sebelumnya dari file

    int level[JMLH_LVL][UKURAN][UKURAN] = { // Inisiialisasi maze
                    { // Level 1
                    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                    {0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
                    {1, 0, 0, 0, 1, 1, 1, 1, 0, 1},
                    {1, 1, 1, 0, 1, 0, 0, 0, 0, 1},
                    {1, 0, 0, 0, 0, 0, 1, 1, 1, 1},
                    {1, 1, 1, 1, 1, 0, 1, 0, 0, 1},
                    {1, 0, 0, 0, 0, 0, 0, 0, 1, 1},
                    {1, 1, 1, 1, 1, 1, 1, 0, 1, 0},
                    {1, 0, 0, 0, 0, 0, 0, 0, 1, 0},
                    {1, 1, 1, 1, 1, 1, 1, 0, 0, 0}
                },
                    { // Level 2
                    {0, 0, 1, 1, 1, 1, 1, 1, 1, 1},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                    {1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
                    {1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
                    {1, 0, 1, 1, 1, 1, 0, 1, 0, 1},
                    {1, 0, 1, 0, 0, 0, 0, 1, 0, 1},
                    {1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
                    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                    {1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
                    {1, 1, 1, 1, 1, 1, 1, 1, 1, 0}
                },
                    { // Level 3
                    {0, 0, 1, 1, 1, 1, 1, 1, 1, 1},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                    {1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
                    {1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
                    {1, 0, 1, 1, 1, 1, 0, 1, 0, 1},
                    {1, 0, 1, 0, 0, 0, 0, 1, 0, 1},
                    {1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
                    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                    {1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
                    {1, 1, 1, 1, 1, 1, 1, 1, 1, 0}
                }, 
                    { // Level 4
                    {0, 0, 1, 1, 1, 1, 1, 1, 1, 1},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                    {1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
                    {1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
                    {1, 0, 1, 1, 1, 1, 0, 1, 0, 1},
                    {1, 0, 1, 0, 0, 0, 0, 1, 0, 1},
                    {1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
                    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                    {1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
                    {1, 1, 1, 1, 1, 1, 1, 1, 1, 0}
                },
                    { // Level 5
                    {0, 0, 1, 1, 1, 1, 1, 1, 1, 1},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                    {1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
                    {1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
                    {1, 0, 1, 1, 1, 1, 0, 1, 0, 1},
                    {1, 0, 1, 0, 0, 0, 0, 1, 0, 1},
                    {1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
                    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                    {1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
                    {1, 1, 1, 1, 1, 1, 1, 1, 1, 0}
                },
        };

    PlaySound(TEXT("welcome.wav"), NULL, SND_FILENAME); // Memainkan suara saat memulai permainan
    system("cls"); // Membersihkan konsol atau tampilan Command Promt (CMD)
    printf(WARNA_MERAH "Now Loading" WARNA_RESET); // Menampilkan tulisan Now Loading
    Sleep(500); // Menunggu 0.5 detik
    printf(WARNA_KUNING ". " WARNA_RESET); // Menampilkan titik
    Sleep(500); // Menunggu 0.5 detik
    printf(WARNA_HIJAU ". " WARNA_RESET); // Menampilkan titik
    Sleep(500); // Menunggu 0.5 detik
    printf(WARNA_PATMA ". " WARNA_RESET); // Menampilkan titik
    Sleep(500); // Menunggu 0.5 detik
    printf(WARNA_BIRU ". " WARNA_RESET); // Menampilkan titik
    Sleep(500); // Menunggu 0.5 detik
    printf(".\n"); // Menampilkan titik

    system("cls"); // Membersihkan konsol atau tampilan Command Promt (CMD)
    printf(WARNA_MERAH "Selamat datang di permainan Maze\n" WARNA_RESET); // Menampilkan judul permainan
    printf(WARNA_HIJAU "Tekan tombol apapun untuk memulai permainan..." WARNA_RESET); // Menampilkan pesan untuk memulai permainan

    getch(); // Menunggu user untuk menekan tombol apapun
    system("cls"); // Membersihkan konsol atau tampilan Command Promt (CMD)
    PlaySound(TEXT("Start.wav"), NULL, SND_FILENAME); // Memainkan suara saat memulai permainan
    PlaySound(TEXT("music.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP); // Memainkan musik saat permainan dimulai

    int pilihan; // Inisiialisasi pilihan menu
    
    do { // Looping untuk menampilkan menu utama
        TampilanUtama(); // Menampilkan menu utama
        printf(WARNA_HIJAU"Masukkan pilihanmu (1-3): "WARNA_RESET); // Menampilkan pesan untuk memilih menu
        scanf("%d", &pilihan); // Mengambil input dari user
        fflush(stdin); // Membersihkan input buffer
        
        switch (pilihan) { // Switch case untuk setiap pilihan menu
            case 1:
                system("cls"); // Membersihkan konsol atau tampilan Command Promt (CMD)
                PermainanMaze(level, &totalskor, papanperingkat); // Pass level array to the PermainanMaze function
                TampilanPapanPeringkat(papanperingkat); // Melihatkan papan peringkat setelah permainan selesai
    			getch(); // Menunggu user untuk menekan tombol apapun
    			SimpanPapanPeringkat(papanperingkat); // Menyimpan papan peringkat yang telah diperbarui ke file
                system("cls"); // Membersihkan konsol atau tampilan Command Promt (CMD)
                break; // Keluar dari switch case
            case 2: // Jika user memilih untuk melihat papan peringkat
                TampilanPapanPeringkat(papanperingkat); // Melihatkan papan peringkat
                printf("\nTekan tombol apapun untuk kembali ke menu utama..."); // Menampilkan pesan untuk kembali ke menu utama
                getch(); // Menunggu user untuk menekan tombol apapun
                break; // Keluar dari switch case
            case 3: // Jika user memilih untuk keluar dari permainan
                printf(WARNA_PATMA"Keluar dari permainan...\n"WARNA_RESET); // Menampilkan pesan keluar dari permainan
                break; // Keluar dari switch case
            default: // Jika input tidak valid
                printf("Pilihan salah. Masukkanlah angka 1 - 3.\n"); // Menampilkan pesan error
                break; // Keluar dari switch case
        }
    } while (pilihan != 3); // Looping untuk menampilkan menu utama

    return 0; // Mengembalikan nilai 0
}
