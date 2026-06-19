# BÁO CÁO DỰ ÁN

## HỆ THỐNG QUẢN LÝ TÀI KHOẢN NGÂN HÀNG
### (Bank Account Management System)

---

**Mã đề tài:** Account_Management

**Ngôn ngữ lập trình:** C++ / C

**Môi trường phát triển:** Visual Studio Code, MinGW (g++)

**Ngày báo cáo:** [Người dùng bổ sung: Ngày tháng]

---

## MỤC LỤC

[Danh mục sẽ được cập nhật sau khi hoàn thiện các chương]

---

## LỜI MỞ ĐẦU

Trong bối cảnh chuyển đổi số ngành tài chính - ngân hàng, việc xây dựng các hệ thống quản lý thông tin khách hàng và tài khoản một cách an toàn, hiệu quả là một nhu cầu thiết yếu. Dự án **"Hệ thống Quản lý Tài khoản Ngân hàng"** được phát triển nhằm đáp ứng nhu cầu đó bằng cách ứng dụng ngôn ngữ lập trình C++ để xây dựng một ứng dụng console quản lý khách hàng, tài khoản và giao dịch ngân hàng.

Báo cáo này trình bày chi tiết quá trình phân tích, thiết kế, cài đặt và kiểm thử hệ thống, đồng thời phân tích các kỹ thuật lập trình hướng đối tượng (OOP), cấu trúc dữ liệu và giải thuật đã được áp dụng trong dự án.

---

## DANH SÁCH HÌNH VẼ, BIỂU ĐỒ VÀ BẢNG BIỂU

[Người dùng bổ sung: Chụp ảnh giao diện chương trình và các kết quả kiểm thử thực tế, sau đó chèn vào đây]

- **Hình 1:** Giao diện Menu chính của hệ thống
- **Hình 2:** Giao diện Quản lý khách hàng & tài khoản
- **Hình 3:** Giao diện Giao dịch (Nạp/Rút/Chuyển khoản)
- **Hình 4:** Giao diện Báo cáo & Sao kê
- **Hình 5:** Minh họa kết quả kiểm thử

---

## BẢNG THUẬT NGỮ VÀ CHỮ VIẾT TẮT

| Thuật ngữ | Ý nghĩa | Ghi chú |
|---|---|---|
| **OOP** | Lập trình hướng đối tượng (Object-Oriented Programming) | Phương pháp luận chính |
| **CRUD** | Tạo, Đọc, Cập nhật, Xóa (Create, Read, Update, Delete) | Các thao tác cơ bản trên dữ liệu |
| **STL** | Thư viện chuẩn C++ (Standard Template Library) | Không sử dụng trong dự án (tự xây dựng) |
| **SLL / DLL** | Danh sách liên kết đơn (Singly Linked List) / Danh sách liên kết kép (Doubly Linked List) | Dự án sử dụng SLL |
| **KH** | Khách hàng | Tiền tố mã khách hàng |
| **TK** | Tài khoản | Số tài khoản ngân hàng |
| **GD** | Giao dịch | Tiền tố mã giao dịch |
| **STK** | Số tài khoản | Định danh tài khoản |
| **CCCD** | Căn cước công dân | 12 chữ số |
| **PIN** | Mã số nhận dạng cá nhân (Personal Identification Number) | 4 chữ số |
| **CLI** | Giao diện dòng lệnh (Command-Line Interface) | Giao diện người dùng |
| **UI** | Giao diện người dùng (User Interface) | Module hiển thị |
| **CSDL** | Cơ sở dữ liệu | Đề cập đến hướng phát triển |

---

## CHƯƠNG 1: TỔNG QUAN DỰ ÁN

### 1.1 Mô tả bài toán

Bài toán đặt ra là xây dựng một hệ thống phần mềm cho phép lưu trữ và quản lý thông tin tài khoản người dùng/khách hàng một cách hệ thống và an toàn. Hệ thống cần đáp ứng các nhu cầu cơ bản của một ngân hàng thu nhỏ bao gồm: đăng ký thông tin khách hàng, tạo và quản lý tài khoản ngân hàng, thực hiện các giao dịch nạp/rút/chuyển khoản, tra cứu lịch sử giao dịch và tính lãi suất tiền gửi.

Dữ liệu của hệ thống cần được lưu trữ bền vững trên file để có thể truy xuất và phục hồi sau mỗi lần khởi động chương trình. Hệ thống phải đảm bảo tính nhất quán dữ liệu, tránh trùng lặp và có cơ chế xác thực thông qua mã PIN.

### 1.2 Mục tiêu của chương trình

- **Mục tiêu tổng quát:** Xây dựng ứng dụng console cho phép đăng ký, đăng nhập và quản trị thông tin khách hàng với khả năng lưu trữ bền vững.
- **Mục tiêu cụ thể:**
  - Cho phép đăng ký khách hàng mới với đầy đủ thông tin (họ tên, CCCD, số điện thoại).
  - Tạo tài khoản ngân hàng với mã PIN và số dư ban đầu.
  - Hỗ trợ các giao dịch: nạp tiền, rút tiền, chuyển khoản giữa các tài khoản.
  - Xác thực giao dịch qua mã PIN (cho phép tối đa 3 lần sai).
  - Cho phép đổi mã PIN và cập nhật số điện thoại.
  - Tra cứu lịch sử giao dịch và sao kê tài khoản.
  - Tự động tính và chốt lãi tiền gửi hàng tháng (lãi suất 4%/năm).
  - Lưu và phục hồi dữ liệu tự động qua file text.

### 1.3 Phạm vi thực hiện

Dự án được triển khai trong phạm vi một ứng dụng console sử dụng ngôn ngữ C++ thuần, với các cấu trúc dữ liệu và giải thuật được tự xây dựng thay vì sử dụng các thư viện có sẵn như STL. Dự án bao gồm:

