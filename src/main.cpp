#include <iostream>
#include <string>

#include "../include/models/customer.h"
#include "../include/models/account.h"
#include "../include/models/transaction.h"
#include "../include/data_structures/linkedList.h"

using namespace std;

int main() {
    cout << "========== 1. TEST MODULE KHACH HANG ==========" << endl;
    // Tạo thử 2 khách hàng
    Customer kh1("KH001", "PTHY", "0123456789", "0987654321");
    Customer kh2("KH002", "Nguyen Van A", "0987654321", "0911222333");
    
    kh1.xuatThongTin();
    kh2.xuatThongTin();

    cout << "\n========== 2. TEST MODULE TAI KHOAN ==========" << endl;
    // Tạo tài khoản cho Duyên (Mã PIN: 1234, Số dư đầu kỳ: 500k)
    Account tk1("1001", "KH001", "1234", 500000);
    tk1.xuatThongTin();
    
    cout << "-> Dang nap 200.000 VND vao tai khoan..." << endl;
    if (tk1.napTien(200000) == true) {
        cout << "   [OK] Nap thanh cong!" << endl;
    }
    
    cout << "-> Dang rut 100.000 VND..." << endl;
    if (tk1.rutTien(100000) == true) {
        cout << "   [OK] Rut thanh cong!" << endl;
    }
    
    cout << "-> Kiem tra ma PIN (Nhap thu 1234): ";
    if (tk1.kiemTraPIN("1234") == true) {
        cout << "Dung! Cho phep giao dich." << endl;
    }
    
    cout << "-> So du sau cung: ";
    tk1.xuatThongTin();

    cout << "\n========== 3. TEST MODULE GIAO DICH ==========" << endl;
    // Ghi nhận lại cái biên lai rút tiền 100k lúc nãy
    Transaction gd1("GD001", "10/06/2026 09:45", "RUT", 100000, "1001", "N/A");
    gd1.xuatThongTin();

    cout << "\n========== 4. TEST MODULE LINKEDLIST ==========" << endl;
    // Khởi tạo một danh sách liên kết chỉ chuyên chứa Tài khoản
    LinkedList<Account> danhSachTK;
    
    // Ném tài khoản tk1 vào danh sách
    danhSachTK.addTail(tk1);
    
    // Tạo thêm một tài khoản mới và ném luôn vào danh sách
    Account tk2("1002", "KH002", "0000", 1500000);
    danhSachTK.addTail(tk2);

    cout << "Tong so tai khoan dang quan ly: " << danhSachTK.getSize() << endl;
    cout << "Danh sach chi tiet cac tai khoan trong he thong:" << endl;
    
    //duyệt Danh sách liên kết để in ra màn hình
    Node<Account>* current = danhSachTK.getHead();
    while (current != nullptr) {
        cout << " - ";
        current->data.xuatThongTin(); // Gọi hàm in của từng class Account bên trong Node
        current = current->next;      // Nhảy sang Node tiếp theo
    }

    cout << "\n========== TEST HOAN TAT ==========" << endl;
    return 0;
}