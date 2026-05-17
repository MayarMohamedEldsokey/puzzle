import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Window 2.15

Window {
    id: window
    width: 1300
    height: 750
    visible: true
    title: "CrossWordQuest"
    color: "#1a1a2e"

    property string currentScreen: "difficulty"
    property string selectedDifficulty: ""
    property int selectedLevel: 1
    property int totalScore: 0   // النقاط المستمرة عبر المستويات

    // بيانات المستويات (15 مستوى لكل صعوبة)
    property var levelsData: {
        "Easy": [
            { words: ["DOG", "CAT", "SUN", "CAR", "BED", "HAT"], hint: "كلمات بسيطة" },
            { words: ["HOT", "COLD", "WARM", "COOL", "DRY", "WET"], hint: "صفات" },
            { words: ["RUN", "JUMP", "WALK", "SIT", "STAND", "FALL"], hint: "أفعال حركة" },
            { words: ["RED", "BLUE", "GREEN", "YELLOW", "BLACK", "WHITE"], hint: "ألوان" },
            { words: ["HAPPY", "SAD", "MAD", "GLAD", "CALM", "WILD"], hint: "مشاعر" },
            { words: ["DAY", "NIGHT", "WEEK", "MONTH", "YEAR", "HOUR"], hint: "وقت" },
            { words: ["UP", "DOWN", "LEFT", "RIGHT", "NORTH", "SOUTH"], hint: "اتجاهات" },
            { words: ["OPEN", "CLOSE", "LOCK", "UNLOCK", "START", "STOP"], hint: "أفعال" },
            { words: ["LOVE", "LIKE", "HATE", "ADORE", "DESPISE", "ENJOY"], hint: "مشاعر" },
            { words: ["APPLE", "BANANA", "ORANGE", "GRAPE", "MANGO", "PEACH"], hint: "فواكه" },
            { words: ["SUN", "MOON", "STAR", "CLOUD", "RAIN", "SNOW"], hint: "طقس" },
            { words: ["BOOK", "PEN", "PAPER", "DESK", "CHAIR", "TABLE"], hint: "أشياء" },
            { words: ["TEACHER", "DOCTOR", "ENGINEER", "NURSE", "DRIVER", "FARMER"], hint: "مهن" },
            { words: ["SCHOOL", "HOSPITAL", "OFFICE", "HOME", "PARK", "MUSEUM"], hint: "أماكن" },
            { words: ["HAPPY", "SAD", "ANGRY", "CALM", "PROUD", "SHY"], hint: "مشاعر" }
        ],
        "Medium": [
            { words: ["PYTHON", "JAVA", "SWIFT", "KOTLIN", "RUBY", "GO"], hint: "لغات برمجة" },
            { words: ["LOGIC", "ALGO", "CODE", "DATA", "ARRAY", "LOOP"], hint: "مصطلحات برمجية" },
            { words: ["MOUSE", "KEYBOARD", "SCREEN", "MONITOR", "PRINTER", "SCANNER"], hint: "كمبيوتر" },
            { words: ["WATER", "EARTH", "FIRE", "AIR", "SOIL", "ROCK"], hint: "عناصر" },
            { words: ["SUMMER", "WINTER", "SPRING", "AUTUMN", "MONTH", "WEEK"], hint: "فصول ووقت" },
            { words: ["CIRCLE", "SQUARE", "TRIANGLE", "RECTANGLE", "OVAL", "DIAMOND"], hint: "أشكال" },
            { words: ["MUSIC", "ART", "DANCE", "THEATER", "CINEMA", "POETRY"], hint: "فنون" },
            { words: ["SCIENCE", "MATH", "PHYSICS", "CHEMISTRY", "BIOLOGY", "ASTRONOMY"], hint: "علوم" },
            { words: ["HISTORY", "GEOGRAPHY", "POLITICS", "ECONOMY", "SOCIOLOGY", "PHILOSOPHY"], hint: "علوم إنسانية" },
            { words: ["SPORTS", "GAMES", "PLAY", "COMPETE", "WIN", "LOSE"], hint: "رياضة" },
            { words: ["FAMILY", "FRIENDS", "LOVE", "CARE", "TRUST", "HONESTY"], hint: "علاقات" },
            { words: ["DOCTOR", "TEACHER", "ENGINEER", "NURSE", "LAWYER", "JUDGE"], hint: "مهن" },
            { words: ["BREAKFAST", "LUNCH", "DINNER", "SNACK", "MEAL", "FOOD"], hint: "وجبات" },
            { words: ["HAPPINESS", "SADNESS", "ANGER", "FEAR", "JOY", "LOVE"], hint: "مشاعر" },
            { words: ["BEAUTIFUL", "WONDERFUL", "AMAZING", "FANTASTIC", "EXCELLENT", "PERFECT"], hint: "صفات" }
        ],
        "Hard": [
            { words: ["ALGORITHM", "DATABASE", "NETWORK", "PROTOCOL", "ENCRYPTION", "DECRYPTION"], hint: "تقنية متقدمة" },
            { words: ["ARTIFICIAL", "INTELLIGENCE", "MACHINE", "LEARNING", "DEEP", "NEURAL"], hint: "ذكاء اصطناعي" },
            { words: ["CRYPTOGRAPHY", "SECURITY", "ENCRYPT", "DECRYPT", "HASH", "SALT"], hint: "أمن معلومات" },
            { words: ["QUANTUM", "PHYSICS", "PARTICLE", "WAVE", "ATOM", "MOLECULE"], hint: "فيزياء" },
            { words: ["BIOLOGY", "CHEMISTRY", "GENETICS", "MICROSCOPE", "CELL", "DNA"], hint: "علوم طبيعية" },
            { words: ["PHILOSOPHY", "ETHICS", "LOGIC", "METAPHYSICS", "EPISTEMOLOGY", "AESTHETICS"], hint: "فلسفة" },
            { words: ["ECONOMICS", "FINANCE", "MARKET", "BUDGET", "INVESTMENT", "STOCK"], hint: "اقتصاد" },
            { words: ["PSYCHOLOGY", "BEHAVIOR", "MIND", "BRAIN", "COGNITION", "PERCEPTION"], hint: "علم نفس" },
            { words: ["LITERATURE", "POETRY", "NOVEL", "DRAMA", "FICTION", "NONFICTION"], hint: "أدب" },
            { words: ["ARCHITECTURE", "DESIGN", "STRUCTURE", "BUILDING", "CONSTRUCTION", "FOUNDATION"], hint: "عمارة" },
            { words: ["ASTRONOMY", "STARS", "GALAXY", "PLANET", "MOON", "SUN"], hint: "فلك" },
            { words: ["GEOLOGY", "MINERALS", "ROCKS", "FOSSIL", "MAGMA", "LAVA"], hint: "جيولوجيا" },
            { words: ["ZOOLOGY", "ANIMALS", "SPECIES", "HABITAT", "ECOSYSTEM", "BIODIVERSITY"], hint: "حيوانات" },
            { words: ["BOTANY", "PLANTS", "FLORA", "FLOWER", "TREE", "GRASS"], hint: "نباتات" },
            { words: ["MEDICINE", "SURGERY", "THERAPY", "DIAGNOSIS", "TREATMENT", "PREVENTION"], hint: "طب" }
        ]
    }

    // بيانات اللعبة الحالية
    property var currentWords: []
    property var currentGrid: []
    property var selectedCells: []
    property int currentLevelScore: 0
    property int wordsFoundCount: 0
    property int lastRow: -1
    property int lastCol: -1
    property int wrongAttempts: 0
    property int timeLeft: 300
    property bool gameActive: true

    // دالة توليد شبكة عشوائية
    function generateGrid(words, size) {
        var grid = Array(size).fill().map(() => Array(size).fill(''))
        for(var w = 0; w < words.length; w++) {
            var word = words[w].word
            var placed = false
            var attempts = 0
            while(!placed && attempts < 200) {
                var direction = Math.floor(Math.random() * 2)
                var row = Math.floor(Math.random() * size)
                var col = Math.floor(Math.random() * size)
                if(direction === 0 && col + word.length <= size) {
                    var canPlace = true
                    for(var i = 0; i < word.length; i++) {
                        if(grid[row][col + i] !== '' && grid[row][col + i] !== word[i]) {
                            canPlace = false
                            break
                        }
                    }
                    if(canPlace) {
                        for(i = 0; i < word.length; i++) grid[row][col + i] = word[i]
                        placed = true
                    }
                } else if(direction === 1 && row + word.length <= size) {
                    canPlace = true
                    for(i = 0; i < word.length; i++) {
                        if(grid[row + i][col] !== '' && grid[row + i][col] !== word[i]) {
                            canPlace = false
                            break
                        }
                    }
                    if(canPlace) {
                        for(i = 0; i < word.length; i++) grid[row + i][col] = word[i]
                        placed = true
                    }
                }
                attempts++
            }
        }
        var letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        for(var r = 0; r < size; r++)
            for(var c = 0; c < size; c++)
                if(grid[r][c] === '')
                    grid[r][c] = letters[Math.floor(Math.random() * letters.length)]
        return grid
    }

    function loadLevel() {
        var levelData = levelsData[selectedDifficulty][selectedLevel - 1]
        var wordsList = []
        for(var i = 0; i < levelData.words.length; i++)
            wordsList.push({ word: levelData.words[i], found: false, hint: levelData.hint })
        currentWords = wordsList
        currentGrid = generateGrid(currentWords, 12)
        currentLevelScore = 0
        wordsFoundCount = 0
        wrongAttempts = 0
        gameActive = true
        timeLeft = selectedDifficulty === "Easy" ? 480 : (selectedDifficulty === "Medium" ? 360 : 300)
        updateTimerDisplay()
        gameScoreText.text = "Level Score: 0"
        gameTotalScoreText.text = "Total Score: " + totalScore
        gameFoundCountText.text = "0/" + currentWords.length + " Words"
        gameWrongCountText.text = "Mistakes: 0"
        wordsListView.model = currentWords
        for(var r = 0; r < 12; r++)
            for(var c = 0; c < 12; c++) {
                var cell = gridRepeater.itemAt(r * 12 + c)
                if(cell) cell.reset()
            }
        clearGameSelection()
        gameResultMessage.visible = false
        if(gameTimer) gameTimer.stop()
        gameTimer.start()
        currentScreen = "game"
    }

    function checkSelectedWord() {
        if(selectedCells.length === 0 || !gameActive) return
        var selectedWord = ""
        for(var i = 0; i < selectedCells.length; i++)
            selectedWord += currentGrid[selectedCells[i].row][selectedCells[i].col]
        var found = false
        for(var j = 0; j < currentWords.length; j++) {
            if(!currentWords[j].found && currentWords[j].word === selectedWord) {
                currentWords[j].found = true
                wordsFoundCount++
                var points = 100
                currentLevelScore += points
                totalScore += points
                gameScoreText.text = "Level Score: " + currentLevelScore
                gameTotalScoreText.text = "Total Score: " + totalScore
                gameFoundCountText.text = wordsFoundCount + "/" + currentWords.length + " Words"
                wordsListView.model = currentWords
                for(var k = 0; k < selectedCells.length; k++) {
                    var cellItem = gridRepeater.itemAt(selectedCells[k].row * 12 + selectedCells[k].col)
                    if(cellItem) cellItem.markAsFound()
                }
                gameResultMessage.text = "🎉 +" + points + " Found: " + selectedWord + " 🎉"
                gameResultMessage.color = "#2ecc71"
                gameResultMessage.visible = true
                resultTimer.start()
                found = true
                break
            }
        }
        if(!found && selectedWord.length > 1) {
            wrongAttempts++
            gameWrongCountText.text = "Mistakes: " + wrongAttempts
            gameResultMessage.text = "❌ " + selectedWord + " is not correct! -30 ❌"
            gameResultMessage.color = "#e74c3c"
            gameResultMessage.visible = true
            resultTimer.start()
            if(gameActive) {
                currentLevelScore = Math.max(0, currentLevelScore - 30)
                totalScore = Math.max(0, totalScore - 30)
                gameScoreText.text = "Level Score: " + currentLevelScore
                gameTotalScoreText.text = "Total Score: " + totalScore
            }
        }
        clearGameSelection()
        if(wordsFoundCount === currentWords.length && gameActive) {
            gameActive = false
            gameTimer.stop()
            levelCompleteDialog.visible = true
        }
    }

    function clearGameSelection() {
        for(var i = 0; i < selectedCells.length; i++) {
            var cellItem = gridRepeater.itemAt(selectedCells[i].row * 12 + selectedCells[i].col)
            if(cellItem && !cellItem.isFound) cellItem.deselect()
        }
        selectedCells = []
        lastRow = -1
        lastCol = -1
    }

    function addToSelection(row, col) {
        if(!gameActive) return
        var existingCell = gridRepeater.itemAt(row * 12 + col)
        if(existingCell && existingCell.isFound) return
        for(var i = 0; i < selectedCells.length; i++)
            if(selectedCells[i].row === row && selectedCells[i].col === col) return
        if(selectedCells.length > 0) {
            var lastCell = selectedCells[selectedCells.length - 1]
            var isHorizontal = (lastCell.row === row && Math.abs(lastCell.col - col) === 1)
            var isVertical = (lastCell.col === col && Math.abs(lastCell.row - row) === 1)
            if(!isHorizontal && !isVertical) clearGameSelection()
        }
        selectedCells.push({ row: row, col: col })
        var cellItem = gridRepeater.itemAt(row * 12 + col)
        if(cellItem && !cellItem.isFound) cellItem.select()
        lastRow = row
        lastCol = col
    }

    function updateTimerDisplay() {
        var minutes = Math.floor(timeLeft / 60)
        var seconds = timeLeft % 60
        gameTimerText.text = "⏱️ " + (minutes < 10 ? "0" + minutes : minutes) + ":" + (seconds < 10 ? "0" + seconds : seconds)
    }

    function goToLevels() {
        if(gameTimer) gameTimer.stop()
        currentScreen = "levels"
    }

    function nextLevel() {
        if(selectedLevel < 15) {
            selectedLevel++
            loadLevel()
            levelCompleteDialog.visible = false
        } else {
            levelCompleteDialog.visible = false
            gameCompleteDialog.visible = true
        }
    }

    Timer {
        id: gameTimer
        interval: 1000
        repeat: true
        onTriggered: {
            if(gameActive && timeLeft > 0) {
                timeLeft--
                updateTimerDisplay()
                if(timeLeft === 0) {
                    gameActive = false
                    gameResultMessage.text = "⏰ Time's Up! Game Over! ⏰"
                    gameResultMessage.visible = true
                }
            }
        }
    }

    Timer {
        id: resultTimer
        interval: 2000
        onTriggered: gameResultMessage.visible = false
    }

    // -------------------- شاشة اختيار الصعوبة --------------------
    Rectangle {
        anchors.fill: parent
        color: "#f4f7fa"
        visible: currentScreen === "difficulty"
        ColumnLayout {
            anchors.centerIn: parent
            width: 900
            spacing: 30
            Text { text: "Choose Difficulty"; font.pixelSize: 36; font.bold: true; color: "#0f172a"; Layout.alignment: Qt.AlignHCenter }
            Row {
                spacing: 30
                Rectangle { width: 260; height: 400; radius: 20; color: "white"
                    ColumnLayout { anchors.fill: parent; anchors.margins: 20; spacing: 15
                        Text { text: "🌿 EASY"; font.pixelSize: 24; font.bold: true; color: "#27ae60" }
                        Text { text: "15 Levels"; font.pixelSize: 14; color: "#7f8c8d" }
                        Text { text: "6 words per level\n8 minutes time limit"; font.pixelSize: 12; color: "#5a5a5a" }
                        Item { Layout.fillHeight: true }
                        Button { text: "Start"; Layout.alignment: Qt.AlignHCenter; background: Rectangle { color: "#27ae60"; radius: 10 }
                            contentItem: Text { text: parent.text; color: "white"; font.bold: true }
                            onClicked: { selectedDifficulty = "Easy"; currentScreen = "levels" } }
                    }
                }
                Rectangle { width: 260; height: 400; radius: 20; color: "#0842a8"
                    ColumnLayout { anchors.fill: parent; anchors.margins: 20; spacing: 15
                        Text { text: "⚡ MEDIUM"; font.pixelSize: 24; font.bold: true; color: "#f39c12" }
                        Text { text: "15 Levels"; font.pixelSize: 14; color: "#bbd3ff" }
                        Text { text: "6 words per level\n6 minutes time limit\nx2 score"; font.pixelSize: 12; color: "#d0d0d0" }
                        Item { Layout.fillHeight: true }
                        Button { text: "Accept"; Layout.alignment: Qt.AlignHCenter; background: Rectangle { color: "#f39c12"; radius: 10 }
                            contentItem: Text { text: parent.text; color: "white"; font.bold: true }
                            onClicked: { selectedDifficulty = "Medium"; currentScreen = "levels" } }
                    }
                }
                Rectangle { width: 260; height: 400; radius: 20; color: "white"
                    ColumnLayout { anchors.fill: parent; anchors.margins: 20; spacing: 15
                        Text { text: "🔥 HARD"; font.pixelSize: 24; font.bold: true; color: "#e74c3c" }
                        Text { text: "15 Levels"; font.pixelSize: 14; color: "#7f8c8d" }
                        Text { text: "6 words per level\n5 minutes time limit\nx3 score"; font.pixelSize: 12; color: "#5a5a5a" }
                        Item { Layout.fillHeight: true }
                        Button { text: "Test"; Layout.alignment: Qt.AlignHCenter; background: Rectangle { color: "#e74c3c"; radius: 10 }
                            contentItem: Text { text: parent.text; color: "white"; font.bold: true }
                            onClicked: { selectedDifficulty = "Hard"; currentScreen = "levels" } }
                    }
                }
            }
        }
    }

    // -------------------- شاشة المستويات (15 مستوى) --------------------
    Rectangle {
        anchors.fill: parent
        color: "#f8f9fb"
        visible: currentScreen === "levels"
        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 40
            spacing: 30
            RowLayout {
                spacing: 20
                Button { text: "← Back"; onClicked: currentScreen = "difficulty" }
                Text { text: selectedDifficulty + " Levels"; font.pixelSize: 32; font.bold: true; color: "#1a1a1a"; Layout.fillWidth: true; horizontalAlignment: Text.AlignHCenter }
                Item { width: 80 }
            }
            Grid {
                Layout.alignment: Qt.AlignHCenter
                columns: 5
                spacing: 20
                Repeater {
                    model: 15
                    Rectangle {
                        width: 90; height: 90; radius: 15; color: "white"; border.color: "#0842a8"; border.width: 2
                        Text { anchors.centerIn: parent; text: (index + 1).toString(); font.pixelSize: 28; font.bold: true; color: "#0842a8" }
                        MouseArea {
                            anchors.fill: parent
                            onClicked: { selectedLevel = index + 1; loadLevel() }
                        }
                    }
                }
            }
        }
    }

    // -------------------- شاشة اللعبة --------------------
    Rectangle {
        anchors.fill: parent
        color: "#1a1a2e"
        visible: currentScreen === "game"
        RowLayout {
            anchors.fill: parent
            anchors.margins: 20
            spacing: 15
            Rectangle {
                Layout.fillWidth: true
                Layout.fillHeight: true
                color: "#0f3460"
                radius: 15
                ColumnLayout {
                    anchors.fill: parent
                    anchors.margins: 15
                    spacing: 10
                    RowLayout {
                        Layout.fillWidth: true
                        Button { text: "← Levels"; background: Rectangle { color: "#2c3e50"; radius: 8 }
                            contentItem: Text { text: parent.text; color: "white" }
                            onClicked: goToLevels() }
                        Text { text: selectedDifficulty + " - Level " + selectedLevel; font.pixelSize: 18; font.bold: true; color: "#e94560"; Layout.alignment: Qt.AlignHCenter; Layout.fillWidth: true }
                        Text { id: gameTimerText; text: "⏱️ 08:00"; font.pixelSize: 16; font.bold: true; color: "#f1c40f" }
                    }
                    Grid {
                        id: gridContainer
                        Layout.alignment: Qt.AlignHCenter
                        rows: 12; columns: 12; spacing: 2
                        Repeater {
                            id: gridRepeater
                            model: 144
                            Rectangle {
                                width: 45; height: 45
                                color: isFound ? "#27ae60" : (isSelected ? "#f39c12" : "#16213e")
                                radius: 5
                                border.color: isSelected ? "#f39c12" : (isFound ? "#27ae60" : "#e94560")
                                border.width: 1
                                property int row: Math.floor(index / 12)
                                property int col: index % 12
                                property bool isSelected: false
                                property bool isFound: false
                                Text {
                                    anchors.centerIn: parent
                                    text: currentGrid.length && currentGrid[row] ? currentGrid[row][col] : ""
                                    font.pixelSize: 16; font.bold: true
                                    color: isFound ? "white" : (isSelected ? "white" : "#bdc3c7")
                                }
                                MouseArea {
                                    anchors.fill: parent
                                    enabled: !isFound && gameActive
                                    hoverEnabled: true
                                    onPressed: { clearGameSelection(); addToSelection(row, col) }
                                    onPositionChanged: {
                                        if(pressed && gameActive) {
                                            var currentGlobal = mapToItem(gridContainer, mouseX, mouseY)
                                            var nearestRow = -1, nearestCol = -1, minDist = 45
                                            for(var i = 0; i < gridRepeater.count; i++) {
                                                var cell = gridRepeater.itemAt(i)
                                                if(cell && !cell.isFound && currentGrid[cell.row] && currentGrid[cell.row][cell.col] !== ' ') {
                                                    var cellCenter = cell.mapToItem(gridContainer, cell.width/2, cell.height/2)
                                                    var dx = cellCenter.x - currentGlobal.x
                                                    var dy = cellCenter.y - currentGlobal.y
                                                    var dist = Math.sqrt(dx*dx + dy*dy)
                                                    if(dist < minDist) { minDist = dist; nearestRow = cell.row; nearestCol = cell.col }
                                                }
                                            }
                                            if(nearestRow !== -1 && (nearestRow !== lastRow || nearestCol !== lastCol))
                                                addToSelection(nearestRow, nearestCol)
                                        }
                                    }
                                    onReleased: { if(!isFound && selectedCells.length && gameActive) checkSelectedWord() }
                                }
                                function select() { isSelected = true; color = "#f39c12" }
                                function deselect() { isSelected = false; color = "#16213e" }
                                function markAsFound() { isFound = true; isSelected = false; color = "#27ae60" }
                                function reset() { isFound = false; isSelected = false; color = "#16213e" }
                            }
                        }
                    }
                    RowLayout {
                        Layout.fillWidth: true
                        spacing: 10
                        Rectangle { Layout.fillWidth: true; height: 40; color: "#16213e"; radius: 8
                            Text { anchors.centerIn: parent; id: gameScoreText; text: "Level Score: 0"; font.pixelSize: 11; color: "#f1c40f" } }
                        Rectangle { Layout.fillWidth: true; height: 40; color: "#16213e"; radius: 8
                            Text { anchors.centerIn: parent; id: gameTotalScoreText; text: "Total Score: 0"; font.pixelSize: 11; color: "#f1c40f" } }
                        Rectangle { Layout.fillWidth: true; height: 40; color: "#16213e"; radius: 8
                            Text { anchors.centerIn: parent; id: gameFoundCountText; text: "0/0 Words"; font.pixelSize: 11; color: "#2ecc71" } }
                        Rectangle { Layout.fillWidth: true; height: 40; color: "#16213e"; radius: 8
                            Text { anchors.centerIn: parent; id: gameWrongCountText; text: "Mistakes: 0"; font.pixelSize: 11; color: "#e74c3c" } }
                    }
                    Rectangle {
                        id: gameResultMessage
                        Layout.fillWidth: true; height: 35; color: "#16213e"; radius: 6
                        visible: false
                        Text { anchors.centerIn: parent; text: "🎉 Found! 🎉"; font.pixelSize: 12; font.bold: true; color: "#2ecc71" }
                    }
                }
            }
            Rectangle {
                Layout.preferredWidth: 280
                Layout.fillHeight: true
                color: "#16213e"
                radius: 15
                ColumnLayout {
                    anchors.fill: parent
                    anchors.margins: 15
                    spacing: 15
                    Text { text: "📋 Words to Find"; font.pixelSize: 18; font.bold: true; color: "#e94560"; Layout.alignment: Qt.AlignHCenter }
                    Rectangle { Layout.fillWidth: true; height: 1; color: "#2c3e50" }
                    ListView {
                        id: wordsListView
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        spacing: 8
                        clip: true
                        model: currentWords
                        delegate: Rectangle {
                            width: wordsListView.width
                            height: 60
                            color: modelData.found ? "#27ae60" : "#1a1a2e"
                            radius: 8
                            border.color: modelData.found ? "#27ae60" : "#e94560"
                            border.width: 1
                            ColumnLayout {
                                anchors.fill: parent
                                anchors.margins: 8
                                RowLayout {
                                    Layout.fillWidth: true
                                    Text { text: modelData.word; font.pixelSize: 14; font.bold: true; color: modelData.found ? "white" : "#f1c40f" }
                                    Item { Layout.fillWidth: true }
                                    Text { text: modelData.found ? "✓" : "◯"; font.pixelSize: 14; color: modelData.found ? "#2ecc71" : "#7f8c8d" }
                                }
                                Text { text: "💡 " + modelData.hint; font.pixelSize: 10; color: modelData.found ? "white" : "#bdc3c7"; wrapMode: Text.WordWrap; visible: !modelData.found }
                            }
                        }
                    }
                    Rectangle { Layout.fillWidth: true; height: 1; color: "#2c3e50" }
                    Text { text: "🎮 How to Play"; font.pixelSize: 14; font.bold: true; color: "white" }
                    Text { text: "• Click and drag over letters\n• Select words horizontally or vertically\n• Release to check your answer"; font.pixelSize: 11; color: "#bdc3c7"; wrapMode: Text.WordWrap }
                }
            }
        }
    }

    // -------------------- حوار إكمال المستوى (مع زرار Next Level) --------------------
    Dialog {
        id: levelCompleteDialog
        modal: true
        width: 350
        x: (window.width - width) / 2
        y: (window.height - height) / 2
        visible: false
        background: Rectangle { color: "#16213e"; radius: 15 }
        ColumnLayout {
            spacing: 20
            anchors.fill: parent
            anchors.margins: 20
            Text { text: "🎉 Level Complete! 🎉"; font.pixelSize: 22; font.bold: true; color: "#e94560"; Layout.alignment: Qt.AlignHCenter }
            Text { text: "Level Score: " + currentLevelScore; font.pixelSize: 14; color: "white"; Layout.alignment: Qt.AlignHCenter }
            Text { text: "Total Score: " + totalScore; font.pixelSize: 14; color: "#f1c40f"; Layout.alignment: Qt.AlignHCenter }
            RowLayout {
                Layout.alignment: Qt.AlignHCenter
                spacing: 20
                Button {
                    text: "Main Menu"
                    background: Rectangle { color: "#2c3e50"; radius: 8 }
                    contentItem: Text { text: parent.text; color: "white"; font.bold: true }
                    onClicked: {
                        levelCompleteDialog.visible = false
                        currentScreen = "difficulty"
                        selectedLevel = 1
                        totalScore = 0
                    }
                }
                Button {
                    text: "Next Level →"
                    background: Rectangle { color: "#e94560"; radius: 8 }
                    contentItem: Text { text: parent.text; color: "white"; font.bold: true }
                    onClicked: nextLevel()
                }
            }
        }
    }

    // -------------------- حوار إكمال اللعبة --------------------
    Dialog {
        id: gameCompleteDialog
        modal: true
        width: 400
        x: (window.width - width) / 2
        y: (window.height - height) / 2
        visible: false
        background: Rectangle { color: "#16213e"; radius: 15 }
        ColumnLayout {
            spacing: 20
            anchors.fill: parent
            anchors.margins: 20
            Text { text: "🏆 GRANDMASTER! 🏆"; font.pixelSize: 24; font.bold: true; color: "#f1c40f"; Layout.alignment: Qt.AlignHCenter }
            Text { text: "You completed all " + selectedDifficulty + " levels!"; font.pixelSize: 14; color: "white"; Layout.alignment: Qt.AlignHCenter }
            Text { text: "⭐ Final Score: " + totalScore + " ⭐"; font.pixelSize: 16; font.bold: true; color: "#e94560"; Layout.alignment: Qt.AlignHCenter }
            Button {
                text: "Back to Menu"
                Layout.alignment: Qt.AlignHCenter
                background: Rectangle { color: "#e94560"; radius: 8 }
                contentItem: Text { text: parent.text; color: "white"; font.bold: true }
                onClicked: {
                    gameCompleteDialog.visible = false
                    currentScreen = "difficulty"
                    selectedLevel = 1
                    totalScore = 0
                }
            }
        }
    }
}