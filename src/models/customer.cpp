#include "../../include/models/customer.h"
#include <iostream>

//triển khai hàm khởi tạo
Customer::Customer(){
   this->maKH = "CHUA_CO";
   this->hoTen = "Chua cap nhat";
   this->cccd = "N/A";
   this->sdt = "N/A"; 
}
Customer::Customer(std::string maKH, std::string hoTen, std::string cccd, std::string sdt){
    this->maKH = maKH;
    this->hoTen = hoTen;
    this->cccd = cccd;
    this->sdt = sdt;
}

//lấy dữ liệu
std::string Customer::getMaKH() const{
    return this->maKH;
}
std::string Customer::getHoTen() const{
    return this->hoTen;
}
std::string Customer::getCCCD() const{
    return this->cccd;
}
std::string Customer::getSDT() const{
    return this->sdt;
}

//sửa dữ liệu
void Customer::setHoTen(std::string hoTenMoi){
    this->hoTen = hoTenMoi;
}

void Customer::setCCCD(std::string cccdMoi){
    this->cccd = cccdMoi;
}
void Customer::setSDT(std::string sdtMoi){
    this->sdt = sdtMoi;
}

//lấy thông tin
void Customer::xuatThongTin() const{
    std::cout << "Ma KH: " << this->maKH
              << " | Ho ten: " << this->hoTen
              << " | CCCD: " << this->cccd
              << " | SDT: " << this->sdt << std::endl;
}

//sinh mã KH
std::string Customer::sinhMaKH(int soThuTuMoi){
    std::string chuoiSo = std::to_string(soThuTuMoi);

    while (chuoiSo.length() < 3){
        chuoiSo = "0" + chuoiSo;
    }

    return "KH" + chuoiSo;
}

