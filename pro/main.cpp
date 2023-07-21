#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <memory>
#include <algorithm>

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
    friend ostream& operator<<(ostream& os, const Reservation& r) {
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
    friend ostream& operator<<(ostream& os, const VIPReservation& r) {
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
    //�ж����ӵ�ԤԼ��Ϣ�Ƿ�Ϸ�
    bool check(shared_ptr<Reservation> r) {
        for (const auto& res : reservations) {
            if (res->name == r->name)
            {
                cout << "�����ظ������������롣" << endl;
                return true;
            }
            if (res->roomNumber == r->roomNumber)
            {
                cout << "������ظ������������롣" << endl;
                return true;
            }
            if (res->phoneNumber == r->phoneNumber)
            {
                cout << "�绰���ظ������������롣" << endl;
                return true;
            }
            if (res->idNumber == r->idNumber) {
                cout << "���֤���ظ������������롣" << endl;
                return true;
            }
        }
        return false;
    }
    // ����ԤԼ��Ϣ
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
            cout << "��Ч��ѡ�����������롣" << endl;
        }
    }


    // ��ʾԤԼ��Ϣ
    void displayReservations() {
        if (reservations.empty()) {
            cout << "û��ԤԼ��Ϣ" << endl;
        }
        else {
            for (const auto& r : reservations) {
                r->display();
            }
        }
    }

    // �޸�ԤԼ��Ϣ
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

    // ɾ��ԤԼ��Ϣ
    void deleteReservation(const string& name) {
        int flag = 1;
        for (auto it = reservations.begin(); it != reservations.end(); ++it) {
            if ((*it)->name == name) {
                reservations.erase(it);
                flag = 0;
                break;
            }
        }
        if (flag)cout << "δ�ҵ�����" << "\n";
    }

    // ����ԤԼ��Ա��Ϣ
    shared_ptr<Reservation> findReservation(const string& name = "", const string& phoneNumber = "", const string& idNumber = "") {
        for (const auto& r : reservations) {
            if (r->name == name || r->phoneNumber == phoneNumber || r->idNumber == idNumber) {
                return r;
            }
        }
        return nullptr;
    }

    // ����Ƶ�ԤԼ��Ϣ���ļ�
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

    // ���ļ����ؾƵ�ԤԼ��Ϣ
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
    string phoneNumber; // ���� phoneNumber ����
    string idNumber; // ���� idNumber ����

    while (true) {
        cout << "******************* �Ƶ�ԤԼϵͳ *******************" << endl;
        cout << "* 1. ����ԤԼ��Ϣ" << endl;
        cout << "* 2. ����VIPԤԼ��Ϣ" << endl;
        cout << "* 3. ��ʾԤԼ��Ϣ" << endl;
        cout << "* 4. �޸�ԤԼ��Ϣ" << endl;
        cout << "* 5. ɾ��ԤԼ��Ϣ" << endl;
        cout << "* 6. ����ԤԼ��Ա��Ϣ" << endl;
        cout << "* 7. ����Ƶ�ԤԼ��Ϣ" << endl;
        cout << "* 8. ����ԤԼ��Ϣ" << endl;
        cout << "* 9. �˳�" << endl;
        cout << "*****************************************************" << endl;
        cout << "����������ѡ��: ";
        cin >> choice;

        switch (choice) {
        case 1:
            do {
                cout << "����������: ";
                cin >> name;
                cout << "�����뷿���: ";
                cin >> roomNumber;
                cout << "������绰����: ";
                cin >> phoneNumber;
                cout << "���������֤��: ";
                cin >> idNumber;
            } while (hotel.check(make_shared<Reservation>(name, roomNumber, phoneNumber, idNumber)));
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
            do {
                cout << "�������µķ����: ";
                cin >> roomNumber;
                cout << "�������µĵ绰����: ";
                cin >> phoneNumber;
                cout << "�������µ����֤��: ";
                cin >> idNumber;
            } while (hotel.check(make_shared<VIPReservation>(" ", roomNumber, vipLevel, phoneNumber, idNumber)));
            hotel.modifyReservation(name, roomNumber, phoneNumber, idNumber);
            cout << "�������" << endl;
            break;
        case 5:
            do {
                cout << "������Ҫɾ����ԤԼ������: ";
                cin >> name;
                auto p = hotel.findReservation(name);
                if (p == nullptr)cout << "δ�ҵ����ˣ�����������" << "\n";
            } while (hotel.findReservation(name) == nullptr);
            hotel.deleteReservation(name);
            cout << "�������" << endl;
            break;
        case 6:
            cout << "������Ҫ���ҵ�ԤԼ������: ";
            cin >> name;
            if (auto r = hotel.findReservation(name)) {
                r->display();
            }
            else {
                cout << "δ�ҵ�ԤԼ��Ա��Ϣ" << endl;
            }
            cout << "�������" << endl;
            break;
        case 7:
            hotel.saveToFile("reservations.txt");
            cout << "�������" << endl;
            break;
        case 8:
            cout << "------------------- ����ѡ�� -------------------" << endl;
            cout << "- 1. ������������" << endl;
            cout << "- 2. ���ڷ��������" << endl;
            cout << "- 3. ���ڵ绰��������" << endl;
            cout << "- 4. �������֤������" << endl;
            cout << "----------------------------------------------" << endl;
            cout << "����������ѡ��: ";
            cin >> choice;
            hotel.sortReservations(choice);
            hotel.displayReservations();
            cout << "�������" << endl;
            break;
        case 9:
            return 0;
        default:
            cout << "��Ч��ѡ�����������롣" << endl;
        }
        cout << "��������ȷ��" << endl;
        cin.ignore();
        cin.get();
        // ����
        system("cls");
    }

    return 0;
}
