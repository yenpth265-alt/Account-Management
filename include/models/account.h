#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>

class Account {
    private:
        std::string soTK;
        std::string maKH;
        std::string maPIN;
        long long soDu;
        std::string ngayMo;
    public:
        //hàm khởi tạo
        Account();
        Account(std::string soTK, std::string maKH, 
                std::string maPIN, long long soDu, std::string ngayMo);
        
        //lấy dữ liệu
        std::string getSoTK() const;
        std::string getMaKH() const;
        long long getSoDu() const;
        std::string getNgayMo() const;
        
        //cập nhật dữ liệu
        bool kiemTraPIN(std::string pinNhapVao) const;
        bool doiPIN(std::string pinCu, 
                    std::string pinMoi);
        bool napTien(long long soTien);
        bool rutTien(long long soTien);
        void xuatThongTin() const;

        // Cho phép hàm lưu file truy cập PIN để ghi ra đĩa (không public ra ngoài)
        friend void SaveAllData(class BankSystem& bank);
};

#endif 