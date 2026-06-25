#include "test_runner.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

// Hàm phụ: đọc file, xem có chuỗi cần tìm không
static bool FileChuaChuoi(const string& duongDan, const string& chuoiCanTim) {
    ifstream f(duongDan);
    if (!f.is_open()) return false;
    string line;
    while (getline(f, line)) {
        if (line.find(chuoiCanTim) != string::npos) return true;
    }
    return false;
}

void test_HopXam(){
    BankSystem bank;

    // TC 1
    bank.themKhachHang("KH001", "Nguyen Van A", "123456789012", "0918273645");
    bank.taoTaiKhoan("100031461", "KH001", "1234", 700000);

    {
        ofstream fKH("data_test/customers.txt");
        fKH << "maKH|hoTen|cccd|sdt\n";
        Node<Customer>* c = bank.getDanhSachKH().getHead();
        while (c != NULL) {
            fKH << c->data.getMaKH() << "|" << c->data.getHoTen() << "|"
                << c->data.getCCCD() << "|" << c->data.getSDT() << "\n";
            c = c->next;
        }
        fKH.close();

        ofstream fTK("data_test/accounts.txt");
        fTK << "soTK|maKH|maPIN|soDu|ngayMo\n";
        Node<Account>* t = bank.getDanhSachTK().getHead();
        while (t != NULL) {
            fTK << t->data.getSoTK() << "|" << t->data.getMaKH() << "|"
                << "1234" << "|" << t->data.getSoDu() << "|" << t->data.getNgayMo() << "\n";
            t = t->next;
        }
        fTK.close();
    }

    kiemTra("TC1 - File customers.txt co chua KH001", 
            FileChuaChuoi("data_test/customers.txt", "KH001|Nguyen Van A"), true);
    kiemTra("TC1 - File accounts.txt co chua so tai khoan moi tao", 
            FileChuaChuoi("data_test/accounts.txt", "100031461|KH001"), true);

    // TC 2
    TransactionLogic trans(&bank);
    bank.themKhachHang("KH002", "Nguyen Thi B", "987654321098", "0938294756");
    bank.taoTaiKhoan("100000215", "KH002", "9090", 700000);

    trans.NapTien("100000215", 300000);              // 700,000 -> 1,000,000
    trans.RutTien("100000215", "9090", 200000);       // 1,000,000 -> 800,000
    trans.ChuyenKhoan("100000215", "9090", "100031461", 150000); // -> 650,000

    long long soDuThucTeRAM = bank.timKiemTaiKhoan("100000215")->getSoDu();
    kiemTraGiaTri("TC2 - So du tren RAM sau chuoi giao dich", soDuThucTeRAM, 650000);

    // Ghi lại xuống file và kiểm tra đồng bộ
    {
        ofstream fTK("data_test/accounts.txt");
        fTK << "soTK|maKH|maPIN|soDu|ngayMo\n";
        Node<Account>* t = bank.getDanhSachTK().getHead();
        while (t != NULL) {
            fTK << t->data.getSoTK() << "|" << t->data.getMaKH() << "|"
                << "----" << "|" << t->data.getSoDu() << "|" << t->data.getNgayMo() << "\n";
            t = t->next;
        }
        fTK.close();
    }
    kiemTra("TC2 - File accounts.txt khop voi so du RAM (650,000)",
            FileChuaChuoi("data_test/accounts.txt", "100000215|KH002|----|650000"), true);

    // TC 3
    Customer* kh = bank.timKiemKhachHang("KH001");
    kh->setSDT("0918273645"); 
    kh->setSDT("0918273646"); 

    {
        ofstream fKH("data_test/customers.txt");
        fKH << "maKH|hoTen|cccd|sdt\n";
        Node<Customer>* c = bank.getDanhSachKH().getHead();
        while (c != NULL) {
            fKH << c->data.getMaKH() << "|" << c->data.getHoTen() << "|"
                << c->data.getCCCD() << "|" << c->data.getSDT() << "\n";
            c = c->next;
        }
        fKH.close();
    }
    kiemTra("TC3 - File customers.txt cap nhat SDT moi cho KH001",
            FileChuaChuoi("data_test/customers.txt", "KH001|Nguyen Van A|123456789012|0918273646"), true);
}