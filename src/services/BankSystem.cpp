#include "../../include/services/BankSystem.h"
#include <iostream>
BankSystem::BankSystem() {
    // LinkedList đã tự khởi tạo danh sách rỗng
}

// ==========================================
// 1. KIỂM TRA TRÙNG SỐ TÀI KHOẢN
// ==========================================
bool BankSystem::kiemTraTrungSTK(std::string maTK) {
    Node<Account>* current = danhSachTK.getHead();
    while (current != nullptr) {
        if (current->data.getMaTK() == maTK) {
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
    while (current != nullptr) {
        if (current->data.getMaKH() == maKH) {
            return &(current->data); // Trả về địa chỉ của khách hàng
        }
        current = current->next;
    }
    return nullptr; // Không tìm thấy
}

Account* BankSystem::timKiemTaiKhoan(std::string maTK) {
    Node<Account>* current = danhSachTK.getHead();
    while (current != nullptr) {
        if (current->data.getMaTK() == maTK) {
            return &(current->data); 
        }
        current = current->next;
    }
    return nullptr; 
}

// ==========================================
// 3. THÊM KHÁCH HÀNG
// ==========================================
bool BankSystem::themKhachHang(std::string maKH, std::string hoTen, std::string cccd, std::string sdt) {
    if (timKiemKhachHang(maKH) != nullptr) {
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
    if (kiemTraTrungSTK(maTK) == true) {
        std::cout << "[LOI] So tai khoan " << maTK << " da co nguoi su dung!" << std::endl;
        return false;
    }

    if (timKiemKhachHang(maKH) == nullptr) {
        std::cout << "[LOI] Khong tim thay khach hang ma " << maKH << ". Vui long tao KH truoc!" << std::endl;
        return false;
    }

    if (soDuBanDau < 50000) {
        std::cout << "[LOI] So du ban dau phai >= 50.000 VND!" << std::endl;
        return false;
    }

    Account tkMoi(soTK, maKH, maPIN, soDuBanDau);
    danhSachTK.addTail(tkMoi);
    
    std::cout << "[THANH CONG] Da tao tai khoan " << maTK << " cho khach hang " << maKH << std::endl;
    return true;
}