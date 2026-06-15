# include "../../include/utils/UI.h"
# include "../../include/utils/fileManager.h"
#include "../../include/services/ReportLogic.h"
# include <iostream>
# include <limits>

using namespace std;

void XoaManHinh(){
    system("cls");
}

void DungManHinh(){
    cout << "\nNhan Enter de tiep tuc";
    // Xóa sạch bộ nhớ đệm (buffer) để không bị trôi lệnh
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cin.get();
}
double NhapSoTien(){
    double soTien;
    while (true){
        cin >> soTien;
        if (cin.fail() || soTien <= 0) {
            cout << "[LOI] So tien khong hop le, vui long nhap lai: ";
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            break;
        }
    }
    return soTien;
}

void MenuChinh(BankSystem& bank, TransactionLogic& trans, ReportLogic& report){
    int luaChon;
    do {
        XoaManHinh();
        cout << "=== HE THONG QUAN LY NGAN HANG ===" << endl;
        cout << "1. Quan ly Khach hang & Tai khoan" << endl;
        cout << "2. Giao dich (Nap/Rut/Chuyen khoan)" << endl;
        cout << "3. Bao cao, Sao ke, Tinh lai" << endl;
        cout << "0. Thoat chuong trinh" << endl;
        cout << "Nhap lua chon: ";
        cin >> luaChon;

        switch(luaChon) {
            case 1: MenuQuanLy(bank); break;
            case 2: MenuGiaoDich(trans); break;
            case 3: MenuBaoCao(bank, report); break;
            case 0: cout << "Dang thoat..." << endl; break;
            default: cout << "Lua chon sai!" << endl; DungManHinh();
        }
    } while(luaChon != 0);
}

void MenuQuanLy(BankSystem& bank){
    XoaManHinh();
    cout << "=== QUAN LY KHACH HANG ===" << endl;
    cout << "1. Them khach hang moi" << endl;
    cout << "2. Tao tai khoan moi" << endl;
    cout << "Nhap lua chon: ";
    int chon; cin >> chon;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    switch(chon) {
        case 1:{
            string ma, ten, cccd, sdt;
            cout << "Nhap Ma KH: "; cin >> ma;
            cout << "Nhap Ho ten: "; cin.ignore(); getline(cin, ten);
            cout << "Nhap CCCD: "; cin >> cccd;
            cout << "Nhap SDT: "; cin >> sdt;
            bank.themKhachHang(ma, ten, cccd, sdt);
        }break;
        
        case 2:{
            string maKH, soTK, maPIN;
            double soDu;
            cout << "Nhap ma KH: "; cin >> maKH;
            cout << "Nhap so TK: "; cin >> soTK;
            cout << "Nhap ma PIN: "; cin >> maPIN;
            cout << "Nhap so du ban dau: "; soDu = NhapSoTien();

            bank.taoTaiKhoan(soTK, maKH, maPIN, soDu);
            cout << "Tao tai khoan thanh cong!" << endl;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }break;
    }
    
    DungManHinh();
}     

void MenuGiaoDich(TransactionLogic& trans) {
    XoaManHinh();
    cout << "=== MENU GIAO DICH ===" << endl;
    cout << "1. Nap tien" << endl;
    cout << "2. Rut tien" << endl;
    cout << "3. Chuyen khoan" << endl;
    cout << "Nhap lua chon: ";
    int chon; 
    cin >> chon;

    string stk, pin, stkNhan; 
    double soTien;

    cout << "Nhap STK: "; cin >> stk;
    cout << "Nhap ma PIN: "; cin >> pin; // Yêu cầu nhập mã PIN trước

    // Xác thực mã PIN trước khi thực hiện giao dịch nào
    Account* tk = trans.getBankSystem()->timKiemTaiKhoan(stk);
    if (tk == NULL || !tk->kiemTraPIN(pin)) {
        cout << "[LOI] Tai khoan khong ton tai hoac sai ma PIN!" << endl;
        DungManHinh();
        return;
    }

    switch(chon) {
        case 1: // Nạp tiền
            cout << "Nhap so tien nap: "; soTien = NhapSoTien();
            trans.NapTien(stk, soTien);
            break;

        case 2: // Rút tiền
            cout << "Nhap so tien rut: "; soTien = NhapSoTien();
            trans.RutTien(stk, pin, soTien);
            break;

        case 3: // Chuyển khoản
            cout << "Nhap STK nhan: "; cin >> stkNhan;
            cout << "Nhap so tien: "; soTien = NhapSoTien();
            trans.ChuyenKhoan(stk, pin, stkNhan, soTien);
            break;

        default:
            cout << "Lua chon khong hop le!" << endl;
            break;
    }
    DungManHinh();
}        

void MenuBaoCao(BankSystem& bank, ReportLogic& report) {
    XoaManHinh();
    cout << "=== MENU BAO CAO & SAO KE ===" << endl;
    cout << "1. Xem sao ke tat ca giao dich cua tai khoan" << endl;
    cout << "2. Xem sao ke theo khoang thoi gian" << endl;
    cout << "3. Tinh lai suat tien gui" << endl;
    cout << "0. Quay lai" << endl;
    cout << "Nhap lua chon: ";
    int chon; cin >> chon;

    if (chon == 0) return;

    string stk;
    cout << "Nhap STK: "; cin >> stk;

    // Kiểm tra tài khoản tồn tại trước khi làm tiếp
    if (bank.timKiemTaiKhoan(stk) == NULL) {
        cout << "[LOI] Khong tim thay tai khoan " << stk << "!" << endl;
        DungManHinh();
        return;
    }

    switch(chon) {
        case 1:
            report.XemSaoKe(stk); // Gọi hàm có sẵn
            break;
        case 2: {
            string tuNgay, denNgay;
            cout << "Nhap ngay bat dau (dd/mm/yyyy): "; cin >> tuNgay;
            cout << "Nhap ngay ket thuc (dd/mm/yyyy): "; cin >> denNgay;
            report.XemSaoKeTheoKhoangThoiGian(stk, tuNgay, denNgay); // Bạn cần viết hàm này
            break;
        }
        case 3: {
            double laiSuat;
            cout << "Nhap lai suat nam (%): "; cin >> laiSuat;
            double tienLai = report.TinhLaiThang(stk, laiSuat);
            cout << "-> Tien lai du kien: " << tienLai << " VND" << endl;
            break;
        }
        default:
            cout << "Lua chon khong hop le!" << endl;
    }
    DungManHinh();
}