#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <memory>
#include <algorithm>

using namespace std;

class Reservation {
public:
    string name; // 预约人姓名
    int roomNumber; // 房间号
    string phoneNumber; // 电话号码
    string idNumber; // 身份证号

    Reservation() {}

    Reservation(string n, int r, string p, string i) : name(n), roomNumber(r), phoneNumber(p), idNumber(i) {}

    // 重载<<运算符，用于输出预约信息
    friend ostream& operator<<(ostream& os, const Reservation& r) {
        os << "姓名: " << r.name << ", 房间号: " << r.roomNumber << ", 电话号码: " << r.phoneNumber << ", 身份证号: " << r.idNumber;
        return os;
    }

    // 虚函数，用于派生类的扩展
    virtual void display() {
        cout << *this << endl;
    }
};


class VIPReservation : public Reservation {
public:
    int vipLevel; // VIP等级

    VIPReservation() {}

    VIPReservation(string n, int r, int v, string p, string i) : Reservation(n, r, p, i), vipLevel(v) {}

    // 重载<<运算符，用于输出预约信息
    friend ostream& operator<<(ostream& os, const VIPReservation& r) {
        os << "姓名: " << r.name << ", 房间号: " << r.roomNumber << ", VIP等级: " << r.vipLevel << ", 电话号码: " << r.phoneNumber << ", 身份证号: " << r.idNumber;
        return os;
    }

    // 覆盖基类的虚函数
    void display() override {
        cout << *this << endl;
    }
};


class Hotel {
private:
    vector<shared_ptr<Reservation>> reservations; // 预约信息列表

public:
    // 增加预约信息
    void addReservation(shared_ptr<Reservation> r) {
        reservations.push_back(r);
    }
    //判断增加的预约信息是否合法
    bool check(shared_ptr<Reservation> r) {
        for (const auto& res : reservations) {
            if (res->name == r->name)
            {
                cout << "姓名重复，请重新输入。" << endl;
                return true;
            }
            if (res->roomNumber == r->roomNumber)
            {
                cout << "房间号重复，请重新输入。" << endl;
                return true;
            }
            if (res->phoneNumber == r->phoneNumber)
            {
                cout << "电话号重复，请重新输入。" << endl;
                return true;
            }
            if (res->idNumber == r->idNumber) {
                cout << "身份证号重复，请重新输入。" << endl;
                return true;
            }
        }
        return false;
    }
    // 排序预约信息
    void sortReservations(int option) {
        switch (option) {
        case 1:
            sort(reservations.begin(), reservations.end(), [](const shared_ptr<Reservation>& a, const shared_ptr<Reservation>& b) {
                return a->name < b->name;
                });
            break;
        case 2:
            sort(reservations.begin(), reservations.end(), [](const shared_ptr<Reservation>& a, const shared_ptr<Reservation>& b) {
                return a->roomNumber < b->roomNumber;
                });
            break;
        case 3:
            sort(reservations.begin(), reservations.end(), [](const shared_ptr<Reservation>& a, const shared_ptr<Reservation>& b) {
                return a->phoneNumber < b->phoneNumber;
                });
            break;
        case 4:
            sort(reservations.begin(), reservations.end(), [](const shared_ptr<Reservation>& a, const shared_ptr<Reservation>& b) {
                return a->idNumber < b->idNumber;
                });
            break;
        default:
            cout << "无效的选择，请重新输入。" << endl;
        }
    }


    // 显示预约信息
    void displayReservations() {
        if (reservations.empty()) {
            cout << "没有预约信息" << endl;
        }
        else {
            for (const auto& r : reservations) {
                r->display();
            }
        }
    }

    // 修改预约信息
    void modifyReservation(const string& name, int newRoomNumber, const string& newPhoneNumber, const string& newIdNumber) {
        for (auto& r : reservations) {
            if (r->name == name) {
                r->roomNumber = newRoomNumber;
                r->phoneNumber = newPhoneNumber;
                r->idNumber = newIdNumber;
                break;
            }
        }
    }

    // 删除预约信息
    void deleteReservation(const string& name) {
        int flag = 1;
        for (auto it = reservations.begin(); it != reservations.end(); ++it) {
            if ((*it)->name == name) {
                reservations.erase(it);
                flag = 0;
                break;
            }
        }
        if (flag)cout << "未找到此人" << "\n";
    }

    // 查找预约人员信息
    shared_ptr<Reservation> findReservation(const string& name = "", const string& phoneNumber = "", const string& idNumber = "") {
        for (const auto& r : reservations) {
            if (r->name == name || r->phoneNumber == phoneNumber || r->idNumber == idNumber) {
                return r;
            }
        }
        return nullptr;
    }

    // 保存酒店预约信息到文件
    void saveToFile(const string& filename) {
        ofstream file(filename);
        for (const auto& r : reservations) {
            if (dynamic_pointer_cast<VIPReservation>(r)) {
                file << "VIP ";
            }
            else {
                file << "Normal ";
            }
            file << r->name << " " << r->roomNumber << " " << r->phoneNumber << " " << r->idNumber << endl;
        }
        file.close();
    }

