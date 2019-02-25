#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setGifs();

private slots:
    void startGifs();

    void on_action_New_odenation_triggered();

    void on_actionGraph_triggered();

    void on_action_Data_base_triggered();

private:
    Ui::MainWindow *ui;

    QMovie **vetMovie;
    QTimer *timer;
};

#endif // MAINWINDOW_H
