#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>

class Account {
    private:
        std::string soTK;
        std::string maKH;
        std::string maPIN;
        double soDu;
        std::string ngayMo;
    public:
        //hàm khởi tạo
        Account();
        Account(std::string soTK, std::string maKH, 
                std::string maPIN, double soDu, std::string ngayMo);
        
        //lấy dữ liệu
        std::string getSoTK() const;
        std::string getMaKH() const;
        std::string getMaPIN() const { return maPIN; }
        double getSoDu() const;
        std::string getNgayMo() const;
        
        //cập nhật dữ liệu
        bool kiemTraPIN(std::string pinNhapVao) const;
        bool doiPIN(std::string pinCu, 
                    std::string pinMoi);
        bool napTien(double soTien);
        bool rutTien(double soTien);
        void xuatThongTin() const;
};

#endif 