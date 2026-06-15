//khai báo các hàm vẽ menu console
#ifndef UI_H
#define UI_H

#include "../services/BankSystem.h"
#include "../services/TransactionLogic.h"

// Các hàm hỗ trợ điều hướng
void XoaManHinh();
void DungManHinh();
double NhapSoTien();

// Các hàm hiển thị menu có truyền tham số hệ thống
void MenuChinh(BankSystem& bank, TransactionLogic& trans);      // Menu tổng quát
void MenuQuanLy(BankSystem& bank);                              // Quản lý khách hàng và tài khoản
void MenuGiaoDich(TransactionLogic& trans);                     // Nghiệp vụ nạp, rút, chuyển khoản
void MenuBaoCao(BankSystem& bank);                              // Xem lịch sử giao dịch, sao kê

#endif
