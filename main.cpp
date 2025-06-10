#include "UserInterface.h"
#include <iostream>
#include <exception>

using namespace std;

int main() {
    try {
        // ��l�ƴ��ܰT��
        cout << "��l�ư]�Ⱥ޲z�t��..." << endl;
        cout << "�w�]�[�J�ܽd������..." << endl;

        // �إ߰]�Ⱥ޲z��
        FinanceManager manager;

        // �[�J�w�]�������ơ]�ܽd�Ρ^
        manager.addTransaction(Transaction(1, 3000.0, "2025-05-01", "�~��J�b", "���J", "income"));
        manager.addTransaction(Transaction(2, 150.0, "2025-05-02", "�W���ʪ�", "�ͬ�", "expense"));
        manager.addTransaction(Transaction(3, 80.0, "2025-05-03", "�@�ة����O", "�T��", "expense"));
        manager.addTransaction(Transaction(4, 500.0, "2025-05-04", "��¾���J", "���J", "income"));
        manager.addTransaction(Transaction(5, 200.0, "2025-05-05", "��q�O", "��q", "expense"));

        cout << "�����ƪ�l�Ƨ����A�@�[�J 5 ����������C" << endl;

        // ��ܨt�Ϊ����P����
        cout << "\n========== �t�θ�T ==========" << endl;
        cout << "�����G1.0.0" << endl;
        cout << "�ҲաG�]�Ⱥ޲z�t��" << endl;
        cout << "�\��G���J�P��X�޲z�B����d�ߡB����έp" << endl;
        cout << "=============================" << endl;

        // �߰ݬO�_Ū���������ɮ�
        cout << "\n�O�_�n�q�ɮ׸��J��������H(y/n): ";
        char choice;
        cin >> choice;
        cin.ignore(); // �M����J�w�İ�

        if (choice == 'y' || choice == 'Y') {
            cout << "�п�J�ɮצW�١]�w�]�� finance.csv�^: ";
            string filename;
            getline(cin, filename);

            if (filename.empty()) {
                filename = "finance.csv";
            }

            try {
                manager.loadFromFile(filename);
                cout << "�����Ƹ��J�����C" << endl;
            }
            catch (...) {
                cout << "Ū����Ʈɵo�Ϳ��~�A�N�~��ϥιw�]���..." << endl;
            }
        }

        // �ҰʨϥΪ̤���
        UserInterface ui(manager);
        ui.run();

        // �߰ݬO�_�ƥ��x�s���
        cout << "\n�O�_�n�x�s��Ƴƥ��H(y/n): ";
        cin >> choice;

        if (choice == 'y' || choice == 'Y') {
            cout << "��Ƥw�x�s�� finance_backup.csv�C" << endl;
            manager.saveToFile("finance_backup.csv");
        }

        cout << "\n�P�¨ϥΥ��t�ΡA���z�]�Ȱ��d�I" << endl;

    }
    catch (const exception& e) {
        // �����зǨҥ~���~
        cerr << "\n�{���o�Ϳ��~�G " << e.what() << endl;
        cerr << "�нT�{��J��Ʃ��ɮ׮榡�O�_���T�C" << endl;

        cout << "\n�Ы� Enter �䵲��...";
        cin.get();
        return 1;

    }
    catch (...) {
        // ������L�������~
        cerr << "\n�o�ͥ������~�A�t�ΧY�N�����C" << endl;

        cout << "\n�Ы� Enter �䵲��...";
        cin.get();
        return 1;
    }

    return 0;
}
