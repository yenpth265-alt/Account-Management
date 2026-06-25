#include <iostream>
#include "test_runner.h"
using namespace std;

int soTestDat = 0;
int soTestFail = 0;

void kiemTra(const string& tenTC, bool thucTe, bool mongDoi) {
    if (thucTe == mongDoi) {
        cout << "[DAT]  " << tenTC << endl;
        soTestDat++;
    } else {
        cout << "[FAIL] " << tenTC
             << "  (mong doi=" << mongDoi << ", thuc te=" << thucTe << ")" << endl;
        soTestFail++;
    }
}

void kiemTraGiaTri(const string& tenTC, long long thucTe, long long mongDoi) {
    if (thucTe == mongDoi) {
        cout << "[DAT]  " << tenTC << " (= " << thucTe << ")" << endl;
        soTestDat++;
    } else {
        cout << "[FAIL] " << tenTC
             << "  (mong doi=" << mongDoi << ", thuc te=" << thucTe << ")" << endl;
        soTestFail++;
    }
}

void kiemTraChuoi(const string& tenTC, const string& thucTe, const string& mongDoi) {
    if (thucTe == mongDoi) {
        cout << "[DAT]  " << tenTC << endl;
        soTestDat++;
    } else {
        cout << "[FAIL] " << tenTC
             << "  (mong doi=\"" << mongDoi << "\", thuc te=\"" << thucTe << "\")" << endl;
        soTestFail++;
    }
}

int main(){
    test_HopTrang();
    test_LoTrinh();
    test_HopXam();
    test_HopDen();

    cout << "\n=================================================" << endl;
    cout << "                KET QUA TONG HOP                  " << endl;
    cout << "=================================================" << endl;
    cout << "Tong so test case : " << (soTestDat + soTestFail) << endl;
    cout << "So test DAT       : " << soTestDat << endl;
    cout << "So test FAIL      : " << soTestFail << endl;
    cout << "Ty le thanh cong  : "
         << (100.0 * soTestDat / (soTestDat + soTestFail)) << "%" << endl;
    cout << "=================================================" << endl;

    return (soTestFail == 0) ? 0 : 1;
}