# Information_Theory_Project
Part 2 in my project of Information theory in semester 4 in PTIT
# Thông tin môn học
- Môn: Lý thuyết thông tin PTIT.
- Giảng viên: Phạm Văn Sự.
- Mã lớp: Nhóm 4 lớp CT01.

# Thành viên
- Bùi Quốc Lập - B24DCAT161.
- Nguyễn Như Sáng - B24DCAT243.
- Vũ Minh Tân - B24DCAT247.
  
# Đề bài chung
Sử dụng ngôn ngữ lập trình C/C++ hoàn thành bài tập theo yêu cầu. Mỗi nhóm chỉ có một đề. Nhóm tập hợp và thực hiện phân công. Chương trình được lập trình sao cho có thể kiểm thử được dữ liệu của các ví dụ trong môn học và theo chuẩn ICPC. Bonus cho các nhóm xây dựng ứng dụng hoàn chỉnh cho phép lựa chọn input chuẩn nhưng cho phép lựa chọn output theo dạng đầy đủ lời giải tự luận, sinh kết quả cho các câu trắc nghiệm.

# Yêu cầu nhóm được giao
Xây dựng class bit, vector từ mã nhị phân và các helper class khác nếu cần. Kiểm tra một đa thức có phải là đa thức kiểm tra của một mã vòng tuyến tính C(l,k) không.

# Cấu trúc project
- `Bit.h`: header khai báo những thuộc tính dùng trong `Bit.cpp`.
- `Bit.cpp`: chương trình C++ triển khai class bit.
- `BinaryVector.h`: header khai báo những thuộc tính dùng trong `BinaryVector.cpp`.
- `BinaryVector.cpp`: triển khai class vector từ mã nhị phân.
- `Polynomial.h`: header khai báo những thuộc tính dùng trong `Polynomial.cpp`.
- `Polynomial.cpp`: triển khai class đa thức.
- `main.cpp`: source code cho phiên bản input đầy đủ (ví dụ x^3 + x + 1) và được lựa chọn giải nhanh hoặc chi tiết.
- `main_icpc.cpp`: source code cho phiên bản input dạng icpc (t testcase, nhập n,k, đa thức cho dưới dạng 10101...) và output YES/NO.
- `main`: executable tạo từ `main.cpp`, có được bằng cách biên dịch `g++ main.cpp Bit.cpp BinaryVector.cpp Polynomial.cpp -o main`.
- `icpc`: executable tạo từ `main_icpc.cpp`, có được bằng cách biên dịch `g++ main_icpc.cpp Bit.cpp BinaryVector.cpp Polynomial.cpp -o icpc`.
- Folder `icpc_tests` chứa các test case dưới dạng ICPC.
