#include "UserInterface.h"
#include <cstdlib>
#include <regex>

// 构造函数
UserInterface::UserInterface(FinanceManager& fm) : manager(&fm) {}

// 析构函数
UserInterface::~UserInterface() {}

// 运行主界面循环
void UserInterface::run() {
    showWelcome();
    int choice;

    do {
        displayMainMenu();
        choice = getIntInput("请选择操作 (1-8): ");

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
            cout << "无效选择，请重新输入！" << endl;
            break;
        }

        if (choice != 8) {
            pauseForUser();
        }

    } while (choice != 8);
}

// 显示欢迎信息
void UserInterface::showWelcome() const {
    clearScreen();
    cout << "=====================================" << endl;
    cout << "    欢迎使用个人财务管理系统！" << endl;
    cout << "=====================================" << endl;
    cout << endl;
}

// 显示告别信息
void UserInterface::showGoodbye() const {
    cout << "\n=====================================" << endl;
    cout << "    感谢使用个人财务管理系统！" << endl;
    cout << "         期待您的再次使用" << endl;
    cout << "=====================================" << endl;
}

// 显示主菜单
void UserInterface::displayMainMenu() const {
    cout << "\n========== 主菜单 ==========" << endl;
    cout << "1. 添加交易记录" << endl;
    cout << "2. 删除交易记录" << endl;
    cout << "3. 查看所有交易" << endl;
    cout << "4. 计算收支总额" << endl;
    cout << "5. 查看统计信息" << endl;
    cout << "6. 保存到文件" << endl;
    cout << "7. 从文件加载" << endl;
    cout << "8. 退出程序" << endl;
    cout << "============================" << endl;
}

// 添加交易界面
void UserInterface::addTransactionInterface() {
    cout << "\n========== 添加交易记录 ==========" << endl;

    int id = getIntInput("请输入交易ID: ");
    double amount = getDoubleInput("请输入金额: ");

    string date;
    do {
        date = getStringInput("请输入日期 (YYYY-MM-DD): ");
        if (!isValidDate(date)) {
            cout << "日期格式错误，请重新输入！" << endl;
        }
    } while (!isValidDate(date));

    string description = getStringInput("请输入描述: ");
    string category = getStringInput("请输入分类: ");

    string type;
    do {
        type = getStringInput("请输入类型 (income/expense): ");
        if (!isValidType(type)) {
            cout << "类型错误，请输入 'income' 或 'expense'！" << endl;
        }
    } while (!isValidType(type));

    Transaction newTransaction(id, amount, date, description, category, type);
    manager->addTransaction(newTransaction);

    cout << "交易记录添加成功！" << endl;
}

// 删除交易界面
void UserInterface::deleteTransactionInterface() {
    cout << "\n========== 删除交易记录 ==========" << endl;

    int id = getIntInput("请输入要删除的交易ID: ");
    manager->deleteTransaction(id);
}

// 显示交易列表界面
void UserInterface::listTransactionsInterface() const {
    cout << "\n========== 所有交易记录 ==========" << endl;
    manager->listTransactions();
    cout << "=================================" << endl;
}

// 计算总金额界面
void UserInterface::calculateTotalInterface() const {
    cout << "\n========== 收支统计 ==========" << endl;

    double totalIncome = manager->calculateTotal("income");
    double totalExpense = manager->calculateTotal("expense");
    double balance = totalIncome - totalExpense;

    cout << "总收入: " << totalIncome << " 元" << endl;
    cout << "总支出: " << totalExpense << " 元" << endl;
    cout << "净收入: " << balance << " 元" << endl;
    cout << "=============================" << endl;
}

// 显示统计信息界面
void UserInterface::showStatisticsInterface() const {
    cout << "\n========== 详细统计信息 ==========" << endl;

    double totalIncome = manager->calculateTotal("income");
    double totalExpense = manager->calculateTotal("expense");
    double balance = totalIncome - totalExpense;

    cout << "收入统计: " << totalIncome << " 元" << endl;
    cout << "支出统计: " << totalExpense << " 元" << endl;
    cout << "净收入: " << balance << " 元" << endl;

    if (balance > 0) {
        cout << "财务状况: 盈余" << endl;
    }
    else if (balance < 0) {
        cout << "财务状况: 亏损" << endl;
    }
    else {
        cout << "财务状况: 收支平衡" << endl;
    }

    cout << "=================================" << endl;
}

// 保存文件界面
void UserInterface::saveToFileInterface() const {
    cout << "\n========== 保存到文件 ==========" << endl;

    string filename = getStringInput("请输入文件名 (例: data.csv): ");
    manager->saveToFile(filename);
}

// 加载文件界面
void UserInterface::loadFromFileInterface() {
    cout << "\n========== 从文件加载 ==========" << endl;

    string filename = getStringInput("请输入文件名: ");
    manager->loadFromFile(filename);
}

// 清理输入缓冲区
void UserInterface::clearInputBuffer() const {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// 获取整数输入
int UserInterface::getIntInput(const string& prompt) const {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            clearInputBuffer();
            return value;
        }
        else {
            cout << "输入错误，请输入有效的整数！" << endl;
            clearInputBuffer();
        }
    }
}

// 获取浮点数输入
double UserInterface::getDoubleInput(const string& prompt) const {
    double value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            clearInputBuffer();
            return value;
        }
        else {
            cout << "输入错误，请输入有效的数字！" << endl;
            clearInputBuffer();
        }
    }
}

// 获取字符串输入
string UserInterface::getStringInput(const string& prompt) const {
    string value;
    cout << prompt;
    getline(cin, value);
    return value;
}

// 验证日期格式
bool UserInterface::isValidDate(const string& date) const {
    regex datePattern(R"(\d{4}-\d{2}-\d{2})");
    return regex_match(date, datePattern);
}

// 验证交易类型
bool UserInterface::isValidType(const string& type) const {
    return (type == "income" || type == "expense");
}

// 暂停等待用户输入
void UserInterface::pauseForUser() const {
    cout << "\n按 Enter 键继续...";
    cin.get();
}

// 清屏功能
void UserInterface::clearScreen() const {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}