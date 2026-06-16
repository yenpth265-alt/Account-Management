#include "../../include/services/ReportLogic.h"
#include <iostream>
#include <ctime>
#include <cstdio>

ReportLogic::ReportLogic(BankSystem* bank){
    this->bankSystem = bank;
}

static std::string LayNgayHienTai() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    char buf[20];
    sprintf(buf, "%02d/%02d/%04d", ltm->tm_mday, 1 + ltm->tm_mon, 1900 + ltm->tm_year);
    return std::string(buf);
}

static int ChuyenNgaySangInt(const std::string& ngay) {
    int d, m, y;
    sscanf(ngay.c_str(), "%d/%d/%d", &d, &m, &y);
    return y * 10000 + m * 100 + d;
}

// Kiem tra thang T/Y da duoc tinh lai chua (co giao dich LAI trong thang do chua)
static bool DaTinhLaiThang(LinkedList<Transaction>& dsGD,
                            const std::string& soTK, int thang, int nam) {
    Node<Transaction>* curr = dsGD.getHead();
    while (curr != NULL) {
        if (curr->data.getLoaiGD() == "LAI" && curr->data.getSoTKNhan() == soTK) {
            std::string tg = curr->data.getThoiGian().substr(0, 10);
            int d, m, y;
            sscanf(tg.c_str(), "%d/%d/%d", &d, &m, &y);
            if (m == thang && y == nam) return true;
        }
        curr = curr->next;
    }
    return false;
}

// Tinh tong tien lai da cong tu truoc den nay
static double TinhTongLaiDaCong(LinkedList<Transaction>& dsGD, const std::string& soTK) {
    double tong = 0.0;
    Node<Transaction>* curr = dsGD.getHead();
    while (curr != NULL) {
        if (curr->data.getLoaiGD() == "LAI" && curr->data.getSoTKNhan() == soTK)
            tong += curr->data.getSoTien();
        curr = curr->next;
    }
    return tong;
}

// Tinh so du cua TK vao cuoi thang (thang/nam) bang cach di nguoc tu so du hien tai
static double TinhSoDuCuoiThang(Account* tk, LinkedList<Transaction>& dsGD,
                                  int thang, int nam) {
    int thangNay = nam * 100 + thang;
    double soDu  = tk->getSoDu();
    std::string soTK = tk->getSoTK();

    Node<Transaction>* curr = dsGD.getHead();
    while (curr != NULL) {
        std::string tg = curr->data.getThoiGian().substr(0, 10);
        int d, m, y;
        sscanf(tg.c_str(), "%d/%d/%d", &d, &m, &y);
        int thangGD = y * 100 + m;

        if (thangGD > thangNay) {
            std::string loai  = curr->data.getLoaiGD();
            double soTien     = curr->data.getSoTien();
            std::string tkGui = curr->data.getSoTKGui();
            std::string tkNhan= curr->data.getSoTKNhan();

            if (loai == "NAP"  && tkGui  == soTK) soDu -= soTien;
            else if (loai == "RUT"  && tkGui  == soTK) soDu += soTien;
            else if (loai == "CHUYEN_KHOAN") {
                if (tkGui  == soTK) soDu += soTien;
                if (tkNhan == soTK) soDu -= soTien;
            }
            else if (loai == "LAI" && tkNhan == soTK) soDu -= soTien;
        }
        curr = curr->next;
    }
    return soDu;
}

// -------------------------------------------------------
// XEM LICH SU GIAO DICH
// -------------------------------------------------------
void ReportLogic::XemLichSuTheoTK(std::string soTK){
    Account* tk = this->bankSystem->timKiemTaiKhoan(soTK);
    if (tk == NULL){
        std::cout << "[LOI] Khong tim thay tai khoan " << soTK << "!" << std::endl;
        return;
    }
    LinkedList<Transaction>& dsGD = this->bankSystem->getDanhSachGD();
    std::cout << "LICH SU GIAO DICH CUA TAI KHOAN " << soTK << std::endl;
    int soGD = 0;
    Node<Transaction>* curr = dsGD.getHead();
    while (curr != NULL){
        if (curr->data.getSoTKGui() == soTK || curr->data.getSoTKNhan() == soTK){
            curr->data.xuatThongTin();
            soGD++;
        }
        curr = curr->next;
    }
    if (soGD == 0)
        std::cout << "Tai khoan nay chua co giao dich nao." << std::endl;
}

