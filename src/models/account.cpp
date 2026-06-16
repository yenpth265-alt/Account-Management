#include "../../include/models/account.h"
#include <iostream>
#include <ctime>
#include <cstdio>

// THÊM: hàm phụ lấy ngày hiện tại dạng dd/mm/yyyy
static std::string LayNgayHienTai() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    char buf[20];
    sprintf(buf, "%02d/%02d/%04d", ltm->tm_mday, 1 + ltm->tm_mon, 1900 + ltm->tm_year);
    return std::string(buf);
}

//1. Triển khai hàm khởi tạo

//Hàm khởi tạo mặc định (mới tạo mảng/ds trống)
Account::Account(){
    this->soTK = "CHUA_CO";
    this->maKH = "CHUA_CO";
    this->maPIN = "0000";
    this->soDu = 0.0;
    this->ngayMo = LayNgayHienTai();
}

//Hàm khởi tạo khi có tham số
Account::Account(std::string soTK, std::string maKH, 
                std::string maPIN, double soDu, std::string ngayMo){
        this->soTK = soTK;
        this->maKH = maKH;
        this->maPIN = maPIN;
        this->soDu = soDu;
        this->ngayMo = ngayMo;
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
std::string Account::getNgayMo() const{
    return this->ngayMo;
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
    if(soTien > 0 && (this->soDu - soTien) >= 50000.0) {
        this->soDu -= soTien;
        return true;
    }
    return false;
}
//Hàm xuất thông tin
void Account::xuatThongTin() const {
    std::cout << "STK: " << this->soTK 
              << " | Ma KH: " << this->maKH 
              << " | So du: " << this->soDu << " VND" 
              <<" | Ngay mo: " << this->ngayMo
              << std::endl;
}