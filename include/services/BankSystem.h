#ifndef BANKSYSTEM_H
#define BANKSYSTEM_H

#include "../data_structures/linkedList.h"
#include "../models/customer.h"
#include "../models/account.h"
<<<<<<< HEAD
=======
#include "../models/transaction.h" 
>>>>>>> 8f16444fe624b04dc7f66b175c12c58b1bdb81bd
#include <string>

class BankSystem {
    private:
        LinkedList<Customer> danhSachKH;
        LinkedList<Account> danhSachTK;
<<<<<<< HEAD
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

=======
        LinkedList<Transaction> danhSachGD; 
    public:
        BankSystem();

        bool kiemTraTrungCCCD(std::string cccd);
        bool kiemTraTrungSTK(std::string soTK);

        static bool kiemTraCCCDHopLe(const std::string& cccd);  
        static bool kiemTraPINHopLe(const std::string& pin);      
        static bool kiemTraSDTHopLe(const std::string& sdt);      
        static bool kiemTraNgayHopLe(const std::string& ngay);
        
        std::string sinhMaKHMoi(); 
        std::string sinhSTKMoi();    
        
        Customer* timKiemKhachHang(std::string maKH);
        Account* timKiemTaiKhoan(std::string soTK);
        
        bool themKhachHang(std::string maKH, std::string hoTen,
                    std::string cccd, std::string sdt);
        bool taoTaiKhoan(std::string soTK, 
                            std::string maKH, 
                            std::string maPIN, long long soDuBanDau);
        bool naptaiKhoanTuFile(std::string soTK, std::string maKH, 
                        std::string maPIN, long long soDu, std::string ngayMo);
        
        LinkedList<Transaction>& getDanhSachGD(); 
        LinkedList<Customer>& getDanhSachKH();
        LinkedList<Account>& getDanhSachTK() { return danhSachTK; }
        
        friend void SaveAllData(BankSystem& bank);
        friend void LoadAllData(BankSystem& bank);
};
#endif
>>>>>>> 8f16444fe624b04dc7f66b175c12c58b1bdb81bd
