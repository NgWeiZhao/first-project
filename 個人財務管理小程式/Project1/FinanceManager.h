#ifndef FINANCEMANAGER_H
#define FINANCEMANAGER_H

#include "Transaction.h"
#include "Category.h"
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

class FinanceManager {
private:
    vector<Transaction> transactions;
    vector<Category> categories;

public:
    void addTransaction(const Transaction& t) {
        transactions.push_back(t);
    }

    void deleteTransaction(int id) {
        for (auto it = transactions.begin(); it != transactions.end(); ++it) {
            if (it->getId() == id) {
                transactions.erase(it);
                cout << "Transaction with ID " << id << " deleted." << endl;
                return;
            }
        }
        cout << "Transaction with ID " << id << " not found." << endl;
    }

    void listTransactions() const {
        for (const auto& t : transactions) {
            cout << t.getDetails() << endl;
        }
    }

    double calculateTotal(const string& type) const {
        double total = 0.0;
        for (const auto& t : transactions) {
            if (t.getType() == type) {
                total += t.getAmount();
            }
        }
        return total;
    }

    void saveToFile(const string& filename) const {
        ofstream out(filename);
        for (const auto& t : transactions) {
            out << t.toCSV() << endl;
        }
        out.close();
        cout << "Transactions saved to " << filename << endl;
    }

    void loadFromFile(const string& filename) {
        ifstream in(filename);
        string line;
        transactions.clear();
        while (getline(in, line)) {
            transactions.push_back(Transaction::fromCSV(line));
        }
        in.close();
        cout << "Transactions loaded from " << filename << endl;
    }
};

#endif
