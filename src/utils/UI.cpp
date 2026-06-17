# include "../../include/utils/UI.h"
# include "../../include/utils/fileManager.h"
# include "../../include/services/ReportLogic.h"
# include <iostream>
# include <limits>

using namespace std;

void XoaManHinh(){
    system("cls");
}

void DungManHinh(){
    cout << "\nNhan Enter de tiep tuc";
    // Xóa sạch bộ nhớ đệm để không bị trôi lệnh
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cin.get();
}
long long NhapSoTien(){
    long long soTien;
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
    // XoaManHinh(); // Đã comment lại để không bị xóa mất chữ, đỡ rối màn hình
    cout << "========================================" << endl;
    cout << "   QUAN LY KHACH HANG & TAI KHOAN      " << endl;
    cout << "========================================" << endl;
    cout << "  1. Dang ky Khach hang & Tao Tai khoan " << endl;
    cout << "  0. Quay lai                           " << endl;
    cout << "========================================" << endl;
    cout << "Nhap lua chon: ";
    int chon; cin >> chon;
    
    switch(chon) {
        case 1:{
            string ten, cccd, sdt, maPIN;
            long long soDu;
            cout << "--- DANG KY KHACH HANG & TAO TAI KHOAN ---" << endl;
            
            while (true) {
                cout << "Nhap CCCD (12 chu so): "; cin >> cccd;
                if (!BankSystem::kiemTraCCCDHopLe(cccd)) {
                    cout << "[LOI] CCCD phai la 12 chu so. Vui long nhap lai." << endl;
                } else if (bank.kiemTraTrungCCCD(cccd)) {
                    cout << "[LOI] CCCD nay da duoc dang ky tren he thong!" << endl;
                } else {
                    break;
                }
            }

            cout << "Nhap Ho ten: "; cin.ignore(); getline(cin, ten);
            
            while (true) {
                cout << "Nhap SDT (10 chu so, bat dau bang 0): "; cin >> sdt;
                if (!BankSystem::kiemTraSDTHopLe(sdt)) {
                    cout << "[LOI] SDT khong hop le. Vui long nhap lai." << endl;
                } else {
                    break;
                }
            }

            while (true) {
                cout << "Tao ma PIN (4 chu so): "; cin >> maPIN;
                if (!BankSystem::kiemTraPINHopLe(maPIN)) {
                    cout << "[LOI] PIN phai la 4 chu so. Vui long nhap lai." << endl;
                } else {
                    break;
                }
            }

            cout << "Nhap so du ban dau (toi thieu 50,000 VND): "; soDu = NhapSoTien();

            // 2. Tự động sinh mã Khách hàng
            string maKH = bank.sinhMaKHMoi();

            // 3. Tự động sinh Số tài khoản 
            string soTK = bank.sinhSTKMoi();

            // 4. Lưu vào hệ thống BankSystem
            bank.themKhachHang(maKH, ten, cccd, sdt);
            bank.taoTaiKhoan(soTK, maKH, maPIN, soDu);
            
            cout << "\n[THANH CONG] Da dang ky & tao tai khoan thanh cong!" << endl;
            cout << "=> MA KHACH HANG cua ban : " << maKH << endl;
            cout << "=> SO TAI KHOAN cua ban  : " << soTK << " (Vui long ghi nho!)" << endl;
            
            // 5. Ghi ngay xuống file text (Lưu tức thì)
            SaveAllData(bank); 
            break;
        }
        case 0: 
            break;
        default:
            cout << "[LOI] Lua chon khong hop le!" << endl;
    }
    DungManHinh();
}  

void MenuGiaoDich(TransactionLogic& trans) {
    
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

    string stk;

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
            cout << "Nhap so tien nap: "; 
            long long soTien = NhapSoTien();
            trans.NapTien(stk, soTien);
            SaveAllData(*(trans.getBankSystem()));
            break;;
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
                long long soTien = NhapSoTien();
                if (trans.RutTien(stk, pin, soTien)){
                    SaveAllData(*(trans.getBankSystem()));
                    break;
                }
                 
                cout << "Nhap lai so tien (0 de huy): ";
                long long retry; cin >> retry;
                if (retry == 0) { cout << "Da huy thao tac." << endl; break; }
            }
            break;;
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
                long long soTien = NhapSoTien();
                if (trans.ChuyenKhoan(stk, pin, stkNhan, soTien)) {
                    SaveAllData(*(trans.getBankSystem()));
                    break;
                }
                cout << "Nhap lai so tien (0 de huy): ";
                long long retry; cin >> retry;
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
    
    cout << "========================================" << endl;
    cout << "        MENU BAO CAO & SAO KE          " << endl;
    cout << "========================================" << endl;
    cout << "  1. Xem sao ke tat ca giao dich       " << endl;
    cout << "  2. Xem sao ke theo khoang thoi gian  " << endl;
    cout << "  3. Tra cuu tien lai tich luy         " << endl;
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
            
            // Ép sang số nguyên để so sánh (YYYYMMDD)
            int start = report.ChuyenNgaySangInt(tuNgay); 
            int end = report.ChuyenNgaySangInt(denNgay);
            int now = report.ChuyenNgaySangInt(report.LayNgayHienTai()); // Bạn cần chỉnh public các hàm tiện ích này trong ReportLogic

            if (start > now || end > now) {
                cout << "[LOI] Khong the sao ke giao dich trong tuong lai!" << endl;
                break;
            }
            if (start > end) {
                cout << "[LOI] Ngay bat dau khong duoc lon hon ngay ket thuc!" << endl;
                break;
            }
            
            cout << endl;
            report.XemSaoKeTheoKhoangThoiGian(stk, tuNgay, denNgay); 
            break;
        }
        case 3: {
            cout << "--- TRA CUU TIEN LAI TICH LUY ---" << endl;
            report.TinhLaiThang(stk, 4.0, 0, 0); 
            break;
        }
        default:
            cout << "Lua chon khong hop le!" << endl;
    }
    DungManHinh();
}