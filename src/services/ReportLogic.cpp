#include "../../include/services/ReportLogic.h"
#include <iostream>
#include <ctime>
#include <cstdio>

using namespace std;

ReportLogic::ReportLogic(BankSystem* bank){
    this->bankSystem = bank;
}

string ReportLogic::LayNgayHienTai() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    char buf[20];
    sprintf(buf, "%02d/%02d/%04d", ltm->tm_mday, 1 + ltm->tm_mon, 1900 + ltm->tm_year);
    return string(buf);
}

int ReportLogic::ChuyenNgaySangInt(const string& ngay) {
    int d, m, y;
    sscanf(ngay.c_str(), "%d/%d/%d", &d, &m, &y);
    return y * 10000 + m * 100 + d;
}

// Hàm phụ: Lấy số ngày của một tháng bất kỳ (có tính năm nhuận)
static int LaySoNgayTrongThang(int thang, int nam) {
    switch(thang) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12: return 31;
        case 4: case 6: case 9: case 11: return 30;
        case 2: 
            if ((nam % 4 == 0 && nam % 100 != 0) || (nam % 400 == 0)) return 29;
            return 28;
        default: return 0;
    }
}

// Kiểm tra xem tháng này đã được chốt lãi chưa
static bool DaTinhLaiThang(LinkedList<Transaction>& dsGD, const string& soTK, int thang, int nam) {
    Node<Transaction>* curr = dsGD.getHead();
    while (curr != NULL) {
        if (curr->data.getLoaiGD() == "LAI" && curr->data.getSoTKNhan() == soTK) {
            string tg = curr->data.getThoiGian().substr(0, 10);
            int d, m, y;
            sscanf(tg.c_str(), "%d/%d/%d", &d, &m, &y);
            if (m == thang && y == nam) return true;
        }
        curr = curr->next;
    }
    return false;
}

// Tính tổng tiền lãi từ lúc mở tài khoản
static long long TinhTongLaiDaCong(LinkedList<Transaction>& dsGD, const string& soTK) {
    long long tong = 0;
    Node<Transaction>* curr = dsGD.getHead();
    while (curr != NULL) {
        if (curr->data.getLoaiGD() == "LAI" && curr->data.getSoTKNhan() == soTK)
            tong += curr->data.getSoTien();
        curr = curr->next;
    }
    return tong;
}

// Tính số dư cuối ngày bằng cách đảo ngược thời gian từ hiện tại về quá khứ.
// Dùng double ở đây vì là phép tính trung gian — kết quả trả về long long.
static long long TinhSoDuCuoiNgay(Account* tk, LinkedList<Transaction>& dsGD, int d, int m, int y) {
    int ngayMucTieu = y * 10000 + m * 100 + d;
    double soDu = (double)tk->getSoDu(); // Bắt đầu từ số dư hiện tại
    string soTK = tk->getSoTK();

    Node<Transaction>* curr = dsGD.getHead();
    while (curr != NULL) {
        string tg = curr->data.getThoiGian().substr(0, 10);
        int dGD, mGD, yGD;
        sscanf(tg.c_str(), "%d/%d/%d", &dGD, &mGD, &yGD);
        int ngayGD = yGD * 10000 + mGD * 100 + dGD;

        // Nếu giao dịch diễn ra SAU ngày mục tiêu -> Trừ ngược lại để tìm số dư của quá khứ
        if (ngayGD > ngayMucTieu) {
            string loai = curr->data.getLoaiGD();
            long long soTien = curr->data.getSoTien();
            string tkGui = curr->data.getSoTKGui();
            string tkNhan = curr->data.getSoTKNhan();

            if (loai == "NAP" && tkGui == soTK) soDu -= soTien;
            else if (loai == "RUT" && tkGui == soTK) soDu += soTien;
            else if (loai == "CHUYEN_KHOAN") {
                if (tkGui == soTK) soDu += soTien;
                if (tkNhan == soTK) soDu -= soTien;
            }
            else if (loai == "LAI" && tkNhan == soTK) soDu -= soTien;
        }
        curr = curr->next;
    }
    if (soDu < 0) soDu = 0;
    return (long long)soDu;
}

// -------------------------------------------------------
// XEM LỊCH SỬ VÀ SAO KÊ 
// -------------------------------------------------------
void ReportLogic::XemLichSuTheoTK(string soTK){
    Account* tk = this->bankSystem->timKiemTaiKhoan(soTK);
    if (tk == NULL) return;
    LinkedList<Transaction>& dsGD = this->bankSystem->getDanhSachGD();
    int soGD = 0;
    Node<Transaction>* curr = dsGD.getHead();
    while (curr != NULL){
        if (curr->data.getSoTKGui() == soTK || curr->data.getSoTKNhan() == soTK){
            curr->data.xuatThongTin();
            soGD++;
        }
        curr = curr->next;
    }
    if (soGD == 0) cout << "Tai khoan nay chua co giao dich nao." << endl;
}

