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
    // Doc khach hang
    ifstream fileKH("data/customers.txt");
    string line;
    while (getline(fileKH, line)){
        stringstream ss(line);
        string maKH = getNextToken(ss);
        string hoTen = getNextToken(ss);
        string cccd = getNextToken(ss);
        string sdt = getNextToken(ss);

        bank.themKhachHang (maKH, hoTen, cccd, sdt);
    }
    fileKH.close();

    //Doc tai khoan
    ifstream fileTK("data/accounts.txt");
    while (getline(fileTK, line)) {
        stringstream ss(line);
        string soTK = getNextToken(ss);
        string maKH = getNextToken(ss);
        string maPIN = getNextToken(ss);
        double soDu = stod(getNextToken(ss));
        string ngayMo = getNextToken(ss);
        
        bank.naptaiKhoanTuFile(soTK, maKH, maPIN, soDu, ngayMo);
    }
    fileTK.close();

    ifstream fileGD("data/transactions.txt");
    while (getline(fileGD, line)) {
        stringstream ss(line);
        string maGD     = getNextToken(ss);
        string thoiGian = getNextToken(ss);
        string loaiGD   = getNextToken(ss);
        double soTien   = stod(getNextToken(ss));
        string soTKGui  = getNextToken(ss);
        string soTKNhan = getNextToken(ss);

        Transaction gd(maGD, thoiGian, loaiGD, soTien, soTKGui, soTKNhan);
        bank.getDanhSachGD().addTail(gd);
    }
    fileGD.close();
}

void SaveAllData(BankSystem& bank) {
    // Lưu khách hàng
    ofstream fileKH("data/customers.txt");
    Node<Customer>* currKH = bank.danhSachKH.getHead(); // Cần đảm bảo quyền truy cập
    while (currKH != NULL) {
        fileKH << currKH->data.getMaKH() << "|" << currKH->data.getHoTen() << "|" 
               << currKH->data.getCCCD() << "|" << currKH->data.getSDT() << endl;
        currKH = currKH->next;
    }
    fileKH.close();

    // Lưu tài khoản
    ofstream fileTK("data/accounts.txt");
    Node<Account>* currTK = bank.getDanhSachTK().getHead();
    while (currTK != NULL) {
        fileTK << currTK->data.getSoTK() << "|" << currTK->data.getMaKH() << "|" 
               << currTK->data.getMaPIN() << "|" << currTK->data.getSoDu() << "|"
               << currTK->data.getNgayMo() << endl; 
        currTK = currTK->next;
    }
    fileTK.close();

    // LLưu giao dịch
    ofstream fileGD("data/transactions.txt");
    Node<Transaction>* currGD = bank.getDanhSachGD().getHead();
    while (currGD != NULL) {
        fileGD << currGD->data.getMaGD() << "|" << currGD->data.getThoiGian() << "|" 
               << currGD->data.getLoaiGD() << "|" << currGD->data.getSoTien() << "|" 
               << currGD->data.getSoTKGui() << "|" << currGD->data.getSoTKNhan() << endl;
        currGD = currGD->next;
    }
    fileGD.close();
}