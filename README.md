# IT012-mips-to-binary

## to-do list
1. viết hàm chuyển từ hex -> dec
2. để xử lí vấn đề địa chỉ: <br/>
    + tạo 1 map<string, int> lưu tên label : địa chỉ line của label
    + tạo biến int PC để đếm địa chỉ dưới dạng dec, mỗi lần dọc 1 lệnh thì PC += 4
    + lần đọc đầu xoá kí tự thùa, lưu vào 1 vector chứa pair<int, vector<string>> lines
    + trong đó pair.first là địa chỉ của dòng đó, bắt đầu từ 0, lưu dạng dec cho dễ tính toán
    + pair.second là words
    
    + lần đọc 3, lần đọc để dịch code
      + nếu gặp hàng mà words.size là 1 -> là label
        + tìm lại địa chỉ của label qua map -> tính offset = địa chỉ label - (địa chỉ dòng hiện tại + 4) / 4
        + chuyển offset về dạng bù 2(nếu âm) - 16bit để ghép vào trường immediate
  
  ví dụ: <br/>
  ```bash
  00000000: addi $s1, $zero, 0
  00000004: beq $s1, $zero, eee
  00000008: addi $s1, $s1, 1
  0000000c: eee:
  00000010: addi $s1, $s1, -1
  
  -> để tính immediate cho beq
  b1: tính (địa chỉ của label(eee) = (địa chỉ hiện tại(dòng 2) + 4)) = 00000004
  b2: chia cho 4 để ra offset: ta được 00000001 hay chính là 1
  b3: mở rộng thành số 16bit: 0000000000000001
  b4: chuyển về dạng bù 2, tuy nhiên TH này 1 > 0 nên không cần thực hiện
  ```
