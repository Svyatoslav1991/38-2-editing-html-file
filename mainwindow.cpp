#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWebEngineView>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->settingApplication();
    this->createSignalSlotConnections();
}

//--------------------------------------------------------------------------

MainWindow::~MainWindow()
{
    delete ui;
}

//--------------------------------------------------------------------------

void MainWindow::settingApplication()
{
    m_pWebView = std::make_unique<QWebEngineView>(this);
    ui->centralwidget->layout()->addWidget(m_pWebView.get());
    this->setWindowTitle("HTML-редактор");

    this->setWindowIcon(QIcon(":/icons/html.png"));

    ui->openHtml_action->setIcon(QIcon(":/icons/openFile.png"));
    ui->openHtml_action->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));

    ui->saveHtml_action->setIcon(QIcon(":/icons/saveFile.png"));
    ui->saveHtml_action->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));

    ui->exit_action->setIcon(QIcon(":/icons/cross.ico"));
    ui->exit_action->setShortcut(QKeySequence(Qt::ALT + Qt::Key_F4));
}

//--------------------------------------------------------------------------

void MainWindow::createSignalSlotConnections()
{
    connect(ui->exit_action, SIGNAL(triggered(bool)), this, SLOT(close()));
    connect(ui->plainTextEdit, SIGNAL(textChanged()), this, SLOT(updateWebView()));
    connect(ui->openHtml_action, SIGNAL(triggered(bool)), this, SLOT(loadHtml()));
    connect(ui->saveHtml_action, SIGNAL(triggered(bool)), this, SLOT(saveHtml()));
}

//--------------------------------------------------------------------------

void MainWindow::updateWebView()
{
    m_pWebView->setHtml(ui->plainTextEdit->toPlainText());
}

//--------------------------------------------------------------------------

void MainWindow::loadHtml()
{
    QString path = QDir::currentPath() + "/htmls";
    QString fileName = QFileDialog::getOpenFileName(this, "Открыть файл html", path, "(*.html  *.htm)");
    if (!fileName.isEmpty())
    {
        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream in(&file);
            QString htmlText = in.readAll();
            ui->plainTextEdit->setPlainText(htmlText);
            updateWebView();
            file.close();
        }
        else
        {
            QMessageBox::critical(this, "Ошибка", "Не удалось открыть html-файл");
        }
    }
}

//--------------------------------------------------------------------------

void MainWindow::saveHtml()
{
    QString htmlText = ui->plainTextEdit->toPlainText();
    if(htmlText.isEmpty())
    {
        return;
    }

    QString path = QDir::currentPath() + "/htmls";
    QString fileName = QFileDialog::getSaveFileName(this, "Сохранить html файл", path, "(*.html *.htm)");
    if (!fileName.isEmpty())
    {
        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QTextStream out(&file);
            out << htmlText;
            file.close();
        }
        else
        {
            QMessageBox::critical(this, "Ошибка", "Не удалось открыть html-файл!");
        }
    }
}