- Thiết kế và cài đặt 3 lớp mô hình chính: `Customer`, `Account`, `Transaction`
- Xây dựng cấu trúc danh sách liên kết đơn tổng quát (`LinkedList<T>`) để quản lý bộ nhớ động
- Phát triển 3 module dịch vụ: `BankSystem`, `TransactionLogic`, `ReportLogic`
- Xây dựng giao diện người dùng CLI với hệ thống menu phân cấp
- Cơ chế đọc/ghi dữ liệu từ file với định dạng phân tách bằng ký tự `|`
- Hệ thống tự động tính lãi hàng tháng và chốt lãi khi khởi động chương trình

### 1.4 Công nghệ và ngôn ngữ lập trình sử dụng

| Công nghệ | Mô tả | Tỷ lệ sử dụng |
|---|---|---|
| **C++** | Ngôn ngữ lập trình chính | ~97.5% |
| **C** | Hàm xử lý thời gian (`ctime`, `cstdio`, `sprintf`, `sscanf`) | ~2.5% |
| **MinGW g++** | Trình biên dịch | — |
| **File text (.txt)** | Lưu trữ dữ liệu | — |

**Phương pháp phát triển:**
Dự án áp dụng phương pháp tự xây dựng cấu trúc dữ liệu (custom data structures) thay vì phụ thuộc vào thư viện chuẩn STL, nhằm:
- Tối ưu hiệu năng cho bài toán cụ thể
- Nâng cao hiểu biết về cơ chế quản lý bộ nhớ thủ công
- Tăng tính linh hoạt khi mở rộng hệ thống

### 1.5 Phân công công việc

#### 1.5.1 Thành viên thực hiện

[Người dùng bổ sung: Danh sách thành viên nhóm]

#### 1.5.2 Phân công chi tiết nhiệm vụ (đề xuất)

| STT | Nhiệm vụ | Mô tả chi tiết | File liên quan |
|---|---|---|---|
| 1 | Phát triển lớp mô hình | Thiết kế và cài đặt các lớp `Customer`, `Account`, `Transaction` | `include/models/*.h`, `src/models/*.cpp` |
| 2 | Xây dựng cấu trúc dữ liệu | Cài đặt `LinkedList<T>` (Singly Linked List) dạng template | `include/data_structures/linkedList.h` |
| 3 | Phát triển logic ngân hàng | Lớp `BankSystem` - quản lý khách hàng, tài khoản, kiểm tra dữ liệu | `include/services/BankSystem.h`, `src/services/BankSystem.cpp` |
| 4 | Phát triển xử lý giao dịch | Lớp `TransactionLogic` - nạp, rút, chuyển khoản | `include/services/TransactionLogic.h`, `src/services/TransactionLogic.cpp` |
| 5 | Phát triển báo cáo & sao kê | Lớp `ReportLogic` - sao kê, lịch sử, tính lãi | `include/services/ReportLogic.h`, `src/services/ReportLogic.cpp` |
| 6 | Thiết kế giao diện UI | Xây dựng menu console, xử lý nhập xuất | `include/utils/UI.h`, `src/utils/UI.cpp` |
| 7 | Xử lý dữ liệu file | Đọc/ghi dữ liệu với file text (customers, accounts, transactions) | `include/utils/fileManager.h`, `src/utils/fileManager.cpp` |
| 8 | Tích hợp & Kiểm thử | Tích hợp các module và kiểm thử tổng thể | `src/main.cpp` |

---

## CHƯƠNG 2: CƠ SỞ LÝ THUYẾT VÀ CÔNG NGHỆ

### 2.1 Lập trình hướng đối tượng (OOP) trong C++

Dự án áp dụng đầy đủ 4 tính chất của lập trình hướng đối tượng:

**a) Tính đóng gói (Encapsulation):**
Tất cả các lớp (`Customer`, `Account`, `Transaction`) đều sử dụng từ khóa `private` để bảo vệ dữ liệu nội bộ và chỉ cung cấp các phương thức `public` (getter) để truy cập:

```cpp
// Ví dụ từ class Account (include/models/account.h)
class Account {
    private:
        std::string soTK;       // Số tài khoản - private
        std::string maKH;       // Mã khách hàng - private
        std::string maPIN;      // Mã PIN - private
        long long soDu;         // Số dư - private
        std::string ngayMo;     // Ngày mở - private
    public:
        std::string getSoTK() const;    // Getter public
        long long getSoDu() const;       // Getter public
        bool kiemTraPIN(std::string);   // Xác thực PIN
        bool napTien(long long);        // Nạp tiền
        bool rutTien(long long);        // Rút tiền
};
```

**b) Tính kế thừa (Inheritance):**
Hiện tại dự án chưa sử dụng kế thừa giữa các lớp mô hình, tuy nhiên các lớp dịch vụ (`TransactionLogic`, `ReportLogic`) nhận tham chiếu đến `BankSystem` qua con trỏ, tạo thành quan hệ hợp thành (composition).

**c) Tính đa hình (Polymorphism):**
Được áp dụng thông qua cơ chế **Template** trong `LinkedList<T>`, cho phép một cấu trúc danh sách liên kết duy nhất quản lý được nhiều kiểu dữ liệu khác nhau (`Customer`, `Account`, `Transaction`).

**d) Tính trừu tượng (Abstraction):**
Các lớp dịch vụ (`BankSystem`, `TransactionLogic`, `ReportLogic`) cung cấp các phương thức trừu tượng hóa nghiệp vụ ngân hàng, che giấu chi tiết cài đặt bên trong.

### 2.2 Cơ chế lưu trữ dữ liệu

Hệ thống sử dụng cơ chế lưu trữ file text với định dạng tùy chỉnh, phân tách các trường dữ liệu bằng ký tự `|` (pipe). Ba file dữ liệu được sử dụng:

