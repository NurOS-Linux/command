#include <QApplication>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QProcess>
#include <QCloseEvent>
#include <QDir>
#include <QFontDatabase>
#include <QTabWidget>
#include <QTabBar>
#include <QShortcut>
#include <QMenuBar>
#include <QMenu>
#include <QStyleFactory>
#include <QPalette>
#include <qtermwidget.h>

class TerminalTab : public QWidget {
    Q_OBJECT

public:
    explicit TerminalTab(QWidget *parent = nullptr) : QWidget(parent) {
        auto *layout = new QVBoxLayout(this);
        layout->setContentsMargins(0, 0, 0, 0);
        layout->setSpacing(0);
        
        terminal = new QTermWidget(0, this);


        QFont terminalFont = QFont(QStringLiteral("Noto Sans Mono"));
        terminalFont.setPointSize(11);
        terminalFont.setStyleHint(QFont::Monospace);
        terminal->setTerminalFont(terminalFont);

        terminal->setColorScheme(QStringLiteral("DarkPastels"));
        terminal->setScrollBarPosition(QTermWidget::ScrollBarRight);
        terminal->setBlinkingCursor(true);
        terminal->setTerminalOpacity(1.0);
        terminal->setWorkingDirectory(QDir::homePath());
        terminal->setMargin(12);

        QString shell = QString::fromLocal8Bit(qgetenv("SHELL"));
        if (shell.isEmpty()) {
            shell = QStringLiteral("/bin/bash");
        }

        QStringList args;
        args << QStringLiteral("--login");

        terminal->setShellProgram(shell);
        terminal->setArgs(args);
        terminal->startShellProgram();

        layout->addWidget(terminal);
        
        connect(terminal, &QTermWidget::finished, this, &TerminalTab::terminalFinished);
    }

    QTermWidget* getTerminal() { return terminal; }

signals:
    void terminalFinished();

private:
    QTermWidget *terminal;
};

class CustomTabBar : public QTabBar {
    Q_OBJECT
protected:
    QSize tabSizeHint(int index) const override {
        QSize size = QTabBar::tabSizeHint(index);
        size.setHeight(36);
        return size;
    }
};

class CustomTabWidget : public QTabWidget {
    Q_OBJECT
public:
    explicit CustomTabWidget(QWidget *parent = nullptr) : QTabWidget(parent) {
        auto *customTabBar = new CustomTabBar;
        QTabWidget::setTabBar(customTabBar);
    }
};

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr) : QMainWindow(parent) {
        setWindowTitle(QStringLiteral("aether Command"));
        resize(900, 650);

        tabs = new CustomTabWidget(this);
        tabs->setTabsClosable(true);
        tabs->setMovable(true);
        tabs->setDocumentMode(true);
        setCentralWidget(tabs);

        setupMenuBar();
        setupStyleSheet();

        connect(tabs, &QTabWidget::tabCloseRequested, this, &MainWindow::closeTab);
        createTab();
    }

protected:
    void closeEvent(QCloseEvent *event) override {
        while (tabs->count() > 0) {
            closeTab(0);
        }
        QMainWindow::closeEvent(event);
    }

private slots:
    void createTab() {
        auto *tab = new TerminalTab(this);
        int index = tabs->addTab(tab, QStringLiteral("Terminal"));
        
        connect(tab, &TerminalTab::terminalFinished, this, [this, tab]() {
            int index = tabs->indexOf(tab);
            if (index != -1) {
                closeTab(index);
            }
        });

        tabs->setCurrentIndex(index);
        tab->getTerminal()->setFocus();
        updateTabTitle(index);
    }

    void closeTab(int index) {
        if (index >= 0 && index < tabs->count()) {
            auto *tab = qobject_cast<TerminalTab*>(tabs->widget(index));
            tabs->removeTab(index);
            delete tab;

            if (tabs->count() == 0) {
                createTab();
            }
        }
    }

    void closeCurrentTab() {
        closeTab(tabs->currentIndex());
    }

    void updateTabTitle(int index) {
        QString title = QStringLiteral("Terminal %1").arg(index + 1);
        tabs->setTabText(index, title);
    }

