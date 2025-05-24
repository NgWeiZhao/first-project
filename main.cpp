#include "UserInterface.h"
#include <iostream>
#include <exception>

using namespace std;

int main() {
    try {
        // 显示程序启动信息
        cout << "正在启动个人财务管理系统..." << endl;
        cout << "初始化中..." << endl;

        // 创建财务管理器对象
        FinanceManager manager;

        // 预加载一些示例数据（可选）
        cout << "加载示例数据..." << endl;
        manager.addTransaction(Transaction(1, 3000.0, "2025-05-01", "工资", "收入", "income"));
        manager.addTransaction(Transaction(2, 150.0, "2025-05-02", "超市购物", "食物", "expense"));
        manager.addTransaction(Transaction(3, 80.0, "2025-05-03", "交通费", "出行", "expense"));
        manager.addTransaction(Transaction(4, 500.0, "2025-05-04", "兼职收入", "收入", "income"));
        manager.addTransaction(Transaction(5, 200.0, "2025-05-05", "购买衣服", "购物", "expense"));

        cout << "系统初始化完成！" << endl;
        cout << "已加载 5 条示例交易记录" << endl;

        // 显示系统信息
        cout << "\n========== 系统信息 ==========" << endl;
        cout << "版本: 1.0.0" << endl;
        cout << "作者: 个人财务管理系统" << endl;
        cout << "功能: 收支管理、统计分析、数据存储" << endl;
        cout << "=============================" << endl;

        // 询问用户是否要加载已有数据文件
        cout << "\n是否要加载已保存的数据文件？(y/n): ";
        char choice;
        cin >> choice;
        cin.ignore(); // 清理输入缓冲区

        if (choice == 'y' || choice == 'Y') {
            cout << "请输入文件名 (默认: finance.csv): ";
            string filename;
            getline(cin, filename);

            if (filename.empty()) {
                filename = "finance.csv";
            }

            try {
                manager.loadFromFile(filename);
                cout << "数据加载成功！" << endl;
            }
            catch (...) {
                cout << "文件加载失败，使用示例数据继续..." << endl;
            }
        }

        // 创建用户界面对象并运行
        UserInterface ui(manager);
        ui.run();

        // 程序结束前询问是否保存数据
        cout << "\n是否要保存当前数据？(y/n): ";
        cin >> choice;

        if (choice == 'y' || choice == 'Y') {
            cout << "数据已自动保存到 finance_backup.csv" << endl;
            manager.saveToFile("finance_backup.csv");
        }

        cout << "\n程序已安全退出。" << endl;

    }
    catch (const exception& e) {
        // 异常处理
        cerr << "\n程序运行出现错误: " << e.what() << endl;
        cerr << "请检查数据文件格式或联系技术支持。" << endl;

        cout << "\n按任意键退出...";
        cin.get();
        return 1;

    }
    catch (...) {
        // 捕获所有其他异常
        cerr << "\n程序遇到未知错误，即将退出。" << endl;

        cout << "\n按任意键退出...";
        cin.get();
        return 1;
    }

    return 0;
}