| File | Mục đích | Định dạng mỗi dòng |
|---|---|---|
| `data/customers.txt` | Lưu danh sách khách hàng | `maKH\|hoTen\|cccd\|sdt` |
| `data/accounts.txt` | Lưu danh sách tài khoản | `soTK\|maKH\|maPIN\|soDu\|ngayMo` |
| `data/transactions.txt` | Lưu lịch sử giao dịch | `maGD\|thoiGian\|loaiGD\|soTien\|soTKGui\|soTKNhan` |

Cơ chế đọc/ghi được thực hiện thông qua hai hàm chính trong `fileManager.cpp`:
- `LoadAllData(BankSystem& bank)`: Đọc dữ liệu từ 3 file và nạp vào hệ thống
- `SaveAllData(BankSystem& bank)`: Ghi toàn bộ dữ liệu từ hệ thống ra 3 file

Quy trình đọc dữ liệu sử dụng `std::stringstream` và hàm `getline` với delimiter `|` để tách trường, đảm bảo tính toàn vẹn dữ liệu khi đóng/mở chương trình.

### 2.3 Cấu trúc dữ liệu và giải thuật áp dụng

#### 2.3.1 Bảng băm (Hash Table)

**Phát hiện trong code:** Dự án **không** cài đặt bảng băm (hash table) một cách tường minh. Tuy nhiên, tư tưởng bảng băm được áp dụng trong hàm `sinhSTKMoi()` (BankSystem.cpp, dòng 171-177) để đảm bảo số tài khoản sinh ra là duy nhất:

```cpp
std::string BankSystem::sinhSTKMoi() {
    srand((unsigned int)time(0));
    std::string soTK = std::to_string(100000000 + rand() % 900000000);
    while (kiemTraTrungSTK(soTK))
        soTK = std::to_string(100000000 + rand() % 900000000);
    return soTK;
}
```

Cơ chế này sinh số tài khoản ngẫu nhiên 9 chữ số và kiểm tra trùng lặp bằng cách duyệt danh sách liên kết (dùng `kiemTraTrungSTK`). Nếu muốn tối ưu tốc độ tìm kiếm khi đăng nhập trong tương lai, cần cài đặt bảng băm riêng.

**Lưu ý:** Hiện tại, để kiểm tra trùng số tài khoản, hệ thống sử dụng danh sách liên kết đơn với độ phức tạp O(n).

#### 2.3.2 Mảng động (Dynamic Array)

**Phát hiện trong code:** Dự án **không** sử dụng mảng động (dynamic array / `std::vector`), mà thay vào đó sử dụng **danh sách liên kết đơn** (`LinkedList<T>`) để quản lý danh sách đối tượng. Lựa chọn này cho phép:

- Kích thước co giãn linh hoạt mà không cần cấp phát lại vùng nhớ như mảng động
- Thêm/xóa phần tử ở vị trí bất kỳ với độ phức tạp O(1) (nếu có con trỏ tới node)
- Tuy nhiên, truy cập ngẫu nhiên (random access) có độ phức tạp O(n)

#### 2.3.3 Data Structures: Lớp LinkedList\<T\> (Singly Linked List)

**Phát hiện trong code** (`include/data_structures/linkedList.h`):

Đây là cấu trúc dữ liệu quan trọng nhất của dự án, được cài đặt dưới dạng **template class** để hỗ trợ đa kiểu dữ liệu:

**Cấu trúc Node:**
```cpp
template <class T>
struct Node {
    T data;
    Node* next;
    Node(T newData) {
        this->data = newData;
        this->next = NULL;
    }
};
```

**Lớp LinkedList:**
```cpp
template <class Y>
class LinkedList {
    private:
        Node<Y>* head;    // Con trỏ đầu danh sách
        Node<Y>* tail;    // Con trỏ cuối danh sách
        int count;        // Số lượng phần tử
    public:
        LinkedList();                       // Hàm khởi tạo
        ~LinkedList();                      // Hàm hủy (giải phóng bộ nhớ)
        Node<Y>* getHead() const;           // Lấy phần tử đầu
        void addTail(Y newData);            // Thêm vào cuối O(1)
        int getSize() const;                // Lấy kích thước
        void clear();                       // Xóa toàn bộ danh sách
};
```

**Các phương thức quan trọng:**
- `addTail()`: Thêm phần tử vào cuối danh sách với độ phức tạp O(1) nhờ con trỏ `tail`
- `clear()`: Duyệt toàn bộ danh sách và giải phóng từng node, tránh rò rỉ bộ nhớ
- `getHead()`: Cho phép duyệt tuần tự danh sách từ đầu đến cuối

**Ứng dụng trong BankSystem (BankSystem.h):**
```cpp
class BankSystem {
    private:
        LinkedList<Customer> danhSachKH;        // Danh sách khách hàng
        LinkedList<Account> danhSachTK;         // Danh sách tài khoản
        LinkedList<Transaction> danhSachGD;     // Danh sách giao dịch
};
```

### 2.4 Kiểm thử

#### 2.4.1 Kiểm thử hộp đen (Black-box Testing)

Áp dụng để kiểm tra các chức năng từ góc nhìn người dùng mà không cần biết cấu trúc bên trong. Các trường hợp kiểm thử bao gồm:

- Kiểm tra đăng ký với dữ liệu hợp lệ/không hợp lệ
- Kiểm tra đăng nhập với PIN đúng/sai
- Kiểm tra chuyển khoản với số dư đủ/không đủ
- Kiểm tra rút tiền với số tiền hợp lệ/không hợp lệ
- Kiểm tra ngày tháng năm hợp lệ (có tính năm nhuận) qua hàm `kiemTraNgayHopLe()`

