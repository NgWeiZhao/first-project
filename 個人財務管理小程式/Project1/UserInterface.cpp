#include "UserInterface.h"
#include <cstdlib>
#include <regex>

// 建構子
UserInterface::UserInterface(FinanceManager& fm) : manager(&fm) {}

// 解構子
UserInterface::~UserInterface() {}

// 主程式迴圈
void UserInterface::run() {
    showWelcome();
    int choice;

    do {
        displayMainMenu();
        choice = getIntInput("請選擇操作項目 (1-8): ");

        switch (choice) {
        case 1:
            addTransactionInterface();
            break;
        case 2:
            deleteTransactionInterface();
            break;
        case 3:
            listTransactionsInterface();
            break;
        case 4:
            calculateTotalInterface();
            break;
        case 5:
            showStatisticsInterface();
            break;
        case 6:
            saveToFileInterface();
            break;
        case 7:
            loadFromFileInterface();
            break;
        case 8:
            showGoodbye();
            break;
        default:
            cout << "無效選項，請重新選擇。" << endl;
            break;
        }

        if (choice != 8) {
            pauseForUser();
        }

    } while (choice != 8);
}

// 顯示歡迎訊息
void UserInterface::showWelcome() const {
    clearScreen();
    cout << "=====================================" << endl;
    cout << "    歡迎使用個人財務管理系統！" << endl;
    cout << "=====================================" << endl;
    cout << endl;
}

// 顯示告別訊息
void UserInterface::showGoodbye() const {
    cout << "\n=====================================" << endl;
    cout << "    感謝使用個人財務管理系統！" << endl;
    cout << "         歡迎再次使用！" << endl;
    cout << "=====================================" << endl;
}

// 顯示主選單
void UserInterface::displayMainMenu() const {
    cout << "\n========== 主選單 ==========" << endl;
    cout << "1. 新增交易紀錄" << endl;
    cout << "2. 刪除交易紀錄" << endl;
    cout << "3. 查看所有交易" << endl;
    cout << "4. 計算總收入與支出" << endl;
    cout << "5. 查看統計資訊" << endl;
    cout << "6. 儲存至檔案" << endl;
    cout << "7. 從檔案載入" << endl;
    cout << "8. 離開系統" << endl;
    cout << "============================" << endl;
}

// 新增交易紀錄介面
void UserInterface::addTransactionInterface() {
    cout << "\n========== 新增交易紀錄 ==========" << endl;

    int id = getIntInput("請輸入交易ID: ");
    double amount = getDoubleInput("請輸入金額: ");

    string date;
    do {
        date = getStringInput("請輸入日期 (YYYY-MM-DD): ");
        if (!isValidDate(date)) {
            cout << "日期格式不正確，請重新輸入。" << endl;
        }
    } while (!isValidDate(date));

    string description = getStringInput("請輸入描述: ");
    string category = getStringInput("請輸入類別: ");

    string type;
    do {
        type = getStringInput("請輸入類型 (income/expense): ");
        if (!isValidType(type)) {
            cout << "類型必須為 'income' 或 'expense'。" << endl;
        }
    } while (!isValidType(type));

    Transaction newTransaction(id, amount, date, description, category, type);
    manager->addTransaction(newTransaction);

    cout << "交易紀錄新增成功！" << endl;
}

// 刪除交易紀錄介面
void UserInterface::deleteTransactionInterface() {
    cout << "\n========== 刪除交易紀錄 ==========" << endl;

    int id = getIntInput("請輸入要刪除的交易ID: ");
    manager->deleteTransaction(id);
}

// 顯示所有交易紀錄
void UserInterface::listTransactionsInterface() const {
    cout << "\n========== 所有交易紀錄 ==========" << endl;
    manager->listTransactions();
    cout << "=================================" << endl;
}

// 計算總收入與支出
void UserInterface::calculateTotalInterface() const {
    cout << "\n========== 總收入與支出 ==========" << endl;

    double totalIncome = manager->calculateTotal("income");
    double totalExpense = manager->calculateTotal("expense");
    double balance = totalIncome - totalExpense;

    cout << "總收入: " << totalIncome << " 元" << endl;
    cout << "總支出: " << totalExpense << " 元" << endl;
    cout << "結餘: " << balance << " 元" << endl;
    cout << "=============================" << endl;
}

// 顯示統計資訊
void UserInterface::showStatisticsInterface() const {
    cout << "\n========== 詳細統計資訊 ==========" << endl;

    double totalIncome = manager->calculateTotal("income");
    double totalExpense = manager->calculateTotal("expense");
    double balance = totalIncome - totalExpense;

    cout << "收入統計: " << totalIncome << " 元" << endl;
    cout << "支出統計: " << totalExpense << " 元" << endl;
    cout << "結餘: " << balance << " 元" << endl;

    if (balance > 0) {
        cout << "財務狀況: 盈餘" << endl;
    }
    else if (balance < 0) {
        cout << "財務狀況: 赤字" << endl;
    }
    else {
        cout << "財務狀況: 收支平衡" << endl;
    }

    cout << "=================================" << endl;
}

// 儲存至檔案介面
void UserInterface::saveToFileInterface() const {
    cout << "\n========== 儲存至檔案 ==========" << endl;

    string filename = getStringInput("請輸入檔案名稱 (預設: data.csv): ");
    manager->saveToFile(filename);
}

// 從檔案載入介面
void UserInterface::loadFromFileInterface() {
    cout << "\n========== 從檔案載入 ==========" << endl;

    string filename = getStringInput("請輸入檔案名稱: ");
    manager->loadFromFile(filename);
}

// 清除輸入緩衝區
void UserInterface::clearInputBuffer() const {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// 取得整數輸入
int UserInterface::getIntInput(const string& prompt) const {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            clearInputBuffer();
            return value;
        }
        else {
            cout << "輸入無效，請輸入有效的整數。" << endl;
            clearInputBuffer();
        }
    }
}

// 取得浮點數輸入
double UserInterface::getDoubleInput(const string& prompt) const {
    double value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            clearInputBuffer();
            return value;
        }
        else {
            cout << "輸入無效，請輸入有效的數字。" << endl;
            clearInputBuffer();
        }
    }
}

// 取得字串輸入
string UserInterface::getStringInput(const string& prompt) const {
    string value;
    cout << prompt;
    getline(cin, value);
    return value;
}

// 驗證日期格式
bool UserInterface::isValidDate(const string& date) const {
    regex datePattern(R"(\d{4}-\d{2}-\d{2})");
    return regex_match(date, datePattern);
}

// 驗證交易類型
bool UserInterface::isValidType(const string& type) const {
    return (type == "income" || type == "expense");
}

// 暫停等待使用者
void UserInterface::pauseForUser() const {
    cout << "\n按 Enter 鍵繼續...";
    cin.get();
}

// 清除螢幕
void UserInterface::clearScreen() const {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
