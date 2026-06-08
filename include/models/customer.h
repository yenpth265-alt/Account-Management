#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>

class Customer {
    private:
        std::string maKH;
        std::string hoTen;
        std::string cccd;
        std::string sdt;
    public:
        //khởi tạo
        Customer();
        Customer(std::string maKH, std::string hoTen,
                std::string cccd, std::string sdt );

        //lấy dữ liệu ra đọc
        std::string getMaKH() const;
        std::string getHoTen() const;
        std::string getCCCD() const;
        std::string getSDT() const;
        
        //sửa, cập nhật dữ liệu
        void setHoTen(std::string hoTenMoi);
        void setCCCD(std::string cccdMoi);
        void setSDT(std::string sdtMoi);
    
        //xuatThongTin
        void xuatThongTin() const;

        //sinh maKh mới
        static std::string sinhMaKH(int soThuTuMoi);
};

#endif