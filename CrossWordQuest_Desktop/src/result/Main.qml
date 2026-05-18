import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Window {
    id: window
    width: 1000
    height: 700
    visible: true
    title: "Crossword Game"

    StackView {
        id: myStack
        anchors.fill: parent
        initialItem: difficultySelectorPage
    }

    Component {
        id: difficultySelectorPage

        Rectangle {
            color: "#f4f7fa"

            RowLayout {
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.margins: 40
                spacing: 20

                Rectangle {
                    id: backToMenuButton
                    width: 45
                    height: 45
                    radius: 22.5
                    color: "#ffffff"
                    border.color: "#e2e8f0"
                    border.width: 1

                    Text {
                        text: "←"
                        font.pixelSize: 22
                        color: "#0f172a"
                        anchors.centerIn: parent
                    }

                    MouseArea {
                        anchors.fill: parent
                        cursorShape: Qt.PointingHandCursor
                        hoverEnabled: true

                        onEntered: backToMenuButton.color = "#f1f5f9"
                        onExited: backToMenuButton.color = "#ffffff"

                        // ══════════════════════════════════════════════════════════════
                        // التعديل هنا في دالة الضغط على سهم الباك
                        // ══════════════════════════════════════════════════════════════
                        onClicked: {
                            if (myStack.depth > 1) {

                                myStack.pop()
                            } else {

                                if (typeof homepage !== "undefined") {
                                    homepage.show();
                                }
                                window.close();
                            }
                        }
                    }
                }

                ColumnLayout {
                    spacing: 2

                    Text {
                        text: "LEVEL SELECTION"
                        font.pixelSize: 12
                        color: "gray"
                    }
                    Text {
                        text: "Choose Difficulty"
                        font.pixelSize: 32
                        font.bold: true
                        color: "#0f172a"
                    }
                }
            }

            Row {
                anchors.centerIn: parent
                spacing: 20

                DifficultyCard {
                    levelTitle: "NOVICE"; mainTitle: "Easy"
                    desc: "Relaxed vocabulary and helpful hints."; btnText: "Start >"
                    isBlue: false
                    onClicked: myStack.push(levelsPage, {difficultyName: "Easy"})
                }

                DifficultyCard {
                    levelTitle: "STANDARD"; mainTitle: "Medium"
                    desc: "The classic experience. Balanced wordplay."; btnText: "Accept >"
                    isBlue: true
                    onClicked: myStack.push(levelsPage, {difficultyName: "Medium"})
                }

                DifficultyCard {
                    levelTitle: "GRANDMASTER"; mainTitle: "Hard"
                    desc: "Obscure clues and complex grid patterns."; btnText: "Test >"
                    isBlue: false
                    onClicked: myStack.push(levelsPage, {difficultyName: "Hard"})
                }
            }
        }
    }

    Component {
        id: levelsPage
        LevelsPage {}
    }
}