private:
    void setupMenuBar() {
        auto *menuBar = new QMenuBar(this);
        auto *fileMenu = menuBar->addMenu(QStringLiteral("File"));
        
        auto *newTabAction = fileMenu->addAction(QStringLiteral("New Tab"));
        newTabAction->setShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_T));
        
        auto *closeTabAction = fileMenu->addAction(QStringLiteral("Close Tab"));
        closeTabAction->setShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_W));
        
        fileMenu->addSeparator();
        
        auto *quitAction = fileMenu->addAction(QStringLiteral("Quit"));
        quitAction->setShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_Q));

        connect(newTabAction, &QAction::triggered, this, &MainWindow::createTab);
        connect(closeTabAction, &QAction::triggered, this, &MainWindow::closeCurrentTab);
        connect(quitAction, &QAction::triggered, this, &MainWindow::close);

        setMenuBar(menuBar);
    }

    void setupStyleSheet() {
        setStyleSheet(QStringLiteral(R"(
            QMainWindow {
                background-color: #1a1a1a;
            }
            QTabWidget::pane {
                border: none;
                background-color: #1a1a1a;
                border-radius: 10px;
            }
            QTabWidget::tab-bar {
                alignment: left;
            }
            QTabBar::tab {
                background-color: #2d2d2d;
                color: #ffffff;
                padding: 10px 20px;
                border: none;
                min-width: 140px;
                margin-right: 4px;
                border-top-left-radius: 8px;
                border-top-right-radius: 8px;
                font-size: 13px;
            }
            QTabBar::tab:selected {
                background-color: #5c90ff;
                color: #ffffff;
            }
            QTabBar::tab:hover:!selected {
                background-color: #3d3d3d;
            }
            QTabBar::close-button {
                image: url(close.png);
                subcontrol-position: right;
                margin: 2px;
            }
            QTabBar::close-button:hover {
                background-color: #ff5c5c;
                border-radius: 2px;
            }
            QMenuBar {
                background-color: #1a1a1a;
                color: #ffffff;
                border: none;
                padding: 8px 0;
            }
            QMenuBar::item {
                background-color: transparent;
                padding: 8px 12px;
                margin: 0 4px;
                border-radius: 6px;
            }
            QMenuBar::item:selected {
                background-color: #2d2d2d;
            }
            QMenuBar::item:pressed {
                background-color: #5c90ff;
            }
            QMenu {
                background-color: #2d2d2d;
                color: #ffffff;
                border: 1px solid #3d3d3d;
                border-radius: 8px;
                padding: 8px 0;
            }
            QMenu::item {
                padding: 8px 32px 8px 16px;
                border-radius: 4px;
                margin: 2px 4px;
            }
            QMenu::item:selected {
                background-color: #5c90ff;
            }
            QMenu::separator {
                height: 1px;
                background-color: #3d3d3d;
                margin: 6px 0;
            }
            QScrollBar:vertical {
                border: none;
                background-color: #2d2d2d;
                width: 14px;
                border-radius: 7px;
                margin: 0;
            }
            QScrollBar::handle:vertical {
                background-color: #5c90ff;
                border-radius: 7px;
                min-height: 30px;
            }
            QScrollBar::handle:vertical:hover {
                background-color: #4a7ae0;
            }
            QScrollBar::add-line:vertical,
            QScrollBar::sub-line:vertical {
                height: 0;
            }
            QScrollBar::add-page:vertical,
            QScrollBar::sub-page:vertical {
                background-color: transparent;
            }
        )"));
    }

private:
    CustomTabWidget *tabs;
};

#include "main.moc"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    app.setApplicationName(QStringLiteral("aether Command"));
    app.setApplicationVersion(QStringLiteral("1.0"));
    
    QPalette darkPalette;
    darkPalette.setColor(QPalette::Window, QColor(26, 26, 26));
    darkPalette.setColor(QPalette::WindowText, QColor(255, 255, 255));
    darkPalette.setColor(QPalette::Base, QColor(45, 45, 45));
    darkPalette.setColor(QPalette::AlternateBase, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::ToolTipBase, QColor(255, 255, 255));
    darkPalette.setColor(QPalette::ToolTipText, QColor(255, 255, 255));
    darkPalette.setColor(QPalette::Text, QColor(255, 255, 255));
    darkPalette.setColor(QPalette::Button, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::ButtonText, QColor(255, 255, 255));
    darkPalette.setColor(QPalette::Link, QColor(92, 144, 255));
    app.setPalette(darkPalette);
    
    app.setStyle(QStyleFactory::create(QStringLiteral("Fusion")));

    QFontDatabase::addApplicationFont(QStringLiteral("/usr/share/fonts/noto/NotoSansMono-Regular.ttf"));

    MainWindow window;
    window.show();
    
    return app.exec();
}