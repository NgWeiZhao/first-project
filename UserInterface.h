#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "FinanceManager.h"
#include <iostream>
#include <string>
#include <limits>

using namespace std;

// 用户界面类，提供控制台交互功能
class UserInterface {
private:
    FinanceManager* manager;  // 财务管理器指针

    void displayMainMenu() const;  // 显示主菜单
    void addTransactionInterface();  // 添加交易界面
    void deleteTransactionInterface();  // 删除交易界面
    void listTransactionsInterface() const;  // 显示交易列表界面
    void calculateTotalInterface() const;  // 计算总金额界面
    void saveToFileInterface() const;  // 保存文件界面
    void loadFromFileInterface();  // 加载文件界面
    void showStatisticsInterface() const;  // 显示统计信息界面
    void clearInputBuffer() const;  // 清理输入缓冲区
    int getIntInput(const string& prompt) const;  // 获取整数输入
    double getDoubleInput(const string& prompt) const;  // 获取浮点数输入
    string getStringInput(const string& prompt) const;  // 获取字符串输入
    bool isValidDate(const string& date) const;  // 验证日期格式
    bool isValidType(const string& type) const;  // 验证交易类型

public:
    UserInterface(FinanceManager& fm);  // 构造函数
    ~UserInterface();  // 析构函数
    void run();  // 运行主界面循环
    void showWelcome() const;  // 显示欢迎信息
    void showGoodbye() const;  // 显示告别信息
    void pauseForUser() const;  // 暂停等待用户输入
    void clearScreen() const;  // 清屏功能
};

#endif