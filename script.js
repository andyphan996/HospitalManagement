// Hàm đọc file JSON và hiển thị lên bảng
async function loadHospitals() {
    try {
        // Thêm tham số thời gian để trình duyệt không dùng bản lưu cũ (cache)
        const response = await fetch('out.json?t=' + new Date().getTime());
        if (!response.ok) return;

        const data = await response.json();
        const tbody = document.querySelector('#hospitalTable tbody');
        
        let html = '';
        data.forEach(h => {
            const row = `<tr class="updated">
                <td><strong>${h.name}</strong></td>
                <td><span class="city-badge">${h.city}</span></td>
                <td><span class="price-tag">${h.price.toLocaleString('vi-VN')} VNĐ</span></td>
            </tr>`;
            tbody.innerHTML += row;
        });
        
        // Chỉ cập nhật giao diện nếu dữ liệu có thay đổi để tránh lag
        if (tbody.innerHTML !== html) {
            tbody.innerHTML = html;
            console.log("Dữ liệu đã được cập nhật từ C++!");
        }
    } catch (error) {
        console.log("Đang chờ dữ liệu từ C++...");
    }
}

// Tự động chạy hàm loadHospitals mỗi 1000ms (1 giây)
setInterval(loadHospitals, 1000);

// Chạy lần đầu tiên khi mở trang
loadHospitals();