#### 2.4.2 Kiểm thử hộp trắng (White-box Testing)

Áp dụng để kiểm tra cấu trúc code bên trong:

- Kiểm tra vòng lặp duyệt danh sách trong các hàm `timKiemKhachHang()`, `timKiemTaiKhoan()`
- Kiểm tra các nhánh điều kiện trong hàm `kiemTraNgayHopLe()` (xử lý tháng 2 năm nhuận)
- Kiểm tra giải phóng bộ nhớ trong `LinkedList::~LinkedList()`

---

## CHƯƠNG 3: KỸ THUẬT THIẾT KẾ CHƯƠNG TRÌNH

### 3.1 Kỹ thuật thiết kế cấu trúc chương trình

Chương trình được thiết kế theo hai cơ chế chính: **phân rã Top-down** và **Module hóa**, phối hợp chặt chẽ với nhau nhằm tạo ra một hệ thống có cấu trúc rõ ràng, dễ bảo trì và mở rộng.

**Cơ chế Top-down:** Luồng thực thi bắt đầu từ hàm `main()` (tại `src/main.cpp`), gọi đến `MenuChinh()` — hàm điều khiển trung tâm. Từ `MenuChinh()`, chương trình phân rã xuống các menu con như `MenuQuanLy()`, `MenuGiaoDich()`, `MenuBaoCao()`; mỗi menu con tiếp tục gọi đến các hàm nghiệp vụ cụ thể trong các lớp `BankSystem`, `TransactionLogic`, `ReportLogic`. Cấu trúc phân cấp này giúp luồng xử lý của chương trình trở nên trực quan và dễ theo dõi.

**Ưu điểm của cơ chế Top-down trong dự án:**

- **Tổ chức luồng xử lý rõ ràng, có thứ bậc:** Hàm `main()` chỉ đóng vai trò khởi tạo hệ thống (`LoadAllData`, tạo đối tượng `bank`, `trans`, `report`) và gọi `MenuChinh()`. Toàn bộ logic điều hướng nằm trong `MenuChinh()`, giúp người đọc nắm được kiến trúc tổng thể của chương trình chỉ sau một lượt đọc `main.cpp`. Từ `MenuChinh()` đi sâu xuống `MenuQuanLy()` → `themKhachHang()` → `kiemTraCCCDHopLe()` theo từng mức chi tiết tăng dần.

- **Dễ phát triển theo từng bước:** Có thể xây dựng và kiểm thử chương trình từ trên xuống dưới: viết `main()` trước với các lời gọi hàm giả (stub), sau đó lần lượt cài đặt `MenuChinh()`, rồi đến các menu con, cuối cùng là các hàm nghiệp vụ. Quá trình này cho phép phát hiện lỗi thiết kế tổng thể ngay từ đầu mà không cần đợi hoàn thiện toàn bộ chi tiết.

- **Giảm độ phức tạp của từng hàm:** Mỗi hàm chỉ đảm nhận một nhiệm vụ cụ thể ở một mức trừu tượng nhất định. Ví dụ, `MenuGiaoDich()` chỉ chịu trách nhiệm hiển thị menu và gọi `trans.NapTien()` / `trans.RutTien()` / `trans.ChuyenKhoan()`, không quan tâm đến cách các giao dịch đó được xử lý bên trong. Ngược lại, `TransactionLogic::ChuyenKhoan()` xử lý chi tiết nghiệp vụ mà không can thiệp vào giao diện.

- **Dễ dàng bổ sung chức năng mới:** Khi cần thêm một tính năng (ví dụ: "Khóa tài khoản"), chỉ cần thêm một lựa chọn mới vào `MenuChinh()` hoặc `MenuQuanLy()`, viết hàm xử lý tương ứng trong `BankSystem`, và gọi nó từ menu — không làm ảnh hưởng đến các nhánh chức năng đã có.

**Cơ chế Module hóa:** Toàn bộ mã nguồn được chia tách thành các file riêng biệt theo nhóm chức năng, đặt trong các thư mục tương ứng:

| Thư mục | Nhóm chức năng | File chính |
|---|---|---|
| `include/models/` + `src/models/` | Lớp mô hình dữ liệu | `customer.h/.cpp`, `account.h/.cpp`, `transaction.h/.cpp` |
| `include/services/` + `src/services/` | Lớp nghiệp vụ | `BankSystem.h/.cpp`, `TransactionLogic.h/.cpp`, `ReportLogic.h/.cpp` |
| `include/utils/` + `src/utils/` | Tiện ích | `UI.h/.cpp`, `fileManager.h/.cpp` |
| `include/data_structures/` | Cấu trúc dữ liệu | `linkedList.h` |

**Ưu điểm của Module hóa trong dự án:**

- **Dễ hiểu:** Mỗi file chỉ chứa một nhóm chức năng nhất định, giúp người đọc nhanh chóng xác định vị trí của từng thành phần. Ví dụ, muốn hiểu cách một giao dịch chuyển khoản được xử lý, chỉ cần đọc file `TransactionLogic.cpp` mà không cần quan tâm đến cách dữ liệu được lưu xuống file (nằm trong `fileManager.cpp`).

- **Dễ bảo trì và mở rộng:** Khi cần thay đổi quy tắc kiểm tra CCCD, chỉ cần sửa trong `BankSystem.cpp` tại hàm `kiemTraCCCDHopLe()`, các module khác không bị ảnh hưởng. Tương tự, muốn thêm loại giao dịch mới, chỉ cần thêm hàm trong `TransactionLogic.cpp` và gọi từ `UI.cpp`.

- **Dễ kiểm thử:** Có thể kiểm thử từng module độc lập. Ví dụ, kiểm tra riêng hàm `kiemTraNgayHopLe()` trong `BankSystem.cpp` với nhiều bộ dữ liệu ngày tháng (năm nhuận, tháng 2, tháng 30 ngày) mà không cần chạy toàn bộ chương trình.

