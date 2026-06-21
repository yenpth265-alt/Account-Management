//khai báo hàm sao kê, lịch sử
#ifndef REPORTLOGIC_H
#define REPORTLOGIC_H
#include "BankSystem.h"
#include "string"

struct KetQuaChotLai {
        int soTKDuocCong;
        long long tongTienCong;
};
class ReportLogic {
    private:
        BankSystem* bankSystem; 
    public:
        ReportLogic(BankSystem* bank);

        std::string LayNgayHienTai();
    int ChuyenNgaySangInt(const std::string& ngay);
    
    void XemLichSuTheoTK(std::string soTK);
    
    void XemSaoKe(std::string soTK);

    void XemSaoKeTheoKhoangThoiGian(std::string soTK, std::string tuNgay, std::string denNgay);

    double TinhLaiThang(std::string soTK, double laiSuatNamPhanTram,
                            int thangXem = 0, int namXem = 0);
    long long TinhTongLaiDaCong(const std::string& soTK);
    
    KetQuaChotLai TuDongChotLaiHangThang();

};
#endif