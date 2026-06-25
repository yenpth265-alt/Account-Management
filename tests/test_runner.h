#ifndef TEST_RUNNER_H
#define TEST_RUNNER_H
#include <string>
#include "../include/services/BankSystem.h"
#include "../include/services/TransactionLogic.h"
#include "../include/services/ReportLogic.h"

using namespace std;

// bộ đếm kq toàn cục
extern int soTestDat;
extern int soTestFail;

// kiểm tra dùng chung
void kiemTra (const string& tenTC, bool thucTe, bool mongDoi);
void kiemTraGiaTri (const string& tenTC, long long thucTe, long long mongDoi);
void kiemTraChuoi (const string& tenTC, const string& thucTe, const string& mongDoi);

void test_HopTrang();
void test_LoTrinh();
void test_HopXam();
void test_HopDen();

#endif