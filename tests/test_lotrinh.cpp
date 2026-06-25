#include "test_runner.h"
#include <iostream>
 using namespace std;

 void test_LoTrinh(){

    // TC 1
    {
        BankSystem bank;
        TransactionLogic trans(&bank);
        bank.themKhachHang("KH001", "Nguyen Van A", "123456789012", "0918273645");
        bank.taoTaiKhoan("100000001", "KH001", "1234", 700000);

        bool r1 = trans.ChuyenKhoan("100000001", "1234", "100000001", 100000);
        kiemTra("TC1 - Chuyen khoan: Trung tai khoan nhan", r1, false);
    }

    // TC 2
    {
        BankSystem bank;
        TransactionLogic trans(&bank);
        bank.themKhachHang("KH001", "Nguyen Van A", "123456789012", "0918273645");
        bank.themKhachHang("KH002", "Nguyen Thi B", "987654321098", "0938294756");
        bank.taoTaiKhoan("100000001", "KH001", "1234", 700000);
        bank.taoTaiKhoan("100000215", "KH002", "9090", 700000);

        bool r2 = trans.ChuyenKhoan("100000215", "9090", "100000001", 150000);
        kiemTra("TC2 - Chuyen khoan: Luong chuan", r2, true);
        kiemTraGiaTri("TC2 - So du TK gui sau chuyen", bank.timKiemTaiKhoan("100000215")->getSoDu(), 550000);
        kiemTraGiaTri("TC2 - So du TK nhan sau chuyen", bank.timKiemTaiKhoan("100000001")->getSoDu(), 850000);
    }

    // TC 3
    {
        BankSystem bank;
        ReportLogic report(&bank);
        bank.themKhachHang("KH002", "Nguyen Thi B", "987654321098", "0938294756");
        bank.naptaiKhoanTuFile("100000215", "KH002", "9090", 700000, "19/05/2026");
        // Ngay mo la thang truoc -> ky vong he thong phat hien va chot lai

        KetQuaChotLai kq = report.TuDongChotLaiHangThang();
        kiemTra("TC3 - Tu dong chot lai: Phat hien TK chua chot",
                (kq.soTKDuocCong > 0), true);
        cout << "       (So TK duoc cong: " << kq.soTKDuocCong
             << " | Tong tien cong: " << kq.tongTienCong << " VND)\n";
    }

    // TC 4
    {
        BankSystem bank;
        ReportLogic report(&bank);
        bank.themKhachHang("KH002", "Nguyen Thi B", "987654321098", "0938294756");
        bank.naptaiKhoanTuFile("100000215", "KH002", "9090", 700000, "19/05/2026");

        double laiThangTruoc = report.TinhLaiThang("100000215", 4.0, 5, 2026);
        kiemTra("TC4 - Tinh lai thang truoc: Tinh duoc gia tri > 0", (laiThangTruoc > 0), true);
        cout << "       (Tien lai tinh duoc thang 5: " << laiThangTruoc << " VND)\n";
    }

    // TC 5
    {
        BankSystem bank;
        bank.themKhachHang("KH001", "Nguyen Van A", "123456789012", "0918273645");
        bank.taoTaiKhoan("100000001", "KH001", "1234", 700000);
        Account* tk = bank.timKiemTaiKhoan("100000001");

        int soLanSai = 0;
        bool pinDung = false;
        string pinNhap[1] = {"1234"}; // nhap dung ngay lan dau
        for (int i = 0; i < 1 && !pinDung; i++) {
            if (tk->kiemTraPIN(pinNhap[i])) { pinDung = true; }
            else { soLanSai++; }
        }
        kiemTra("TC5 - Doi SDT: PIN dung ngay lan dau", pinDung, true);
        kiemTraGiaTri("TC5 - So lan sai = 0", soLanSai, 0);
    }

    // TC 6
    {
        BankSystem bank;
        bank.themKhachHang("KH001", "Nguyen Van A", "123456789012", "0918273645");
        bank.taoTaiKhoan("100000001", "KH001", "1234", 700000);
        Account* tk = bank.timKiemTaiKhoan("100000001");

        string pinNhap[3] = {"0000", "1111", "2222"}; // sai ca 3 lan
        int soLanSai = 0;
        bool pinDung = false;
        for (int i = 0; i < 3; i++) {
            if (tk->kiemTraPIN(pinNhap[i])) { pinDung = true; break; }
            soLanSai++;
        }
        kiemTra("TC6 - Doi SDT: Sai PIN 3 lan -> huy thao tac", pinDung, false);
        kiemTraGiaTri("TC6 - Vong lap chay du 3 lan", soLanSai, 3);
    }

    // TC 7
    {
        BankSystem bank;
        TransactionLogic trans(&bank);
        bank.themKhachHang("KH001", "Nguyen Van A", "123456789012", "0918273645");
        bank.taoTaiKhoan("100000001", "KH001", "1234", 700000);

        bool r7 = trans.ChuyenKhoan("100000001", "1234", "999999999", 100000);
        kiemTra("TC7 - Chuyen khoan: TK nhan khong ton tai", r7, false);
        kiemTraGiaTri("TC7 - So du TK gui khong doi", bank.timKiemTaiKhoan("100000001")->getSoDu(), 700000);
    }

    // TC 8
    {
        BankSystem bank;
        TransactionLogic trans(&bank);
        bank.themKhachHang("KH001", "Nguyen Van A", "123456789012", "0918273645");
        bank.taoTaiKhoan("100000001", "KH001", "1234", 700000);

        bool r8 = trans.NapTien("100000001", 0);
        kiemTra("TC8 - Nap tien: Ranh gioi soTien = 0", r8, false);
    }

    // TC 9
    {
        BankSystem bank;
        TransactionLogic trans(&bank);
        bank.themKhachHang("KH001", "Nguyen Van A", "123456789012", "0918273645");
        bank.taoTaiKhoan("100000001", "KH001", "1234", 1000000);

        bool r9 = trans.RutTien("100000001", "1234", 950000);
        kiemTra("TC9 - Rut tien: Ranh gioi duoi hop le", r9, true);
        kiemTraGiaTri("TC9 - So du dung 50,000 VND", bank.timKiemTaiKhoan("100000001")->getSoDu(), 50000);
    }
 }