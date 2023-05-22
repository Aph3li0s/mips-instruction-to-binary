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
+ Không lỗi syntax như thiếu tham số trong 1 lệnh
+ Không code dưới dạng
```bash
label_name_1 : label_name_2: code
```
+ Tuy nhiên, trường hợp này sẽ được chấp nhận
```bash
label_name : code
```

*Contributors:[ Aph3li0s](https://github.com/Aph3li0s), [whynotkimhari](https://github.com/whynotkimhari), [phamtruc-work
](https://github.com/phamtruc-work)*
