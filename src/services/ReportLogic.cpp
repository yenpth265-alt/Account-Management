#include "../../include/services/ReportLogic.h"
#include <iostream>
#include <ctime>
#include <cstdio>

ReportLogic::ReportLogic(BankSystem* bank){
    this ->bankSystem = bank;
}

// Hàm phụ: tính số tháng đầy đủ đã trôi qua giữa ngày mở TK và ngày hiện tại
// (cả 2 dạng "dd/mm/yyyy")
static int TinhSoThangGui(const std::string& ngayMo, const std::string& ngayHienTai) {
    int dMo, mMo, yMo, dNow, mNow, yNow;
    sscanf(ngayMo.c_str(), "%d/%d/%d", &dMo, &mMo, &yMo);
    sscanf(ngayHienTai.c_str(), "%d/%d/%d", &dNow, &mNow, &yNow);

    int soThang = (yNow - yMo) * 12 + (mNow - mMo);

    // Nếu ngày hiện tại trong tháng chưa tới ngày mở TK -> chưa tính tháng đó
    if (dNow < dMo) {
        soThang--;
    }

    return (soThang > 0) ? soThang : 0;
}

// xem toàn bộ lịch sử giao dịch
void ReportLogic::XemLichSuToanHeThong(){
    LinkedList<Transaction>& dsGD = this->bankSystem->getDanhSachGD();

    if(dsGD.getSize() == 0){
        std::cout << "[THONG BAO] He thong chua co giao dich nao!" << std:: endl;
        return;
    }
    std::cout << "LICH SU GIAO DICH TOAN HE THONG (" 
              << dsGD.getSize() << " giao dich ) " << std::endl;
    
    Node<Transaction>* current = dsGD.getHead();
    while (current != NULL) {
        current->data.xuatThongTin();
        current = current->next;
    }
}
//XEM LICH SU THEO TAI KHOAN
void ReportLogic::XemLichSuTheoTK(std::string soTK){
    Account* tk = this->bankSystem->timKiemTaiKhoan(soTK);
    if (tk == NULL){
        std::cout << "[LOI] Khong tim thay tai khoan" << soTK << " !" << std::endl;
        return;
    }
    LinkedList<Transaction>& dsGD = this->bankSystem->getDanhSachGD();
    std::cout << "LICH SU GIAO DICH CUA TAI KHOAN "<< soTK << std::endl;
    
    int soGD = 0;
    Node<Transaction>*current = dsGD.getHead();
    while (current != NULL){
        if (current->data.getSoTKGui() == soTK || current->data.getSoTKNhan() == soTK){
            current->data.xuatThongTin();
            soGD++;
        }
        current = current->next;
    }
    if (soGD == 0){
        std::cout << "Tai khoan nay chua co giao dich nao" << std::endl;

    }
}
//SAO KÊ TÀI KHOẢN
void ReportLogic::XemSaoKe(std::string soTK){
    Account* tk = this->bankSystem->timKiemTaiKhoan(soTK);
    if(tk==NULL){
        std:: cout <<"[LOI] Khong tim thay tai khoan" << soTK << std::endl;
        return;
    }
    std::cout << "   SAO KE TAI KHOAN   " << soTK << std::endl;
    std::cout << " Thong tin tai khoan: ";
    tk->xuatThongTin();

    std::cout << "\nChi tiet giao dich:" << std::endl;
    XemLichSuTheoTK(soTK);
}

//THỐNG KÊ TỔNG GIAO DỊCH THEO LOẠI
void ReportLogic::ThongKeTongGiaoDich() {
    LinkedList<Transaction>& dsGD = this->bankSystem->getDanhSachGD();
 
    double tongNap = 0;
    double tongRut = 0;
    double tongChuyen = 0;
 
    int soGDNap = 0;
    int soGDRut = 0;
    int soGDChuyen = 0;
 
    Node<Transaction>* current = dsGD.getHead();
    while (current != NULL) {
        std::string loai = current->data.getLoaiGD();
        double soTien = current->data.getSoTien();
 
        if (loai == "NAP") {
            tongNap += soTien;
            soGDNap++;
        } else if (loai == "RUT") {
            tongRut += soTien;
            soGDRut++;
        } else if (loai == "CHUYEN_KHOAN") {
            tongChuyen += soTien;
            soGDChuyen++;
        }
 
        current = current->next;
    }
 
    std::cout << "===== THONG KE GIAO DICH TOAN HE THONG =====" << std::endl;
    std::cout << "- Nap tien    : " << soGDNap << " giao dich, tong "
              << std::fixed << tongNap << " VND" << std::endl;
    std::cout << "- Rut tien    : " << soGDRut << " giao dich, tong "
              << std::fixed << tongRut << " VND" << std::endl;
    std::cout << "- Chuyen khoan: " << soGDChuyen << " giao dich, tong "
              << std::fixed << tongChuyen << " VND" << std::endl;
}
double ReportLogic::TinhLaiThang(std::string soTK, double laiSuatNamPhanTram) {
    // Tìm tài khoản
    Account* tk = this->bankSystem->timKiemTaiKhoan(soTK);
    
    // Nếu tài khoản không tồn tại, trả về 0
    if (tk == NULL) {
        std:: cout << "Lỗi! Không tìm thấy tài khoản" << soTK << "!" << std::endl;
        return 0;
    }

     // Lấy ngày hiện tại
    time_t now = time(0);
    tm* ltm = localtime(&now);
    char buf[20];
    sprintf(buf, "%02d/%02d/%04d", ltm->tm_mday, 1 + ltm->tm_mon, 1900 + ltm->tm_year);
    std::string ngayHienTai = buf;

    int soThangGui = TinhSoThangGui(tk->getNgayMo(), ngayHienTai);

    // Xử lý trường hợp TK mới tạo chưa đủ 1 tháng
    if (soThangGui <= 0) {
        std::cout << "[THONG BAO] Tai khoan " << soTK 
                  << " chua mo du 1 thang, chua duoc tinh lai." << std::endl;
        return 0.0;
    }

    double laiThang = tk->getSoDu() * (laiSuatNamPhanTram / 100.0 / 12.0) * soThangGui;
    return laiThang;
}