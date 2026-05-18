import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Window {
    id: window
    visible: true
    width: 1000
    height: 700
    title: "CrossWordQuest - Game Result"

    Rectangle {
        id: resultPage
        anchors.fill: parent
        color: "#F8F9FC" // الخلفية الفاتحة المريحة للعين

        // التوب بار العلوي (اللوجو واسم اللاعب)
        RowLayout {
            id: topBar
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.topMargin: 20
            anchors.leftMargin: 40
            anchors.rightMargin: 40
            height: 50
            spacing: 15

            Button {
                id: resultBackBtn
                background: Rectangle {
                    color: resultBackBtn.hovered ? "#e2e8f0" : "#ffffff"
                    radius: 8
                    border.color: "#cbd5e1"
                    border.width: 1
                }
                contentItem: Text {
                    text: "← Back"
                    color: "#0f172a"
                    font.pixelSize: 13
                    font.bold: true
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
                onClicked: window.close()
            }

            Text {
                text: "CrossWordQuest"
                font.pixelSize: 22
                font.bold: true
                color: "#1E3A8A"
            }

            Item { Layout.fillWidth: true } // مسافة مرنة في النص

            RowLayout {
                spacing: 10
                Text {
                    text: "Hi, Afnan 👋"
                    font.pixelSize: 16
                    color: "#475569"
                }
                Rectangle {
                    width: 36
                    height: 36
                    radius: 18
                    color: "#1E293B"
                    Text {
                        text: "A"
                        color: "white"
                        font.bold: true
                        anchors.centerIn: parent
                    }
                }
            }
        }

        // المحتوى الأساسي (العنوان والكروت)
        ColumnLayout {
            anchors.top: topBar.bottom
            anchors.bottom: bottomSection.top
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: 40
            spacing: 25

            // العناوين الرئيسية في النص
            ColumnLayout {
                Layout.alignment: Qt.AlignHCenter
                spacing: 5
                Text {
                    text: "Game Result"
                    font.pixelSize: 36
                    font.bold: true
                    color: "#1E3A8A"
                    Layout.alignment: Qt.AlignHCenter
                }
                Text {
                    text: "Incredible performance, Pro Solver!"
                    font.pixelSize: 16
                    color: "#64748B"
                    Layout.alignment: Qt.AlignHCenter
                }
            }

            // صف الكروت (كارت التير الشمال + كارت الإحصائيات اليمين)
            RowLayout {
                spacing: 30
                Layout.fillWidth: true
                Layout.fillHeight: true

                // 1. كارت التير (اليسار)
                Rectangle {
                    id: tierCard
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    Layout.preferredWidth: 400
                    color: "white"
                    radius: 16
                    border.color: "#E2E8F0"
                    border.width: 1

                    ColumnLayout {
                        anchors.centerIn: parent
                        spacing: 15

                        // الدائرة البنفسجية بداخلها الأيقونة
                        Rectangle {
                            width: 140
                            height: 140
                            radius: 70
                            color: "#E0D7FF"
                            Layout.alignment: Qt.AlignHCenter

                            Text {
                                text: "🏅"
                                font.pixelSize: 60
                                anchors.centerIn: parent
                            }
                        }

                        Rectangle {
                            color: "#6366F1"
                            radius: 8
                            width: 120
                            height: 26
                            Layout.alignment: Qt.AlignHCenter
                            Text {
                                text: "YOU ACHIEVED"
                                color: "white"
                                font.pixelSize: 11
                                font.bold: true
                                anchors.centerIn: parent
                            }
                        }

                        Text {
                            text: "Grandmaster Tier"
                            font.pixelSize: 26
                            font.bold: true
                            color: "#1E293B"
                            Layout.alignment: Qt.AlignHCenter
                        }

                        Text {
                            text: "You've reached Level 42"
                            font.pixelSize: 14
                            color: "#64748B"
                            Layout.alignment: Qt.AlignHCenter
                        }
                    }
                }

                // 2. كارت الإحصائيات والأزرار (اليمين)
                ColumnLayout {
                    spacing: 20
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    Layout.preferredWidth: 500

                    Rectangle {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        color: "white"
                        radius: 16
                        border.color: "#E2E8F0"
                        border.width: 1

                        ColumnLayout {
                            anchors.fill: parent
                            anchors.margins: 25
                            spacing: 20

                            // السكور والوقت
                            RowLayout {
                                Layout.fillWidth: true
                                ColumnLayout {
                                    spacing: 2
                                    Text { text: "TOTAL SCORE"; font.pixelSize: 12; font.bold: true; color: "#64748B" }
                                    Text { text: "12,450"; font.pixelSize: 40; font.bold: true; color: "#2563EB" }
                                }
                                Item { Layout.fillWidth: true }
                                ColumnLayout {
                                    spacing: 2
                                    Layout.alignment: Qt.AlignRight
                                    Text { text: "Time Elapsed"; font.pixelSize: 13; color: "#64748B"; Layout.alignment: Qt.AlignRight }
                                    Text { text: "⏱️ 04:32"; font.pixelSize: 18; font.bold: true; color: "#1E293B"; Layout.alignment: Qt.AlignRight }
                                }
                            }

                            // الكروت الصغيرة (Correct & Misses)
                            RowLayout {
                                spacing: 15
                                Layout.fillWidth: true

                                // كارت الإجابات الصحيحة
                                Rectangle {
                                    Layout.fillWidth: true
                                    height: 65
                                    color: "#F0FDF4"
                                    radius: 10
                                    RowLayout {
                                        anchors.centerIn: parent
                                        spacing: 10
                                        Text { text: "✅"; font.pixelSize: 16 }
                                        ColumnLayout {
                                            spacing: 1
                                            Text { text: "Correct"; font.pixelSize: 11; color: "#166534" }
                                            Text { text: "24 Words"; font.pixelSize: 15; font.bold: true; color: "#14532D" }
                                        }
                                    }
                                }

                                // كارت الأخطاء
                                Rectangle {
                                    Layout.fillWidth: true
                                    height: 65
                                    color: "#FEF2F2"
                                    radius: 10
                                    RowLayout {
                                        anchors.centerIn: parent
                                        spacing: 10
                                        Text { text: "❌"; font.pixelSize: 16 }
                                        ColumnLayout {
                                            spacing: 1
                                            Text { text: "Misses"; font.pixelSize: 11; color: "#991B1B" }
                                            Text { text: "2 Words"; font.pixelSize: 15; font.bold: true; color: "#7F1D1D" }
                                        }
                                    }
                                }
                            }

                            Item { Layout.fillHeight: true } // مسافة عازلة

                            // زرار Play Again والأزرار الجانبية
                            RowLayout {
                                spacing: 12
                                Layout.fillWidth: true

                                Button {
                                    id: playAgainBtn
                                    Layout.fillWidth: true
                                    Layout.preferredHeight: 50
                                    contentItem: Text {
                                        text: "🔄 Play Again" // تم تعديل المسافة هنا لتجنب مشاكل الرموز المشوهة
                                        color: "white"
                                        font.pixelSize: 16
                                        font.bold: true
                                        horizontalAlignment: Text.AlignHCenter
                                        verticalAlignment: Text.AlignVCenter
                                    }
                                    background: Rectangle {
                                        color: playAgainBtn.hovered ? "#1D4ED8" : "#2563EB"
                                        radius: 10
                                    }
                                    onClicked: {
                                        if (typeof myStack !== "undefined") {
                                            myStack.pop()
                                        } else {
                                            if (typeof homepage !== "undefined") { homepage.show(); }
                                            window.close(); // يقفل النافذة مباشرة وبأمان
                                        }
                                    }
                                }

                                Button {
                                    id: homeBtn
                                    Layout.preferredWidth: 50
                                    Layout.preferredHeight: 50
                                    contentItem: Text { text: "🏠"; font.pixelSize: 18; horizontalAlignment: Text.AlignHCenter; verticalAlignment: Text.AlignVCenter }
                                    background: Rectangle {
                                        color: homeBtn.hovered ? "#E2E8F0" : "#F1F5F9"
                                        radius: 10
                                        border.color: "#CBD5E1"
                                    }
                                    onClicked: {
                                        if (typeof homepage !== "undefined") {
                                            homepage.show();
                                        }
                                        window.close();
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        // 3. الجزء السفلي (الـ Progress Bar لـ نقاط الخبرة XP)
        Rectangle {
            id: bottomSection
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: 40
            height: 100
            color: "white"
            radius: 14
            border.color: "#E2E8F0"
            border.width: 1

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 20
                spacing: 10

                RowLayout {
                    Layout.fillWidth: true
                    Text { text: "Experience Points"; font.pixelSize: 14; font.bold: true; color: "#1E293B" }
                    Item { Layout.fillWidth: true }
                    Text { text: "850 XP to Level 43"; font.pixelSize: 13; color: "#64748B" }
                }

                // شريط التقدم (الـ Progress Bar) المتدرج الألوان الملون
                Rectangle {
                    id: progressBg
                    Layout.fillWidth: true
                    height: 12
                    color: "#E2E8F0"
                    radius: 6

                    Rectangle {
                        width: progressBg.width * 0.75
                        height: parent.height
                        radius: 6
                        gradient: Gradient {
                            orientation: Gradient.Horizontal
                            GradientStop { position: 0.0; color: "#3B82F6" }
                            GradientStop { position: 1.0; color: "#8B5CF6" }
                        }
                    }
                }

                RowLayout {
                    Layout.fillWidth: true
                    Text { text: "Level 42"; font.pixelSize: 11; color: "#64748B" }
                    Item { Layout.fillWidth: true }
                    Text { text: "Level 43"; font.pixelSize: 11; color: "#64748B" }
                }
            }
        }
    }
}