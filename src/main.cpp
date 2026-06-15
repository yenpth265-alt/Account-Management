# include <iostream>
# include "../include/utils/UI.h"
# include "../include/utils/fileManager.h"
# include "../include/services/BankSystem.h"
# include "../include/services/TransactionLogic.h"

using namespace std;
int main(){
  // Khởi tạo đối tượng
  BankSystem bank;
  TransactionLogic trans(&bank);
  ReportLogic report(&bank);

  // Nạp dữ liệu từ file vào hệ thống
  LoadAllData(bank);

  // Đồng bộ số GD đã tạo, tránh sinh trùng mã GD
  trans.SetSoGDDaTao(bank.getDanhSachGD().getSize());

  // Chạy giao diện
  MenuChinh(bank, trans, report);

  // Lưu dữ liệu lại vào file
  SaveAllData(bank);

  return 0;
}
  