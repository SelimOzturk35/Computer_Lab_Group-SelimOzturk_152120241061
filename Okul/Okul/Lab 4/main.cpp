#include <iostream>
#include <string>

using namespace std;

struct MoneyBundle {
    string serialNumber;
    string currencyType;
    int billCounts[3];
    MoneyBundle* next;
};

struct Customer {
    string customerName;
    string transactionType;
};

class MoneyStack {
private:
    MoneyBundle* top;

public:
    MoneyStack() : top(nullptr) {}

    void push(string serial, string currency, int b100, int b50, int b20) {
        MoneyBundle* newBundle = new MoneyBundle();
        newBundle->serialNumber = serial;
        newBundle->currencyType = currency;
        newBundle->billCounts[0] = b100;
        newBundle->billCounts[1] = b50;
        newBundle->billCounts[2] = b20;
        newBundle->next = top;

        top = newBundle;
    }

    MoneyBundle* pop() {
        if (top == nullptr) return nullptr;

        MoneyBundle* temp = top;
        top = top->next;
        return temp;
    }

    void display() {
        if (top == nullptr) {
            cout << "[!] Kasa (Stack) bos." << endl;
            return;
        }
        cout << "Kasa Icerigi" << endl;
        MoneyBundle* current = top;
        while (current != nullptr) {
            cout << "Seri No: " << current->serialNumber
                << " | Birim: " << current->currencyType
                << " | Banknotlar: [100'luk: " << current->billCounts[0]
                << ", 50'lik: " << current->billCounts[1]
                << ", 20'lik: " << current->billCounts[2] << "]" << endl;
            current = current->next;
        }
    }

    bool isEmpty() {
        return top == nullptr;
    }
};

class CustomerQueue {
private:
    Customer queue[5];
    int front;
    int rear;
    int count;
    int maxSize = 5;

public:
    CustomerQueue() : front(0), rear(0), count(0) {}

    void enqueue(string name, string transaction) {
        if (count == maxSize) {
            cout << "Kuyruk dolu! '" << name << "' siraya alinamadi." << endl;
            return;
        }
        queue[rear].customerName = name;
        queue[rear].transactionType = transaction;

        rear = (rear + 1) % maxSize;
        count++;
    }

    Customer dequeue() {
        Customer emptyCustomer = { "", "" };
        if (count == 0) return emptyCustomer;

        Customer c = queue[front];
        front = (front + 1) % maxSize;
        count--;
        return c;
    }

    void display() {
        if (count == 0) {
            cout << "Bekleyen musteri yok." << endl;
            return;
        }
        cout << "Musteri Kuyrugu" << endl;
        for (int i = 0; i < count; i++) {
            int index = (front + i) % maxSize;
            cout << i + 1 << ". Siradaki: " << queue[index].customerName
                << " | Islem: " << queue[index].transactionType << endl;
        }
    }

    bool isEmpty() {
        return count == 0;
    }
};

int main() {
    MoneyStack safe;
    CustomerQueue bankLine;

    safe.push("TXN-001", "TL", 10, 5, 20);
    safe.push("TXN-002", "USD", 5, 10, 0);
    safe.push("TXN-003", "EUR", 2, 0, 50);

    bankLine.enqueue("Ali", "Withdraw");
    bankLine.enqueue("Ayse", "Deposit");
    bankLine.enqueue("Mehmet", "Withdraw");

    safe.display();
    cout << endl;
    bankLine.display();
    cout << "\n=========================================\n";

    cout << "Islemler Gerceklestiriliyor\n\n";

    if (!bankLine.isEmpty() && !safe.isEmpty()) {
        Customer currentCustomer = bankLine.dequeue();
        MoneyBundle* currentMoney = safe.pop();

        cout << "ISLEM BASARILI " << currentCustomer.customerName
            << " adli musterinin '" << currentCustomer.transactionType
            << "' islemi, " << currentMoney->serialNumber
            << " seri numarali (" << currentMoney->currencyType << ") deste kullanilarak yapildi." << endl;

        delete currentMoney;
    }
    else {
        cout << "Islem yapilamadi. Sirada kimse yok" << endl;
    }

    cout << "\n=========================================\n";
    cout << "Guncel Durum\n\n";

    safe.display();
    cout << endl;
    bankLine.display();

    return 0;
}