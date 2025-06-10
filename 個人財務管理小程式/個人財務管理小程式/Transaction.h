#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <sstream>
#include <vector>

using namespace std;

class Transaction {
private:
    int id;
    double amount;
    string date;
    string description;
    string category;
    string type;

public:
    Transaction(int id, double amount, string date, string description, string category, string type)
        : id(id), amount(amount), date(date), description(description), category(category), type(type) {
    }

    int getId() const { return id; }
    double getAmount() const { return amount; }
    string getType() const { return type; }

    string getDetails() const {
        stringstream ss;
        ss << "ID: " << id << ", Amount: " << amount << ", Date: " << date
            << ", Description: " << description << ", Category: " << category
            << ", Type: " << type;
        return ss.str();
    }

    string toCSV() const {
        stringstream ss;
        ss << id << "," << amount << "," << date << "," << description << "," << category << "," << type;
        return ss.str();
    }

    static Transaction fromCSV(const string& csvLine) {
        stringstream ss(csvLine);
        string token;
        vector<string> fields;

        while (getline(ss, token, ',')) {
            fields.push_back(token);
        }

        return Transaction(
            stoi(fields[0]),
            stod(fields[1]),
            fields[2],
            fields[3],
            fields[4],
            fields[5]
        );
    }
};

#endif