    // 从文件加载酒店预约信息
    void loadFromFile(const string& filename) {
        ifstream file(filename);
        string type, name, phoneNumber, idNumber;
        int roomNumber, vipLevel;
        while (file >> type) {
            if (type == "Normal") {
                file >> name >> roomNumber >> phoneNumber >> idNumber;
                reservations.push_back(make_shared<Reservation>(name, roomNumber, phoneNumber, idNumber));
            }
            else if (type == "VIP") {
                file >> name >> roomNumber >> vipLevel >> phoneNumber >> idNumber;
                reservations.push_back(make_shared<VIPReservation>(name, roomNumber, vipLevel, phoneNumber, idNumber));
            }
        }
        file.close();
    }
};

int main() {
    Hotel hotel;
    hotel.loadFromFile("reservations.txt");
    int choice;
    string name;
    int roomNumber;
    int vipLevel;
    string phoneNumber; // 声明 phoneNumber 变量
    string idNumber; // 声明 idNumber 变量

    while (true) {
        cout << "******************* 酒店预约系统 *******************" << endl;
        cout << "* 1. 增加预约信息" << endl;
        cout << "* 2. 增加VIP预约信息" << endl;
        cout << "* 3. 显示预约信息" << endl;
        cout << "* 4. 修改预约信息" << endl;
        cout << "* 5. 删除预约信息" << endl;
        cout << "* 6. 查找预约人员信息" << endl;
        cout << "* 7. 保存酒店预约信息" << endl;
        cout << "* 8. 排序预约信息" << endl;
        cout << "* 9. 退出" << endl;
        cout << "*****************************************************" << endl;
        cout << "请输入您的选择: ";
        cin >> choice;

        switch (choice) {
        case 1:
            do {
                cout << "请输入姓名: ";
                cin >> name;
                cout << "请输入房间号: ";
                cin >> roomNumber;
                cout << "请输入电话号码: ";
                cin >> phoneNumber;
                cout << "请输入身份证号: ";
                cin >> idNumber;
            } while (hotel.check(make_shared<Reservation>(name, roomNumber, phoneNumber, idNumber)));
            hotel.addReservation(make_shared<Reservation>(name, roomNumber, phoneNumber, idNumber));
            cout << "操作完成" << endl;
            break;
        case 2:
            cout << "请输入姓名: ";
            cin >> name;
            cout << "请输入房间号: ";
            cin >> roomNumber;
            cout << "请输入VIP等级: ";
            cin >> vipLevel;
            cout << "请输入电话号码: ";
            cin >> phoneNumber;
            cout << "请输入身份证号: ";
            cin >> idNumber;
            hotel.addReservation(make_shared<VIPReservation>(name, roomNumber, vipLevel, phoneNumber, idNumber));
            cout << "操作完成" << endl;
            break;
        case 3:
            hotel.displayReservations();
            cout << "操作完成" << endl;
            break;
        case 4:
            cout << "请输入要修改的预约人姓名: ";
            cin >> name;
            do {
                cout << "请输入新的房间号: ";
                cin >> roomNumber;
                cout << "请输入新的电话号码: ";
                cin >> phoneNumber;
                cout << "请输入新的身份证号: ";
                cin >> idNumber;
            } while (hotel.check(make_shared<VIPReservation>(" ", roomNumber, vipLevel, phoneNumber, idNumber)));
            hotel.modifyReservation(name, roomNumber, phoneNumber, idNumber);
            cout << "操作完成" << endl;
            break;
        case 5:
            do {
                cout << "请输入要删除的预约人姓名: ";
                cin >> name;
                auto p = hotel.findReservation(name);
                if (p == nullptr)cout << "未找到此人，请重新输入" << "\n";
            } while (hotel.findReservation(name) == nullptr);
            hotel.deleteReservation(name);
            cout << "操作完成" << endl;
            break;
        case 6:
            cout << "请输入要查找的预约人姓名: ";
            cin >> name;
            if (auto r = hotel.findReservation(name)) {
                r->display();
            }
            else {
                cout << "未找到预约人员信息" << endl;
            }
            cout << "操作完成" << endl;
            break;
        case 7:
            hotel.saveToFile("reservations.txt");
            cout << "操作完成" << endl;
            break;
        case 8:
            cout << "------------------- 排序选项 -------------------" << endl;
            cout << "- 1. 基于姓名排序" << endl;
            cout << "- 2. 基于房间号排序" << endl;
            cout << "- 3. 基于电话号码排序" << endl;
            cout << "- 4. 基于身份证号排序" << endl;
            cout << "----------------------------------------------" << endl;
            cout << "请输入您的选择: ";
            cin >> choice;
            hotel.sortReservations(choice);
            hotel.displayReservations();
            cout << "操作完成" << endl;
            break;
        case 9:
            return 0;
        default:
            cout << "无效的选择，请重新输入。" << endl;
        }
        cout << "点击任意键确定" << endl;
        cin.ignore();
        cin.get();
        // 清屏
        system("cls");
    }

    return 0;
}
