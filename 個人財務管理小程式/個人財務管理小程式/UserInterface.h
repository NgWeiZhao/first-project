#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "FinanceManager.h"
#include <iostream>
#include <string>
#include <limits>

using namespace std;

// 使用者介面類別：提供與使用者互動的功能
class UserInterface {
private:
    FinanceManager* manager;  // 財務管理器指標

    // 內部功能介面
    void displayMainMenu() const;               // 顯示主選單
    void addTransactionInterface();             // 新增交易介面
    void deleteTransactionInterface();          // 刪除交易介面
    void listTransactionsInterface() const;     // 列出所有交易
    void calculateTotalInterface() const;       // 計算總收入與支出
    void saveToFileInterface() const;           // 儲存至檔案介面
    void loadFromFileInterface();               // 從檔案讀取資料介面
    void showStatisticsInterface() const;       // 顯示統計資訊
    void clearInputBuffer() const;              // 清除輸入緩衝區

    // 使用者輸入處理
    int getIntInput(const string& prompt) const;         // 取得整數輸入
    double getDoubleInput(const string& prompt) const;   // 取得浮點數輸入
    string getStringInput(const string& prompt) const;   // 取得字串輸入
    bool isValidDate(const string& date) const;          // 驗證日期格式
    bool isValidType(const string& type) const;          // 驗證交易類型

public:
    UserInterface(FinanceManager& fm);   // 建構子
    ~UserInterface();                    // 解構子

    // 執行主流程
    void run();                          // 執行使用者介面主程式
    void showWelcome() const;           // 顯示歡迎訊息
    void showGoodbye() const;           // 顯示離開訊息
    void pauseForUser() const;          // 暫停等待使用者按鍵
    void clearScreen() const;           // 清除螢幕內容
};

#endif
