#include "../../include/services/BankSystem.h"
#include <iostream>
#include <ctime>
#include <cstdio>
#include <string>

static std::string LayNgayHienTai() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    char buf[20];
    sprintf(buf, "%02d/%02d/%04d", ltm->tm_mday, 1 + ltm->tm_mon, 1900 + ltm->tm_year);
    return std::string(buf);
}
BankSystem::BankSystem() {
    // LinkedList đã tự khởi tạo danh sách rỗng
}

// ==========================================
// 1. KIỂM TRA TRÙNG
// ==========================================
bool BankSystem::kiemTraTrungSTK(std::string soTK) {
    Node<Account>* current = danhSachTK.getHead();
    while (current != NULL) {
        if (current->data.getSoTK() == soTK) return true;
        current = current->next;
    }
    return false;
}
 
bool BankSystem::kiemTraTrungCCCD(std::string cccd) {
    Node<Customer>* current = danhSachKH.getHead();
    while (current != NULL) {
        if (current->data.getCCCD() == cccd) return true;
        current = current->next;
    }
    return false;
}

// ==========================================
// 2. TÌM KIẾM KHÁCH HÀNG & TÀI KHOẢN
// ==========================================
Customer* BankSystem::timKiemKhachHang(std::string maKH) {
    Node<Customer>* current = danhSachKH.getHead();
    while (current != NULL) {
        if (current->data.getMaKH() == maKH) {
            return &(current->data); // Trả về địa chỉ của khách hàng
        }
        current = current->next;
    }
    return NULL; // Không tìm thấy
}

Account* BankSystem::timKiemTaiKhoan(std::string soTK) {
    Node<Account>* current = danhSachTK.getHead();
    while (current != NULL) {
        if (current->data.getSoTK() == soTK) {
            return &(current->data); 
        }
        current = current->next;
    }
    return NULL; 
}

// ==========================================
// 3. THÊM KHÁCH HÀNG
// ==========================================
bool BankSystem::themKhachHang(std::string maKH, std::string hoTen, std::string cccd, std::string sdt) {
    if (timKiemKhachHang(maKH) != NULL) {
        //std::cout << "[LOI] Ma khach hang " << maKH << " da ton tai trong he thong!" << std::endl;
        return false;
    }
    
    Customer khMoi(maKH, hoTen, cccd, sdt);
    danhSachKH.addTail(khMoi);
    
   return true;
}

// ==========================================
// 4. TẠO TÀI KHOẢN MỚI
// ==========================================
bool BankSystem::taoTaiKhoan(std::string soTK, std::string maKH, std::string maPIN, long long soDuBanDau) {
    if (kiemTraTrungSTK(soTK) == true) {
        //std::cout << "[LOI] So tai khoan " << soTK << " da co nguoi su dung!" << std::endl;
        return false;
    }

    if (timKiemKhachHang(maKH) == NULL) {
        //std::cout << "[LOI] Khong tim thay khach hang ma " << maKH << ". Vui long tao KH truoc!" << std::endl;
        return false;
    }

    if (soDuBanDau < 50000) {
        //std::cout << "[LOI] So du ban dau phai >= 50.000 VND!" << std::endl;
        return false;
    }

    std::string ngayMo = LayNgayHienTai();

    Account tkMoi(soTK, maKH, maPIN, soDuBanDau, ngayMo);
    danhSachTK.addTail(tkMoi);
    
    //std::cout << "[THANH CONG] Da tao tai khoan " << soTK << " cho khach hang " << maKH << std::endl;
    return true;
}


bool BankSystem::naptaiKhoanTuFile(std::string soTK, std::string maKH, 
                                    std::string maPIN, long long soDu, std::string ngayMo) {
    if (kiemTraTrungSTK(soTK)) {
        return false; // tránh trùng STK nếu file bị lỗi
    }
    Account tk(soTK, maKH, maPIN, soDu, ngayMo);
    danhSachTK.addTail(tk);
    return true;
}

// ==========================================
// GETTERS
// ==========================================
LinkedList<Transaction>& BankSystem::getDanhSachGD() {
    return danhSachGD; 
}
LinkedList<Customer>&    BankSystem::getDanhSachKH() { 
    return danhSachKH; 
}

// ==========================================
// VALIDATION DỮ LIỆU ĐẦU VÀO
// ==========================================


bool BankSystem::kiemTraCCCDHopLe(const std::string& cccd) {
    if (cccd.length() != 12) return false;
    for (char c : cccd) {
        if (c < '0' || c > '9') return false;
    }
    return true;
}

bool BankSystem::kiemTraPINHopLe(const std::string& pin) {
    if (pin.length() != 4) return false;
    for (char c : pin) {
        if (c < '0' || c > '9') return false;
    }
    return true;
}

bool BankSystem::kiemTraSDTHopLe(const std::string& sdt) {
    if (sdt.length() != 10) return false;
    if (sdt[0] != '0') return false;
    for (char c : sdt) {
        if (c < '0' || c > '9') return false;
    }
    return true;
}

// ==========================================
// SINH MÃ TỰ ĐỘNG
// ==========================================
std::string BankSystem::sinhMaKHMoi() {
    int soKH = danhSachKH.getSize() + 1;
    std::string maKH = Customer::sinhMaKH(soKH);
    while (timKiemKhachHang(maKH) != NULL) {
        soKH++;
        maKH = Customer::sinhMaKH(soKH);
    }
    return maKH;
}
 
std::string BankSystem::sinhSTKMoi() {
    srand((unsigned int)time(0));
    std::string soTK = std::to_string(100000000 + rand() % 900000000);
    while (kiemTraTrungSTK(soTK))
        soTK = std::to_string(100000000 + rand() % 900000000);
    return soTK;
}

bool BankSystem::kiemTraNgayHopLe(const std::string& ngay) {
    int d, m, y;
    if (sscanf(ngay.c_str(), "%d/%d/%d", &d, &m, &y) != 3) return false;
    if (y < 1900 || y > 3000) return false;
    if (m < 1 || m > 12) return false;

    int soNgayTrongThang = 31;
    if (m == 4 || m == 6 || m == 9 || m == 11) {
        soNgayTrongThang = 30;
    } else if (m == 2) {
        if ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0)) soNgayTrongThang = 29;
        else soNgayTrongThang = 28;
    }
    return (d >= 1 && d <= soNgayTrongThang);
}