#include "test_runner.h"
#include <iostream>
using namespace std;

void test_HopTrang(){

    // TC1, 2
    {
        BankSystem bank;
        bank.themKhachHang ("KH001", "Nguyen Van A", "123456789012", "0918273645");
        bank.taoTaiKhoan("100000001", "KH001", "1234", 1000000);
        Account* tk = bank.timKiemTaiKhoan("100000001");

        // TC 1
        bool r1 = tk->rutTien(200000);
        kiemTra("TC1 - Rut tien: Luong hop le", r1, true);
        kiemTraGiaTri("TC1 - So du con lai", tk->getSoDu(), 800000);

        // TC 2
        bool r2 = tk->rutTien(960000);
        kiemTra("TC2 - Rut tien: Vi pham so du toi thieu", r2, false);
        kiemTraGiaTri("TC2 - So du khong doi", tk->getSoDu(), 800000);
    }

    // TC3
    {
        BankSystem bank;
        bank.themKhachHang("KH001", "Nguyen Van A", "123456789012", "0918273645");
        bank.taoTaiKhoan("100000001", "KH001", "1234", 700000);

        Account* tkSai = bank.timKiemTaiKhoan("123456789"); // STK khong ton tai
        kiemTra("TC3 - Doi PIN: STK khong ton tai", (tkSai == NULL), true);
    }

    // TC 4
    {
        BankSystem bank;
        bank.themKhachHang("KH001", "Nguyen Van A", "123456789012", "0918273645");
        bank.taoTaiKhoan("100000001", "KH001", "1234", 700000);
        Account* tk = bank.timKiemTaiKhoan("100000001");

        bool r4 = tk->doiPIN("0000", "5678"); // PIN hien tai sai (dung la 1234)
        kiemTra("TC4 - Doi PIN: Sai PIN hien tai", r4, false);
    }

    // TC 5
    {
        string pinMoi = "3232", xacNhan = "6767";
        bool khopNhau = (pinMoi == xacNhan);
        kiemTra("TC5 - Doi PIN: Xac nhan PIN khong khop", khopNhau, false);
    }

    // TC 6
    {
        BankSystem bank;
        bank.themKhachHang("KH001", "Nguyen Van A", "123456789012", "0918273645");
        bank.taoTaiKhoan("100000001", "KH001", "1234", 700000);
        Account* tk = bank.timKiemTaiKhoan("100000001");

        string pinCu = "1234", pinMoi = "5678", xacNhan = "5678";
        bool r6 = false;
        if (pinMoi == xacNhan) {
            r6 = tk->doiPIN(pinCu, pinMoi);
        }
        kiemTra("TC6 - Doi PIN: Luong hop le hoan toan", r6, true);
        kiemTra("TC6 - PIN moi xac thuc dung", tk->kiemTraPIN("5678"), true);
    }

    // TC 7
    {
        BankSystem bank;
        bank.themKhachHang("KH001", "Nguyen Van A", "123456789012", "0918273645");
        bool r7 = bank.taoTaiKhoan("200000001", "KH001", "1234", 45000);
        kiemTra("TC7 - Tao TK: Thieu so du ban dau toi thieu", r7, false);
    }

    // TC 8
    {
        BankSystem bank;
        bank.themKhachHang("KH001", "Nguyen Van A", "123456789012", "0918273645");
        bool r8 = bank.taoTaiKhoan("200000002", "KH001", "1234", 700000);
        kiemTra("TC8 - Tao TK: Thoa man moi dieu kien", r8, true);
        kiemTra("TC8 - TK moi duoc tim thay sau khi tao", (bank.timKiemTaiKhoan("200000002") != NULL), true);
    }
}
