#include "UserInterface.h"
#include <cstdlib>
#include <regex>

// �غc�l
UserInterface::UserInterface(FinanceManager& fm) : manager(&fm) {}

// �Ѻc�l
UserInterface::~UserInterface() {}

// �D�{���j��
void UserInterface::run() {
    showWelcome();
    int choice;

    do {
        displayMainMenu();
        choice = getIntInput("�п�ܾާ@���� (1-8): ");

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
            cout << "�L�Ŀﶵ�A�Э��s��ܡC" << endl;
            break;
        }

        if (choice != 8) {
            pauseForUser();
        }

    } while (choice != 8);
}

// ����w��T��
void UserInterface::showWelcome() const {
    clearScreen();
    cout << "=====================================" << endl;
    cout << "    �w��ϥέӤH�]�Ⱥ޲z�t�ΡI" << endl;
    cout << "=====================================" << endl;
    cout << endl;
}

// ��ܧi�O�T��
void UserInterface::showGoodbye() const {
    cout << "\n=====================================" << endl;
    cout << "    �P�¨ϥέӤH�]�Ⱥ޲z�t�ΡI" << endl;
    cout << "         �w��A���ϥΡI" << endl;
    cout << "=====================================" << endl;
}

// ��ܥD���
void UserInterface::displayMainMenu() const {
    cout << "\n========== �D��� ==========" << endl;
    cout << "1. �s�W�������" << endl;
    cout << "2. �R���������" << endl;
    cout << "3. �d�ݩҦ����" << endl;
    cout << "4. �p���`���J�P��X" << endl;
    cout << "5. �d�ݲέp��T" << endl;
    cout << "6. �x�s���ɮ�" << endl;
    cout << "7. �q�ɮ׸��J" << endl;
    cout << "8. ���}�t��" << endl;
    cout << "============================" << endl;
}

// �s�W�����������
void UserInterface::addTransactionInterface() {
    cout << "\n========== �s�W������� ==========" << endl;

    int id = getIntInput("�п�J���ID: ");
    double amount = getDoubleInput("�п�J���B: ");

    string date;
    do {
        date = getStringInput("�п�J��� (YYYY-MM-DD): ");
        if (!isValidDate(date)) {
            cout << "����榡�����T�A�Э��s��J�C" << endl;
        }
    } while (!isValidDate(date));

    string description = getStringInput("�п�J�y�z: ");
    string category = getStringInput("�п�J���O: ");

    string type;
    do {
        type = getStringInput("�п�J���� (income/expense): ");
        if (!isValidType(type)) {
            cout << "���������� 'income' �� 'expense'�C" << endl;
        }
    } while (!isValidType(type));

    Transaction newTransaction(id, amount, date, description, category, type);
    manager->addTransaction(newTransaction);

    cout << "��������s�W���\�I" << endl;
}

// �R�������������
void UserInterface::deleteTransactionInterface() {
    cout << "\n========== �R��������� ==========" << endl;

    int id = getIntInput("�п�J�n�R�������ID: ");
    manager->deleteTransaction(id);
}

// ��ܩҦ��������
void UserInterface::listTransactionsInterface() const {
    cout << "\n========== �Ҧ�������� ==========" << endl;
    manager->listTransactions();
    cout << "=================================" << endl;
}

// �p���`���J�P��X
void UserInterface::calculateTotalInterface() const {
    cout << "\n========== �`���J�P��X ==========" << endl;

    double totalIncome = manager->calculateTotal("income");
    double totalExpense = manager->calculateTotal("expense");
    double balance = totalIncome - totalExpense;

    cout << "�`���J: " << totalIncome << " ��" << endl;
    cout << "�`��X: " << totalExpense << " ��" << endl;
    cout << "���l: " << balance << " ��" << endl;
    cout << "=============================" << endl;
}

// ��ܲέp��T
void UserInterface::showStatisticsInterface() const {
    cout << "\n========== �ԲӲέp��T ==========" << endl;

    double totalIncome = manager->calculateTotal("income");
    double totalExpense = manager->calculateTotal("expense");
    double balance = totalIncome - totalExpense;

    cout << "���J�έp: " << totalIncome << " ��" << endl;
    cout << "��X�έp: " << totalExpense << " ��" << endl;
    cout << "���l: " << balance << " ��" << endl;

    if (balance > 0) {
        cout << "�]�Ȫ��p: �վl" << endl;
    }
    else if (balance < 0) {
        cout << "�]�Ȫ��p: ���r" << endl;
    }
    else {
        cout << "�]�Ȫ��p: ���䥭��" << endl;
    }

    cout << "=================================" << endl;
}

// �x�s���ɮפ���
void UserInterface::saveToFileInterface() const {
    cout << "\n========== �x�s���ɮ� ==========" << endl;

    string filename = getStringInput("�п�J�ɮצW�� (�w�]: data.csv): ");
    manager->saveToFile(filename);
}

// �q�ɮ׸��J����
void UserInterface::loadFromFileInterface() {
    cout << "\n========== �q�ɮ׸��J ==========" << endl;

    string filename = getStringInput("�п�J�ɮצW��: ");
    manager->loadFromFile(filename);
}

// �M����J�w�İ�
void UserInterface::clearInputBuffer() const {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// ���o��ƿ�J
int UserInterface::getIntInput(const string& prompt) const {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            clearInputBuffer();
            return value;
        }
        else {
            cout << "��J�L�ġA�п�J���Ī���ơC" << endl;
            clearInputBuffer();
        }
    }
}

// ���o�B�I�ƿ�J
double UserInterface::getDoubleInput(const string& prompt) const {
    double value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            clearInputBuffer();
            return value;
        }
        else {
            cout << "��J�L�ġA�п�J���Ī��Ʀr�C" << endl;
            clearInputBuffer();
        }
    }
}

// ���o�r���J
string UserInterface::getStringInput(const string& prompt) const {
    string value;
    cout << prompt;
    getline(cin, value);
    return value;
}

// ���Ҥ���榡
bool UserInterface::isValidDate(const string& date) const {
    regex datePattern(R"(\d{4}-\d{2}-\d{2})");
    return regex_match(date, datePattern);
}

// ���ҥ������
bool UserInterface::isValidType(const string& type) const {
    return (type == "income" || type == "expense");
}

// �Ȱ����ݨϥΪ�
void UserInterface::pauseForUser() const {
    cout << "\n�� Enter ���~��...";
    cin.get();
}

// �M���ù�
void UserInterface::clearScreen() const {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
