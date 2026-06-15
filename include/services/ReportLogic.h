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
    
    // In lịch sử giao dịch của 1 tk cụ thể
    // giao dịch nạp/rút/chuyển khoản của tk đó 
    void XemLichSuTheoTK(std::string soTK);

    // In sao kê (số dư hiện tại, danh sách giao dịch) cho 1 tk
    void XemSaoKe(std::string soTK);

    // Xem sao kê trong khoảng thời gian tùy chọn
    void XemSaoKeTheoKhoangThoiGian(std::string soTK, std::string tuNgay, std::string denNgay);

    // Thêm vào trong class ReportLogic
    double TinhLaiThang(std::string soTK, double laiSuatNamPhanTram);
};
#endif