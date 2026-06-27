# Hệ thống Quản lý Tài khoản Ngân hàng (Bank Account Management System)

Ứng dụng console quản lý khách hàng, tài khoản và giao dịch ngân hàng, được viết bằng **C++ thuần** với cấu trúc dữ liệu **LinkedList tự xây dựng** (không dùng STL) và lưu trữ dữ liệu bền vững qua **file text**.

---

## Yêu cầu hệ thống

| Thành phần | Yêu cầu |
|---|---|
| **Hệ điều hành** | Windows 10/11 (khuyến nghị), Linux, macOS |
| **Trình biên dịch** | MinGW-w64 (g++) hoặc MSVC, Clang |
| **Môi trường phát triển** | Visual Studio Code (khuyến nghị), CLion, hoặc bất kỳ IDE/editor nào hỗ trợ C++ |
| **Công cụ build** | g++ (MinGW) hoặc make |

---

## Cấu trúc thư mục

```
Account_Management/
│
├── bank_system.exe              # File thực thi (đã biên dịch sẵn)
├── generator.cpp                # File sinh dữ liệu mẫu
├── generator.exe                # File thực thi generator
├── README.md                    # Hướng dẫn (file này)
│
├── data/                        # Thư mục chứa dữ liệu
│   ├── accounts.txt             # Dữ liệu tài khoản
│   ├── customers.txt            # Dữ liệu khách hàng
│   └── transactions.txt         # Dữ liệu giao dịch
│
├── include/                     # Thư mục chứa file header (.h)
│   ├── data_structures/
│   │   └── linkedList.h         # LinkedList<T> template
│   ├── models/
│   │   ├── account.h            # Lớp Account
│   │   ├── customer.h           # Lớp Customer
│   │   └── transaction.h        # Lớp Transaction
│   ├── services/
│   │   ├── BankSystem.h         # Lớp BankSystem
│   │   ├── ReportLogic.h        # Lớp ReportLogic
│   │   └── TransactionLogic.h   # Lớp TransactionLogic
│   └── utils/
│       ├── fileManager.h        # Đọc/ghi file
│       └── UI.h                 # Giao diện người dùng
│
└── src/                         # Thư mục chứa file nguồn (.cpp)
    ├── main.cpp                 # Điểm vào chương trình
    ├── models/
    │   ├── account.cpp
    │   ├── customer.cpp
    │   └── transaction.cpp
    ├── services/
    │   ├── BankSystem.cpp
    │   ├── ReportLogic.cpp
    │   └── TransactionLogic.cpp
    └── utils/
        ├── fileManager.cpp
        └── UI.cpp
```

---

## Hướng dẫn cài đặt và chạy chương trình (Build bằng MinGW g++)

### Bước 1: Cài đặt MinGW-w64

**Trên Windows:**

