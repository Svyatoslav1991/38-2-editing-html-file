#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>
#include <QWebEngineView>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    std::unique_ptr<QWebEngineView> m_pWebView;

    void settingApplication();

    void createSignalSlotConnections();

public slots:
    void updateWebView();
    void loadHtml();
    void saveHtml();
};
#endif // MAINWINDOW_H
