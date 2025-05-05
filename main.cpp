#include "FinanceManager.h"

using namespace std;

int main() {
    FinanceManager manager;

    // ��������
    manager.addTransaction(Transaction(1, 100.0, "2025-05-06", "Grocery", "Food", "expense"));
    manager.addTransaction(Transaction(2, 2000.0, "2025-05-01", "Salary", "Income", "income"));

    // �@ʾ����
    manager.listTransactions();

    // Ӌ�������c֧��
    cout << "Total expenses: " << manager.calculateTotal("expense") << endl;
    cout << "Total income: " << manager.calculateTotal("income") << endl;

    // �����c�xȡ
    manager.saveToFile("finance.csv");
    manager.loadFromFile("finance.csv");

    return 0;
}
