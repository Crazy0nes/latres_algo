#include <iostream>

using namespace std;

struct Produk{
    int kode;
    string nama;
    int stok;
    string jenis;
};

struct PTBNode{
    Produk produk;
    PTBNode *left;
    PTBNode *right;

    PTBNode(int kode, string nama, int stok, string jenis){
       produk.kode = kode;
       produk.nama = nama;
       produk.stok = stok;
       produk.jenis = jenis;
        left = nullptr;
        right = nullptr;
    }
};

void insert(PTBNode *&root, int valuekode, string valuenama, int valuestok, string valuejenis){
    if(root == nullptr){
        root = new PTBNode(valuekode, valuenama, valuestok, valuejenis );
        return;
    }

    PTBNode *current = root;
    while(true){
        if(valuekode < current->produk.kode){
            if(current->left == nullptr){
                current->left = new PTBNode(valuekode, valuenama, valuestok, valuejenis);
                return;
            }
            current = current->left;
        }else{
            if(current->right == nullptr){
                current->right = new PTBNode(valuekode, valuenama, valuestok, valuejenis);
                return;
            }
            current = current->right;
        }
    }
}

PTBNode* search(PTBNode *root, int cari){
    PTBNode *current = root;
    while(true){

        if(current -> produk.kode == cari){
            cout << "Produk " << cari <<" ditemukan" << endl;
            return current;
        }
        if(cari < current->produk.kode){
            current = current->left;
        }else{
            current = current->right;
        }
    }
    cout << cari << "produk tidak ditemukan" << endl; 
    return nullptr;
}

void preorder(PTBNode *root){
    if(root == nullptr){
       return;
    }
    cout << "Kode: " <<root->produk.kode << endl;
    cout << "Nama: " << root-> produk.nama << endl;
    cout << "Stok: " << root-> produk.stok << endl;
    cout << "Jenis: " << root-> produk.jenis << endl;
    cout << "------------------------" << endl;
    preorder(root->left);
    preorder(root->right);
}

void inorder(PTBNode *root){
    if(root == nullptr){
        return;
    }
    inorder(root->left);
    cout << "Kode: " <<root->produk.kode << endl;
    cout << "Nama: " << root-> produk.nama << endl;
    cout << "Stok: " << root-> produk.stok << endl;
    cout << "Jenis: " << root-> produk.jenis << endl;
    cout << "------------------------" << endl;
    inorder(root->right);
}

void deleteNode(PTBNode *&root, int hapus){
    if(root == nullptr){
        cout << "Produk dengan kode " << hapus << " tidak ditemukan.\n";
        return;
    }

    if(hapus < root->produk.kode){
        deleteNode(root->left, hapus);
    }else if(hapus > root->produk.kode){
        deleteNode(root->right, hapus);
    }else{
        PTBNode *temp = root;
        if(root->left == nullptr){
            root = root->right;
        }else if(root->right == nullptr){
            root = root->left;
    }else{
        PTBNode *successor = root->right;
        while(successor->left != nullptr){
            successor = successor->left;
        }
        root->produk = successor->produk;
        deleteNode(root->right, successor->produk.kode);
        return;
    }
    free(temp);
    }
}

#define MAX_STACK 100

enum AksiType { TAMBAH, HAPUS };

struct LogAksi {
    AksiType aksi;
    Produk produk;
};

struct StackAksi {
    LogAksi data[MAX_STACK];
    int top;
    StackAksi() { top = -1; }
    bool isEmpty() { return top == -1; }
    bool isFull() { return top == MAX_STACK - 1; }
    void push(LogAksi aksi) {
        if (!isFull()) data[++top] = aksi;
    }
    LogAksi pop() {
        if (!isEmpty()) return data[top--];
        LogAksi dummy; dummy.aksi = TAMBAH;
        return dummy;
    }
    LogAksi peek() {
        if (!isEmpty()) return data[top];
        LogAksi dummy; dummy.aksi = TAMBAH;
        return dummy;
    }
};

