#include "models/account.h"
#include <iostream>

//1. Triển khai hàm khởi tạo

//Hàm khởi tạo mặc định (mới tạo mảng/ds trống)
Account::Account(){
    this->soTK = "CHUA_CO";
    this->maKH = "CHUA_CO";
    this->maPIN = "0000";
    this->soDu = 0.0;
}

//Hàm khởi tạo khi có tham số
Account::Account(std::string soTK, std::string maKH, 
                std::string maPIN, double soDu){
        this->soTK = soTK;
        this->maKH = maKH;
        this->maPIN = maPIN;
        this->soDu = soDu;
}

//2. Lấy dữ liệu

std::string Account::getSoTK() const {
    return this->soTK;
}
std::string Account::getMaKH() const {
    return this->maKH;
}
double Account::getSoDu() const {
    return this->soDu; 
}

//3. Xử lý nghiệp vụ
 
//Hàm đối chiếu mã PIN
bool Account::kiemTraPIN(std::string pinNhapVao) const {
    return (this->maPIN == pinNhapVao);
}

//Hàm đổi mã PIN : xác thực mã PIN cũ trước khi đổi
bool Account::doiPIN(std::string pinCu, std::string pinMoi){
    if (this->kiemTraPIN(pinCu)){
        this->maPIN = pinMoi;
        return true;
    }
    return false;
}
//Hàm nạp tiền : số tiền nạp > 0
bool Account::napTien(double soTien) {
    if (soTien > 0){
        this->soDu += soTien;
        return true;
    }
    return false;
}
//Hàm rút tiền
bool Account::rutTien(double soTien) {
    if(soTien > 0 && soTien <= this->soDu) {
        this->soDu -= soTien;
        return true;
    }
    return false;
}
//Hàm xuất thông tin
void Account::xuatThongTin() const {
    std::cout << "STK: " << this->maTK 
              << " | Ma KH: " << this->maKH 
              << " | So du: " << std::fixed << this->soDu << " VND" 
              << std::endl;
}