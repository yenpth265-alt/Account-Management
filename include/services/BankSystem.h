#ifndef BANKSYSTEM_H
#define BANKSYSTEM_H

#include "../data_structures/linkedList.h"
#include "../models/customer.h"
#include "../models/account.h"
#include <string>

class BankSystem {
    private:
        LinkedList<Customer> danhSachKH;
        LinkedList<Account> danhSachTK;
    public:
        BankSystem();
        bool kiemTraTrungSTK(std::string soTK);
        Customer* timKiemKhachHang(std::string maKH);
        Account* timKiemTaiKhoan(std::string soTK);
        bool themKH(std::string maKH, std::string hoTen,
                    std::string cccd, std::string sdt);
        bool taoTaiKhoan(std::string maTK, 
                            std::string maKH, 
                            std::string maPIN, double soDuBanDau);
};
#endif

#ifndef BANKSYSTEM_H
#define BANKSYSTEM_H

#include "../data_structures/linkedList.h"
#include "../models/customer.h"
#include "../models/account.h"
#include <string>

class BankSystem {
    private:
        LinkedList<Customer> danhSachKH;
        LinkedList<Account> danhSachTK;
    public:
        BankSystem();
        bool kiemTraTrungSTK(std::string soTK);
        Customer* timKiemKhachHang(std::string maKH);
        Account* timKiemTaiKhoan(std::string soTK);
        bool themKH(std::string maKH, std::string hoTen,
                    std::string cccd, std::string sdt);
        bool taoTaiKhoan(std::string maTK, 
                            std::string maKH, 
                            std::string maPIN, double soDuBanDau);
};
#endif