- **Không lặp lại code (DRY - Don't Repeat Yourself):** Các thao tác dùng chung được đóng gói thành hàm dùng lại nhiều lần. Ví dụ, logic tách trường dữ liệu từ file được viết một lần duy nhất trong hàm `getNextToken()` tại `fileManager.cpp` và được tái sử dụng khi đọc cả ba file `customers.txt`, `accounts.txt` và `transactions.txt`.

### 3.1.1 Các mô thức lập trình được sử dụng

**a) Lập trình Hướng đối tượng (OOP):**

Dự án áp dụng tính đóng gói (Encapsulation) và ẩn giấu thông tin (Information Hiding) thông qua các lớp `Customer`, `Account`, `Transaction`. Mỗi lớp đóng gói dữ liệu nhạy cảm ở chế độ `private` và chỉ cung cấp các phương thức truy cập (getter) hoặc thao tác (method) ở chế độ `public`.

Ví dụ — lớp `Account` (`include/models/account.h`):
- Thuộc tính `maPIN` (Mã PIN) được khai báo `private`, không có getter công khai. Thay vào đó, phương thức `kiemTraPIN(string pinNhapVao)` cho phép xác thực PIN từ bên ngoài mà không tiết lộ giá trị thực.
- Thuộc tính `soDu` (Số dư) được khai báo `private`, chỉ có getter `getSoDu()` và các phương thức `napTien()`, `rutTien()` dùng để thay đổi số dư một cách có kiểm soát (kiểm tra số dư tối thiểu 50.000 VND khi rút).

Ví dụ — lớp `Customer` (`include/models/customer.h`):
- Thuộc tính `cccd`, `sdt` được `private`. Việc cập nhật số điện thoại chỉ được thực hiện qua phương thức `setSDT()`, có thể mở rộng để thêm kiểm tra tính hợp lệ sau này.
- Lớp `BankSystem` được khai báo là `friend` của lớp `Account` (tại `account.h` dòng 34: `friend void SaveAllData(class BankSystem& bank)`), cho phép hàm lưu file truy cập `maPIN` để ghi ra đĩa mà vẫn giữ được tính an toàn ở các ngữ cảnh khác.

**b) Lập trình mệnh lệnh (Imperative Programming):**

Chương trình thực thi tuần tự theo từng câu lệnh, kết hợp với các cấu trúc điều khiển (vòng lặp, rẽ nhánh) để thao tác dữ liệu.

Ví dụ — Duyệt danh sách liên kết với vòng lặp `while` và con trỏ:
```cpp
// BankSystem.cpp — tìm kiếm tài khoản
Account* BankSystem::timKiemTaiKhoan(std::string soTK) {
    Node<Account>* current = danhSachTK.getHead();
    while (current != NULL) {
        if (current->data.getSoTK() == soTK) {
            return &(current->data);
        }
        current = current->next;   // Di chuyển đến node kế tiếp
    }
    return NULL;
}
```

Ví dụ — Sử dụng câu lệnh rẽ nhánh trong kiểm tra ngày hợp lệ:
```cpp
// BankSystem.cpp — xử lý tháng 2 năm nhuận
if (m == 4 || m == 6 || m == 9 || m == 11) {
    soNgayTrongThang = 30;
} else if (m == 2) {
    if ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0))
        soNgayTrongThang = 29;
    else
        soNgayTrongThang = 28;
}
```

**c) Lập trình phòng ngừa (Defensive Programming):**

Mọi dữ liệu nhập từ người dùng và trạng thái hệ thống đều được kiểm tra trước khi xử lý, nhằm ngăn chặn lỗi phát sinh ở runtime.

Ví dụ — Kiểm tra tính hợp lệ của dữ liệu đầu vào:
- CCCD phải đúng 12 chữ số: `BankSystem::kiemTraCCCDHopLe()` (`BankSystem.cpp`, dòng 133).
- Số điện thoại phải 10 chữ số, bắt đầu bằng '0': `BankSystem::kiemTraSDTHopLe()` (`BankSystem.cpp`, dòng 149).
- Mã PIN phải đúng 4 chữ số: `BankSystem::kiemTraPINHopLe()` (`BankSystem.cpp`, dòng 141).
- Số dư ban đầu phải >= 50.000 VND: kiểm tra trong `BankSystem::taoTaiKhoan()` (`BankSystem.cpp`, dòng 93-96).

Ví dụ — Kiểm tra lỗi hệ thống trước khi đọc file (trong `fileManager.cpp`):
```cpp
if (!file.is_open()) {
    std::cerr << "[LOI] Khong the mo file " << fileName << "!" << std::endl;
    return;
}
```

Ví dụ — Kiểm tra tồn tại trước khi thao tác:
```cpp
// TransactionLogic.cpp — kiểm tra tài khoản tồn tại trước khi nạp tiền
Account* tk = this->bankSystem->timKiemTaiKhoan(soTK);
if (tk == NULL) {
    std::cout << "[LOI] Khong tim thay tai khoan!" << std::endl;
    return false;
}
```

### 3.1.2 Các kỹ thuật quản lý và xử lý dữ liệu

**a) Cấu trúc dữ liệu tự định nghĩa — LinkedList:**

Hệ thống sử dụng danh sách liên kết đơn (`LinkedList<T>`) được tự xây dựng hoàn toàn bằng tay, không dùng thư viện STL, để quản lý danh sách các đối tượng `Customer`, `Account`, `Transaction`.

