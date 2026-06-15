#include "../../include/services/BankSystem.h"
#include <iostream>
#include <ctime>
#include <cstdio>

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
// 1. KIỂM TRA TRÙNG SỐ TÀI KHOẢN
// ==========================================
bool BankSystem::kiemTraTrungSTK(std::string soTK) {
    Node<Account>* current = danhSachTK.getHead();
    while (current != NULL) {
        if (current->data.getSoTK() == soTK) {
            return true; // Phát hiện có người dùng số này rồi!
        }
        current = current->next;
    }
    return false; // Số tài khoản này an toàn
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
        std::cout << "[LOI] Ma khach hang " << maKH << " da ton tai trong he thong!" << std::endl;
        return false;
    }
    
    Customer khMoi(maKH, hoTen, cccd, sdt);
    danhSachKH.addTail(khMoi);
    
    std::cout << "[THANH CONG] Da them khach hang: " << hoTen << std::endl;
    return true;
}

// ==========================================
// 4. TẠO TÀI KHOẢN MỚI
// ==========================================
bool BankSystem::taoTaiKhoan(std::string soTK, std::string maKH, std::string maPIN, double soDuBanDau) {
    if (kiemTraTrungSTK(soTK) == true) {
        std::cout << "[LOI] So tai khoan " << soTK << " da co nguoi su dung!" << std::endl;
        return false;
    }

    if (timKiemKhachHang(maKH) == NULL) {
        std::cout << "[LOI] Khong tim thay khach hang ma " << maKH << ". Vui long tao KH truoc!" << std::endl;
        return false;
    }

    if (soDuBanDau < 50000) {
        std::cout << "[LOI] So du ban dau phai >= 50.000 VND!" << std::endl;
        return false;
    }

    std::string ngayMo = LayNgayHienTai();

    Account tkMoi(soTK, maKH, maPIN, soDuBanDau, ngayMo);
    danhSachTK.addTail(tkMoi);
    
    std::cout << "[THANH CONG] Da tao tai khoan " << soTK << " cho khach hang " << maKH << std::endl;
    return true;
}
LinkedList<Transaction>& BankSystem::getDanhSachGD() {
    return danhSachGD; // Trả về danh sách giao dịch mà bạn đã khai báo trong class
}

bool BankSystem::naptaiKhoanTuFile(std::string soTK, std::string maKH, 
                                    std::string maPIN, double soDu, std::string ngayMo) {
    if (kiemTraTrungSTK(soTK)) {
        return false; // tránh trùng STK nếu file bị lỗi
    }
    Account tk(soTK, maKH, maPIN, soDu, ngayMo);
    danhSachTK.addTail(tk);
    return true;
}