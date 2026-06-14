# include <iostream>
# include "utils/UI.h"
# include "utils/fileManager.h
# include "include/services/BankSystem.h"
# include "include/services/TransactionLogic.h"

using namespace std;
int main(){
  // Khởi tạo đối tượng
  BankSystem bank;
  TransactionLogic trans(&bank);

  // Nạp dữ liệu từ file vào hệ thống
  LoadAllData(bank);

  // Chạy giao diện
  MenuChinh(bank, trans);

  // Lưu dữ liệu lại vào file
  SaveAllData(bank);

  return 0;
}
  
