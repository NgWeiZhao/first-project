#include "FinanceManager.h"

using namespace std;

int main() {
    FinanceManager manager;

    // 新增交易
    manager.addTransaction(Transaction(1, 100.0, "2025-05-06", "Grocery", "Food", "expense"));
    manager.addTransaction(Transaction(2, 2000.0, "2025-05-01", "Salary", "Income", "income"));

    // 顯示交易
    manager.listTransactions();

    // 計算收入與支出
    cout << "Total expenses: " << manager.calculateTotal("expense") << endl;
    cout << "Total income: " << manager.calculateTotal("income") << endl;

    // 儲存與讀取
    manager.saveToFile("finance.csv");
    manager.loadFromFile("finance.csv");

    return 0;
}
