# include <iostream>
# include <fstream>
# include <sstream>
# include <string>


# include "../../include/utils/fileManager.h"

using namespace std;
// Tach chuoi bang dau |
string getNextToken(stringstream& ss){
    string token;
    getline(ss,token, '|');
    return token;
}

void LoadAllData (BankSystem& bank){
    string dummyLine; // biến tạm chứa dòng tiêu đề
    string line;

    // Doc khach hang
    ifstream fileKH("data/customers.txt");
    if (!fileKH.is_open()) {
        cout << "[CANH BAO] Khong tim thay file data/customers.txt. Bat dau voi du lieu trong." << endl;
    } else {
        getline(fileKH, dummyLine); // bỏ dòng tiêu đề
        while (getline(fileKH, line)) {
            if (line.empty()) continue;
            stringstream ss(line);
            string maKH  = getNextToken(ss);
            string hoTen = getNextToken(ss);
            string cccd  = getNextToken(ss);
            string sdt   = getNextToken(ss);
            bank.themKhachHang(maKH, hoTen, cccd, sdt);
        }
        fileKH.close();
    }

    //Doc tai khoan
    ifstream fileTK("data/accounts.txt");
    if (!fileTK.is_open()) {
        cout << "[CANH BAO] Khong tim thay file data/accounts.txt. Bat dau voi du lieu trong." << endl;
    } else {
        getline(fileTK, dummyLine);
        while (getline(fileTK, line)) {
            if (line.empty()) continue;
            stringstream ss(line);
            string soTK  = getNextToken(ss);
            string maKH  = getNextToken(ss);
            string maPIN = getNextToken(ss);
            long long soDu  = stoll(getNextToken(ss));
            string ngayMo = getNextToken(ss);
            bank.naptaiKhoanTuFile(soTK, maKH, maPIN, soDu, ngayMo);
        }
        fileTK.close();
    }

    //Doc giao dich
    ifstream fileGD("data/transactions.txt");
    if (!fileGD.is_open()) {
        cout << "[CANH BAO] Khong tim thay file data/transactions.txt. Bat dau voi du lieu trong." << endl;
    } else {
        getline(fileGD, dummyLine);
        while (getline(fileGD, line)) {
            if (line.empty()) continue;
            stringstream ss(line);
            string maGD     = getNextToken(ss);
            string thoiGian = getNextToken(ss);
            string loaiGD   = getNextToken(ss);
            long long soTien   = stoll(getNextToken(ss));
            string soTKGui  = getNextToken(ss);
            string soTKNhan = getNextToken(ss);
            Transaction gd(maGD, thoiGian, loaiGD, soTien, soTKGui, soTKNhan);
            bank.getDanhSachGD().addTail(gd);
        }
        fileGD.close();
    }
}

void SaveAllData(BankSystem& bank) {
    // Lưu khách hàng
    ofstream fileKH("data/customers.txt");
    if (!fileKH.is_open()) {
        cout << "[LOI] Khong the ghi file data/customers.txt!" << endl;
    } else {
        fileKH << "maKH|hoTen|cccd|sdt" << endl; 
        Node<Customer>* currKH = bank.getDanhSachKH().getHead();
        while (currKH != NULL) {
            fileKH << currKH->data.getMaKH()  << "|"
                   << currKH->data.getHoTen() << "|"
                   << currKH->data.getCCCD()  << "|"
                   << currKH->data.getSDT()   << endl;
            currKH = currKH->next;
        }
        fileKH.close();
    }

    // Lưu tài khoản
    ofstream fileTK("data/accounts.txt");
    if (!fileTK.is_open()) {
        cout << "[LOI] Khong the ghi data/accounts.txt!" << endl;
    } else {
        fileTK << "soTK|maKH|maPIN|soDu|ngayMo" << endl;
        Node<Account>* currTK = bank.getDanhSachTK().getHead();
        while (currTK != NULL) {
            fileTK << currTK->data.getSoTK()   << "|"
                   << currTK->data.getMaKH()   << "|"
                   << currTK->data.maPIN        << "|"  // friend access
                   << currTK->data.getSoDu()   << "|"  
                   << currTK->data.getNgayMo() << endl;
            currTK = currTK->next;
        }
        fileTK.close();
    }

    // LLưu giao dịch
    ofstream fileGD("data/transactions.txt");
    if (!fileGD.is_open()) {
        cout << "[LOI] Khong the ghi file data/transactions.txt!" << endl;
    } else {
        fileGD << "maGD|thoiGian|loaiGD|soTien|soTKGui|soTKNhan" << endl;
        Node<Transaction>* currGD = bank.getDanhSachGD().getHead();
        while (currGD != NULL) {
            fileGD << currGD->data.getMaGD()    << "|"
                   << currGD->data.getThoiGian()<< "|"
                   << currGD->data.getLoaiGD()  << "|"
                   << currGD->data.getSoTien()  << "|"
                   << currGD->data.getSoTKGui() << "|"
                   << currGD->data.getSoTKNhan()<< endl;
            currGD = currGD->next;
        }
        fileGD.close();
    }
}