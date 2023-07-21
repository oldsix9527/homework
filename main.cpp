#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <memory>

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
    friend ostream &operator<<(ostream &os, const Reservation &r) {
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
    friend ostream &operator<<(ostream &os, const VIPReservation &r) {
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

    // 显示预约信息
    void displayReservations() {
        if (reservations.empty()) {
            cout << "没有预约信息" << endl;
        } else {
            for (const auto &r : reservations) {
                r->display();
            }
        }
    }

    // 修改预约信息
    void modifyReservation(const string &name, int newRoomNumber) {
        for (auto &r : reservations) {
            if (r->name == name) {
                r->roomNumber = newRoomNumber;
                break;
            }
        }
    }

    // 删除预约信息
    void deleteReservation(const string &name) {
        for (auto it = reservations.begin(); it != reservations.end(); ++it) {
            if ((*it)->name == name) {
                reservations.erase(it);
                break;
            }
        }
    }

    // 查找预约人员信息
    shared_ptr<Reservation> findReservation(const string &name) {
        for (const auto &r : reservations) {
            if (r->name == name) {
                return r;
            }
        }
        return nullptr;
    }

    // 保存酒店预约信息到文件
    void saveToFile(const string &filename) {
        ofstream file(filename);
        for (const auto &r : reservations) {
            if (dynamic_pointer_cast<VIPReservation>(r)) {
                file << "VIP ";
            } else {
                file << "Normal ";
            }
            file << r->name << " " << r->roomNumber << " " << r->phoneNumber << " " << r->idNumber << endl;
        }
        file.close();
    }

    // 从文件加载酒店预约信息
    void loadFromFile(const string &filename) {
        ifstream file(filename);
        string type, name, phoneNumber, idNumber;
        int roomNumber, vipLevel;
        while (file >> type) {
            if (type == "Normal") {
                file >> name >> roomNumber >> phoneNumber >> idNumber;
                reservations.push_back(make_shared<Reservation>(name, roomNumber, phoneNumber, idNumber));
            } else if (type == "VIP") {
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
        cout << "1. 增加预约信息" << endl;
        cout << "2. 增加VIP预约信息" << endl;
        cout << "3. 显示预约信息" << endl;
        cout << "4. 修改预约信息" << endl;
        cout << "5. 删除预约信息" << endl;
        cout << "6. 查找预约人员信息" << endl;
        cout << "7. 保存酒店预约信息" << endl;
        cout << "8. 退出" << endl;
        cout << "请输入您的选择: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "请输入姓名: ";
            cin >> name;
            cout << "请输入房间号: ";
            cin >> roomNumber;
            cout << "请输入电话号码: ";
            cin >> phoneNumber;
            cout << "请输入身份证号: ";
            cin >> idNumber;
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
            cout << "请输入新的房间号: ";
            cin >> roomNumber;
            hotel.modifyReservation(name, roomNumber);
            cout << "操作完成" << endl;
            break;
        case 5:
            cout << "请输入要删除的预约人姓名: ";
            cin >> name;
            hotel.deleteReservation(name);
            cout << "操作完成" << endl;
            break;
        case 6:
            cout << "请输入要查找的预约人姓名: ";
            cin >> name;
            if (auto r = hotel.findReservation(name)) {
                r->display();
            } else {
                cout << "未找到预约人员信息" << endl;
            }
            cout << "操作完成" << endl;
            break;
        case 7:
            hotel.saveToFile("reservations.txt");
            cout << "操作完成" << endl;
            break;
        case 8:
            return 0;
        default:
            cout << "无效的选择，请重新输入。" << endl;
        }
        cout<<"点击任意键确定"<<endl;
        cin.ignore();
        cin.get();
        // 清屏
        system("cls");
    }

    return 0;
}
