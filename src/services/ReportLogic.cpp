#include "../../include/services/ReportLogic.h"
#include <iostream>
ReportLogic::ReportLogic(BankSystem* bank){
    this ->bankSystem = bank;
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
    while (current != nullptr) {
        current->data.xuatThongTin();
        current = current->next;
    }
}
//XEM LICH SU THEO TAI KHOAN
void ReportLogic::XemLichSuTheoTK(std::string soTK){
    Account* tk = this->bankSystem->timKiemTaiKhoan(soTK);
    if (tk == nullptr){
        std::cout << "[LOI] Khong tim thay tai khoan" << soTK << " !" << std::endl;
        return;
    }
    LinkedList<Transaction>& dsGD = this->bankSystem->getDanhSachGD();
    std::cout << "LICH SU GIAO DICH CUA TAI KHOAN "<< soTK << std::endl;
    
    int soGD = 0;
    Node<Transaction>*current = dsGD.getHead();
    while (current != nullptr){
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
    if(tk==nullptr){
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
    while (current != nullptr) {
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