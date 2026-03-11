#include <iostream>
#include <string>

using namespace std;

struct Node {
    string songTitle;
    Node* next;
};

void addSong(Node*& head, const string& title) {
    Node* newNode = new Node();
    newNode->songTitle = title;
    newNode->next = head;6
    head = newNode;
}

void searchSong(Node* head, const string& title) {
    Node* temp = head;
    while (temp != nullptr) {
        if (temp->songTitle == title) {
            cout << "[+] Sahnede: " << title << " listede bulundu.\n";
            return;
        }
        temp = temp->next;
    }
    cout << "[-] " << title << " listede bulunamadi.\n";
}

void listSongs(Node* head) {
    if (head == nullptr) {
        cout << "Oynatma listesi bos.\n";
        return;
    }

    Node* temp = head;
    int count = 1;
    while (temp != nullptr) {
        cout << count << ". " << temp->songTitle << "\n";
        temp = temp->next;
        count++;
    }
}

void clearPlaylist(Node*& head) {
    Node* current = head;
    while (current != nullptr) {
        Node* nextNode = current->next;
        delete current;
        current = nextNode;
    }
    head = nullptr;
}

int main() {
    Node* head = nullptr;
    int choice;
    string title;

    do {
        cout << "\n--- Playlist Menusu ---\n";
        cout << "1. Add\n2. Search\n3. List\n4. Exit\n";
        cout << "Seciminiz: ";
        cin >> choice;

        cin.ignore();

        switch (choice) {
            case 1:
                cout << "Sarki adi girin: ";
                getline(cin, title);
                addSong(head, title);
                break;
            case 2:
                cout << "Aranacak sarki adi: ";
                getline(cin, title);
                searchSong(head, title);
                break;
            case 3:
                listSongs(head);
                break;
            case 4:
                cout << "Cikiliyor. Bellek temizleniyor...\n";
                clearPlaylist(head);
                break;
            default:
                cout << "Gecersiz secim. Tekrar deneyin.\n";
        }
    } while (choice != 4);

    return 0;
}
