// Lấy các phần tử lưới
let playerGrid = document.querySelector('.player-grid');
let computerGrid = document.querySelector('.computer-grid');
let statusMessage = document.getElementById('statusMessage');
let startButton = document.getElementById('startGame');
let statusComputerMessage = document.getElementById('statusComputerMessage');
let statusPlayerMessage = document.getElementById('statusPlayerMessage');
// Tạo lưới 10x10
let gridSize = 10;
let playerBoard = [];
let computerBoard = [];
let playerShips = 0;
let currentShipLength = 0;  // Độ dài thuyền hiện tại
let direction = 'horizontal';  // Hướng của thuyền, 'horizontal' hoặc 'vertical'
let currentShipIndex = 0;

// Trạng thái lượt của người chơi
let playerAttacked = false;
let playerAttackedCells = []; // Mảng theo dõi ô đã bị tấn công của người chơi
let computerAttackedCells = []; // Mảng theo dõi ô đã bị tấn công của máy

// Danh sách các thuyền với độ dài khác nhau
let ships = [
    { name: 'Hàng không mẫu hạm', length: 5 },
    { name: 'Tàu chiến', length: 4 },
    { name: 'Tàu tuần dương', length: 3 },
    { name: 'Tàu ngầm', length: 3 },
    { name: 'Tàu khu trục', length: 2 }
];

// Khởi tạo lưới trống
function createBoard(gridElement, board, isPlayer = false) {
    for (let i = 0; i < gridSize; i++) {
        const row = [];
        for (let j = 0; j < gridSize; j++) {
            const cell = document.createElement('div');
            cell.classList.add('bg-gray-300', 'h-10', 'w-10', 'border', 'border-black');
            if (isPlayer) {
                cell.addEventListener('click', () => placePlayerShip(i, j));
            }
            gridElement.appendChild(cell);
            row.push(cell);
        }
        board.push(row);
    }
}
let playerShipsCount = 17;  // Tổng số thuyền của người chơi
let computerShipsCount = 17; // Tổng số thuyền của máy

// Người chơi tự đặt thuyền
function placePlayerShip(x, y) {
    const ship = ships[currentShipIndex];  // Lấy thuyền hiện tại từ danh sách
    currentShipLength = ship.length;

    if (canPlaceShip(x, y, currentShipLength, direction, playerBoard)) {
        placeShipOnBoard(x, y, currentShipLength, direction, playerBoard);
        playerShips++;
        currentShipIndex++;  // Chuyển sang thuyền tiếp theo

        if (currentShipIndex < ships.length) {
            statusMessage.textContent = `Đã đặt ${ship.name}. Tiếp tục đặt ${ships[currentShipIndex].name}.`;
        } else {
            startButton.disabled = false;
            statusMessage.textContent = "Đã đặt đủ chiến hạm! Bắt đầu trò chơi.";
        }
    } else {
        statusMessage.textContent = "Không thể đặt tàu ở đây!";
    }
}

// Kiểm tra nếu có thể đặt thuyền tại vị trí được chọn
function canPlaceShip(x, y, length, direction, board) {
    if (direction === 'horizontal') {
        if (y + length > gridSize) return false;
        for (let i = 0; i < length; i++) {
            if (board[x][y + i].classList.contains('ship')) return false;
        }
    } else {
        if (x + length > gridSize) return false;
        for (let i = 0; i < length; i++) {
            if (board[x + i][y].classList.contains('ship')) return false;
        }
    }
    return true;
}

// Đặt thuyền lên lưới
function placeShipOnBoard(x, y, length, direction, board, isComputer = false) {
    if (direction === 'horizontal') {
        for (let i = 0; i < length; i++) {
            board[x][y + i].classList.add('ship');
            if (!isComputer) board[x][y + i].classList.add('bg-yellow-500');  // Hiển thị thuyền người chơi
        }
    } else {
        for (let i = 0; i < length; i++) {
            board[x + i][y].classList.add('ship');
            if (!isComputer) board[x + i][y].classList.add('bg-yellow-500');  // Hiển thị thuyền người chơi
        }
    }
}

// Đặt thuyền ngẫu nhiên cho máy
function placeShips(board) {
    ships.forEach(ship => {
        let placed = false;
        while (!placed) {
            const direction = Math.random() > 0.5 ? 'horizontal' : 'vertical';
            const x = Math.floor(Math.random() * gridSize);
            const y = Math.floor(Math.random() * gridSize);
            if (canPlaceShip(x, y, ship.length, direction, board)) {
                placeShipOnBoard(x, y, ship.length, direction, board, true);  // isComputer = true
                placed = true;
            }
        }
    });
}

