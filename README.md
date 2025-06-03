# 🐚 Tiny Shell

## 📌 Giới thiệu

**Tiny Shell** là trình thông dịch lệnh nhỏ gọn và hiệu quả được viết bằng C++ dành cho hệ điều hành Windows. Nó cung cấp một giao diện tương tác để thực thi các tác vụ cơ bản như quản lý file, thư mục, biến môi trường và tiến trình.

## 🚀 Tính năng nổi bật

* **Quản lý File và Thư mục:**

  * Tạo, xóa, di chuyển, đổi tên thư mục và file.
  * Liệt kê file theo định dạng, đọc và ghi file.

* **Quản lý Tiến trình:**

  * Khởi chạy, tạm dừng, hủy tiến trình.
  * Chạy tiến trình ở foreground/background.
  * Liệt kê tiến trình đang hoạt động.

* **Biến môi trường:**

  * Thêm/xóa biến môi trường, hiển thị danh sách các biến.

* **Các lệnh tiện ích:**

* Hiển thị thời gian, ngày tháng hệ thống.

* Máy tính bỏ túi (calculator).

* Hiệu ứng vui nhộn (dancing animation).

## 💻 Cách cài đặt🐚 Tiny Shell

## 📌 Giới thiệu

**Tiny Shell** là trình thông dịch lệnh nhỏ gọn và hiệu quả được viết bằng C++ dành cho hệ điều hành Windows. Nó cung cấp một giao diện tương tác để thực thi các tác vụ cơ bản như quản lý file, thư mục, biến môi trường và tiến trình.

## 🚀 Tính năng nổi bật

* **Quản lý File và Thư mục:**

  * Tạo, xóa, di chuyển, đổi tên thư mục và file.
  * Liệt kê file theo định dạng, đọc và ghi file.

* **Quản lý Tiến trình:**

  * Khởi chạy, tạm dừng, hủy tiến trình.
  * Chạy tiến trình ở foreground/background.
  * Liệt kê tiến trình đang hoạt động.

* **Biến môi trường:**

  * Thêm/xóa biến môi trường, hiển thị danh sách các biến.

* **Các lệnh tiện ích:**

Clone repository:

```bash
git clone <your_repository_url>
cd <your_repository>
```

Biên dịch chương trình (dùng MinGW trên Windows):

```bash
g++ -std=c++17 main.cpp Manager/*.cpp -o tiny_shell.exe
```

## 🚩 Cách sử dụng

Khởi động shell:

```bash
tiny_shell.exe
```

Một số lệnh phổ biến:

```shell
help                # Xem danh sách các lệnh hỗ trợ
cd <thư_mục>        # Đổi thư mục làm việc
dir                 # Liệt kê nội dung thư mục
create_file <file>  # Tạo một file mới
delete_file <file>  # Xóa một file
run_fg <file>       # Chạy tiến trình foreground
run_bg <file>       # Chạy tiến trình background
path                # Xem biến môi trường PATH
add_path <path>     # Thêm vào PATH
kill <pid>          # Hủy một tiến trình
exit                # Thoát khỏi shell
```

## 🎯 Mục đích

Shell này nhằm giúp người dùng dễ dàng tương tác với hệ thống, hiểu sâu hơn về cách hoạt động của tiến trình, file system và biến môi trường trong lập trình C++ và Windows API.

## 📜 Bản quyền

Dự án được phát hành theo giấy phép MIT.
