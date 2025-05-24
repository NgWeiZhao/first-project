#include "UserInterface.h"
#include <cstdlib>
#include <regex>

// ���캯��
UserInterface::UserInterface(FinanceManager& fm) : manager(&fm) {}

// ��������
UserInterface::~UserInterface() {}

// ����������ѭ��
void UserInterface::run() {
    showWelcome();
    int choice;

    do {
        displayMainMenu();
        choice = getIntInput("��ѡ����� (1-8): ");

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
            cout << "��Чѡ�����������룡" << endl;
            break;
        }

        if (choice != 8) {
            pauseForUser();
        }

    } while (choice != 8);
}

// ��ʾ��ӭ��Ϣ
void UserInterface::showWelcome() const {
    clearScreen();
    cout << "=====================================" << endl;
    cout << "    ��ӭʹ�ø��˲������ϵͳ��" << endl;
    cout << "=====================================" << endl;
    cout << endl;
}

// ��ʾ�����Ϣ
void UserInterface::showGoodbye() const {
    cout << "\n=====================================" << endl;
    cout << "    ��лʹ�ø��˲������ϵͳ��" << endl;
    cout << "         �ڴ������ٴ�ʹ��" << endl;
    cout << "=====================================" << endl;
}

// ��ʾ���˵�
void UserInterface::displayMainMenu() const {
    cout << "\n========== ���˵� ==========" << endl;
    cout << "1. ��ӽ��׼�¼" << endl;
    cout << "2. ɾ�����׼�¼" << endl;
    cout << "3. �鿴���н���" << endl;
    cout << "4. ������֧�ܶ�" << endl;
    cout << "5. �鿴ͳ����Ϣ" << endl;
    cout << "6. ���浽�ļ�" << endl;
    cout << "7. ���ļ�����" << endl;
    cout << "8. �˳�����" << endl;
    cout << "============================" << endl;
}

// ��ӽ��׽���
void UserInterface::addTransactionInterface() {
    cout << "\n========== ��ӽ��׼�¼ ==========" << endl;

    int id = getIntInput("�����뽻��ID: ");
    double amount = getDoubleInput("��������: ");

    string date;
    do {
        date = getStringInput("���������� (YYYY-MM-DD): ");
        if (!isValidDate(date)) {
            cout << "���ڸ�ʽ�������������룡" << endl;
        }
    } while (!isValidDate(date));

    string description = getStringInput("����������: ");
    string category = getStringInput("���������: ");

    string type;
    do {
        type = getStringInput("���������� (income/expense): ");
        if (!isValidType(type)) {
            cout << "���ʹ��������� 'income' �� 'expense'��" << endl;
        }
    } while (!isValidType(type));

    Transaction newTransaction(id, amount, date, description, category, type);
    manager->addTransaction(newTransaction);

    cout << "���׼�¼��ӳɹ���" << endl;
}

// ɾ�����׽���
void UserInterface::deleteTransactionInterface() {
    cout << "\n========== ɾ�����׼�¼ ==========" << endl;

    int id = getIntInput("������Ҫɾ���Ľ���ID: ");
    manager->deleteTransaction(id);
}

// ��ʾ�����б����
void UserInterface::listTransactionsInterface() const {
    cout << "\n========== ���н��׼�¼ ==========" << endl;
    manager->listTransactions();
    cout << "=================================" << endl;
}

// �����ܽ�����
void UserInterface::calculateTotalInterface() const {
    cout << "\n========== ��֧ͳ�� ==========" << endl;

    double totalIncome = manager->calculateTotal("income");
    double totalExpense = manager->calculateTotal("expense");
    double balance = totalIncome - totalExpense;

    cout << "������: " << totalIncome << " Ԫ" << endl;
    cout << "��֧��: " << totalExpense << " Ԫ" << endl;
    cout << "������: " << balance << " Ԫ" << endl;
    cout << "=============================" << endl;
}

// ��ʾͳ����Ϣ����
void UserInterface::showStatisticsInterface() const {
    cout << "\n========== ��ϸͳ����Ϣ ==========" << endl;

    double totalIncome = manager->calculateTotal("income");
    double totalExpense = manager->calculateTotal("expense");
    double balance = totalIncome - totalExpense;

    cout << "����ͳ��: " << totalIncome << " Ԫ" << endl;
    cout << "֧��ͳ��: " << totalExpense << " Ԫ" << endl;
    cout << "������: " << balance << " Ԫ" << endl;

    if (balance > 0) {
        cout << "����״��: ӯ��" << endl;
    }
    else if (balance < 0) {
        cout << "����״��: ����" << endl;
    }
    else {
        cout << "����״��: ��֧ƽ��" << endl;
    }

    cout << "=================================" << endl;
}

// �����ļ�����
void UserInterface::saveToFileInterface() const {
    cout << "\n========== ���浽�ļ� ==========" << endl;

    string filename = getStringInput("�������ļ��� (��: data.csv): ");
    manager->saveToFile(filename);
}

// �����ļ�����
void UserInterface::loadFromFileInterface() {
    cout << "\n========== ���ļ����� ==========" << endl;

    string filename = getStringInput("�������ļ���: ");
    manager->loadFromFile(filename);
}

// �������뻺����
void UserInterface::clearInputBuffer() const {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// ��ȡ��������
int UserInterface::getIntInput(const string& prompt) const {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            clearInputBuffer();
            return value;
        }
        else {
            cout << "���������������Ч��������" << endl;
            clearInputBuffer();
        }
    }
}

// ��ȡ����������
double UserInterface::getDoubleInput(const string& prompt) const {
    double value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            clearInputBuffer();
            return value;
        }
        else {
            cout << "���������������Ч�����֣�" << endl;
            clearInputBuffer();
        }
    }
}

// ��ȡ�ַ�������
string UserInterface::getStringInput(const string& prompt) const {
    string value;
    cout << prompt;
    getline(cin, value);
    return value;
}

// ��֤���ڸ�ʽ
bool UserInterface::isValidDate(const string& date) const {
    regex datePattern(R"(\d{4}-\d{2}-\d{2})");
    return regex_match(date, datePattern);
}

// ��֤��������
bool UserInterface::isValidType(const string& type) const {
    return (type == "income" || type == "expense");
}

// ��ͣ�ȴ��û�����
void UserInterface::pauseForUser() const {
    cout << "\n�� Enter ������...";
    cin.get();
}

// ��������
void UserInterface::clearScreen() const {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}