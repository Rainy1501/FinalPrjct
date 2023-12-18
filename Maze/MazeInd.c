#include <stdio.h>
#include <stdbool.h>
#include <conio.h> 
#include <windows.h>
#include <time.h>
#include <string.h>

#define UKURAN 10
#define JMLH_LVL 2 // Jumlah dari level di game
#define SKORPLAYER 20 // Jumlah maksimum dari pemain di papan skor

// Kode warna dari ANSI
#define WARNA_HITAM     "\x1b[30m"
#define WARNA_MERAH     "\x1b[31m"
#define WARNA_HIJAU   "\x1b[32m"
#define WARNA_KUNING  "\x1b[33m"
#define WARNA_BIRU    "\x1b[34m"
#define WARNA_PATMA "\x1b[35m"
#define WARNA_SIYAN    "\x1b[36m"
#define WARNA_PUTIH "\x1b[37m"
#define LATAR_WARNA_HITAM "\x1b[40m"
#define LATAR_WARNA_MERAH "\x1b[41m"
#define LATAR_WARNA_HIJAU "\x1b[42m"
#define LATAR_WARNA_KUNING "\x1b[43m"
#define LATAR_WARNA_BIRU "\x1b[44m"
#define LATAR_WARNA_PATMA "\x1b[45m"
#define LATAR_WARNA_SIYAN "\x1b[46m"
#define LATAR_WARNA_PUTIH "\x1b[47m"

#define WARNA_RESET   "\x1b[0m"

typedef struct {
	char NamaPemain [30];
	int skor;
} Player; 

// Fungsi membuat Tampilan Utama dari Permainan
void TampilanUtama() {
    system("cls"); // Membersihkan konsol atau tampilan Command Promt (CMD)
    printf(WARNA_SIYAN "Selamat datang di Maze Game!\n" WARNA_RESET); // Menampilkan judul permainan
    printf(WARNA_HIJAU"1. Mulai Permainan\n"); // Menampilkan pilihan menu
    printf("2. Liat Papan Peringkat\n"); // Menampilkan pilihan menu
    printf("3. Keluar\n" WARNA_RESET); // Menampilkan pilihan menu
}

// Fungsi untuk meletakkan posisi kursor pada konsol atau command promt (CMD)
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Sebuah fungsi untuk membuat maze dengan keterbatasan penglihatan
void printMaze(int maze[UKURAN][UKURAN], int playerX, int playerY, int skor, clock_t startTime) { // Mengambil maze, posisi pemain, skor, dan waktu mulai sebagai parameter
    system("cls"); // Membersihkan konsol atau tampilan Command Promt (CMD)
    clock_t currentTime = clock(); // Mengambil waktu saat ini
    double timeElapsed = ((double)(currentTime - startTime)) / CLOCKS_PER_SEC; // Menghitung waktu yang telah berlalu

    // Membuat batasan bagian atas dari kotak
    printf(WARNA_MERAH "+" WARNA_RESET);
    for (int i = 0; i < UKURAN * 2; i++) {
        printf(WARNA_HIJAU"-" WARNA_RESET);
    }
    printf(WARNA_MERAH"+" WARNA_RESET);
    printf(WARNA_SIYAN " Skor: %d" WARNA_RESET, skor); // Menampilkan skor

    // Membuat maze dan pemain di sekitar kotak
    for (int i = 0; i < UKURAN; i++) {
        printf("\n" WARNA_HIJAU "|" WARNA_RESET); // Bagian batasan kiri dari kotak
        for (int j = 0; j < UKURAN; j++) {
            int distance = abs(playerX - j) + abs(playerY - i);
            if (distance == 0 || distance <= 4) {
                if (i == playerY && j == playerX) {
                    printf(WARNA_KUNING "P " WARNA_RESET); // Wujud dari pemain
                } else if (maze[i][j] == 1) {
                    printf(WARNA_SIYAN"# "WARNA_RESET); // Dinding yang bakal ditampilin ketika berada di jangkauan yang bisa dilihat
                } else {
                    printf("  "); // Ruang kosong
                }
            } else {
                printf("  "); // Menyembunyikan dinding yang berada diluar jangkauan penglihatan
            }
        }
        printf(WARNA_HIJAU "|" WARNA_RESET); // Bagian batasan kanan dari kotak
    }

    // Bagian batasan bawah dari kotak
    printf("\n" WARNA_MERAH "+" WARNA_RESET);
    for (int i = 0; i < UKURAN * 2; i++) {
        printf(WARNA_HIJAU"-"WARNA_RESET);
    }
    printf(WARNA_MERAH"+" WARNA_RESET);
    printf(WARNA_SIYAN " \nWaktu: %.2f Detik" WARNA_RESET, timeElapsed); // Menampilkan waktu yang telah berlalu

    // Menampilkan instruksi cara bermain di bawah layar permainan
    gotoxy(0, UKURAN + 4); // Mengatur posisi dari Cara Bermain
    printf(WARNA_PATMA "Cara Bermain:\n");
    printf("W - Maju keatas\n");
    printf("S - Maju Kebawah\n");
    printf("A - Maju kekiri\n");
    printf("D - Maju kekanan\n");
    printf("K - Keluar\n" WARNA_RESET);
}