StackAksi aksiStack;

void insertWithLog(PTBNode *&root, int valuekode, string valuenama, int valuestok, string valuejenis){
    insert(root, valuekode, valuenama, valuestok, valuejenis);
    Produk p; p.kode = valuekode; p.nama = valuenama; p.stok = valuestok; p.jenis = valuejenis;
    LogAksi log; log.aksi = TAMBAH; log.produk = p;
    aksiStack.push(log);
}

void deleteNodeWithLog(PTBNode *&root, int hapus){
    PTBNode* node = search(root, hapus);
    if(node != nullptr){
        LogAksi log; log.aksi = HAPUS; log.produk = node->produk;
        aksiStack.push(log);
        deleteNode(root, hapus);
    }
}

void undo(PTBNode *&root){
    if(aksiStack.isEmpty()){
        cout << "Tidak ada aksi untuk di-undo.\n";
        return;
    }
    LogAksi last = aksiStack.pop();
    if(last.aksi == TAMBAH){
        deleteNode(root, last.produk.kode);
        cout << "Undo tambah produk berhasil.\n";
    }else if(last.aksi == HAPUS){
        insert(root, last.produk.kode, last.produk.nama, last.produk.stok, last.produk.jenis);
        cout << "Undo hapus produk berhasil.\n";
    }
}

void filterJenis(PTBNode *root, string jenis){
    if(root == nullptr) return;
    filterJenis(root->left, jenis);
    if(root->produk.jenis == jenis){
        cout << "Kode: " << root->produk.kode << endl;
        cout << "Nama: " << root->produk.nama << endl;
        cout << "Stok: " << root->produk.stok << endl;
        cout << "Jenis: " << root->produk.jenis << endl;
        cout << "------------------------" << endl;
    }
    filterJenis(root->right, jenis);
}

int main() {
    PTBNode* root = nullptr;
    int pilihan;
    do {
        system("cls");
        cout << "\n=== MENU MANAJEMEN GUDANG ===\n";
        cout << "1. Tambah Produk\n";
        cout << "2. Tampilkan Daftar Produk (Inorder)\n";
        cout << "3. Filter Produk Berdasarkan Jenis\n";
        cout << "4. Hapus Produk\n";
        cout << "5. Undo Aksi Terakhir\n";
        cout << "6. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;
        cin.ignore();

        switch(pilihan) {
            case 1: {
                int kode, stok;
                string nama, jenis;
                cout << "Masukkan kode produk: "; cin >> kode; cin.ignore();
                cout << "Masukkan nama produk: "; getline(cin, nama);
                cout << "Masukkan stok produk: "; cin >> stok; cin.ignore();
                cout << "Masukkan jenis produk: "; getline(cin, jenis);
                insertWithLog(root, kode, nama, stok, jenis);
                cout << "Produk berhasil ditambahkan.\n";
                system("pause");    
                break;
            }
            case 2:
                cout << "\n=== DAFTAR PRODUK ===\n";
                inorder(root);
                system("pause");
                break;
            case 3: {
                string jenis;
                cout << "Masukkan jenis produk yang ingin difilter: ";
                getline(cin, jenis);
                cout << "\n=== PRODUK DENGAN JENIS: " << jenis << " ===\n";
                filterJenis(root, jenis);
                system("pause");
                break;
            }
            case 4: {
                int kode;
                cout << "Masukkan kode produk yang ingin dihapus: ";
                cin >> kode; cin.ignore();
                deleteNodeWithLog(root, kode);
                cout << "Produk berhasil dihapus.\n";
                system("pause");
                break;
            }
            case 5:
                undo(root);
                system("pause");
                break;
            case 6:
                cout << "Terima kasih!\n";
                system("pause");
                break;
            default:
                cout << "Pilihan tidak valid.\n";
                system("pause");
        }
    } while (pilihan != 6);

    return 0;
}