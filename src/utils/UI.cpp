# include "../../include/utils/UI.h"
# include "../../include/utils/fileManager.h"
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

void MenuChinh(BankSystem& bank, TransactionLogic& trans){
    int luaChon;
    do {
        XoaManHinh();
        cout << "=== HE THONG QUAN LY NGAN HANG ===" << endl;
        cout << "1. Quan ly Khach hang & Tai khoan" << endl;
        cout << "2. Giao dich (Nap/Rut/Chuyen khoan)" << endl;
        cout << "3. Bao cao & Sao ke" << endl;
        cout << "0. Thoat chuong trinh" << endl;
        cout << "Nhap lua chon: ";
        cin >> luaChon;

        switch(luaChon) {
            case 1: MenuQuanLy(bank); break;
            case 2: MenuGiaoDich(trans); break;
            case 3: MenuBaoCao(bank); break;
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

    switch(chon) {
        case 1: // Nạp tiền
            cout << "Nhap STK: "; cin >> stk;
            cout << "Nhap so tien: "; soTien = NhapSoTien();
            trans.NapTien(stk, soTien);
            break;

        case 2: // Rút tiền
            cout << "Nhap STK: "; cin >> stk;
            cout << "Nhap ma PIN: "; cin >> pin;
            cout << "Nhap so tien: "; soTien = NhapSoTien();
            trans.RutTien(stk, pin, soTien);
            break;

        case 3: // Chuyển khoản
            cout << "Nhap STK gui: "; cin >> stk;
            cout << "Nhap ma PIN: "; cin >> pin;
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
void MenuBaoCao(BankSystem& bank) {
    XoaManHinh();
    cout << "=== BAO CAO GIAO DICH ===" << endl;
    cout << "1. Xem toan bo lich su giao dich" << endl;
    cout << "2. Sao ke mot tai khoan" << endl;
    cout << "Nhap lua chon: ";
    int chon; cin >> chon;

    if (chon == 1) {
        // Duyệt danh sách giao dịch
        Node<Transaction>* curr = bank.getDanhSachGD().getHead();
        if (curr == NULL) cout << "Chua co giao dich nao!" << endl;
        while (curr != NULL) {
            curr->data.xuatThongTin();
            curr = curr->next;
        }
    } 
    else if (chon == 2) {
        string stk;
        cout << "Nhap STK can sao ke: "; cin >> stk;
        Node<Transaction>* curr = bank.getDanhSachGD().getHead();
        bool found = false;
        while (curr != NULL) {
            // Kiểm tra nếu giao dịch liên quan đến STK đó
            if (curr->data.getSoTKGui() == stk || curr->data.getSoTKNhan() == stk) {
                curr->data.xuatThongTin();
                found = true;
            }
            curr = curr->next;
        }
        if (!found) cout << "Tai khoan khong co giao dich nao!" << endl;
    }
    DungManHinh();
}