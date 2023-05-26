# Đồ án IT012 MIPS to binary code
Build trình thông dịch hợp ngữ MIPS bằng C++ 

* Bao gồm lệnh nhóm lệnh I và R (Không yêu cầu code lệnh J)
* Input file .asm, output file .txt chứa binary code
* Các lệnh gồm
```bash
R:
add | addu | and
jr  | nor  | or
slt | sltu | sll
srl | sub  | subu

I:
addi | addiu | andi | beq | bne
lb   | lw    | ori  | sb  | sw
```
# Quy định Input
+ Không lỗi logic
+ Không lỗi syntax nặng như lệnh add $t1, $t2, $t3 mà lại input như sau
```bash
add
$t1
$t2
$t3
```
+ Lệnh có thể viết ở dạng tắt như: lw $s1, ($s2) thay cho lw $s1, 0($s2),... tuy nhiên không được thiếu tham số trong lệnh
+ Lệnh add với số vui lòng dùng addi,...
+ Không hỗ trợ .data, syscall,...

# Output
+ 1 file .txt chứa các dòng ở dạng: " PC(int) : code "
+ 1 file .txt chứa các dòng thể hiện code được dịch sang binary
+ 1 file .txt chứa các dòng thể hiện code được dịch sang hexa

*Contributors:[ Aph3li0s](https://github.com/Aph3li0s), [whynotkimhari](https://github.com/whynotkimhari), [phamtruc-work
](https://github.com/phamtruc-work)*
