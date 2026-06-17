//khai báo hàm nạp, rút, chuyển khoản, lưu lịch sử giao dịch
#ifndef TRANSACTIONLOGIC_H
#define TRANSACTIONLOGIC_H

#include "BankSystem.h"
#include "../models/transaction.h"
#include <string>

class TransactionLogic {
    private:
        BankSystem* bankSystem; // con trỏ trỏ tới hệ thống ngân hàng đang chạy
        int soGDDaTao; // dùng để sinh mã GD tự động

        // hàm phụ để ghi lại 1 gd vào danh sách gd của BankSystem
        void GhiNhanGiaoDich(std::string loaiGD, long long soTien,
                            std::string soTKGui, std::string soTKNhan);
    public:
        BankSystem* getBankSystem();
            
        TransactionLogic(BankSystem* bank);

        //đồng bộ số GD đã tạo khi load dữ liệu cũ từ file,tránh sinh trùng mã GD
        void SetSoGDDaTao(int soGD);
        
        //NẠP TIỀN
        //Trả về true nếu thành công, false nếu lỗi 
        // vidu: không tìm thấy Tk, số tiền âm,...
        bool NapTien(std::string soTK, long long soTien);
        
        //RÚT TIỀN
        // Cần kiểm tra mã PIN trước khi rút
        bool RutTien(std::string soTK, std::string maPIN, long long soTien);

        //CHUYỂN KHOẢN
        // Kiểm tra mã PIN của TK gửi, kiểm tra số dư đủ, kiểm tra Tk nhân có tồn tại
        bool ChuyenKhoan(std::string soTKGui, std::string maPIN, std::string soTKNhan, long long soTien);
    
        
};
#endif