Đặc điểm nổi bật:
- **Cấp phát động (Dynamic Allocation):** Mỗi phần tử (`Node`) được cấp phát riêng lẻ trên vùng nhớ Heap thông qua `new Node<T>(data)` (`linkedList.h`, dòng 40). Khi không còn sử dụng, destructor gọi `clear()` để duyệt toàn bộ danh sách và giải phóng từng `Node` bằng `delete`, đảm bảo không rò rỉ bộ nhớ.
- **Linh hoạt mở rộng:** Kích thước danh sách chỉ bị giới hạn bởi bộ nhớ khả dụng, không cần khai báo trước như mảng tĩnh. Phương thức `addTail()` thêm phần tử mới với độ phức tạp O(1) nhờ con trỏ `tail`.

So sánh với mảng tĩnh (static array):
| Tiêu chí | Mảng tĩnh | LinkedList (dự án) |
|---|---|---|
| Kích thước | Cố định ngay từ đầu | Linh hoạt, cấp phát động |
| Thêm phần tử | Phải biết trước số lượng, dễ tràn | `addTail()` O(1), không lo tràn |
| Giải phóng bộ nhớ | Tự động khi ra khỏi scope | Destructor gọi `clear()` thủ công |

**b) Cơ chế lưu trữ bền vững (Persistence) qua file text:**

Dữ liệu được ghi xuống ba file text trong thư mục `data/` và được tự động đọc lại mỗi khi chương trình khởi động, đảm bảo không mất thông tin giữa các phiên làm việc.

Quy trình đọc/ghi được quản lý bởi module `fileManager.cpp`:
- **Khi khởi động (`LoadAllData()`):** Gọi lần lượt `LoadCustomers()`, `LoadAccounts()`, `LoadTransactions()` để đọc từng file, dùng `getline(ss, token, '|')` để tách trường. Mỗi bản ghi được chuyển đổi thành đối tượng (`Customer`, `Account`, `Transaction`) và thêm vào danh sách liên kết tương ứng thông qua `addTail()`.
- **Khi thoát hoặc sau mỗi giao dịch (`SaveAllData()`):** Duyệt toàn bộ `LinkedList`, ghi từng đối tượng thành một dòng trong file với định dạng phân tách `|`. Ví dụ, một giao dịch được ghi thành:
  ```
  GD001|10/12/2022 03:46|NAP|3075389|526997230|N/A
  ```

Cơ chế này được gọi ở `main.cpp` (dòng 18 và 27):
```cpp
LoadAllData(bank);   // Nạp dữ liệu khi mở chương trình
// ... thực hiện các thao tác nghiệp vụ ...
SaveAllData(bank);   // Lưu dữ liệu trước khi thoát
```

### 3.1.3 Kỹ thuật dùng hàm và tham số

**a) Truyền tham chiếu (Pass-by-reference) bằng dấu `&`:**

Kỹ thuật này được sử dụng xuyên suốt dự án nhằm tránh sao chép dữ liệu lớn (các đối tượng `BankSystem`, `LinkedList`, `Customer`, `Account`), từ đó tối ưu bộ nhớ và hiệu năng.

Các trường hợp áp dụng cụ thể:

| Vị trí | Khai báo | Giải thích |
|---|---|---|
| `UI.h` | `void MenuChinh(BankSystem& bank, TransactionLogic& trans, ReportLogic& report)` | Truyền tham chiếu `BankSystem` — đối tượng chứa ba `LinkedList` lớn — vào hàm menu để các menu con có thể thao tác trực tiếp trên dữ liệu gốc |
| `UI.h` | `void MenuQuanLy(BankSystem& bank)` | Truyền tham chiếu `BankSystem` để thao tác tìm kiếm, thêm khách hàng/tài khoản |
| `UI.h` | `void MenuGiaoDich(TransactionLogic& trans)` | Truyền tham chiếu `TransactionLogic` để thực hiện nạp/rút/chuyển mà không cần sao chép lại toàn bộ đối tượng logic |
| `fileManager.h` | `void LoadAllData(BankSystem& bank)` | Truyền tham chiếu `BankSystem` để nạp dữ liệu từ file trực tiếp vào ba danh sách bên trong |
| `BankSystem.h` | `static bool kiemTraCCCDHopLe(const std::string& cccd)` | Truyền tham chiếu hằng `const std::string&` cho các hàm kiểm tra, tránh sao chép chuỗi dài 12 ký tự CCCD |

**b) Sử dụng con trỏ (Pointer) — ký hiệu `*`:**

Con trỏ được dùng để thao tác trực tiếp với bộ nhớ, đặc biệt trong cấu trúc danh sách liên kết và tìm kiếm đối tượng.

| Vị trí | Khai báo | Mục đích |
|---|---|---|
| `linkedList.h` | `Node<Y>* head; Node<Y>* tail;` | Con trỏ quản lý đầu và cuối danh sách liên kết; dùng `head` để duyệt, `tail` để thêm O(1) |
| `linkedList.h` | `Node<Y>* current = this->head;` | Con trỏ duyệt từng node trong hàm `clear()`; lưu `nextNode = current->next` trước khi `delete current` để giữ đường đi |
| `BankSystem.h` | `Customer* timKiemKhachHang(std::string maKH)` | Trả về địa chỉ của `Customer` tìm được, cho phép thao tác trực tiếp trên đối tượng thật thay vì bản sao |
| `TransactionLogic.h` | `BankSystem* bankSystem` | Con trỏ đến `BankSystem` để lớp giao dịch có thể truy cập dữ liệu khách hàng, tài khoản |

Ví dụ cụ thể: Trong `BankSystem::timKiemTaiKhoan()`, con trỏ trả về `&(current->data)` cho phép hàm gọi sửa đổi trực tiếp số dư của tài khoản:
```cpp
// TransactionLogic.cpp — rút tiền
Account* tk = this->bankSystem->timKiemTaiKhoan(soTK);
if (tk->rutTien(soTien) == false) return false;  // Thay đổi trực tiếp trên dữ liệu gốc
```

