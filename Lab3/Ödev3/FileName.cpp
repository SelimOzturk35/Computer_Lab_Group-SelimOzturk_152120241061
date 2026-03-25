#include <iostream>
#include <string>

using namespace std;

struct Page {
    string url;
    string title;
    int accessTime[3];
    Page* next;
    Page* prev;

    Page(string u, string t, int h, int m, int s) {
        url = u;
        title = t;
        accessTime[0] = h;
        accessTime[1] = m;
        accessTime[2] = s;
        next = nullptr;
        prev = nullptr;
    }
};

class BrowserHistory {
private:
    Page* head;
    Page* tail;
    Page* current;

public:
    BrowserHistory() {
        head = nullptr;
        tail = nullptr;
        current = nullptr;
    }

    ~BrowserHistory() {
        Page* temp = head;
        while (temp != nullptr) {
            Page* nextNode = temp->next;
            delete temp;
            temp = nextNode;
        }
        cout << "Hafiza temizlendi. Gecmis silindi.\n";
    }

    void visit(string url, string title, int h, int m, int s) {
        Page* newPage = new Page(url, title, h, m, s);

        if (head == nullptr) {
            head = tail = current = newPage;
        }
        else {

            Page* temp = current->next;
            while (temp != nullptr) {
                Page* toDelete = temp;
                temp = temp->next;
                delete toDelete;
            }

            current->next = newPage;
            newPage->prev = current;
            tail = newPage;
            current = newPage;
        }
        cout << "-> Ziyaret edildi: " << title << "\n";
    }

    void back() {
        if (current != nullptr && current->prev != nullptr) {
            current = current->prev;
            cout << "-> Geri gidildi. Su anki sayfa: " << current->title << "\n";
        }
        else {
            cout << "-> Geri gidilecek sayfa yok!\n";
        }
    }

    // FORWARD: Sonraki sayfaya git
    void forward() {
        if (current != nullptr && current->next != nullptr) {
            current = current->next;
            cout << "-> Ileri gidildi. Su anki sayfa: " << current->title << "\n";
        }
        else {
            cout << "-> Ileri gidilecek sayfa yok!\n";
        }
    }

    // DELETE ENTRY: Mevcut sayfayı sil ve listeyi tekrar bağla
    void deleteEntry() {
        if (current == nullptr) {
            cout << "-> Silinecek sayfa yok!\n";
            return;
        }

        Page* toDelete = current;

        // Silinen düğüm listenin başıysa (head)
        if (toDelete == head) {
            head = head->next;
            if (head != nullptr) head->prev = nullptr;
        }

        // Silinen düğüm listenin sonuysa (tail)
        if (toDelete == tail) {
            tail = tail->prev;
            if (tail != nullptr) tail->next = nullptr;
        }

        // Aradan siliniyorsa önceki ve sonrakini birbirine bağla
        if (toDelete->prev != nullptr) {
            toDelete->prev->next = toDelete->next;
        }
        if (toDelete->next != nullptr) {
            toDelete->next->prev = toDelete->prev;
        }

        // Current pointer'ını makul bir yere taşı (önce geriye, yoksa ileriye)
        if (toDelete->prev != nullptr) {
            current = toDelete->prev;
        }
        else {
            current = toDelete->next;
        }

        cout << "-> " << toDelete->title << " gecmisten silindi.\n";
        delete toDelete; // Düğümü bellekten tamamen uçur
    }

    // DISPLAY HISTORY: Tüm geçmişi yazdır
    void displayHistory() {
        if (head == nullptr) {
            cout << "\nTarayici gecmisi bos.\n";
            return;
        }

        cout << "\n--- Tarayici Gecmisi ---\n";
        Page* temp = head;
        while (temp != nullptr) {
            // Hocanın istediği: Şu anki sayfayı belirginleştir
            if (temp == current) {
                cout << "[SU AN] -> ";
            }
            else {
                cout << "           ";
            }

            cout << temp->title << " (" << temp->url << ") - Ziyaret Zamani: ";

            // Hocanın istediği: Zaman dizisini yazdırmak için zorunlu for döngüsü
            for (int i = 0; i < 3; i++) {
                if (temp->accessTime[i] < 10) cout << "0"; // 9 yerine 09 yazması için
                cout << temp->accessTime[i];
                if (i < 2) cout << ":";
            }
            cout << "\n";

            temp = temp->next;
        }
        cout << "------------------------\n\n";
    }
};

int main() {
    BrowserHistory history;

    // Hocanın veya asistanın test edeceği muhtemel bir senaryo
    history.visit("google.com", "Google", 14, 30, 0);
    history.visit("esogu.edu.tr", "ESOGU", 14, 35, 12);
    history.visit("github.com", "GitHub", 14, 40, 50);

    history.displayHistory(); // 3 siteyi de göstermeli, current GitHub'da

    history.back(); // ESOGU'ye dönmeli
    history.displayHistory();

    history.deleteEntry(); // ESOGU'yü silmeli, current Google'a veya GitHub'a geçmeli (koda göre Google'a geçer)
    history.displayHistory();

    // Program kapanırken "EXIT" mantığı devreye girer ve Destructor çalışarak kalan tüm düğümleri otomatik siler.
    return 0;
}