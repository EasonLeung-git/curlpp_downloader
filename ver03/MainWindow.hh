#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QToolButton>
#include <QFileDialog>
#include <QMessageBox>
#include <QThread>

#include "CUrlppDownloader.hh"

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
    QString *m_saved_file_name;
    std::ofstream *m_fstream;

    CUrlppDownloader *m_downloader;

    void initQtConnect();
    void initCurlpp();

    std::size_t writeFunction(const char *p, std::size_t size, std::size_t nmbe)
    {
        std::fstream f(this->m_downloader->getFileName());
        f.write(p, size * nmbe);

        return size * nmbe;
    }
};

#endif // MAINWINDOW_HH