void ReportLogic::XemSaoKe(string soTK){
    Account* tk = this->bankSystem->timKiemTaiKhoan(soTK);
    if (tk == NULL){ cout << "[LOI] Khong tim thay tai khoan " << soTK << endl; return; }
    cout << "========================================" << endl;
    cout << "       SAO KE TAI KHOAN: " << soTK        << endl;
    cout << "========================================" << endl;
    tk->xuatThongTin();
    cout << "\nChi tiet giao dich:" << endl;
    XemLichSuTheoTK(soTK);
    cout << "========================================" << endl;
}

void ReportLogic::XemSaoKeTheoKhoangThoiGian(string soTK, string tuNgay, string denNgay) {
    Account* tk = this->bankSystem->timKiemTaiKhoan(soTK);
    if (tk == NULL) return;
    LinkedList<Transaction>& dsGD = this->bankSystem->getDanhSachGD();
    int start = ChuyenNgaySangInt(tuNgay);
    int end   = ChuyenNgaySangInt(denNgay);
    bool co   = false;

    cout << "========================================" << endl;
    cout << "  SAO KE TU " << tuNgay << " DEN " << denNgay << endl;
    cout << "========================================" << endl;

    Node<Transaction>* curr = dsGD.getHead();
    while (curr != NULL) {
        string ngayGD = curr->data.getThoiGian().substr(0, 10);
        int dateInt = ChuyenNgaySangInt(ngayGD);
        if ((curr->data.getSoTKGui() == soTK || curr->data.getSoTKNhan() == soTK) && dateInt >= start && dateInt <= end) {
            curr->data.xuatThongTin();
            co = true;
        }
        curr = curr->next;
    }
    if (!co) cout << "Khong co giao dich nao trong khoang thoi gian nay." << endl;
    cout << "========================================" << endl;
}

