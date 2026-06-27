#ifndef TRANSACTION_H
#define TRANSACTION_H

#include<string>

class Transaction {
    private:
        std::string maGD;
        std::string thoiGian;
        std::string loaiGD;
        long long soTien;
        std::string soTKGui;
        std::string soTKNhan;
    
    public:
    //Hàm khởi tạo
    Transaction();
    Transaction(std::string maGD, std::string thoiGian,
                std::string loaiGD, long long soTien, 
                std::string soTKGui, std::string soTKNhan);
    
    //Hàm getters
    std::string getMaGD() const;
    std::string getThoiGian() const;
    std::string getLoaiGD() const;
    long long getSoTien() const;
    std::string getSoTKNhan() const;
    std::string getSoTKGui() const;

    //Hàm sinh mã gdich
    static std::string sinhMaGD(int soThuTuMoi);
    void xuatThongTin() const;
};

#endif