// Fungsi untuk bermain game
void playMazeGame(int levels[JMLH_LVL][UKURAN][UKURAN], int* totalskor, Player papanperingkat[]) {
    int skor = 0; // Inisiialisasi skor untuk level saat ini
    clock_t startTime, endTime; // Inisiialisasi waktu mulai dan waktu selesai
    double timeTaken; // Inisiialisasi waktu yang dibutuhkan untuk menyelesaikan level saat ini

    for (int level = 0; level < JMLH_LVL; level++) { // Looping untuk setiap level
        int playerX = 0, playerY = 0; // Inisiialisasi posisi pemain
        int exitX = UKURAN - 1, exitY = UKURAN - 1; // Inisiialisasi posisi exit
        int moves = 0; // Variabel untuk menghitung gerakan pemain
        clock_t startTime = clock(); // Memulai waktu untuk level

        while (playerX != exitX || playerY != exitY) {
            
            printMaze(levels[level], playerX, playerY, *totalskor, startTime); // Menampilkan maze, pemain, dan skor

            char move = getch();

            int newX = playerX, newY = playerY;

            switch (move) {
                case 'W':
                case 'w':
                    newY--;
                    break;
                case 'S':
                case 's':
                    newY++;
                    break;
                case 'A':
                case 'a':
                    newX--;
                    break;
                case 'D':
                case 'd':
                    newX++;
                    break;
                case 'K':
                case 'k':
                    printf("Mengakhiri Permainan...\n");
                    getch();
                    return;
                default:
                    continue;
            }

            if (newX >= 0 && newX < UKURAN && newY >= 0 && newY < UKURAN && levels[level][newY][newX] == 0) {
                playerX = newX;
                playerY = newY;
                moves++; // Menambahkan hitungan gerakan yang valid
            }
        }

        clock_t endTime = clock();
        timeTaken = ((double)(endTime - startTime)) / CLOCKS_PER_SEC; // Kalkulasikan waktu yang dibutuhkan untuk menyelesaikan level

        printf(WARNA_KUNING "Congratulations! You reached the exit of level %d!\n" WARNA_RESET, level + 1);
        printf("Total moves: %d\n", moves);
        printf("Time taken: %.2f seconds\n" WARNA_RESET, timeTaken);

        // Mengkalkulasi skor berdasarkan waktu dan gerakan (rumus sederhana)
        skor = 1000 - (moves * 10) - (int)(timeTaken * 10);
        if (skor < 0) {
            skor = 0; // Memastiin skor tidak negatif
        }
        printf("Your skor for level %d: %d\n", level + 1, skor);

        // Menambah skor pemain saat ini ke skor total
        *totalskor += skor;

        // Mengoper skor ke fungsi printMaze
        printMaze(levels[level], playerX, playerY, *totalskor, startTime);

        getch();
        system("cls");
    }

    printf(WARNA_SIYAN "Selamat! Kamu sudah menamatkan semua tantangan\n" WARNA_RESET);
    printf("Total skor dari semua level : %d\n", *totalskor);
    PlaySound(TEXT("Welldone.wav"), NULL, SND_FILENAME);
    PlaySound(TEXT("Victory.wav"), NULL, SND_FILENAME);

    printf("Masukkan namamu yang akan ditampilkan di papan peringkat: ");
    char NamaPemain[50];
    fgets(NamaPemain, sizeof(NamaPemain), stdin);
    NamaPemain[strcspn(NamaPemain, "\n")] = '\0'; // Membuang karakter newline dari NamaPemain

    // Cari posisi untuk memasukkan skor pemain saat ini
    int insertPosition = -1;
    for (int i = SKORPLAYER - 1; i >= 0; i--) {
        if (*totalskor > papanperingkat[i].skor) {
            insertPosition = i;
        }
    }

    // Geser skor yang ada untuk memberi ruang bagi skor pemain saat ini
    if (insertPosition != -1) {
        for (int i = SKORPLAYER - 1; i > insertPosition; i--) {
            strcpy(papanperingkat[i].NamaPemain, papanperingkat[i - 1].NamaPemain);
            papanperingkat[i].skor = papanperingkat[i - 1].skor;
        }
        strcpy(papanperingkat[insertPosition].NamaPemain, NamaPemain);
        papanperingkat[insertPosition].skor = *totalskor;
    }

}

