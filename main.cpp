#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <memory>

using namespace std;

class Reservation {
public:
    string name; // ԤԼ������
    int roomNumber; // �����
    string phoneNumber; // �绰����
    string idNumber; // ���֤��

    Reservation() {}

    Reservation(string n, int r, string p, string i) : name(n), roomNumber(r), phoneNumber(p), idNumber(i) {}

    // ����<<��������������ԤԼ��Ϣ
    friend ostream &operator<<(ostream &os, const Reservation &r) {
        os << "����: " << r.name << ", �����: " << r.roomNumber << ", �绰����: " << r.phoneNumber << ", ���֤��: " << r.idNumber;
        return os;
    }

    // �麯�����������������չ
    virtual void display() {
        cout << *this << endl;
    }
};


class VIPReservation : public Reservation {
public:
    int vipLevel; // VIP�ȼ�

    VIPReservation() {}

    VIPReservation(string n, int r, int v, string p, string i) : Reservation(n, r, p, i), vipLevel(v) {}

    // ����<<��������������ԤԼ��Ϣ
    friend ostream &operator<<(ostream &os, const VIPReservation &r) {
        os << "����: " << r.name << ", �����: " << r.roomNumber << ", VIP�ȼ�: " << r.vipLevel << ", �绰����: " << r.phoneNumber << ", ���֤��: " << r.idNumber;
        return os;
    }

    // ���ǻ�����麯��
    void display() override {
        cout << *this << endl;
    }
};


class Hotel {
private:
    vector<shared_ptr<Reservation>> reservations; // ԤԼ��Ϣ�б�

public:
    // ����ԤԼ��Ϣ
    void addReservation(shared_ptr<Reservation> r) {
        reservations.push_back(r);
    }

    // ��ʾԤԼ��Ϣ
    void displayReservations() {
        if (reservations.empty()) {
            cout << "û��ԤԼ��Ϣ" << endl;
        } else {
            for (const auto &r : reservations) {
                r->display();
            }
        }
    }

    // �޸�ԤԼ��Ϣ
    void modifyReservation(const string &name, int newRoomNumber) {
        for (auto &r : reservations) {
            if (r->name == name) {
                r->roomNumber = newRoomNumber;
                break;
            }
        }
    }

    // ɾ��ԤԼ��Ϣ
    void deleteReservation(const string &name) {
        for (auto it = reservations.begin(); it != reservations.end(); ++it) {
            if ((*it)->name == name) {
                reservations.erase(it);
                break;
            }
        }
    }

    // ����ԤԼ��Ա��Ϣ
    shared_ptr<Reservation> findReservation(const string &name) {
        for (const auto &r : reservations) {
            if (r->name == name) {
                return r;
            }
        }
        return nullptr;
    }

    // ����Ƶ�ԤԼ��Ϣ���ļ�
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

    // ���ļ����ؾƵ�ԤԼ��Ϣ
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
    string phoneNumber; // ���� phoneNumber ����
    string idNumber; // ���� idNumber ����

    while (true) {
        cout << "1. ����ԤԼ��Ϣ" << endl;
        cout << "2. ����VIPԤԼ��Ϣ" << endl;
        cout << "3. ��ʾԤԼ��Ϣ" << endl;
        cout << "4. �޸�ԤԼ��Ϣ" << endl;
        cout << "5. ɾ��ԤԼ��Ϣ" << endl;
        cout << "6. ����ԤԼ��Ա��Ϣ" << endl;
        cout << "7. ����Ƶ�ԤԼ��Ϣ" << endl;
        cout << "8. �˳�" << endl;
        cout << "����������ѡ��: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "����������: ";
            cin >> name;
            cout << "�����뷿���: ";
            cin >> roomNumber;
            cout << "������绰����: ";
            cin >> phoneNumber;
            cout << "���������֤��: ";
            cin >> idNumber;
            hotel.addReservation(make_shared<Reservation>(name, roomNumber, phoneNumber, idNumber));
            cout << "�������" << endl;
            break;
        case 2:
            cout << "����������: ";
            cin >> name;
            cout << "�����뷿���: ";
            cin >> roomNumber;
            cout << "������VIP�ȼ�: ";
            cin >> vipLevel;
            cout << "������绰����: ";
            cin >> phoneNumber;
            cout << "���������֤��: ";
            cin >> idNumber;
            hotel.addReservation(make_shared<VIPReservation>(name, roomNumber, vipLevel, phoneNumber, idNumber));
            cout << "�������" << endl;
            break;
        case 3:
            hotel.displayReservations();
            cout << "�������" << endl;
            break;
        case 4:
            cout << "������Ҫ�޸ĵ�ԤԼ������: ";
            cin >> name;
            cout << "�������µķ����: ";
            cin >> roomNumber;
            hotel.modifyReservation(name, roomNumber);
            cout << "�������" << endl;
            break;
        case 5:
            cout << "������Ҫɾ����ԤԼ������: ";
            cin >> name;
            hotel.deleteReservation(name);
            cout << "�������" << endl;
            break;
        case 6:
            cout << "������Ҫ���ҵ�ԤԼ������: ";
            cin >> name;
            if (auto r = hotel.findReservation(name)) {
                r->display();
            } else {
                cout << "δ�ҵ�ԤԼ��Ա��Ϣ" << endl;
            }
            cout << "�������" << endl;
            break;
        case 7:
            hotel.saveToFile("reservations.txt");
            cout << "�������" << endl;
            break;
        case 8:
            return 0;
        default:
            cout << "��Ч��ѡ�����������롣" << endl;
        }
        cout<<"��������ȷ��"<<endl;
        cin.ignore();
        cin.get();
        // ����
        system("cls");
    }

    return 0;
}
