#include "../../include/models/transaction.h"
#include <iostream>
#include <string>

//1. Hàm khởi tạo
Transaction::Transaction(){
    this->maGD = "CHUA_CO";
    this->thoiGian = "N/A";
    this->loaiGD = "N/A";
    this->soTien = 0.0;
    this->soTKGui = "N/A";
    this->soTKNhan = "N/A";
}

Transaction::Transaction(std::string maGD, 
                std::string thoiGian, 
                std::string loaiGD,
                double soTien, std::string soTKGui ,
                std::string soTKNhan) {
    this->maGD = maGD;
    this->thoiGian = thoiGian;
    this->loaiGD = loaiGD;
    this->soTien = soTien;
    this->soTKGui = soTKGui;
    this->soTKNhan = soTKNhan;
}

//2. Hàm getters
std::string Transaction::getMaGD() const {
    return this->maGD;
}
std::string Transaction::getThoiGian() const { 
    return this->thoiGian; 
}
std::string Transaction::getLoaiGD() const { 
    return this->loaiGD; 
}
double Transaction::getSoTien() const { 
    return this->soTien; 
}
// header có mà cpp ko thấy nma nhét 2 hàm này vào
// lại thấy lỗi :))
std::string Transaction::getSoTKGui() const {
    return this->soTKGui;
}
std::string Transaction::getSoTKNhan() const {
    return this->soTKNhan;
}


//3. Hàm sinh mã tự động
std::string Transaction::sinhMaGD(int soThuTuMoi) {
    std::string chuoiSo = std::to_string(soThuTuMoi);
    while (chuoiSo.length() < 3) {
        chuoiSo = "0" + chuoiSo;
    }
    return "GD" + chuoiSo;
}
//Hàm in biên lai
void Transaction::xuatThongTin() const {
    std::cout << "[" << this->thoiGian << "] " 
              << "Ma GD: " << this->maGD 
              << " | Loai: " << this->loaiGD 
              << " | So tien: " << this->soTien << " VND";

    //Nếu là gd ckhoan thì in thêm người nhận
    if (this->loaiGD == "CHUYEN_KHOAN" && this->soTKNhan != "N/A") {
        std::cout << " | Tu TK: " << this->soTKGui << " -> Den TK: " << this->soTKNhan;
    } else {
        std::cout << " | TK: " << this->soTKGui;
    }
    
    std::cout << std::endl;
}      