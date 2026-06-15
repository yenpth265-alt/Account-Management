//khai báo hàm sao kê, lịch sử
#ifndef REPORTLOGIC_H
#define REPORTLOGIC_H
#include "BankSystem.h"
#include "string"
class ReportLogic {
    private:
        BankSystem* bankSystem; //con trỏ trỏ tới hệ thống ngân hàng đang chạy
    public:
        ReportLogic(BankSystem* bank);
    
    // In lịch sử giao dịch trong hệ thống
    void XemLichSuToanHeThong();

    // In lịch sử giao dịch của 1 tk cụ thể
    // giao dịch nạp/rút/chuyển khoản của tk đó 
    void XemLichSuTheoTK(std::string soTK);

    // In sao kê (số dư hiện tại, danh sách giao dịch) cho 1 tk
    void XemSaoKe(std::string soTK);

    // Thống kê tổng số tiền đã giao dịch theo loại (nạp/rút/chuyển khoản)
    void ThongKeTongGiaoDich();

    // Thêm vào trong class ReportLogic
    double TinhLaiThang(std::string soTK, double laiSuatNamPhanTram);
};
#endif