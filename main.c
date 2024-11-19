#include <stdio.h>
#include <string.h>

struct tokbuk {
    char id[100], buku[100], penulis[100];
    int harga, diskon, stock;
};
struct user {
    char email[30], username[30], password[30];
};
int login(int role);
void signup();
void menu_manager();
void manager_tambahitem();
void menu_kasir();
void menu_pelanggan();


int main() {
    int angka;
    printf("\n~~ Selamat Datang ~~\n");
    printf("Ketik sembarang angka untuk memulai, 0 untuk mengakhiri program: ");
    scanf("%d", &angka);

    while (angka!=0) {
        int role, menu_buyer;
        printf("Login sebagai? (manager(1)/kasir(2)/pelanggan(3)): ");
        scanf("%d", &role);

        switch (role)
        {
        case 1:
            if (login(role)) {
                menu_manager();
            }
            break;
        case 2:
            if (login(role)) {
                menu_kasir();
            }
            break;
        case 3:
            printf("Ketik (1) untuk sign up, (2) untuk login\n");
            scanf("%d", &menu_buyer);
            if (menu_buyer == 1){
                signup();
            } else if (menu_buyer == 2){
                if (login(role)) {
                menu_pelanggan();
                }
            } else break;
        
        default:
            printf("Role tidak dikenal.\n");
            break;
        }
        
        printf("\n~~ Selamat Datang ~~\n");
        printf("Ketik sembarang angka untuk memulai, 0 untuk mengakhiri program: ");
        scanf("%d", &angka);
    }

    return 0;
}

void signup(){
    FILE* f_signup;
    struct user regis;
    f_signup = fopen ("user.dat", "ab");
    if (!f_signup) {
        printf("Gagal membuka file.\n");
        return;
    }

    printf("Masukkan alamat email: ");
    scanf("%30s", regis.email);
    printf("Masukkan username (Maksimal 20 Karakter): ");
    scanf("%30s", regis.username);
    printf("Masukkan kata sandi: ");
    scanf("%30s", regis.password);

    fclose(f_signup);
}

int login(int role) {
    char username[20], password[20];
    printf("Masukkan username: ");
    scanf("%20s", username); 
           /*^ Membatasi jumlah input*/
    printf("Masukkan kata sandi: ");
    scanf("%20s", password);
           /*^ Membatasi jumlah input*/
    switch (role){
        case 1:
            if (strcmp(username, "manager") == 0 && strcmp(password, "1234") == 0) {
            return 1;
            }
            break;
        case 2:
            if (strcmp(username, "kasir") == 0 && strcmp(password, "4321") == 0) {
            return 1;
            }
            break;
        case 3:
            FILE* flogin;
            struct user login;
            flogin = fopen("user.dat", "rb");
            if (!flogin) {
                printf("Gagal membuka file\n");
                return 0;
            }

            while(fread(&login, sizeof(login), 1, flogin)){
                if (strcmp(login.username, username)==0 && strcmp(login.password, password)==0){
                    return 1;
                }
            }
            fclose(flogin);
            break;
        default:
            break;
    }
    printf("Nama atau kata sandi salah.\n");
    return 0;
}

void manager_tambahitem() {
    FILE *f_biner;
    struct tokbuk data;
    f_biner = fopen("databuku.dat", "ab");
    if (!f_biner) {
        printf("Gagal membuka file.\n");
        return;
    }

    printf("Masukkan ID               : "); 
    scanf("%s", data.id);
    printf("Masukkan Judul Buku       : "); 
    scanf(" %[^\n]", data.buku);
    printf("Masukkan Penulis          : "); 
    scanf(" %[^\n]", data.penulis);
    printf("Masukkan Harga            : "); 
    scanf("%d", &data.harga);
    do {
    printf("Masukkan Diskon (0 - 100) : "); 
    scanf("%d", &data.diskon);
    } while (data.diskon > 100 || data.diskon < 0);
    printf("Masukkan Jumlah           : "); 
    scanf("%d", &data.stock);

   
    fwrite(&data, sizeof(struct tokbuk), 1, f_biner);

    fclose(f_biner);
    printf("Data berhasil ditambahkan.\n");
}

void kasir_lihatitem() {
    FILE *f_biner;
    struct tokbuk data;

    f_biner = fopen("databuku.dat", "rb");
    if (!f_biner) {
        printf("Gagal membuka file.\n");
        return;
    }

    printf(" %-15s  %-30s  %-20s  %-7s  %-6s  %-7s \n", "ID", "Judul Buku", "Penulis", "Harga", "Diskon", "Stok");

    while (fread(&data, sizeof(struct tokbuk), 1, f_biner) != 0) {
        printf(" %-15.15s  %-30.30s  %-20.20s  %-7d  %-6d  %-7d \n", data.id, data.buku, data.penulis, data.harga, data.diskon, data.stock);
    }

    fclose(f_biner);
}

void menu_manager() {
    int pilihan;
    do {
        printf("\n== Menu Manager ==\n");
        printf("1. Tambah Item\n");
        printf("2. Edit Item\n");
        printf("3. Hapus Item\n");
        printf("4. Diskon\n");
        printf("5. Rekapitulasi dan Laporan\n");
        printf("6. Log Out\n");
        printf("Pilihan: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                manager_tambahitem();
                break;
            case 2:
                printf("Edit Item dipilih.\n");
                break;
            case 3:
                printf("Hapus Item dipilih.\n");
                break;
            case 4:
                printf("Diskon dipilih.\n");
                break;
            case 5:
                printf("Rekapitulasi dan Laporan dipilih.\n");
                break;
            case 6:
                printf("Log Out.\n");
                break;
            default:
                printf("Pilihan tidak valid.\n");
        }
    } while (pilihan != 6);
}

void menu_kasir() {
    int pilihan;
    do {
        printf("\n== Menu Kasir ==\n");
        printf("1. Lihat item\n");
        printf("2. Penjualan\n");
        printf("3. Log Out\n");
        printf("Pilihan: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                kasir_lihatitem();
                break;
            case 2:
                printf("Menu Penjualan dipilih.\n");
                break;
            case 3:
                printf("Log Out.\n");
                break;
            default:
                printf("Pilihan tidak valid.\n");
        }
    } while (pilihan != 3);
}

void menu_pelanggan(){
    int pilihan;
    do{
        printf("\n== Menu Pelanggan ==\n");
        printf("1. Beli barang.\n");
        printf("2. Log Out\n");
        printf("Pilihan: ");
        scanf("%d", &pilihan);

        switch(pilihan){
            case 1:
                printf("Beli barang dipilih.\n");
                break;
            case 2:
                printf("Log Out.\n");
                break;
            default:
                printf("Pilihan tidak valid.\n");
        }

    } while (pilihan != 2);
}