// -------------------------------------------------------
// SAO KE
// -------------------------------------------------------
void ReportLogic::XemSaoKe(std::string soTK){
    Account* tk = this->bankSystem->timKiemTaiKhoan(soTK);
    if (tk == NULL){
        std::cout << "[LOI] Khong tim thay tai khoan " << soTK << std::endl;
        return;
    }
    std::cout << "========================================" << std::endl;
    std::cout << "       SAO KE TAI KHOAN: " << soTK        << std::endl;
    std::cout << "========================================" << std::endl;
    tk->xuatThongTin();
    std::cout << "\nChi tiet giao dich:" << std::endl;
    XemLichSuTheoTK(soTK);
    std::cout << "========================================" << std::endl;
}

void ReportLogic::XemSaoKeTheoKhoangThoiGian(std::string soTK,
                                               std::string tuNgay,
                                               std::string denNgay) {
    Account* tk = this->bankSystem->timKiemTaiKhoan(soTK);
    if (tk == NULL){
        std::cout << "[LOI] Khong tim thay tai khoan " << soTK << std::endl;
        return;
    }
    LinkedList<Transaction>& dsGD = this->bankSystem->getDanhSachGD();
    int start = ChuyenNgaySangInt(tuNgay);
    int end   = ChuyenNgaySangInt(denNgay);
    bool co   = false;

    std::cout << "========================================" << std::endl;
    std::cout << "  SAO KE TU " << tuNgay << " DEN " << denNgay << std::endl;
    std::cout << "  Tai khoan : " << soTK                        << std::endl;
    std::cout << "========================================" << std::endl;

    Node<Transaction>* curr = dsGD.getHead();
    while (curr != NULL) {
        std::string ngayGD = curr->data.getThoiGian().substr(0, 10);
        int dateInt = ChuyenNgaySangInt(ngayGD);
        if ((curr->data.getSoTKGui() == soTK || curr->data.getSoTKNhan() == soTK)
            && dateInt >= start && dateInt <= end) {
            curr->data.xuatThongTin();
            co = true;
        }
        curr = curr->next;
    }
    if (!co)
        std::cout << "Khong co giao dich nao trong khoang thoi gian nay." << std::endl;
    std::cout << "========================================" << std::endl;
}

