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
    KetQuaChotLai kq = report.TuDongChotLaiHangThang();
    if (kq.soTKDuocCong > 0) {
        cout << "[HE THONG] Phat hien " << kq.soTKDuocCong
             << " tai khoan chua duoc chot lai cac thang truoc." << endl;
        cout << "[HE THONG] Da tu dong cong tong cong "
             << kq.tongTienCong << " VND tien lai!" << endl;
        cout << "----------------------------------------" << endl;
    }
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
    cout << "========================================" << endl;
    cout << "   QUAN LY KHACH HANG & TAI KHOAN      " << endl;
    cout << "========================================" << endl;
    cout << "  1. Dang ky Khach hang & Tao Tai khoan " << endl;
    cout << "  2. Doi ma PIN tai khoan               " << endl;
    cout << "  3. Doi so dien thoai                  " << endl;
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

            while (true){
                cout << "Nhap so du ban dau (toi thieu 50,000 VND): ";
                soDu = NhapSoTien();
                if (soDu < 50000){
                    cout << "[LOI] So du ban dau phai >= 50,000 VND. Vui long nhap lai!" << endl;
                } else {
                    break;
                }
            }
            string maKH = bank.sinhMaKHMoi();
            string soTK = bank.sinhSTKMoi();

            if (bank.themKhachHang(maKH, ten, cccd, sdt)) {
                if (bank.taoTaiKhoan(soTK, maKH, maPIN, soDu)) {
                    cout << "\n[THANH CONG] Da dang ky & tao tai khoan thanh cong!" << endl;
                    cout << "=> MA KHACH HANG cua ban : " << maKH << endl;
                    cout << "=> SO TAI KHOAN cua ban  : " << soTK << " (Vui long ghi nho!)" << endl;
                    SaveAllData(bank); 
                } else {
                    cout << "\n[LOI] Tao tai khoan that bai!" << endl;
                }
            } else {
                cout << "\n[LOI] Them khach hàng that bai!" << endl;
            }
            break;
        }
        case 2: { 
            string stk, pinCu, pinMoi, xacNhanPin;
            cout << "--- DOI MA PIN TAI KHOAN ---" << endl;
            cout << "Nhap So tai khoan: "; cin >> stk;

            Account* tk = bank.timKiemTaiKhoan(stk);
            if (tk == NULL) {
                cout << "[LOI] Khong tim thay tai khoan " << stk << "!" << endl;
                break;
            }

            cout << "Nhap ma PIN hien tai: "; cin >> pinCu;
            cout << "Nhap ma PIN moi (4 so): "; cin >> pinMoi;
            cout << "Xac nhan ma PIN moi: "; cin >> xacNhanPin;

            if (pinMoi != xacNhanPin) {
                cout << "[LOI] Ma PIN xac nhan khong khop voi ma PIN moi!" << endl;
                break;
            }

            if (tk->doiPIN(pinCu, pinMoi)) {
                cout << "[THANH CONG] Da doi ma PIN cho tai khoan " << stk << "!" << endl;
                SaveAllData(bank); 
            } else {
                cout << "[LOI] Ma PIN hien tai khong dung! Thao tac that bai." << endl;
            }
            break;
        }
        case 3: {
            string stk, pin, sdtMoi;
            cout << "--- DOI SO DIEN THOAI KHACH HANG ---" << endl;
            cout << "Nhap So tai khoan: "; cin >> stk;

            Account* tk = bank.timKiemTaiKhoan(stk);
            if (tk == NULL) {
                cout << "[LOI] Khong tim thay tai khoan " << stk << "!" << endl;
                break;
            }

            bool pinDung = false;
            for (int lan = 1; lan <= 3; lan++) {
                cout << "Nhap ma PIN de xac thuc (lan " << lan << "/3): ";
                cin >> pin;
                if (tk->kiemTraPIN(pin)) { 
                    pinDung = true; 
                    break; 
                }
                cout << "[LOI] Ma PIN khong dung!";
                if (lan < 3) cout << " Vui long thu lai." << endl;
            }

            if (!pinDung) {
                cout << "\n[CANH BAO] Sai PIN 3 lan. Huy thao tac doi so dien thoai." << endl;
                break;
            }

            while (true) {
                cout << "Nhap SDT moi (10 chu so, bat dau bang 0): "; cin >> sdtMoi;
                if (!BankSystem::kiemTraSDTHopLe(sdtMoi)) {
                    cout << "[LOI] SDT khong hop le. Vui long nhap lai." << endl;
                } else {
                    break;
                }
            }

            Customer* kh = bank.timKiemKhachHang(tk->getMaKH());
            if (kh != NULL) {
                kh->setSDT(sdtMoi); 
                cout << "[THANH CONG] Da doi so dien thoai moi cho khach hang " << kh->getHoTen() << "!" << endl;
                SaveAllData(bank);
            } else {
                cout << "[LOI] Khong tim thay thong tin khach hang lien ket voi tai khoan này!" << endl;
            }
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
            if (trans.NapTien(stk, soTien)){
                cout << "[THANH CONG] Da nap " << soTien << " VND vao tai khoan " << stk
                << ". So du moi: " << tk->getSoDu() <<"VND" << endl;
                SaveAllData(*(trans.getBankSystem()));
            } 
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
                long long soTien = NhapSoTien();
                if (trans.RutTien(stk, pin, soTien)){
                    cout << "[THANH CONG] Da rut " <<  soTien 
                    << " VND tu tai khoan " << stk
                    << ". So du con lai: " << tk->getSoDu() << "VND" << endl;
    
                    SaveAllData(*(trans.getBankSystem()));
                    break;
                } else{
                    cout << "[LOI] So du khong du de rut!" << endl;
                }
                 
                cout << "Ban co muon thu lai khong? (Nhap so bat ky de TIEP TUC, go 0 de HUY): ";
                long long retry; cin >> retry;
                if (retry == 0) { 
                    cout << "Da huy thao tac." << endl; 
                    break; 
                }
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

            while (true) {
                string stkNhan;
                cout << "Nhap STK nhan: "; cin >> stkNhan;

                if (stk == stkNhan) {
                    cout << "[LOI] Khong the chuyen khoan cho chinh minh!" << endl;
                    cout << "Ban co muon thu lai khong? (Nhap so bat ky de TIEP TUC, go 0 de HUY): ";
                    long long retry; cin >> retry;
                    if (retry == 0) { cout << "--> Da huy thao tac chuyen khoan." << endl; break; }
                    continue; 
                }

                if (trans.getBankSystem()->timKiemTaiKhoan(stkNhan) == NULL) {
                    cout << "[LOI] Khong tim thay tai khoan nhan " << stkNhan << "!" << endl;
                    cout << "Ban co muon thu lai khong? (Nhap so bat ky de TIEP TUC, go 0 de HUY): ";
                    long long retry; cin >> retry;
                    if (retry == 0) { cout << "--> Da huy thao tac chuyen khoan." << endl; break; }
                    continue; 
                }

                cout << "So du hien tai: " << tk->getSoDu() << " VND" << endl;
                cout << "Nhap so tien chuyen: ";
                long long soTien = NhapSoTien();

                if (trans.ChuyenKhoan(stk, pin, stkNhan, soTien)) {
                    cout << "[THANH CONG] Da chuyen " << soTien
                    << " VND tu " << stk << " den " << stkNhan
                    << ". So du con lai TK gui: " << tk->getSoDu() << "VND" << endl;
    
                    SaveAllData(*(trans.getBankSystem()));
                    break; 
                } else {
                    cout << "[LOI] So du tai khoan " << stk << " khong du de chuyen!" << endl;
                }
                
                cout << "Ban co muon thu lai khong? (Nhap so bat ky de TIEP TUC, go 0 de HUY): ";
                long long retry; cin >> retry;
                if (retry == 0) { cout << "--> Da huy thao tac chuyen khoan." << endl; break; }
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
            while (true) {
                cout << "Nhap ngay bat dau (dd/mm/yyyy): "; cin >> tuNgay;
                if (!BankSystem::kiemTraNgayHopLe(tuNgay)) {
                    cout << "[LOI] Dinh dang ngay khong ton tai tren lich! Vui long nhap lai." << endl;
                } else break;
            }
            
            while (true) {
                cout << "Nhap ngay ket thuc (dd/mm/yyyy): "; cin >> denNgay;
                if (!BankSystem::kiemTraNgayHopLe(denNgay)) {
                    cout << "[LOI] Dinh dang ngay khong ton tai tren lich! Vui long nhap lai." << endl;
                } else break;
            }
            // Ép sang số nguyên để so sánh (YYYYMMDD)
            int start = report.ChuyenNgaySangInt(tuNgay); 
            int end = report.ChuyenNgaySangInt(denNgay);
            int now = report.ChuyenNgaySangInt(report.LayNgayHienTai()); 

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
            
            string ngayHienTai = report.LayNgayHienTai();
            int dNow, mNow, yNow;
            sscanf(ngayHienTai.c_str(), "%d/%d/%d", &dNow, &mNow, &yNow);
            
            double tongLaiThangNay = report.TinhLaiThang(stk, 4.0, mNow, yNow);
            
            if (tongLaiThangNay == -2) {
                cout << "\n[THONG BAO] Thang " << mNow << "/" << yNow << " da duoc chot lai truoc do!" << endl;
            } else if (tongLaiThangNay == 0.0) {
                cout << "[THONG BAO] Trong thang " << mNow << "/" << yNow << ", tai khoan chua hoat dong!" << endl;
            } else if (tongLaiThangNay > 0.0) {
                Account* tk = bank.timKiemTaiKhoan(stk);
                
                int dMo, mMo, yMo; 
                sscanf(tk->getNgayMo().c_str(), "%d/%d/%d", &dMo, &mMo, &yMo);
                
                int soNgayTinhLai = 0;
                if (mMo == mNow && yMo == yNow) {
                    soNgayTinhLai = dNow - dMo + 1;
                } else {
                    soNgayTinhLai = dNow;
                }

                cout << "\n========================================" << endl;
                cout << " BANG TINH LAI SUAT CHI TIET (" << mNow << "/" << yNow << ")" << endl;
                cout << "========================================" << endl;
                cout << "Tai khoan    : " << stk << endl;
                cout << "Lai suat     : " << (long long)4.0 << "% / nam" << endl;
                cout << "----------------------------------------" << endl;
                cout << "So ngay tinh lai hop le: " << soNgayTinhLai << " ngay" << endl;
                cout << "Tien lai TAM TINH: " << (long long)tongLaiThangNay << " VND" << endl;
                cout << "----------------------------------------" << endl;
                cout << "Tong lai da chot cac thang truoc: " << report.TinhTongLaiDaCong(stk) << " VND" << endl;
                cout << "So du hien tai (Chua gom lai tam tinh): " << tk->getSoDu() << " VND" << endl;
                cout << "========================================" << endl;
            }
            break;
        }
        default:
            cout << "Lua chon khong hop le!" << endl;
    }
    DungManHinh();
}