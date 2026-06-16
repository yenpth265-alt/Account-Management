#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <random>
#include <iomanip>
#include <sstream>

using namespace std;

// Hàm hỗ trợ format chuỗi số (ví dụ: 1 -> "001")
string formatID(string prefix, int id, int width = 3) {
    ostringstream oss;
    oss << prefix << setfill('0') << setw(width) << id;
    return oss.str();
}

int main() {
    // Cấu hình số lượng dữ liệu muốn sinh
    int soLuongKH = 20;    // 20 khách hàng
    int soLuongTK = 30;    // 30 tài khoản (một số KH có nhiều tài khoản)
    int soLuongGD = 100;   // 100 giao dịch

    // Khởi tạo engine sinh số ngẫu nhiên
    random_device rd;
    mt19937 gen(rd());

    // --- 1. SINH DỮ LIỆU KHÁCH HÀNG (customers.txt) ---
    vector<string> listMaKH;
    vector<string> ho = {"Nguyen", "Tran", "Le", "Pham", "Hoang", "Vu", "Vo", "Dang", "Bui", "Do"};
    vector<string> dem = {"Van", "Thi", "Huu", "Ngoc", "Xuan", "Quang", "Minh", "Thu", "Tuan", "Hoai"};
    vector<string> ten = {"Anh", "Binh", "Chau", "Dung", "Em", "Phong", "Giang", "Hai", "Linh", "Kien"};
    
    uniform_int_distribution<> dist_ho(0, ho.size() - 1);
    uniform_int_distribution<> dist_dem(0, dem.size() - 1);
    uniform_int_distribution<> dist_ten(0, ten.size() - 1);
    uniform_int_distribution<long long> dist_cccd(100000000000LL, 999999999999LL);
    uniform_int_distribution<long long> dist_sdt(900000000, 999999999);

    ofstream fileKH("data/customers.txt");
    
    if (!fileKH.is_open()) {
        cerr << "[LOI] Khong the mo file data/customers.txt (Kiem tra xem thu muc 'data' co ton tai khong!)" << endl;
        return 1;
    }

    fileKH << "MaKH|HoTen|CCCD|SDT\n";

    for (int i = 1; i <= soLuongKH; ++i) {
        string maKH = formatID("KH", i);
        listMaKH.push_back(maKH);
        string hoTen = ho[dist_ho(gen)] + " " + dem[dist_dem(gen)] + " " + ten[dist_ten(gen)];
        string cccd = "0" + to_string(dist_cccd(gen)); // Thêm số 0 ở đầu cho chuẩn CCCD/SDT
        string sdt = "0" + to_string(dist_sdt(gen));
        
        fileKH << maKH << "|" << hoTen << "|" << cccd << "|" << sdt << "\n";
    }
    fileKH.close();
    cout << "-> Da sinh thanh cong " << soLuongKH << " khach hang vao data/customers.txt" << endl;


    // --- 2. SINH DỮ LIỆU TÀI KHOẢN (accounts.txt) ---
    vector<string> listSoTK;
    uniform_int_distribution<> dist_kh(0, listMaKH.size() - 1);
    uniform_int_distribution<long long> dist_stk(100000000, 999999999); // Số tài khoản 9 số
    uniform_int_distribution<> dist_pin(1000, 9999); // Mã PIN 4 số
    uniform_real_distribution<> dist_sodu(50000.0, 50000000.0); // Số dư từ 50k đến 50tr
    uniform_int_distribution<> dist_ngay(1, 28);
    uniform_int_distribution<> dist_thang(1, 12);
    uniform_int_distribution<> dist_nam(2020, 2025);

    ofstream fileTK("data/accounts.txt");
    if (!fileTK.is_open()) {
        cerr << "[LOI] Khong the mo file data/accounts.txt" << endl;
        return 1;
    }

    fileTK << "SoTK|MaKH|MaPIN|SoDu|NgayMo\n";
    
    fileTK << fixed;

    for (int i = 1; i <= soLuongTK; ++i) {
        string soTK = to_string(dist_stk(gen));
        listSoTK.push_back(soTK);
        string maKH = listMaKH[dist_kh(gen)];
        string maPIN = to_string(dist_pin(gen));
        double soDu = dist_sodu(gen);
        
        // Format ngày tháng: dd/mm/yyyy
        ostringstream ngayMo;
        ngayMo << setfill('0') << setw(2) << dist_ngay(gen) << "/" 
               << setw(2) << dist_thang(gen) << "/" << dist_nam(gen);

        fileTK << soTK << "|" << maKH << "|" << maPIN << "|" << soDu << "|" << ngayMo.str() << "\n";
    }
    fileTK.close();
    cout << "-> Da sinh thanh cong " << soLuongTK << " tai khoan vao data/accounts.txt" << endl;


    // --- 3. SINH DỮ LIỆU GIAO DỊCH (transactions.txt) ---
    vector<string> loaiGiaoDich = {"NAP", "RUT", "CHUYEN_KHOAN"};
    uniform_int_distribution<> dist_loai(0, 2);
    uniform_int_distribution<> dist_tk(0, listSoTK.size() - 1);
    uniform_int_distribution<> dist_gio(0, 23);
    uniform_int_distribution<> dist_phut(0, 59);
    uniform_real_distribution<> dist_sotien_gd(50000.0, 5000000.0); // Giao dịch từ 50k đến 5tr

    ofstream fileGD("data/transactions.txt");
    if (!fileGD.is_open()) {
        cerr << "[LOI] Khong the mo file data/transactions.txt" << endl;
        return 1;
    }

    fileGD << "MaGD|ThoiGian|LoaiGD|SoTien|SoTKGui|SoTKNhan\n";
    
    fileGD << fixed;

    for (int i = 1; i <= soLuongGD; ++i) {
        string maGD = formatID("GD", i);
        
        // Format thời gian: dd/mm/yyyy hh:mm
        ostringstream thoiGian;
        thoiGian << setfill('0') << setw(2) << dist_ngay(gen) << "/" 
                 << setw(2) << dist_thang(gen) << "/" << dist_nam(gen) << " "
                 << setw(2) << dist_gio(gen) << ":" << setw(2) << dist_phut(gen);
                 
        string loaiGD = loaiGiaoDich[dist_loai(gen)];
        double soTien = dist_sotien_gd(gen);
        
        string soTKGui = listSoTK[dist_tk(gen)];
        string soTKNhan = "N/A";
        
        // Nếu là chuyển khoản thì bốc ngẫu nhiên thêm một tài khoản nhận (khác tài khoản gửi)
        if (loaiGD == "CHUYEN_KHOAN") {
            do {
                soTKNhan = listSoTK[dist_tk(gen)];
            } while (soTKNhan == soTKGui);
        }

        fileGD << maGD << "|" << thoiGian.str() << "|" << loaiGD << "|" 
               << soTien << "|" << soTKGui << "|" << soTKNhan << "\n";
    }
    fileGD.close();
    cout << "-> Da sinh thanh cong " << soLuongGD << " giao dich vao data/transactions.txt" << endl;

    cout << "\n[HOAN TAT] Tat ca du lieu da duoc ghi vao thu muc 'data/'" << endl;
    return 0;
}