1. Tải MinGW-w64 từ: [https://www.mingw-w64.org/](https://www.mingw-w64.org/) hoặc [MSYS2](https://www.msys2.org/)
2. Cài đặt và thêm đường dẫn `bin` của MinGW vào biến môi trường `PATH` (ví dụ: `C:\mingw64\bin`)
3. Mở Command Prompt và kiểm tra:
   ```cmd
   g++ --version
   ```
   Nếu hiển thị phiên bản g++ (ví dụ: `g++ (MinGW.org GCC Build-2) 9.2.0`), cài đặt thành công.

**Trên Linux:**
```bash
sudo apt update
sudo apt install g++ make
```

**Trên macOS:**
```bash
xcode-select --install
# hoặc
brew install gcc
```

### Bước 2: Mở Terminal tại thư mục dự án

```cmd
cd d:\KTLT\Account_Management
```

(Lưu ý: thay đổi đường dẫn cho phù hợp với vị trí thực tế của dự án trên máy.)

### Bước 3: Biên dịch chương trình

Sử dụng lệnh sau để biên dịch toàn bộ mã nguồn thành file thực thi:

**Trên Windows (cmd):**
```cmd
g++ -o bank_system.exe ^
    src/main.cpp ^
    src/models/customer.cpp ^
    src/models/account.cpp ^
    src/models/transaction.cpp ^
    src/services/BankSystem.cpp ^
    src/services/TransactionLogic.cpp ^
    src/services/ReportLogic.cpp ^
    src/utils/UI.cpp ^
    src/utils/fileManager.cpp ^
    -I include
```

**Trên Linux/macOS (bash):**
```bash
g++ -o bank_system \
    src/main.cpp \
    src/models/customer.cpp \
    src/models/account.cpp \
    src/models/transaction.cpp \
    src/services/BankSystem.cpp \
    src/services/TransactionLogic.cpp \
    src/services/ReportLogic.cpp \
    src/utils/UI.cpp \
    src/utils/fileManager.cpp \
    -I include
```

**Giải thích các tham số biên dịch:**

| Tham số | Ý nghĩa |
|---|---|
| `-o bank_system.exe` | Đặt tên file đầu ra là `bank_system.exe` (trên Linux/macOS có thể là `bank_system`) |
| `src/main.cpp` ... | Danh sách tất cả các file nguồn `.cpp` cần biên dịch |
| `-I include` | Thêm thư mục `include/` vào đường dẫn tìm kiếm header (giúp `#include "..."` hoạt động) |

> **Lưu ý:** Nếu không có lỗi, lệnh trên sẽ tạo ra file `bank_system.exe` (hoặc `bank_system` trên Linux/macOS) trong thư mục hiện tại. Nếu có lỗi, kiểm tra lại đường dẫn file và cú pháp.

### Bước 4: Chạy chương trình

```cmd
bank_system.exe
```

Sau khi khởi động, chương trình sẽ tự động:
1. Nạp dữ liệu từ các file trong thư mục `data/`
2. Tự động chốt lãi hàng tháng (nếu đến kỳ)
3. Hiển thị menu chính với các lựa chọn:
   - **1.** Quản lý khách hàng & tài khoản
   - **2.** Giao dịch tài chính
   - **3.** Báo cáo & Sao kê
   - **0.** Thoát chương trình

### Bước 5 (tùy chọn): Sinh dữ liệu mẫu mới

Nếu muốn tạo lại dữ liệu mẫu (các file trong `data/`):

```cmd
g++ -o generator generator.cpp -I include
generator.exe
```

Lệnh này sẽ sinh ngẫu nhiên dữ liệu khách hàng, tài khoản và giao dịch, ghi đè lên các file hiện có.

---

## Biên dịch và chạy bằng một lệnh duy nhất

Để biên dịch và chạy trong một bước (hữu ích khi phát triển):

**Trên Windows:**
```cmd
g++ -o bank_system.exe ^
    src/main.cpp ^
    src/models/customer.cpp ^
    src/models/account.cpp ^
    src/models/transaction.cpp ^
    src/services/BankSystem.cpp ^
    src/services/TransactionLogic.cpp ^
    src/services/ReportLogic.cpp ^
    src/utils/UI.cpp ^
    src/utils/fileManager.cpp ^
    -I include && bank_system.exe
```

**Trên Linux/macOS:**
```bash
g++ -o bank_system \
    src/main.cpp \
    src/models/customer.cpp \
    src/models/account.cpp \
    src/models/transaction.cpp \
    src/services/BankSystem.cpp \
    src/services/TransactionLogic.cpp \
    src/services/ReportLogic.cpp \
    src/utils/UI.cpp \
    src/utils/fileManager.cpp \
    -I include && ./bank_system
```

---

## Sử dụng Makefile (tùy chọn)

Nếu muốn sử dụng `make` để tự động hóa quá trình build, tạo file `Makefile` trong thư mục gốc với nội dung:

```makefile
CXX = g++
CXXFLAGS = -I include
TARGET = bank_system.exe
SRCDIR = src
OBJDIR = obj

SOURCES = $(SRCDIR)/main.cpp \
          $(SRCDIR)/models/customer.cpp \
          $(SRCDIR)/models/account.cpp \
          $(SRCDIR)/models/transaction.cpp \
          $(SRCDIR)/services/BankSystem.cpp \
          $(SRCDIR)/services/TransactionLogic.cpp \
          $(SRCDIR)/services/ReportLogic.cpp \
          $(SRCDIR)/utils/UI.cpp \
          $(SRCDIR)/utils/fileManager.cpp

OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -rf $(OBJDIR) $(TARGET)

run: $(TARGET)
	./$(TARGET)
```

Sau đó sử dụng các lệnh:
```cmd
make          # Biên dịch chương trình
make run      # Biên dịch và chạy
make clean    # Dọn dẹp file object và file thực thi
```

---

## Xử lý lỗi thường gặp

| Lỗi | Nguyên nhân | Giải pháp |
|---|---|---|
| `g++: command not found` | Chưa cài MinGW hoặc chưa thêm vào PATH | Cài đặt MinGW-w64 và thêm đường dẫn `bin` vào biến môi trường PATH |
| `fatal error: ...: No such file or directory` | Thiếu tham số `-I include` | Thêm `-I include` vào lệnh biên dịch |
| `undefined reference to ...` | Thiếu file `.cpp` trong danh sách biên dịch | Đảm bảo tất cả các file `.cpp` trong `src/` (và các thư mục con) được liệt kê đầy đủ |
| File thực thi không chạy | Thiếu thư viện runtime (DLL) của MinGW | Copy file `libstdc++-6.dll` và `libgcc_s_seh-1.dll` từ thư mục `bin` của MinGW vào cùng thư mục với `bank_system.exe`, hoặc thêm `-static` vào lệnh g++ |

---

## Thông tin dự án

- **Môn học:** Kỹ thuật lập trình
- **Ngôn ngữ:** C++ (kết hợp một phần thư viện C `ctime`, `cstdio`)
- **Cấu trúc dữ liệu chính:** Singly LinkedList (tự xây dựng, template class)
- **Lưu trữ dữ liệu:** File text (.txt) — 3 file: `customers.txt`, `accounts.txt`, `transactions.txt`
- **Giao diện:** Console CLI với hệ thống menu phân cấp

### Tính năng chính

- Đăng ký khách hàng mới (kiểm tra CCCD 12 số, SDT 10 số)
- Tạo tài khoản ngân hàng với mã PIN và số dư tối thiểu
- Nạp tiền, rút tiền, chuyển khoản giữa các tài khoản
- Xác thực giao dịch qua mã PIN (tối đa 3 lần sai)
- Đổi mã PIN, cập nhật số điện thoại
- Xem sao kê tài khoản, lịch sử giao dịch
- Tính lãi suất tiền gửi (4%/năm) và tự động chốt lãi hàng tháng
- Tự động lưu dữ liệu ra file sau mỗi thao tác