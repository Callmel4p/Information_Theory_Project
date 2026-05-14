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

# Ý tưởng giải quyết
## Phần 1: Bit class
Xây dựng class bit bằng `Bit.h` chứa những khai báo và `Bit.cpp` là triển khai của những khai báo thuộc tính của đối tượng bit.

Một giá trị  `value` dạng `bool` mang ý nghĩa giá trị của bit: `false -> 0` và `true -> 1`. Đối với 1 bit chúng ta có các phép toán trên trường GF(2):
-  Cộng/Trừ: thực chất là XOR(^) 2 value.
-  Nhân: thực chất là AND(&) 2 value.
-  Phủ định: là toán tử not(!) của 1 value.

Các phép so sánh: 2 bit là bằng hay khác nhau.

Ngoài ra có 1 số thuộc tính phụ trợ khác, xem trong file `Bit.cpp`

## Phần 2: BinaryVector class
Bản chất 1 từ mã nhị phân là 1 vector các bit. Ta dùng bit object để tạo nên binary object. Một số thuộc tính của class này:
- size: độ dài từ mã.
- hammingWeight: số bit khác không của từ mã.
  
Các phép toán với từ mã nhị phân:
- Cộng: Lấy lần lượt các bit ở các vị trí của 2 từ mã cộng với nhau.
- Gán.
- So sánh: bằng/khác.
- Dịch trái/phải.

Ngoài ra còn 1 số thuộc tính khác, xem chi tiết trong `BinaryVector.cpp`.

## Phần 3: Polynomial class
Polynomial object thực chất là 1 binary vector và bổ sung thêm các phép toán trên trường GF(2) và có ý nghĩa đại diện cho 1 đa thức. Đặt tên binaryvector đại diện là `coeff`, mỗi giá trị trong vector này tương ứng hệ số của đa thức (`coeff[i]` == hệ số của `x^i`).

Các thuộc tính của một Polynomial:
- `degree`: bậc của đa thức, tính bằng cách lấy index lớn nhất mà `coeff[i] != 0`. Đa thức không thì giá trị này là -1.
- `size`: độ dài từ mã tương ứng đa thức.

Các thao tác với một polynomial:
- Trim: xóa các số 0 vô nghĩa (ví dụ sau khi nhân/chia vector trở thành `[1,1,0,0]` tương đương đa thức `1 + x`. Ta cần xóa `0x^2 + 0x^3`, nên trim sẽ trả về `[1,1]`.). Trim sẽ giúp `coeff` luôn giữ ở dạng chuẩn, tránh bug khi thao tác.
- Cộng 2 polynomial a và b: cộng từng hệ số ở bậc tương ứng.
- Nhân 2 polynomial a và b: `result[i+j] += 1` với `a[i] == 1` và `b[j] == 1`.
- Chia 2 polynomial a và b: Giả sử a là số chia, lặp từ bậc của A - bậc của B, tức là bậc tối đa có thể của đa thức thương:
  - Nếu vẫn chia được tiếp -> ghi nhận kết quả vào thương -> khử để có remainder mới.
  - Không chia được tiếp thì không ảnh hưởng đến remainder hiện tại.
- So sánh 2 polynomial: bằng/khác.

Từ input, ta cần parse để có polynomial tương ứng, có 2 phiên bản: parse từ string dùng cho bản interactive (`main`) và parse từ chuỗi binary dùng cho bản ICPC (`icpc`). Ngược lại, từ polynomial, ta cần hàm `toString` để chuyển thành dạng đa thức để hiển thị (chỉ cần ở bản interactive).

Ngoài ra còn một số thuộc tính khác, xem chi tiết trong `Polynomial.cpp`.