// -------------------------------------------------------
// TINH LAI THANG CU THE
// -------------------------------------------------------
// thang=0, nam=0 => thang hien tai
double ReportLogic::TinhLaiThang(std::string soTK, double laiSuatNamPhanTram,
                                   int thangXem, int namXem) {
    Account* tk = this->bankSystem->timKiemTaiKhoan(soTK);
    if (tk == NULL) {
        std::cout << "[LOI] Khong tim thay tai khoan " << soTK << "!" << std::endl;
        return 0;
    }

    std::string ngayHienTai = LayNgayHienTai();
    int dNow, mNow, yNow;
    sscanf(ngayHienTai.c_str(), "%d/%d/%d", &dNow, &mNow, &yNow);

    int dMo, mMo, yMo;
    sscanf(tk->getNgayMo().c_str(), "%d/%d/%d", &dMo, &mMo, &yMo);
    // Neus khong truyen thang cu the thi dung thang hien tai
    if (thangXem == 0) { thangXem = mNow; namXem = yNow; }

    // Kiem tra thang xem co hop le khong (khong duoc truoc ngay mo TK)
    int thangXemInt = namXem * 100 + thangXem;
    int thangMoInt  = yMo    * 100 + mMo;
    int thangNayInt = yNow   * 100 + mNow;

    if (thangXemInt < thangMoInt) {
        std::cout << "[LOI] Tai khoan dươc mo ngay: " << tk->getNgayMo() 
                  << ". Thang:  " << thangXem << "/" << namXem << " chua co lai!" << std::endl;
        return 0;
    }
    if (thangXemInt > thangNayInt) {
        std::cout << "[LOI] Thang " << thangXem << "/" << namXem
                  << " chua den!" << std::endl;
        return 0;
    }

    // Kiem tra da du 1 thang ke tu ngay mo TK chua
    // Lai thang T/Y co neu: ngay hom nay >= ngay mo TK trong thang T/Y
    // tuc la (T/Y > thang mo) VA (neu T/Y == thang hien tai thi dNow >= dMo)
    bool duDieuKien = false;
    if (thangXemInt < thangNayInt) {
       // Thang da qua: chac chan du dieu kien neu thangXem > thangMo
        duDieuKien = (thangXemInt > thangMoInt);
    } else {
        // Thang hien tai: can dNow >= dMo
        duDieuKien = (thangXemInt > thangMoInt) && (dNow >= dMo);
    }

    LinkedList<Transaction>& dsGD = this->bankSystem->getDanhSachGD();
    double tongLaiCu = TinhTongLaiDaCong(dsGD, soTK);

    std::cout << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "   TIEN LAI KHONG KY HAN - " << thangXem << "/" << namXem << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "Tai khoan    : " << soTK                  << std::endl;
    std::cout << "Ngay mo TK   : " << tk->getNgayMo()       << std::endl;
    std::cout << "Lai suat     : " << laiSuatNamPhanTram    << "%/nam" << std::endl;

    if (!duDieuKien) {
        std::cout << "----------------------------------------" << std::endl;
        std::cout << "[THONG BAO] Chua du dieu kien tinh lai thang "
                  << thangXem << "/" << namXem << "." << std::endl;
        std::cout << "  (Can it nhat " << dMo << "/" << thangXem << "/" << namXem
                  << " moi co lai)" << std::endl;
        std::cout << "Tong lai da cong truoc do : " << tongLaiCu   << " VND" << std::endl;
        std::cout << "So du hien tai            : " << tk->getSoDu() << " VND" << std::endl;
        std::cout << "========================================" << std::endl;
        return 0;
    }

    // Da tinh lai thang nay chua
    bool daTinh = DaTinhLaiThang(dsGD, soTK, thangXem, namXem);

    // Tinh so du cuoi thang xem de lam can cu tinh lai
    double soDuThang   = TinhSoDuCuoiThang(tk, dsGD, thangXem, namXem);
    double laiSuatThang = laiSuatNamPhanTram / 100.0 / 12.0;
    double laiThang    = soDuThang * laiSuatThang;

    std::cout << "So du thang " << thangXem << "/" << namXem
              << "  : " << soDuThang   << " VND" << std::endl;
    std::cout << "Tien lai thang nay        : " << laiThang    << " VND" << std::endl;
    std::cout << "----------------------------------------"               << std::endl;

    if (daTinh) {
        std::cout << "[DA TINH] Thang " << thangXem << "/" << namXem
                  << " da duoc cong lai truoc do." << std::endl;
    } else {
        // Cong lai vao so du
        tk->napTien(laiThang);

        // Ghi giao dich loai "LAI"
        int soGD = dsGD.getSize() + 1;
        std::string maGD = Transaction::sinhMaGD(soGD);
        char buf[30];
        sprintf(buf, "%02d/%02d/%04d 00:00", dMo, thangXem, namXem);
        Transaction gdLai(maGD, std::string(buf), "LAI", laiThang, "NGAN_HANG", soTK);
        dsGD.addTail(gdLai);

        tongLaiCu += laiThang; // Cap nhat tong
        std::cout << "[THANH CONG] Da cong lai thang " << thangXem
                  << "/" << namXem << " vao so du." << std::endl;
    }

    std::cout << "Tong lai tu truoc den nay : " << tongLaiCu    << " VND" << std::endl;
    std::cout << "So du hien tai            : " << tk->getSoDu() << " VND" << std::endl;
    std::cout << "========================================" << std::endl;

    return laiThang;
}