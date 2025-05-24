#include "UserInterface.h"
#include <iostream>
#include <exception>

using namespace std;

int main() {
    try {
        // ��ʾ����������Ϣ
        cout << "�����������˲������ϵͳ..." << endl;
        cout << "��ʼ����..." << endl;

        // �����������������
        FinanceManager manager;

        // Ԥ����һЩʾ�����ݣ���ѡ��
        cout << "����ʾ������..." << endl;
        manager.addTransaction(Transaction(1, 3000.0, "2025-05-01", "����", "����", "income"));
        manager.addTransaction(Transaction(2, 150.0, "2025-05-02", "���й���", "ʳ��", "expense"));
        manager.addTransaction(Transaction(3, 80.0, "2025-05-03", "��ͨ��", "����", "expense"));
        manager.addTransaction(Transaction(4, 500.0, "2025-05-04", "��ְ����", "����", "income"));
        manager.addTransaction(Transaction(5, 200.0, "2025-05-05", "�����·�", "����", "expense"));

        cout << "ϵͳ��ʼ����ɣ�" << endl;
        cout << "�Ѽ��� 5 ��ʾ�����׼�¼" << endl;

        // ��ʾϵͳ��Ϣ
        cout << "\n========== ϵͳ��Ϣ ==========" << endl;
        cout << "�汾: 1.0.0" << endl;
        cout << "����: ���˲������ϵͳ" << endl;
        cout << "����: ��֧����ͳ�Ʒ��������ݴ洢" << endl;
        cout << "=============================" << endl;

        // ѯ���û��Ƿ�Ҫ�������������ļ�
        cout << "\n�Ƿ�Ҫ�����ѱ���������ļ���(y/n): ";
        char choice;
        cin >> choice;
        cin.ignore(); // �������뻺����

        if (choice == 'y' || choice == 'Y') {
            cout << "�������ļ��� (Ĭ��: finance.csv): ";
            string filename;
            getline(cin, filename);

            if (filename.empty()) {
                filename = "finance.csv";
            }

            try {
                manager.loadFromFile(filename);
                cout << "���ݼ��سɹ���" << endl;
            }
            catch (...) {
                cout << "�ļ�����ʧ�ܣ�ʹ��ʾ�����ݼ���..." << endl;
            }
        }

        // �����û������������
        UserInterface ui(manager);
        ui.run();

        // �������ǰѯ���Ƿ񱣴�����
        cout << "\n�Ƿ�Ҫ���浱ǰ���ݣ�(y/n): ";
        cin >> choice;

        if (choice == 'y' || choice == 'Y') {
            cout << "�������Զ����浽 finance_backup.csv" << endl;
            manager.saveToFile("finance_backup.csv");
        }

        cout << "\n�����Ѱ�ȫ�˳���" << endl;

    }
    catch (const exception& e) {
        // �쳣����
        cerr << "\n�������г��ִ���: " << e.what() << endl;
        cerr << "���������ļ���ʽ����ϵ����֧�֡�" << endl;

        cout << "\n��������˳�...";
        cin.get();
        return 1;

    }
    catch (...) {
        // �������������쳣
        cerr << "\n��������δ֪���󣬼����˳���" << endl;

        cout << "\n��������˳�...";
        cin.get();
        return 1;
    }

    return 0;
}