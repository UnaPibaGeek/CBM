#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QTableWidgetItem>
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValueRef>
#include <QJsonDocument>
#include "qcgaugewidget.h"
#include "input_filter.h"
#include "connection.h"
#include "QDesktopServices"
//#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    input_filter *mInputFilter;
    connection *mConn;



private slots:

    void set_frames_table();
    void set_buttons_icon();
    void set_speedgauge();
    void onDataChanged(const QModelIndex, const QModelIndex);
    void change_speedgauge(int, int);
    void on_action_Restore_Attack_Template_triggered();
    void on_action_Save_Attack_Template_triggered();
    void on_action_Exit_triggered();
    void on_actionConnect_triggered();
    void on_actionDisconnect_triggered();
    void on_actionWrite_Backdoor_Memory_triggered();
    void on_actionLook_for_Frames_triggered();
    void on_actionClear_Frames_Table_triggered();
    void on_actionOnline_Help_triggered();
    void on_actionAbout_Us_triggered();
    void on_actionCheck_for_Updates_triggered();
    void on_progressBar_valueChanged(int value);

    void on_stop_checkbox_clicked();

    void on_attacker_n_phone_editingFinished();

    void on_id_match_editingFinished();

    void on_gps_long_editingFinished();

    void on_btn_write_backdoor_memory_clicked();

    void on_btn_connect_clicked();

private:
    Ui::MainWindow *ui;
    QStandardItemModel *model;
    QcGaugeWidget *mSpeedGauge;
    QcNeedleItem *mSpeedNeedle;
    QFile *json_handler;
};

#endif // MAINWINDOW_H
