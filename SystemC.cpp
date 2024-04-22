#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QProcess>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QStyle>

class SystemControlWindow : public QWidget {
public:
    SystemControlWindow() {
        auto *layout = new QVBoxLayout(this);

        // Стилизация кнопок
        QString buttonStyle = "QPushButton { background-color: #0078D4; color: white; border-radius: 5px; }"
                              "QPushButton:hover { background-color: #005EA1; }";

        // Кнопка выключения компьютера
        addButton("Выключить", "shutdown /s /t 0", layout, buttonStyle);

        // Кнопка перезагрузки компьютера
        addButton("Перезагрузить", "shutdown /r /t 0", layout, buttonStyle);

        // Кнопка блокировки компьютера
        addButton("Заблокировать", "Rundll32.exe user32.dll,LockWorkStation", layout, buttonStyle);

        // Кнопка для открытия реестра
        addButton("Открыть реестр", "regedit", layout, buttonStyle);

        // Кнопка для открытия параметров Windows
        addButton("Открыть параметры", "ms-settings:", layout, buttonStyle);

        // Добавление кнопки для просмотра системной информации
        addButton("Системная информация", "msinfo32", layout, buttonStyle);

        // Добавление кнопки для доступа к панели управления
        addButton("Панель управления", "control", layout, buttonStyle);

        setLayout(layout);
        setWindowTitle("Управление системой");
        setWindowIcon(style()->standardIcon(QStyle::SP_ComputerIcon));
    }

private:
    void addButton(const QString &text, const QString &command, QVBoxLayout *layout, const QString &style) {
        auto *button = new QPushButton(text, this);
        button->setStyleSheet(style);
        connect(button, &QPushButton::clicked, this, [command]() {
            QProcess::startDetached(command);
        });
        layout->addWidget(button);
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    SystemControlWindow window;
    window.resize(400, 300);
    window.show();

    return app.exec();
}