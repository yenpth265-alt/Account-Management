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
        bool kiemTraTrungSTK(std::string soTK);
        Customer* timKiemKhachHang(std::string maKH);
        Account* timKiemTaiKhoan(std::string soTK);
        
        bool themKhachHang(std::string maKH, std::string hoTen,
                    std::string cccd, std::string sdt);
        bool taoTaiKhoan(std::string maTK, 
                            std::string maKH, 
                            std::string maPIN, double soDuBanDau);
        bool naptaiKhoanTuFile(std::string soTK, std::string maKH, 
                        std::string maPIN, double soDu, std::string ngayMo);
        LinkedList<Transaction>& getDanhSachGD(); //mới
        LinkedList<Customer>& getDanhSachKH() { return danhSachKH; }
        LinkedList<Account>& getDanhSachTK() { return danhSachTK; }
        friend void SaveAllData(BankSystem& bank);
        friend void LoadAllData(BankSystem& bank);
};
#endif