**c) Phân tách tham số đầu vào và giá trị trả về:**

Mỗi hàm đều có kiểu trả về rõ ràng, thường là `bool`, để biểu thị trạng thái thành công/thất bại của thao tác. Cách thiết kế này giúp kiểm soát luồng thực thi một cách nhất quán.

| Hàm | Tham số (input) | Trả về | Ý nghĩa |
|---|---|---|---|
| `BankSystem::themKhachHang()` | `maKH`, `hoTen`, `cccd`, `sdt` | `bool` | `true` nếu thêm thành công, `false` nếu mã KH đã tồn tại |
| `BankSystem::taoTaiKhoan()` | `soTK`, `maKH`, `maPIN`, `soDuBanDau` | `bool` | `false` nếu STK trùng, không tìm thấy KH, hoặc số dư < 50.000 |
| `Account::napTien()` | `soTien` | `bool` | `false` nếu số tiền <= 0 |
| `Account::rutTien()` | `soTien` | `bool` | `false` nếu số dư không đủ (số dư sau rút < 50.000) |
| `BankSystem::kiemTraCCCDHopLe()` | `const std::string& cccd` | `bool` | `false` nếu không đúng 12 chữ số |
| `TransactionLogic::NapTien()` | `soTK`, `soTien` | `bool` | Xâu chuỗi các kiểm tra, trả về `false` nếu bất kỳ bước nào thất bại |

Ví dụ về xâu chuỗi kiểm tra (chaining) trong `TransactionLogic::ChuyenKhoan()`:
```cpp
// Mỗi bước kiểm tra đều trả về false nếu thất bại, dừng ngay lập tức
if (soTien <= 0)               return false;  // Kiểm tra 1: số tiền > 0
if (soTKGui == soTKNhan)       return false;  // Kiểm tra 2: không chuyển cho chính mình
if (tkGui == NULL)             return false;  // Kiểm tra 3: tài khoản gửi tồn tại
if (tkNhan == NULL)            return false;  // Kiểm tra 4: tài khoản nhận tồn tại
if (tkGui->kiemTraPIN(maPIN) == false) return false; // Kiểm tra 5: PIN đúng
if (tkGui->rutTien(soTien) == false) return false;   // Kiểm tra 6: đủ số dư
```

### 3.2 Kỹ thuật đặt tên và trình bày mã trong chương trình

#### 3.2.1 Kỹ thuật đặt tên

Chương trình áp dụng nhất quán quy tắc đặt tên theo chuẩn **CamelCase** cho biến và hàm, và **PascalCase** cho lớp.

**a) Quy tắc đặt tên biến và hàm — CamelCase (chữ cái đầu viết thường, các từ sau viết hoa chữ cái đầu):**

| Tên | Loại | File | Ý nghĩa |
|---|---|---|---|
| `kiemTraPIN()` | Hàm | `account.h` | Hành động kiểm tra mã PIN |
| `soDuBanDau` | Biến tham số | `BankSystem.h` | Số dư ban đầu khi tạo tài khoản |
| `napTien()` | Hàm | `account.h` | Hành động nạp tiền |
| `rutTien()` | Hàm | `account.h` | Hành động rút tiền |
| `sinhMaKHMoi()` | Hàm | `BankSystem.h` | Hành động sinh mã khách hàng mới |
| `danhSachKH` | Biến thành viên | `BankSystem.h` | Danh sách khách hàng |
| `soLuongSai` | Biến cục bộ | `UI.cpp` | Đếm số lần sai PIN |
| `soNgayTrongThang` | Biến cục bộ | `BankSystem.cpp` | Số ngày trong tháng dùng để kiểm tra |

Cách đặt tên CamelCase thể hiện rõ bản chất của từng thành phần:
- Hàm bắt đầu bằng động từ mô tả hành động: `kiemTra...` (kiểm tra), `timKiem...` (tìm kiếm), `sinh...` (sinh), `xuat...` (xuất).
- Biến bắt đầu bằng danh từ mô tả dữ liệu: `soDu` (số dư), `danhSach` (danh sách), `maPIN` (mã PIN).

**b) Quy tắc đặt tên Lớp (Class) — PascalCase (chữ cái đầu mỗi từ viết hoa):**

| Tên lớp | File header | Vai trò |
|---|---|---|
| `Customer` | `customer.h` | Mô hình khách hàng |
| `Account` | `account.h` | Mô hình tài khoản |
| `Transaction` | `transaction.h` | Mô hình giao dịch |
| `BankSystem` | `BankSystem.h` | Hệ thống quản lý ngân hàng trung tâm |
| `TransactionLogic` | `TransactionLogic.h` | Xử lý nghiệp vụ giao dịch |
| `ReportLogic` | `ReportLogic.h` | Xử lý báo cáo và sao kê |
| `LinkedList` | `linkedList.h` | Cấu trúc danh sách liên kết template |

Quy tắc PascalCase giúp phân biệt rõ ràng giữa lớp (kiểu dữ liệu) và biến (thể hiện cụ thể). Ví dụ:
- `LinkedList<Account> danhSachTK;` — `LinkedList` là tên lớp (PascalCase), `danhSachTK` là biến thể hiện của lớp (CamelCase).

#### 3.2.2 Trình bày mã

**a) Kỹ thuật chia tách file:**

Toàn bộ mã nguồn được tổ chức theo mô hình phân tách khai báo (declaration) và triển khai (implementation):

| Loại | Thư mục | Đặc điểm |
|---|---|---|
| **Header files (`.h`)** | `include/` | Chứa khai báo lớp, phương thức, thuộc tính. Có `#ifndef` / `#define` / `#endif` để tránh include trùng lặp (include guard). |
| **Source files (`.cpp`)** | `src/` | Chứa cài đặt chi tiết các phương thức đã khai báo trong header. Include header bằng đường dẫn tương đối (ví dụ: `#include "../../include/models/customer.h"`). |

