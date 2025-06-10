#include "UserInterface.h"
#include <iostream>
#include <exception>

using namespace std;

int main() {
    try {
        // 初始化提示訊息
        cout << "初始化財務管理系統..." << endl;
        cout << "預設加入示範交易資料..." << endl;

        // 建立財務管理器
        FinanceManager manager;

        // 加入預設的交易資料（示範用）
        manager.addTransaction(Transaction(1, 3000.0, "2025-05-01", "薪資入帳", "收入", "income"));
        manager.addTransaction(Transaction(2, 150.0, "2025-05-02", "超市購物", "生活", "expense"));
        manager.addTransaction(Transaction(3, 80.0, "2025-05-03", "咖啡店消費", "娛樂", "expense"));
        manager.addTransaction(Transaction(4, 500.0, "2025-05-04", "兼職收入", "收入", "income"));
        manager.addTransaction(Transaction(5, 200.0, "2025-05-05", "交通費", "交通", "expense"));

        cout << "交易資料初始化完成，共加入 5 筆交易紀錄。" << endl;

        // 顯示系統版本與說明
        cout << "\n========== 系統資訊 ==========" << endl;
        cout << "版本：1.0.0" << endl;
        cout << "模組：財務管理系統" << endl;
        cout << "功能：收入與支出管理、交易查詢、報表統計" << endl;
        cout << "=============================" << endl;

        // 詢問是否讀取交易資料檔案
        cout << "\n是否要從檔案載入交易紀錄？(y/n): ";
        char choice;
        cin >> choice;
        cin.ignore(); // 清除輸入緩衝區

        if (choice == 'y' || choice == 'Y') {
            cout << "請輸入檔案名稱（預設為 finance.csv）: ";
            string filename;
            getline(cin, filename);

            if (filename.empty()) {
                filename = "finance.csv";
            }

            try {
                manager.loadFromFile(filename);
                cout << "交易資料載入完成。" << endl;
            }
            catch (...) {
                cout << "讀取資料時發生錯誤，將繼續使用預設資料..." << endl;
            }
        }

        // 啟動使用者介面
        UserInterface ui(manager);
        ui.run();

        // 詢問是否備份儲存資料
        cout << "\n是否要儲存資料備份？(y/n): ";
        cin >> choice;

        if (choice == 'y' || choice == 'Y') {
            cout << "資料已儲存至 finance_backup.csv。" << endl;
            manager.saveToFile("finance_backup.csv");
        }

        cout << "\n感謝使用本系統，祝您財務健康！" << endl;

    }
    catch (const exception& e) {
        // 捕捉標準例外錯誤
        cerr << "\n程式發生錯誤： " << e.what() << endl;
        cerr << "請確認輸入資料或檔案格式是否正確。" << endl;

        cout << "\n請按 Enter 鍵結束...";
        cin.get();
        return 1;

    }
    catch (...) {
        // 捕捉其他未知錯誤
        cerr << "\n發生未知錯誤，系統即將關閉。" << endl;

        cout << "\n請按 Enter 鍵結束...";
        cin.get();
        return 1;
    }

    return 0;
}
