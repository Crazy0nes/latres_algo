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
            cout << cari <<"produk ditemukan" << endl;
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
    cout << root->produk.nama << " (" << root-> produk.kode << " )";
    preorder(root->left);
    preorder(root->right);
}

void inorder(PTBNode *root){
    if(root == nullptr){
        return;
    }
    inorder(root->left);
    cout << root->produk.nama << " (" << root-> produk.kode << " )";
    inorder(root->right);
}

void postorder(PTBNode *root){
    if(root == nullptr){
        return;
    }
    postorder(root->left);
    postorder(root->right);
    cout << root->produk.nama << " (" << root-> produk.kode << " )";
}

void deleteNode(PTBNode *&root, int hapus){
    if(root == nullptr){
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