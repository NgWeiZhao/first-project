#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "FinanceManager.h"
#include <iostream>
#include <string>
#include <limits>

using namespace std;

// �û������࣬�ṩ����̨��������
class UserInterface {
private:
    FinanceManager* manager;  // ���������ָ��

    void displayMainMenu() const;  // ��ʾ���˵�
    void addTransactionInterface();  // ��ӽ��׽���
    void deleteTransactionInterface();  // ɾ�����׽���
    void listTransactionsInterface() const;  // ��ʾ�����б����
    void calculateTotalInterface() const;  // �����ܽ�����
    void saveToFileInterface() const;  // �����ļ�����
    void loadFromFileInterface();  // �����ļ�����
    void showStatisticsInterface() const;  // ��ʾͳ����Ϣ����
    void clearInputBuffer() const;  // �������뻺����
    int getIntInput(const string& prompt) const;  // ��ȡ��������
    double getDoubleInput(const string& prompt) const;  // ��ȡ����������
    string getStringInput(const string& prompt) const;  // ��ȡ�ַ�������
    bool isValidDate(const string& date) const;  // ��֤���ڸ�ʽ
    bool isValidType(const string& type) const;  // ��֤��������

public:
    UserInterface(FinanceManager& fm);  // ���캯��
    ~UserInterface();  // ��������
    void run();  // ����������ѭ��
    void showWelcome() const;  // ��ʾ��ӭ��Ϣ
    void showGoodbye() const;  // ��ʾ�����Ϣ
    void pauseForUser() const;  // ��ͣ�ȴ��û�����
    void clearScreen() const;  // ��������
};

#endif