// Người chơi tấn công máy
function playerAttack(x, y) {
    if (computerAttackedCells.includes(`${x},${y}`)) {
        statusPlayerMessage.textContent = "Ô này đã bị tấn công rồi!";
        return; // Nếu ô đã bị tấn công, không thực hiện tấn công
    }
    statusPlayerMessage.textContent = "";
    computerAttackedCells.push(`${x},${y}`); // Thêm ô vào danh sách đã tấn công

    if (computerBoard[x][y].classList.contains('ship')) {
        computerBoard[x][y].classList.add('bg-red-500');  // Hiển thị thuyền bị bắn trúng
        statusPlayerMessage.textContent = "Bạn đã trúng mục tiêu!";
        computerShipsCount--;  // Giảm số thuyền của máy đi 1

        if (computerShipsCount === 0) {
            statusMessage.textContent = "Bạn đã thắng!";
            resetGame();
        }
    } else {
        computerBoard[x][y].classList.remove('bg-gray-300');
        computerBoard[x][y].classList.add('bg-blue-500');
        statusPlayerMessage.textContent = "Bạn đã bắn trượt!";
    }
    
    playerAttacked = true;  // Đặt trạng thái lượt của người chơi thành true
}

// Máy tấn công ngẫu nhiên người chơi
function computerAttack() {
    if (!playerAttacked || playerShipsCount === 0) return; // Nếu người chơi chưa tấn công hoặc đã thua, không thực hiện tấn công
    statusComputerMessage.textContent = "";
    let x, y;
    do {
        x = Math.floor(Math.random() * gridSize);
        y = Math.floor(Math.random() * gridSize);
    } while (playerAttackedCells.includes(`${x},${y}`)); // Lặp lại cho đến khi tìm được ô chưa bị tấn công

    playerAttackedCells.push(`${x},${y}`); // Thêm ô vào danh sách đã tấn công

    if (playerBoard[x][y].classList.contains('ship')) {
        playerBoard[x][y].classList.remove('bg-yellow-500')
        playerBoard[x][y].classList.add('bg-red-500')
        playerShipsCount--;  // Giảm số thuyền của người chơi đi 1
        statusComputerMessage.textContent += " Máy bắn trúng!";
        
        if (playerShipsCount === 0) {
            statusMessage.textContent = "Bạn đã thua!";
            resetGame();
        }
    } else {
        playerBoard[x][y].classList.remove('bg-gray-300');
        playerBoard[x][y].classList.add('bg-blue-500');
        statusComputerMessage.textContent += " Máy bắn trượt!";
    }
    playerAttacked = false;  // Đặt trạng thái lượt của người chơi thành false cho lượt tiếp theo
}

// Reset game
function resetGame() {
    // Khôi phục biến đếm số thuyền
    playerShipsCount = 17;  
    computerShipsCount = 17;
    playerAttackedCells = []; // Reset danh sách ô đã tấn công của người chơi
    computerAttackedCells = []; // Reset danh sách ô đã tấn công của máy

    // Xóa lưới hiện tại và khởi tạo lại lưới
    playerBoard = [];
    computerBoard = [];
    playerGrid.innerHTML = '';
    computerGrid.innerHTML = '';
    
    
    
    // Đặt lại trạng thái lượt người chơi
    playerAttacked = false; 

    // Khởi động lại lưới sau 3 giây
    setTimeout(initPlayerBoard, 3000);
}

// Khởi động game
function startGame() {
    computerBoard = [];
    computerGrid.innerHTML = '';
    createBoard(computerGrid, computerBoard);
    placeShips(computerBoard);
    statusMessage.textContent = "Bắt đầu game!";
    computerGrid.addEventListener('click', (event) => {
        const index = Array.from(computerGrid.children).indexOf(event.target);
        const x = Math.floor(index / gridSize);
        const y = index % gridSize;
        playerAttack(x, y);
        computerAttack();
    });
    let computerAreaH2 = document.querySelector('.computer-area h2')
    computerAreaH2.classList.remove('hidden')
}

// Khởi tạo lưới cho người chơi đặt thuyền
function initPlayerBoard() {
    playerBoard = [];
    playerGrid.innerHTML = '';
    statusPlayerMessage.textContent = "";
    createBoard(playerGrid, playerBoard, true);
    currentShipIndex = 0;
    statusMessage.textContent = `Hãy đặt ${ships[currentShipIndex].name} (dài ${ships[currentShipIndex].length}) | Nhấn phím r để đổi hướng đặt`;
    startButton.disabled = true;
}

// Thay đổi hướng thuyền khi nhấn phím 'r'
window.addEventListener('keydown', (event) => {
    if (event.key === 'r') {
        direction = direction === 'horizontal' ? 'vertical' : 'horizontal';
        statusMessage.textContent = `Hướng thuyền hiện tại: ${direction}`;
    }
});

// Sự kiện bắt đầu game
startButton.addEventListener('click', startGame);

// Khởi tạo lưới khi tải trang
initPlayerBoard();







