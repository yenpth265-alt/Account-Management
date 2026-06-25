#include "test_runner.h"
#include <iostream>
using namespace std;

void test_HopDen(){

    // TC 1
    kiemTra("TC1 - CCCD thieu so (5 chu so)", 
            BankSystem::kiemTraCCCDHopLe("12345"), false);
    kiemTra("TC1 - CCCD thua so (16 chu so)", 
            BankSystem::kiemTraCCCDHopLe("1234567890987654"), false);
    kiemTra("TC1 - CCCD dung 12 chu so (hop le)", 
            BankSystem::kiemTraCCCDHopLe("123456789012"), true);

    // TC 2
    kiemTra("TC2 - SDT chua ky tu chu (q535xxxx)", 
            BankSystem::kiemTraSDTHopLe("q535xxxx0"), false);
    kiemTra("TC2 - SDT hop le (10 so, bat dau bang 0)", 
            BankSystem::kiemTraSDTHopLe("0918273645"), true);

    // TC 3
    kiemTra("TC3 - PIN do dai khac 4 (12334)", 
            BankSystem::kiemTraPINHopLe("12334"), false);
    kiemTra("TC3 - PIN chua chu (qu123 - that ra 6 ky tu, van fail do do dai)", 
            BankSystem::kiemTraPINHopLe("qu123"), false);
    kiemTra("TC3 - PIN chua chu, dung 4 ky tu (ab12)", 
            BankSystem::kiemTraPINHopLe("ab12"), false);
    kiemTra("TC3 - PIN hop le (1234)", 
            BankSystem::kiemTraPINHopLe("1234"), true);

    // TC 4
    {
        BankSystem bankTam;
        ReportLogic report(&bankTam); // chi dung de goi ham ChuyenNgaySangInt (khong can BankSystem thuc)
        int ngayHienTaiInt = report.ChuyenNgaySangInt("19/06/2026");
        int ngayKetThucInt = report.ChuyenNgaySangInt("30/06/2026");
        bool laTuongLai = (ngayKetThucInt > ngayHienTaiInt);
        kiemTra("TC4 - Sao ke: Phat hien ngay ket thuc la tuong lai", laTuongLai, true);
    }

    // TC 5
    kiemTra("TC5 - Ngay khong ton tai (12/30/2020 - thang 30 sai)", 
            BankSystem::kiemTraNgayHopLe("12/30/2020"), false);
    kiemTra("TC5 - Ngay khong ton tai (48/06/2021 - ngay 48 sai)", 
            BankSystem::kiemTraNgayHopLe("48/06/2021"), false);
    kiemTra("TC5 - Ngay hop le (30/06/2026)", 
            BankSystem::kiemTraNgayHopLe("30/06/2026"), true);
    kiemTra("TC5 - Ngay 29/02 nam nhuan (2024) hop le", 
            BankSystem::kiemTraNgayHopLe("29/02/2024"), true);
    kiemTra("TC5 - Ngay 29/02 nam khong nhuan (2025) khong hop le", 
            BankSystem::kiemTraNgayHopLe("29/02/2025"), false);

    // TC 6
    kiemTra("TC6 - SDT chua ky tu chu (q535)", 
            BankSystem::kiemTraSDTHopLe("q535"), false);

    // TC 7
    kiemTra("TC7 - SDT bat dau bang so 9 (khong phai 0)", 
            BankSystem::kiemTraSDTHopLe("9087657543"), false);

    // TC 8
    kiemTra("TC8 - SDT ngan hon quy chuan (8676)", 
            BankSystem::kiemTraSDTHopLe("8676"), false);
}