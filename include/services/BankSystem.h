#ifndef BANKSYSTEM_H
#define BANKSYSTEM_H

#include "../data_structures/linkedList.h"
#include "../models/customer.h"
#include "../models/account.h"
#include "../models/transaction.h" // mới thêm nè
#include <string>

class BankSystem {
    private:
        LinkedList<Customer> danhSachKH;
        LinkedList<Account> danhSachTK;
        LinkedList<Transaction> danhSachGD; // mới thêm nè
    public:
        BankSystem();

        bool kiemTraTrungCCCD(std::string cccd);
        bool kiemTraTrungSTK(std::string soTK);

        static bool kiemTraCCCDHopLe(const std::string& cccd);   // Phải đúng 12 chữ số
        static bool kiemTraPINHopLe(const std::string& pin);      // Phải đúng 4 chữ số
        static bool kiemTraSDTHopLe(const std::string& sdt);      // Phải 10 chữ số, bắt đầu 0
        static bool kiemTraNgayHopLe(const std::string& ngay);
        
        std::string sinhMaKHMoi();   // Sinh mã KH tự động
        std::string sinhSTKMoi();    // Sinh STK ngẫu nhiên, không trùng
        
        Customer* timKiemKhachHang(std::string maKH);
        Account* timKiemTaiKhoan(std::string soTK);
        
        bool themKhachHang(std::string maKH, std::string hoTen,
                    std::string cccd, std::string sdt);
        bool taoTaiKhoan(std::string soTK, 
                            std::string maKH, 
                            std::string maPIN, long long soDuBanDau);
        bool naptaiKhoanTuFile(std::string soTK, std::string maKH, 
                        std::string maPIN, long long soDu, std::string ngayMo);
        
        LinkedList<Transaction>& getDanhSachGD(); //mới
        LinkedList<Customer>& getDanhSachKH();
        LinkedList<Account>& getDanhSachTK() { return danhSachTK; }
        
        friend void SaveAllData(BankSystem& bank);
        friend void LoadAllData(BankSystem& bank);
};
#endif