// -------------------------------------------------------
// TÍNH LÃI CỘNG DỒN THEO NGÀY (4%/Năm)
// -------------------------------------------------------
double ReportLogic::TinhLaiThang(string soTK, double laiSuatNamPhanTram, int thangXem, int namXem) {
    Account* tk = this->bankSystem->timKiemTaiKhoan(soTK);
    if (tk == NULL) return 0;

    string ngayHienTai = LayNgayHienTai();
    int dNow, mNow, yNow; 
    sscanf(ngayHienTai.c_str(), "%d/%d/%d", &dNow, &mNow, &yNow);

    if (thangXem == 0) { thangXem = mNow; namXem = yNow; }

    int dMo, mMo, yMo; 
    sscanf(tk->getNgayMo().c_str(), "%d/%d/%d", &dMo, &mMo, &yMo);
    int ngayMoInt = yMo * 10000 + mMo * 100 + dMo;
    int ngayNayInt = yNow * 10000 + mNow * 100 + dNow;
    
    LinkedList<Transaction>& dsGD = this->bankSystem->getDanhSachGD();
    
    // Kiểm tra xem đã chốt lãi tháng này chưa
    if (DaTinhLaiThang(dsGD, soTK, thangXem, namXem)) {
        cout << "\n[THONG BAO] Thang " << thangXem << "/" << namXem << " da duoc chot lai truoc do!" << endl;
        return 0; 
    }

    int soNgayTrongThang = LaySoNgayTrongThang(thangXem, namXem);
    double tongLaiThangNay = 0.0;
    int soNgayTinhLai = 0;
    
    cout << "\n========================================" << endl;
    cout << " BANG TINH LAI SUAT CHI TIET (" << thangXem << "/" << namXem << ")" << endl;
    cout << "========================================" << endl;
    cout << "Tai khoan    : " << soTK << endl;
    cout << "Lai suat     : " << (long long)laiSuatNamPhanTram << "% / nam" << endl;
    cout << "----------------------------------------" << endl;

    // VÒNG LẶP QUÉT QUA TỪNG NGÀY TRONG THÁNG
    for (int d = 1; d <= soNgayTrongThang; ++d) {
        int loopDate = namXem * 10000 + thangXem * 100 + d;
        
        // Chỉ tính lãi cho những ngày từ lúc mở tài khoản đến hiện tại
        if (loopDate >= ngayMoInt && loopDate <= ngayNayInt) {
            long long soDuCuoiNgay = TinhSoDuCuoiNgay(tk, dsGD, d, thangXem, namXem);
            // Công thức: Lãi 1 ngày = (Số dư * 4%) / 365
            double laiNgay = (soDuCuoiNgay * (laiSuatNamPhanTram / 100.0)) / 365.0;
            tongLaiThangNay += laiNgay;
            soNgayTinhLai++;
        }
    }

    if (soNgayTinhLai == 0) {
        cout << "[THONG BAO] Trong thang " << thangXem << "/" << namXem << ", tai khoan chua hoat dong!" << endl;
        return 0;
    }

    cout << "So ngay tinh lai hop le: " << soNgayTinhLai << " ngay" << endl;
    
    //  đây là lãi Tạm Tính, chưa được cộng
    cout << "Tien lai TAM TINH: " << (long long)tongLaiThangNay << " VND" << endl;

    // Vẫn tính tổng lãi của các tháng trước (nếu có)
    long long tongLaiTatCa = TinhTongLaiDaCong(dsGD, soTK);

    cout << "----------------------------------------" << endl;
    cout << "Tong lai da chot cac thang truoc: " << tongLaiTatCa << " VND" << endl;
    cout << "So du hien tai (Chua gom lai tam tinh): " << tk->getSoDu() << " VND" << endl;
    cout << "========================================" << endl;

    return tongLaiThangNay;
}
// -------------------------------------------------------
// TỰ ĐỘNG CHỐT LÃI KHI SANG THÁNG MỚI
// -------------------------------------------------------
void ReportLogic::TuDongChotLaiHangThang() {
    string ngayHienTai = LayNgayHienTai();
    int dNow, mNow, yNow;
    sscanf(ngayHienTai.c_str(), "%d/%d/%d", &dNow, &mNow, &yNow);
    int thangNayInt = yNow * 100 + mNow; // Ví dụ: 202606

    LinkedList<Transaction>& dsGD = this->bankSystem->getDanhSachGD();
    Node<Account>* currTK = this->bankSystem->getDanhSachTK().getHead();

    int soTKTKDuocCong = 0;
    long long tongTienCong = 0;

    // Quét toàn bộ tài khoản trong hệ thống
    while (currTK != NULL) {
        Account* tk = &(currTK->data);
        string soTK = tk->getSoTK();

        int dMo, mMo, yMo;
        sscanf(tk->getNgayMo().c_str(), "%d/%d/%d", &dMo, &mMo, &yMo);

        int yLoop = yMo;
        int mLoop = mMo;

        // Vòng lặp kiểm tra từ tháng mở tài khoản đến TRƯỚC tháng hiện tại
        while (true) {
            int thangLoopInt = yLoop * 100 + mLoop;
            if (thangLoopInt >= thangNayInt) break; // Chỉ tính cho các tháng đã qua

            // Nếu tháng này chưa được cộng lãi -> Tính và cộng ngay!
            if (!DaTinhLaiThang(dsGD, soTK, mLoop, yLoop)) {
                int soNgay = LaySoNgayTrongThang(mLoop, yLoop);
                double tongLai = 0.0; // double trung gian để cộng phần lẻ
                int ngayMoInt = yMo * 10000 + mMo * 100 + dMo;

                for (int d = 1; d <= soNgay; ++d) {
                    int loopDate = yLoop * 10000 + mLoop * 100 + d;
                    
                    if (loopDate >= ngayMoInt) {
                        long long soDuNgay = TinhSoDuCuoiNgay(tk, dsGD, d, mLoop, yLoop);
                        tongLai += (soDuNgay * (4.0 / 100.0)) / 365.0; // Mặc định 4%/năm
                    }
                }

                // Cộng tiền và ghi lịch sử giao dịch (chốt vào ngày cuối cùng của tháng đó)
                if (tongLai > 0) {
                    tk->napTien((long long)tongLai);
                    
                    int soGD = dsGD.getSize() + 1;
                    string maGD = Transaction::sinhMaGD(soGD);
                    char buf[30];
                    sprintf(buf, "%02d/%02d/%04d 23:59", soNgay, mLoop, yLoop); 
                    Transaction gdLai(maGD, string(buf), "LAI", (long long)tongLai, "NGAN_HANG", soTK);
                    dsGD.addTail(gdLai);

                    soTKTKDuocCong++;
                    tongTienCong += (long long)tongLai;
                }
            }
            
            // Tăng lên tháng tiếp theo
            mLoop++;
            if (mLoop > 12) { mLoop = 1; yLoop++; }
        }
        currTK = currTK->next;
    }

    // Nếu có cộng lãi cho ai đó, in ra một thông báo nhỏ lúc bật app
    if (soTKTKDuocCong > 0) {
        cout << "[HE THONG] Phat hien " << soTKTKDuocCong << " tai khoan chua duoc chot lai cac thang truoc." << endl;
        cout << "[HE THONG] Da tu dong quet va cong tong cong " <<(long long)tongTienCong << " VND tien lai vao cac tai khoan!" << endl;
        cout << "----------------------------------------" << endl;
    }
}