
# Hướng dẫn chơi game
## 1. Khởi tạo trò chơi
- Vào file **main.cpp**, sau đó nhấn **F9** để bắt đầu chơi.
## 2. Nội dung trò chơi:
- Đầu tiên, giao diện trò chơi xuất hiện:
  - Chính giữa màn hình: Câu hỏi được lựa chọn ngẫu nhiên.
  - Bảng chữ cái: Người dùng trả lời bằng cách nhấn vào các kí tự trong bảng. Dùng DELETE để xoá 1 kí tự đang nhập, dùng ENTER để gửi câu trả lời.
  - Bên trái: Gợi ý số lượng kí tự của từ cần đoán
  - Bên phải: Điểm số của người chơi. Với mỗi câu hỏi, người chơi sẽ có 30 điểm. Nếu trả lời đúng, số điểm sẽ giữ nguyên; nếu trả lời sai, người chơi sẽ bị trừ 10 điểm. Khi sai quá 3 lần (0 điểm), hệ thống sẽ bỏ qua câu hỏi đó.
- Sau khi trả lời đúng hoặc sai quá 3 lần, người chơi sẽ lựa chọn chơi tiếp hoặc dừng lại bằng cách nhấn phím Y (chơi tiếp) hoặc N (dừng lại).
  - Với lựa chọn Y, hệ thống sẽ đưa ra câu hỏi tiếp theo được lựa chọn ngẫu nhiên.
  - Với lựa chọn N: Nếu số điểm của câu hỏi hiện tại lớn hơn 0, người chơi thắng; Ngược lại, người chơi thua. Sau đó trò chơi kết thúc.






