#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "FinanceManager.h"
#include <iostream>
#include <string>
#include <limits>

using namespace std;

// �ϥΪ̤������O�G���ѻP�ϥΪ̤��ʪ��\��
class UserInterface {
private:
    FinanceManager* manager;  // �]�Ⱥ޲z������

    // �����\�श��
    void displayMainMenu() const;               // ��ܥD���
    void addTransactionInterface();             // �s�W�������
    void deleteTransactionInterface();          // �R���������
    void listTransactionsInterface() const;     // �C�X�Ҧ����
    void calculateTotalInterface() const;       // �p���`���J�P��X
    void saveToFileInterface() const;           // �x�s���ɮפ���
    void loadFromFileInterface();               // �q�ɮ�Ū����Ƥ���
    void showStatisticsInterface() const;       // ��ܲέp��T
    void clearInputBuffer() const;              // �M����J�w�İ�

    // �ϥΪ̿�J�B�z
    int getIntInput(const string& prompt) const;         // ���o��ƿ�J
    double getDoubleInput(const string& prompt) const;   // ���o�B�I�ƿ�J
    string getStringInput(const string& prompt) const;   // ���o�r���J
    bool isValidDate(const string& date) const;          // ���Ҥ���榡
    bool isValidType(const string& type) const;          // ���ҥ������

public:
    UserInterface(FinanceManager& fm);   // �غc�l
    ~UserInterface();                    // �Ѻc�l

    // ����D�y�{
    void run();                          // ����ϥΪ̤����D�{��
    void showWelcome() const;           // ����w��T��
    void showGoodbye() const;           // ������}�T��
    void pauseForUser() const;          // �Ȱ����ݨϥΪ̫���
    void clearScreen() const;           // �M���ù����e
};

#endif
