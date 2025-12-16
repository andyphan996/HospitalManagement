#include <bits/stdc++.h>

using namespace std;

struct Hospital {
    string name;
    string address;
    int price;
};

// Hàm chuyển từ viết hoa thành viết thường
string trans(string s) {
    transform(s.begin(), s.end(), s.begin(), [](unsigned char c){
        return tolower(c);
    });
    return s;
}

// Hàm xoá khoảng trắng thừa
string del_backspace(const string& s) {
    size_t first = s.find_first_not_of(' ');
    if (string::npos == first) return s;
    size_t last = s.find_last_not_of(' ');
    return s.substr(first, (last - first + 1));
}

// Hàm nhập dữ liệu từ file hospital.txt
vector<Hospital> Nhap(string file_name) {
    vector<Hospital> ls;
    ifstream file(file_name);
    string line;
    if (!file.is_open()) return ls;

    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string name, addr, str_price;

        getline(ss, name, ',');
        getline(ss, addr, ',');
        getline(ss, str_price, ',');

        try {
            ls.push_back({name, addr, stoi(str_price)});
        } catch (...) {
            continue;
        }
    }
    file.close();
    return ls;
}
// Xuất file JSON hỗ trợ website
void out_json(vector<Hospital> list, string filename) {
    ofstream file(filename);
    file << "[\n";
    for (int i = 0; i < list.size(); i++) {
        file << "  {\n";
        file << "    \"name\": \"" << list[i].name << "\",\n";
        file << "    \"city\": \"" << list[i].address << "\",\n";
        file << "    \"price\": " << list[i].price << "\n";
        file << "  }" << (i == list.size() - 1 ? "" : ",") << "\n";
    }
    file << "]";
    file.close();
}


// --- Các hàm Sort của bạn ---
void sort_by_name_inc(vector<Hospital> &a) {
    sort(a.begin(), a.end(), [](Hospital a, Hospital b) {
         return a.name < b.name;
    });
}
void sort_by_name_dec(vector<Hospital> &a) {
    sort(a.begin(), a.end(), [](Hospital a, Hospital b) {
         return a.name > b.name;
    });
}
void sort_by_price_inc(vector<Hospital> &a) {
    sort(a.begin(), a.end(), [](Hospital a, Hospital b) {
         return a.price < b.price;
    });
}
void sort_by_price_dec(vector<Hospital> &a) {
    sort(a.begin(), a.end(), [](Hospital a, Hospital b) {
         return a.price > b.price;
    });
}

// Tìm kiếm theo city
void print_by_city(const vector<Hospital> &a, string city) {
    string s = trans(del_backspace(city));
    ofstream fout("city_result.txt");
    cout << "\nResult for city: " << city << endl;
    vector<Hospital> res;
    for (auto x : a) {
        string temp = trans(del_backspace(x.address));
        if (temp.find(s) != string::npos) {
            fout << x.name << " | " << x.price << endl;
            cout << x.name << " (" << x.price << " VND) - " << x.address << endl;
            res.push_back(x);
        }
    }
    if (res.empty()){
        cout << "Hospital not found" << endl;
    }
    else {
        out_json(res,"out.json");
    }
    fout.close();

}

// In ra console
void xuat_console(vector<Hospital> &a) {
    for (auto i : a) {
        cout << left << setw(30) << i.name << setw(20) << i.address << i.price << endl;
    }
}


int main() {
    vector<Hospital> ls = Nhap("hospital.txt");
    if (ls.empty()) {
        cout << "Data empty or hospital.txt not found!" << endl;
        return 0;
    }

    bool flag = true;
    while (flag) {
        int option;
        cout << "1. Show all hospitals" << endl;
        cout << "2. Sort by name (increase)" << endl;
        cout << "3. Sort by name (decrease)" << endl;
        cout << "4. Sort by price (increase)" << endl;
        cout << "5. Sort by price (decrease)" << endl;
        cout << "6. Search hospitals by city" << endl;
        cout << "7. EXIT" << endl;
        cout << "Enter your choice: ";
        cin >> option;

        switch (option) {
            case 1:
                xuat_console(ls);
                out_json(ls, "out.json");
                break;
            case 2:
                sort_by_name_inc(ls);
                xuat_console(ls);
                out_json(ls, "out.json");
                break;
            case 3:
                sort_by_name_dec(ls);
                xuat_console(ls);
                out_json(ls, "out.json");
                break;
            case 4:
                sort_by_price_inc(ls);
                xuat_console(ls);
                out_json(ls, "out.json");
                break;
            case 5:
                sort_by_price_dec(ls);
                xuat_console(ls);
                out_json(ls, "out.json");
                break;
            case 6: {
                string city;
                cout << "Enter city name: ";
                cin.ignore();
                getline(cin, city);
                print_by_city(ls, city);
                break;
            }
            case 7:
                flag = false;
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid option, please try again!" << endl;
                break;
        }
    }
    return 0;
}
