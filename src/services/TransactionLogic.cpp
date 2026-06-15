#include "../../include/services/TransactionLogic.h"
#include <iostream>
#include <ctime>
#include <cstdio>

BankSystem* TransactionLogic::getBankSystem() {
    return this->bankSystem;
}

TransactionLogic::TransactionLogic(BankSystem* bank){
    this->bankSystem = bank;
    this->soGDDaTao = 0;
}

void TransactionLogic::SetSoGDDaTao(int soGD){
    this->soGDDaTao = soGD;
}
// HÀM PHỤ: GHI NHẬN GIAO DỊCH
void TransactionLogic::GhiNhanGiaoDich(std::string loaiGD, double soTien, std::string soTKGui, std::string soTKNhan){
    this->soGDDaTao++;

    std::string maGD = Transaction::sinhMaGD(this->soGDDaTao);

    time_t now = time(0);
    tm* ltm = localtime(&now);
    char buf[20];
    sprintf(buf, "%02d/%02d/%04d %02d:%02d", 
            ltm->tm_mday, 1 + ltm->tm_mon, 1900 + ltm->tm_year, 
            ltm->tm_hour, ltm->tm_min);
    std::string thoiGian = buf;

    Transaction gd(maGD, thoiGian, loaiGD, soTien, soTKGui, soTKNhan);
    this->bankSystem->getDanhSachGD().addTail(gd);
}

// NẠP TIỀN
bool TransactionLogic::NapTien(std::string soTK, double soTien){
    if (soTien <= 0){
        std::cout << "[LOI] So tien nap phai lon hon 0!" << std::endl;
        return false;
    }

    Account* tk = this->bankSystem->timKiemTaiKhoan(soTK);
    if (tk == NULL){
        std::cout << "[LOI] Khong tim thay tai khoan" << soTK << "!" << std::endl;
        return false;
    }
    if (tk->napTien(soTien) == false){
        std::cout << "[LOI] Nap tien khong thanh cong!" << std::endl;
        return false;
    }
    // ghi nhận giao dịch: nạp tiền không có người nhận, để "N/A"
    GhiNhanGiaoDich("NAP", soTien, soTK, "N/A");
    std::cout << "[THANH CONG] Da nap " << std::fixed << soTien << " VND vao tai khoan " << soTK << std::endl;
    return true;
}

// RÚT TIỀN
bool TransactionLogic::RutTien(std::string soTK, std::string maPIN, double soTien){
    if (soTien <=0){
        std::cout <<"[LOI] So tien rut phai lon hon 0!" << std::endl;
        return false;
    }
    Account* tk = this->bankSystem->timKiemTaiKhoan(soTK);
    if (tk == NULL){
        std::cout << "[LOI] Khong tim thay tai khoan " << soTK << "!" << std::endl;
        return false;
    }

    if (tk->kiemTraPIN(maPIN) ==false){
        std::cout << "[LOI] Ma PIN khong dung!" << std::endl;
        return false;
    }
    if (tk->rutTien(soTien) == false){
        std::cout << "[LOI] So du khong du de rut!" <<std::endl;
        return false;
    }
    // ghi nhận giao dịch: rút tiền không có tk nhận -> để "N/A"
    GhiNhanGiaoDich("RUT", soTien, soTK, "N/A");
    std::cout << "[THANH CONG] Da rut" << std::fixed << soTien 
              << " VND tu tai khoan " << soTK << std::endl;
    return true;
}
// CHUYEN KHOAN
bool TransactionLogic::ChuyenKhoan(std::string soTKGui, std::string maPIN,
                                    std::string soTKNhan, double soTien) {
    if (soTien <= 0) {
        std::cout << "[LOI] So tien chuyen phai lon hon 0!" << std::endl;
        return false;
    }
 
    if (soTKGui == soTKNhan) {
        std::cout << "[LOI] Khong the chuyen khoan cho chinh minh!" << std::endl;
        return false;
    }
 
    Account* tkGui = this->bankSystem->timKiemTaiKhoan(soTKGui);
    if (tkGui == NULL) {
        std::cout << "[LOI] Khong tim thay tai khoan gui " << soTKGui << "!" << std::endl;
        return false;
    }
 
    Account* tkNhan = this->bankSystem->timKiemTaiKhoan(soTKNhan);
    if (tkNhan == NULL) {
        std::cout << "[LOI] Khong tim thay tai khoan nhan " << soTKNhan << "!" << std::endl;
        return false;
    }
 
    if (tkGui->kiemTraPIN(maPIN) == false) {
        std::cout << "[LOI] Ma PIN khong dung!" << std::endl;
        return false;
    }
 
    // trừ tiền TK gửi trước, nếu không đủ tiền thì dừng luôn
    if (tkGui->rutTien(soTien) == false) {
        std::cout << "[LOI] So du tai khoan " << soTKGui << " khong du de chuyen!" << std::endl;
        return false;
    }
 
    // cộng tiền cho TK nhận
    tkNhan->napTien(soTien);
 
    // ghi nhận giao dịch chuyển khoản
    GhiNhanGiaoDich("CHUYEN_KHOAN", soTien, soTKGui, soTKNhan);
 
    std::cout << "[THANH CONG] Da chuyen " << std::fixed << soTien
              << " VND tu " << soTKGui << " den " << soTKNhan << std::endl;
    return true;
}