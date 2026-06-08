#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>

class Account {
    private:
        std::string soTK;
        std::string maKH;
        std::string maPIN;
        double soDu;
    public:
        //hàm khởi tạo
        Account();
        Account(std::string soTK, std::string maKH, 
                std::string maPIN, double soDu);
        
        //lấy dữ liệu
        std::string getSoTK() const;
        std::string getMaKH() const;
        double getSoDu() const;
        
        //cập nhật dữ liệu
        bool kiemTraPIN(std::string pinNhapVao) const;
        bool doiPIN(std::string pinCu, 
                    std::string pinMoi);
        bool napTien(double soTien);
        bool rutTien(double soTien);
        void xuatThongTin() const;
};

#endif 