// Fungsi untuk menampilkan papan peringkat
void TampilanPapanPeringkat(Player papanperingkat[]) {
    system("cls");
    printf(WARNA_KUNING "*** Papan Peringkat ***\n\n");
    printf("Peringkat\tNama Pemain\tSkor\n");

    for (int i = 0; i < SKORPLAYER; i++) {
        printf("%d.\t\t%s\t\t%d\n", i + 1, papanperingkat[i].NamaPemain, papanperingkat[i].skor);
    }
}

// Fungsi untuk menyimpan papan peringkat ke file
void SimpanPapanPeringkat(Player papanperingkat[]) {
    FILE *file;
    file = fopen("leaderboard.txt", "w");
    if (file != NULL) {
        for (int i = 0; i < SKORPLAYER; i++) {
            fprintf(file, "%s %d\n", papanperingkat[i].NamaPemain, papanperingkat[i].skor);
        }
        fclose(file);
    } else {
        printf("Gagal membuka file untuk menyimpan data papan peringkat\n");
        printf("Coba buat file leaderboard.txt di direktori yang sama dengan program MazeInd.exe\n");
        getch();
    }
}

// Fungsi untuk memuat papan peringkat dari file
void MemuatPapanPeringkat(Player papanperingkat[]) {
    FILE *file;
    file = fopen("leaderboard.txt", "r");
    if (file != NULL) {
        for (int i = 0; i < SKORPLAYER; i++) {
            fscanf(file, "%s %d\n", papanperingkat[i].NamaPemain, &papanperingkat[i].skor);
        }
        fclose(file);
    } else {
        printf("File tidak ada atau tidak bisa dibuka\n");
    }
}


int main() {
	int totalskor = 0; // Inisiialisasi skor total
	Player papanperingkat[SKORPLAYER] = { 0 }; // Inisiialisasi papan peringkat
	MemuatPapanPeringkat(papanperingkat); // Memuat papan peringkat sebelumnya dari file

    int levels[JMLH_LVL][UKURAN][UKURAN] = {
                    { // Level 1
                    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                    {0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
                    {1, 0, 0, 0, 1, 1, 1, 1, 0, 1},
                    {1, 1, 1, 0, 1, 0, 0, 0, 0, 1},
                    {1, 0, 0, 0, 0, 0, 1, 1, 1, 1},
                    {1, 1, 1, 1, 1, 0, 1, 0, 0, 1},
                    {1, 0, 0, 0, 0, 0, 0, 0, 1, 1},
                    {1, 1, 1, 1, 1, 1, 1, 0, 1, 0},
                    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                    {1, 1, 1, 1, 1, 1, 1, 1, 1, 0}
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
        };

    PlaySound(TEXT("welcome.wav"), NULL, SND_FILENAME);
    system("cls");
    printf(WARNA_MERAH "Now Loading" WARNA_RESET);
    Sleep(500);
    printf(WARNA_KUNING ". " WARNA_RESET);
    Sleep(500);
    printf(WARNA_HIJAU ". " WARNA_RESET);
    Sleep(500);
    printf(WARNA_PATMA ". " WARNA_RESET);
    Sleep(500);
    printf(WARNA_BIRU ". " WARNA_RESET);
    Sleep(500);
    printf(".\n");

    system("cls");
    printf(WARNA_MERAH "Welcome to the Maze Game!\n" WARNA_RESET);
    printf(WARNA_HIJAU "Press any key to start..." WARNA_RESET);

    getch(); // Menunggu user untuk menekan tombol apapun
    system("cls"); // Membersihkan konsol atau tampilan Command Promt (CMD)
    PlaySound(TEXT("Start.wav"), NULL, SND_FILENAME);
    PlaySound(TEXT("music.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

    int choice;
    
    do {
        TampilanUtama();
        printf(WARNA_MERAH"Masukkan pilihanmu (1-3): "WARNA_RESET);
        scanf("%d", &choice);
        fflush(stdin);
        
        switch (choice) {
            case 1:
                system("cls");
                playMazeGame(levels, &totalskor, papanperingkat); // Pass levels array to the playMazeGame function
                TampilanPapanPeringkat(papanperingkat); // Melihatkan papan peringkat setelah permainan selesai
    			getch(); // Menunggu user untuk menekan tombol apapun
    			SimpanPapanPeringkat(papanperingkat); // Menyimpan papan peringkat yang telah diperbarui ke file
                system("cls");
                break;
            case 2:
                TampilanPapanPeringkat(papanperingkat);
                printf("\nTekan tombol apapun untuk kembali ke menu utama...");
                getch();
                break;
            case 3:
                printf("Keluar dari permainan...\n");
                break;
            default:
                printf("Invalid choice. Please enter a number between 1 and 3.\n");
                break;
        }
    } while (choice != 3);

    return 0;
}
