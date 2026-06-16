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
        cout << "========================================" << endl;
        cout << "    HE THONG QUAN LY NGAN HANG         " << endl;
        cout << "========================================" << endl;
        cout << "  1. Quan ly Khach hang & Tai khoan    " << endl;
        cout << "  2. Giao dich (Nap/Rut/Chuyen khoan) " << endl;
        cout << "  3. Bao cao, Sao ke, Tinh lai         " << endl;
        cout << "  0. Thoat chuong trinh                " << endl;
        cout << "========================================" << endl;
        cout << "Nhap lua chon: ";
        cin >> luaChon;

        switch(luaChon) {
            case 1: MenuQuanLy(bank); break;
            case 2: MenuGiaoDich(trans); break;
            case 3: MenuBaoCao(bank, report); break;
            case 0: cout << "Dang thoat" << endl; break;
            default: cout << "[LOI] Lua chon khong hop le!" << endl; DungManHinh();
        }
    } while(luaChon != 0);
}

void MenuQuanLy(BankSystem& bank){
    XoaManHinh();
    cout << "========================================" << endl;
    cout << "   QUAN LY KHACH HANG & TAI KHOAN      " << endl;
    cout << "========================================" << endl;
    cout << "  1. Them khach hang moi                " << endl;
    cout << "  2. Tao tai khoan moi                  " << endl;
    cout << "  0. Quay lai                           " << endl;
    cout << "========================================" << endl;
    cout << "Nhap lua chon: ";
    int chon; cin >> chon;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    switch(chon) {
        case 1:{
            string ma, ten, cccd, sdt;
            cout << "--- THEM KHACH HANG MOI ---" << endl;
            cout << "Nhap Ma KH: "; cin >> ma;
            cout << "Nhap Ho ten: "; cin.ignore(); getline(cin, ten);
            cout << "Nhap CCCD: "; cin >> cccd;
            cout << "Nhap SDT: "; cin >> sdt;
            bank.themKhachHang(ma, ten, cccd, sdt);
            break;
        }
        case 2:{
            string maKH, soTK, maPIN;
            double soDu;
            cout << "--- TAO TAI KHOAN MOI ---" << endl;
            cout << "Nhap ma KH: "; cin >> maKH;
            cout << "Nhap so TK: "; cin >> soTK;
            cout << "Nhap ma PIN: "; cin >> maPIN;
            cout << "Nhap so du ban dau (toi thieu 50,000 VND): "; soDu = NhapSoTien();

            bank.taoTaiKhoan(soTK, maKH, maPIN, soDu);
            cout << "Tao tai khoan thanh cong!" << endl;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
        default:
            cout << "[LOI] Lua chon khong hop le!" << endl;
    }
    DungManHinh();
}     

void MenuGiaoDich(TransactionLogic& trans) {
    XoaManHinh();
    cout << "========================================" << endl;
    cout << "           MENU GIAO DICH              " << endl;
    cout << "========================================" << endl;
    cout << "  1. Nap tien                          " << endl;
    cout << "  2. Rut tien                          " << endl;
    cout << "  3. Chuyen khoan                      " << endl;
    cout << "  0. Quay lai                          " << endl;
    cout << "========================================" << endl;
    cout << "Nhap lua chon: ";
    int chon; 
    cin >> chon;
    if (chon == 0) return;

    string stk, pin, stkNhan; 
    double soTien;

    cout << "Nhap STK: "; cin >> stk;

    // Xác thực mã PIN trước khi thực hiện giao dịch nào
    Account* tk = trans.getBankSystem()->timKiemTaiKhoan(stk);
    if (tk == NULL) {
        cout << "[LOI] Tai khoan khong ton tai!" << endl;
        DungManHinh();
        return;
    }

    switch(chon) {
        case 1:{ // Nạp tiền
            cout << "Nhap so tien nap: "; soTien = NhapSoTien();
            trans.NapTien(stk, soTien);
            break;
        }

        case 2:{  // Rút tiền
            string pin;
            bool pinDung = false;
            for (int lan = 1; lan <= 3; lan++) {
                cout << "Nhap ma PIN (lan " << lan << "/3): ";
                cin >> pin;
                if (tk->kiemTraPIN(pin)) { pinDung = true; break; }
                cout << "[LOI] Ma PIN khong dung!";
                if (lan < 3) cout << " Vui long thu lai." << endl;
            }
            if (!pinDung) {
                cout << "\n[CANH BAO] Sai PIN 3 lan. Huy thao tac." << endl;
                break;
            }

            while (true) {
                cout << "So du hien tai: " << tk->getSoDu() << " VND" << endl;
                cout << "Nhap so tien rut: ";
                double soTien = NhapSoTien();
                if (trans.RutTien(stk, pin, soTien)) break;
                cout << "Nhap lai so tien (0 de huy): ";
                double retry; cin >> retry;
                if (retry == 0) { cout << "Da huy thao tac." << endl; break; }
            }
            break;
        }

        case 3:{ // Chuyển khoản
            string pin;
            bool pinDung = false;
            for (int lan = 1; lan <= 3; lan++) {
                cout << "Nhap ma PIN (lan " << lan << "/3): ";
                cin >> pin;
                if (tk->kiemTraPIN(pin)) { pinDung = true; break; }
                cout << "[LOI] Ma PIN khong dung!";
                if (lan < 3) cout << " Vui long thu lai." << endl;
            }
            if (!pinDung) {
                cout << "\n[CANH BAO] Sai PIN 3 lan. Huy thao tac." << endl;
                break;
            }

            string stkNhan;
            cout << "Nhap STK nhan: "; cin >> stkNhan;
            if (trans.getBankSystem()->timKiemTaiKhoan(stkNhan) == NULL) {
                cout << "[LOI] Khong tim thay tai khoan nhan " << stkNhan << "!" << endl;
                break;
            }

            while (true) {
                cout << "So du hien tai: " << tk->getSoDu() << " VND" << endl;
                cout << "Nhap so tien chuyen: ";
                double soTien = NhapSoTien();
                if (trans.ChuyenKhoan(stk, pin, stkNhan, soTien)) break;
                cout << "Nhap lai so tien (0 de huy): ";
                double retry; cin >> retry;
                if (retry == 0) { cout << "Da huy thao tac." << endl; break; }
            }
            break;
        }

        default:
            cout << "[LOI] Lua chon khong hop le!" << endl;
    }
    DungManHinh();
}        

void MenuBaoCao(BankSystem& bank, ReportLogic& report) {
    XoaManHinh();
    cout << "========================================" << endl;
    cout << "        MENU BAO CAO & SAO KE          " << endl;
    cout << "========================================" << endl;
    cout << "  1. Xem sao ke tat ca giao dich       " << endl;
    cout << "  2. Xem sao ke theo khoang thoi gian  " << endl;
    cout << "  3. Tinh lai suat tien gui             " << endl;
    cout << "  0. Quay lai                          " << endl;
    cout << "========================================" << endl;
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
            report.XemSaoKe(stk); 
            break;
        case 2: {
            string tuNgay, denNgay;
            cout << "Nhap ngay bat dau (dd/mm/yyyy): "; cin >> tuNgay;
            cout << "Nhap ngay ket thuc (dd/mm/yyyy): "; cin >> denNgay;
            cout << endl;
            report.XemSaoKeTheoKhoangThoiGian(stk, tuNgay, denNgay); 
            break;
        }
        case 3: {
            double laiSuat;
            cout << "Nhap lai suat nam (%): "; cin >> laiSuat;
            cout << "Tinh lai thang nao? (0 = thang hien tai, hoac nhap thang nam, vd: 5 2025): ";
            int thang, nam;
            cin >> thang;
            if (thang == 0) {
                report.TinhLaiThang(stk, laiSuat); 
            } else {
                cin >> nam;
                report.TinhLaiThang(stk, laiSuat, thang, nam);
            }
            break;
        }
        default:
            cout << "Lua chon khong hop le!" << endl;
    }
    DungManHinh();
}