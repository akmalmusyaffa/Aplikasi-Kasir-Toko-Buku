#include <stdio.h>
#include <string.h>

struct tokbuk {
    char id[100], buku[100], penulis[100];
    int harga, diskon, stock;
};
struct user {
    char email[30], username[30], password[30];
};

int temp;
int login(int *role);
void signup();
void menu_manager();
void manager_tambahitem();
void manager_edititem();
void menu_kasir();
void kasir_lihatitem();
void menu_pelanggan();


int main() {
    printf("\n~~ Selamat Datang ~~\n");
    printf("Ketik sembarang angka untuk mengakhiri program, 1 untuk memulai: ");
    scanf("%d", &temp);

    while (temp==1) {
        int role, buyer;
        printf("Login sebagai? (manager(1)/kasir(2)/pelanggan(3)): ");
        scanf("%d", &role);

        switch (role)
        {
        case 1:
            if (login(&role)) {
                menu_manager();
            }
            break;
        case 2:
            if (login(&role)) {
                menu_kasir();
            }
            break;
        case 3:
            printf("Ketik (1) untuk sign up, (2) untuk login\n");
            scanf("%d", &buyer);
            if (buyer == 1){
                signup();
            } else if (buyer == 2){
                if (login(&role)) {
                menu_pelanggan();
                }
            } else {
                printf("Pilihan tidak valid");
            }
            break;
        
        default:
            printf("Role tidak dikenal.\n");
            break;
        }
        
        printf("\n~~ Selamat Datang ~~\n");
        printf("Ketik sembarang angka untuk mengakhiri program, 1 untuk memulai: ");
        scanf("%d", &temp);
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
    scanf("%29s", regis.email);
    printf("Masukkan username (Maksimal 20 Karakter): ");
    scanf("%29s", regis.username);
    printf("Masukkan kata sandi: ");
    scanf("%29s", regis.password);

    fwrite(&regis, sizeof(struct user),1, f_signup);

    fclose(f_signup);
}

int login(int *role) {
    char username[20], password[20];
    printf("Masukkan username: ");
    scanf("%19s", username);
    printf("Masukkan kata sandi: ");
    scanf("%19s", password);
    switch (*role){
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
        {
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
        }
            break;
        default:
            break;
    }
    printf("Nama atau kata sandi salah.\n");
    return 0;
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
                manager_hapusitem();
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

void manager_edititem(){
    FILE* fedit = fopen("databuku.dat", "rb+"); 
    struct tokbuk edit;
    char kodeid[20];
    int angka, flag;

    printf("Masukkan kode ID: ");
    scanf("%s", kodeid);


    while(fread(&edit, sizeof(struct tokbuk), 1, fedit)){
        if(strcmp(edit.id, kodeid)==0){
            flag = 1;
            printf("Informasi Buku: ");
            printf(" %-15s  %-30s  %-20s  %-7s  %-6s  %-7s \n", "ID", "Judul Buku", "Penulis", "Harga", "Diskon", "Stok");
            printf(" %-15.15s  %-30.30s  %-20.20s  %-7d  %-6d  %-7d \n", edit.id, edit.buku, edit.penulis, edit.harga, edit.diskon, edit.stock);

            printf("Masukkan informasi yang ingin diedit: ");
            scanf("%d", &angka);
            while (angka>=1 && angka<=6) {
                switch (angka){
                    case 1:
                        printf("Masukkan kode ID: ");
                        scanf("%s", edit.id);
                        break;
                    case 2:
                        printf("Masukkan judul buku: ");
                        scanf("%s", edit.buku);
                        break;
                    case 3:
                        printf("Masukkan penulis: ");
                        scanf("%s", edit.penulis);
                        break;
                    case 4:
                        printf("Masukkan harga: ");
                        scanf("%s", edit.harga);
                        break;
                    case 5:
                        printf("Masukkan diskon: ");
                        scanf("%s", edit.diskon);
                        break;
                    case 6:
                        printf("Masukkan stok: ");
                        scanf("%s", edit.stock);
                        break;
                    default:
                        break;
                    }
                printf("Masukkan informasi yang ingin diedit: ");
                scanf("%d", &angka);
            }
            fseek(fedit, -sizeof(struct tokbuk), SEEK_CUR);
            fwrite(&edit, sizeof(struct tokbuk), 1, fedit);
            printf("Data buku berhasil diubah.\n");
            break;
        }
    }
    if (flag==0){
        printf("Buku tidak ditemukan");
    }
    fclose(fedit);
}

void manager_hapusitem(){
    FILE *f_biner, *f_hapus; 
    struct tokbuk hapus;
    int angka;
    char kodeid[20];

    printf("Ketik 1 untuk melihat daftar item: ");
    scanf("%d", &angka);
    if (angka==1){
        kasir_lihatitem();
    }
    
    printf("Masukkan kode ID: ");
    scanf("%s", kodeid);

    f_biner = fopen("databuku.dat", "rb");
    if (!f_biner) {
        printf("Gagal membuka file.\n");
        return;
    }

    f_hapus = fopen("updatedatabuku.dat", "wb");
    if (!f_hapus) {
        printf("Gagal membuka file sementara.\n");
        fclose(f_biner);
        return;
    }

    int count = 0;
    while (fread(&hapus, sizeof(struct tokbuk), 1, f_biner)) {
        if (strcmp(hapus.id, kodeid) != 0) {
            fwrite(&hapus, sizeof(struct tokbuk), 1, f_hapus);  
        } else {
            count = 1;  
        }
    }
    
    if (count==1) {
        remove("databuku.dat");
        rename("updatedatabuku.dat", "databuku.dat");
        printf("Item berhasil dihapus.\n");
    } else {
        remove("updatedatabuku.dat");
        printf("Data tidak ditemukan.\n");
    }

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
