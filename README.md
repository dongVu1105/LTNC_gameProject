
# Hướng dẫn chơi game CatchTheWord
## 1. Khởi tạo trò chơi
- Vào  **CatchTheWord/main.cpp**, sau đó nhấn **F9** để bắt đầu chơi.
## 2. Nội dung trò chơi:
- Đầu tiên, giao diện trò chơi xuất hiện:
  
  <img src="https://github.com/dongVu1105/LTNC_gameProject/assets/157719316/5ef1779f-85c4-4b40-aa61-2429872c00be" alt="..." width="600" />
  
  - Chính giữa màn hình: Câu hỏi được lựa chọn ngẫu nhiên.
  - Bảng chữ cái: Người dùng trả lời bằng cách nhấn vào các kí tự trong bảng. Dùng DELETE để xoá 1 kí tự đang nhập, dùng ENTER để gửi câu trả lời.
  - Bên trái: Gợi ý số lượng kí tự của từ cần đoán
  - Bên phải: Điểm số của người chơi.
- Với mỗi câu hỏi, người chơi sẽ có 30 điểm.
  - Nếu trả lời đúng, số điểm sẽ giữ nguyên.

    <img src="https://github.com/dongVu1105/LTNC_gameProject/assets/157719316/c60474a0-6daa-4860-8be9-fbfb80a2fc09" alt="..." width="600" />
    
  - Nếu trả lời sai, người chơi sẽ bị trừ 10 điểm.
 
    <img src="https://github.com/dongVu1105/LTNC_gameProject/assets/157719316/9f393993-d899-46a9-906d-429abcb65d3d" alt="..." width="600" />
    
  - Khi sai quá 3 lần (0 điểm), hệ thống sẽ bỏ qua câu hỏi đó.
 
    <img src="https://github.com/dongVu1105/LTNC_gameProject/assets/157719316/21095eb2-f1de-4be5-b613-6650b8503011" alt="..." width="600" />
    
- Sau khi trả lời đúng (hoặc sai quá 3 lần), người chơi sẽ lựa chọn chơi tiếp hoặc dừng lại bằng cách nhấn phím Y (chơi tiếp) hoặc N (dừng lại).

  <img src="https://github.com/dongVu1105/LTNC_gameProject/assets/157719316/fb9f1aeb-930d-46ea-b997-8762c718432c" alt="..." width="600" />
  
  - Với lựa chọn Y, hệ thống sẽ bắt đầu một câu hỏi mới (được lựa chọn ngẫu nhiên).
  - Với lựa chọn N: Nếu số điểm của câu hỏi hiện tại lớn hơn 0, người chơi thắng; Ngược lại, người chơi thua.
 
    <img src="https://github.com/dongVu1105/LTNC_gameProject/assets/157719316/9589baf1-8d4b-426c-a190-f95d6091c71d" alt="..." width="600" />
 
    <img src="https://github.com/dongVu1105/LTNC_gameProject/assets/157719316/9159b506-13f7-4ca0-86c0-751d7d84d110" alt="..." width="600" />
    
  - Cuối cùng, trò chơi kết thúc.