Chi tiết cấu trúc thư mục:

```
include/                          src/
├── data_structures/              ├── main.cpp
│   └── linkedList.h              ├── models/
├── models/                       │   ├── customer.cpp
│   ├── customer.h                │   ├── account.cpp
│   ├── account.h                 │   └── transaction.cpp
│   └── transaction.h             ├── services/
├── services/                     │   ├── BankSystem.cpp
│   ├── BankSystem.h              │   ├── TransactionLogic.cpp
│   ├── TransactionLogic.h        │   └── ReportLogic.cpp
│   └── ReportLogic.h             └── utils/
└── utils/                        ├── fileManager.cpp
    ├── fileManager.h             └── UI.cpp
    └── UI.h
```

Cơ chế include guard giúp tránh lỗi định nghĩa trùng lặp khi một header được include nhiều lần:
```cpp
// Ví dụ: include/models/customer.h
#ifndef CUSTOMER_H     // Nếu chưa được định nghĩa...
#define CUSTOMER_H     // ...thì định nghĩa nó
// ... nội dung file header ...
#endif                 // Kết thúc khối điều kiện
```

**b) Kỹ thuật thụt lề (Indentation):**

Mã nguồn sử dụng thụt lề 4 khoảng trắng (hoặc 1 tab) cho mỗi cấp độ khối lệnh, đảm bảo cấu trúc phân cấp của chương trình được thể hiện rõ ràng:

```cpp
// linkedList.h — thêm phần tử vào cuối danh sách
void addTail(Y newData) {                    // Cấp 0: định nghĩa hàm
    Node<Y>* newNode = new Node<Y>(newData); // Cấp 1: thân hàm

    if (this->head == NULL) {                // Cấp 1: if
        this->head = newNode;                // Cấp 2: thân if
        this->tail = newNode;                // Cấp 2: thân if
    } else {                                 // Cấp 1: else
        this->tail->next = newNode;          // Cấp 2: thân else
        this->tail = newNode;                // Cấp 2: thân else
    }
    this->count++;                           // Cấp 1: kết thúc if/else
}                                            // Cấp 0: kết thúc hàm
```

Các khối lệnh luôn được đóng gói trong cặp dấu ngoặc nhọn `{}` để tránh nhầm lẫn và lỗi logic, kể cả khi khối chỉ có một câu lệnh:
```cpp
// BankSystem.cpp — tuân thủ đóng gói {} cho mọi if/while
while (current != NULL) {                // Dùng {} dù chỉ có 1 lệnh bên trong
    if (current->data.getSoTK() == soTK) {
        return &(current->data);
    }
    current = current->next;
}
```

**c) Cấu trúc chú thích (Comments):**

Chương trình sử dụng hai loại chú thích:

**Chú thích khối (Block comments)** — đặt ở đầu mỗi hàm lớn hoặc đầu mỗi nhóm chức năng để mô tả mục đích tổng quát:

```cpp
// ==========================================
// 1. KIỂM TRA TRÙNG
// ==========================================
bool BankSystem::kiemTraTrungSTK(std::string soTK) { ... }

// ==========================================
// 3. THÊM KHÁCH HÀNG
// ==========================================
bool BankSystem::themKhachHang(...) { ... }

// ==========================================
// VALIDATION DỮ LIỆU ĐẦU VÀO
// ==========================================
bool BankSystem::kiemTraCCCDHopLe(const std::string& cccd) { ... }
```

**Chú thích dòng (Inline comments)** — đặt ở các khối logic phức tạp hoặc các bước quan trọng để giải thích chi tiết:

```cpp
// linkedList.h — hàm clear()
Node<Y>* nextNode = current->next;  // Lưu con trỏ next trước khi xóa
delete current;                      // Giải phóng vùng nhớ
current = nextNode;                  // Di chuyển đến node tiếp theo

// TransactionLogic.cpp — chuyển khoản
if (soTKGui == soTKNhan) {          // Không thể chuyển cho chính mình
    std::cout << "[LOI] Khong the chuyen khoan cho chinh minh!" << std::endl;
    return false;
}
tkGui->rutTien(soTien);             // Trừ tiền TK gửi trước
tkNhan->napTien(soTien);            // Cộng tiền cho TK nhận
```

Kỹ thuật chú thích này giúp:
- Người đọc mới có thể hiểu được cấu trúc tổng quan của file ngay từ cái nhìn đầu tiên (nhờ chú thích khối).
- Các bước xử lý phức tạp (như giải phóng Node trong LinkedList, kiểm tra điều kiện chuyển khoản) được giải thích rõ ràng, hạn chế hiểu nhầm khi bảo trì sau này.

<task_progress>
- [x] Read all key source files to understand project structure (Customer, Account, Transaction, BankSystem, TransactionLogic, LinkedList, UI, fileManager, main)
- [x] Write section 3.1: Kỹ thuật thiết kế cấu trúc chương trình (Top-down, Module hóa, 4 ưu điểm)
- [x] Write section 3.1.1: Các mô thức lập trình (OOP, Imperative, Defensive)
- [x] Write section 3.1.2: Kỹ thuật quản lý và xử lý dữ liệu (LinkedList, file persistence)
- [x] Write section 3.1.3: Kỹ thuật dùng hàm và tham số (pass-by-reference, pointer, return bool)
- [x] Write section 3.2.1: Kỹ thuật đặt tên (CamelCase, PascalCase)
- [x] Write section 3.2.2: Trình bày mã (file separation, indentation, comments)
- [x] Update PROJECT_REPORT.md with new Chapter 3 content replacing old sections 3.1-3.2
</task_progress>