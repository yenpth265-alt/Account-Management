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
// Hàm phụ: ghi nhận giao dịch
void TransactionLogic::GhiNhanGiaoDich(std::string loaiGD, long long soTien, std::string soTKGui, std::string soTKNhan){
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
bool TransactionLogic::NapTien(std::string soTK, long long soTien){
    if (soTien <= 0){
        return false;
    }

    Account* tk = this->bankSystem->timKiemTaiKhoan(soTK);
    if (tk == NULL){
        return false;
    }
    if (tk->napTien(soTien) == false){
        return false;
    }
    // ghi nhận giao dịch: nạp tiền không có người nhận, để "N/A"
    GhiNhanGiaoDich("NAP", soTien, soTK, "N/A");
    return true;
}

// RÚT TIỀN
bool TransactionLogic::RutTien(std::string soTK, std::string maPIN, long long soTien){
    if (soTien <=0){
        return false;
    }
    Account* tk = this->bankSystem->timKiemTaiKhoan(soTK);
    if (tk == NULL){
        return false;
    }

    if (tk->kiemTraPIN(maPIN) ==false){
        return false;
    }
    if (tk->rutTien(soTien) == false){
        return false;
    }
    // ghi nhận giao dịch: rút tiền không có tk nhận -> để "N/A"
    GhiNhanGiaoDich("RUT", soTien, soTK, "N/A");
    return true;
}
// CHUYỂN KHOẢN
bool TransactionLogic::ChuyenKhoan(std::string soTKGui, std::string maPIN,
                                    std::string soTKNhan, long long soTien) {
    if (soTien <= 0) {
        return false;
    }
 
    if (soTKGui == soTKNhan) {
        return false;
    }
 
    Account* tkGui = this->bankSystem->timKiemTaiKhoan(soTKGui);
    if (tkGui == NULL) {
        return false;
    }
 
    Account* tkNhan = this->bankSystem->timKiemTaiKhoan(soTKNhan);
    if (tkNhan == NULL) {
        return false;
    }

    if (tkGui->kiemTraPIN(maPIN) == false) {
        return false;
    }
 
    // trừ tiền TK gửi trước, nếu không đủ tiền thì dừng luôn
    if (tkGui->rutTien(soTien) == false) {
        return false;
    }
 
    // cộng tiền cho TK nhận
    tkNhan->napTien(soTien);
 
    // ghi nhận giao dịch chuyển khoản
    GhiNhanGiaoDich("CHUYEN_KHOAN", soTien, soTKGui, soTKNhan);
 
    return true;
}