#include "mainwindow.h"
#include "ui_mainwindow.h"

bool connected = false;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /* ## GUI SETUP ## */
    set_frames_table();
    set_buttons_icon();
    set_speedgauge();

    /* ## SIGNALS ## */
    connect(ui->injection_frames_table->model(), SIGNAL(dataChanged(const QModelIndex&, const QModelIndex&)), this, SLOT(onDataChanged(const QModelIndex&, const QModelIndex&)));

    ui->status_label->setText("OFF");

}

MainWindow::~MainWindow()
{
    delete ui;
}

/* ## # GUI SETUP # ## */

void MainWindow::set_frames_table()
{
    /* ## FRAMES TABLE ## */
    model = new QStandardItemModel(5,11,this);

    model->setHorizontalHeaderItem(0, new QStandardItem(QString("ID")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("DLC")));
    model->setHorizontalHeaderItem(2, new QStandardItem(QString("#1")));
    model->setHorizontalHeaderItem(3, new QStandardItem(QString("#2")));
    model->setHorizontalHeaderItem(4, new QStandardItem(QString("#3")));
    model->setHorizontalHeaderItem(5, new QStandardItem(QString("#4")));
    model->setHorizontalHeaderItem(6, new QStandardItem(QString("#5")));
    model->setHorizontalHeaderItem(7, new QStandardItem(QString("#6")));
    model->setHorizontalHeaderItem(8, new QStandardItem(QString("#7")));
    model->setHorizontalHeaderItem(9, new QStandardItem(QString("#8")));
    model->setHorizontalHeaderItem(10, new QStandardItem(QString("SMS")));

    /* FIXING STUPID QT BUG (? */
    for(int r=0;r<=4;r++)
    for(int c=0;c<=10;c++) {
    QStandardItem *item = new QStandardItem(QString("").arg(r).arg(c));
    model->setItem(r, c, item);
    }

    ui->injection_frames_table->setModel(model);

}

void MainWindow::set_buttons_icon()
{
    /* ## BUTTON'S ICON ## */

    QPixmap pixmap_btn_icon_restore(":/restore_icon.ico");
    QIcon RestoreIcon(pixmap_btn_icon_restore);
    ui->action_Restore_Attack_Template->setIcon(RestoreIcon);

    QPixmap pixmap_btn_icon_save(":/save_icon.png");
    QIcon SaveIcon(pixmap_btn_icon_save);
    ui->action_Save_Attack_Template->setIcon(SaveIcon);

    QPixmap pixmap_btn_icon_exit(":/exit_icon.png");
    QIcon ExitIcon(pixmap_btn_icon_exit);
    ui->action_Exit->setIcon(ExitIcon);

    QPixmap pixmap_btn_icon_connect(":/connect-icon-v2.png");
    QIcon ConnectIcon(pixmap_btn_icon_connect);
    ui->actionConnect->setIcon(ConnectIcon);
    ui->btn_connect->setIcon(ConnectIcon);

    QPixmap pixmap_btn_icon_disconnect(":/disconnect_icon.png");
    QIcon DisconnectIcon(pixmap_btn_icon_disconnect);
    ui->actionDisconnect->setIcon(DisconnectIcon);

    QPixmap pixmap_btn_icon_write(":/write_icon.png");
    QIcon WriteIcon(pixmap_btn_icon_write);
    ui->actionWrite_Backdoor_Memory->setIcon(WriteIcon);
    ui->btn_write_backdoor_memory->setIcon(WriteIcon);

    QPixmap pixmap_btn_icon_look(":/look_icon.png");
    QIcon LookIcon(pixmap_btn_icon_look);
    ui->actionLook_for_Frames->setIcon(LookIcon);

    QPixmap pixmap_btn_icon_clear(":/clear_icon.ico");
    QIcon ClearIcon(pixmap_btn_icon_clear);
    ui->actionClear_Frames_Table->setIcon(ClearIcon);

    QPixmap pixmap_btn_icon_help(":/help_icon.png");
    QIcon HelpIcon(pixmap_btn_icon_help);
    ui->actionOnline_Help->setIcon(HelpIcon);

    QPixmap pixmap_btn_icon_about(":/about_icon.ico");
    QIcon AboutIcon(pixmap_btn_icon_about);
    ui->actionAbout_Us->setIcon(AboutIcon);

    QPixmap pixmap_btn_icon_updates(":/updates_icon.png");
    QIcon UpdatesIcon(pixmap_btn_icon_updates);
    ui->actionCheck_for_Updates->setIcon(UpdatesIcon);

    QPixmap pixmap_btn_icon_gps(":/gps_icon.png");
    QIcon GPSIcon(pixmap_btn_icon_gps);
    ui->advanced_tab->setTabIcon(0,GPSIcon);

    QPixmap pixmap_btn_icon_frame(":/frame_icon.png");
    QIcon FrameIcon(pixmap_btn_icon_frame);
    ui->advanced_tab->setTabIcon(1,FrameIcon);
}

void MainWindow::set_speedgauge()
{
    /* ## SPEEDGAUGE SETTINGS ## */
    mSpeedGauge = new QcGaugeWidget;
    mSpeedGauge->addBackground(99);
    QcBackgroundItem *bkg1 = mSpeedGauge->addBackground(92);
    bkg1->clearrColors();
    bkg1->addColor(0.1,Qt::black);
    bkg1->addColor(1.0,Qt::white);

    QcBackgroundItem *bkg2 = mSpeedGauge->addBackground(88);
    bkg2->clearrColors();
    bkg2->addColor(0.1,Qt::gray);
    bkg2->addColor(1.0,Qt::darkGray);

    mSpeedGauge->addArc(55);
    mSpeedGauge->addDegrees(65)->setValueRange(0,80);
    mSpeedGauge->addColorBand(50);

    mSpeedGauge->addValues(80)->setValueRange(0,80);

    mSpeedGauge->addLabel(70)->setText("Km/h");
    QcLabelItem *lab = mSpeedGauge->addLabel(40);
    lab->setText("0");
    mSpeedNeedle = mSpeedGauge->addNeedle(60);
    mSpeedNeedle->setLabel(lab);
    mSpeedNeedle->setColor(Qt::white);
    mSpeedNeedle->setValueRange(0,80);
    mSpeedGauge->addBackground(7);
    mSpeedGauge->addGlass(88);

    ui->verticalLayout->addWidget(mSpeedGauge);
}

void MainWindow::change_speedgauge(int increment, int decrement)
{
    /* ## SPEEDGAUGE IS A DECORATION WIDGET ## */
    int current_value = mSpeedNeedle->currentValue();

    if( increment != 0 && current_value < 75){
        mSpeedNeedle->setCurrentValue(current_value+increment);
    }

    if( decrement != 0 && current_value > 11){
        mSpeedNeedle->setCurrentValue(current_value-decrement);
    }
}

void MainWindow::onDataChanged(const QModelIndex current, const QModelIndex next)
{
    /* ## # WHEN FRAME TABLE DATA CHANGED # ## */

    /* # Text-Align: Center # */
    ui->injection_frames_table->model()->setData(current, Qt::AlignCenter, Qt::TextAlignmentRole);

    /* # Get fun with SpeedGauge :) # */
    if(current.column() == 10){
        if(current.data() == ""){
            change_speedgauge(0,6);
        }else{
            change_speedgauge(3,0);
        }
    }
}


/* ######################################################## */

/* ## # MENUES # ## */
void MainWindow::on_action_Restore_Attack_Template_triggered()
{
    /* ## LOAD A JSON ATTACK TEMPLATE ## */

    QString filter;
    QString attack_tpl_file = QFileDialog::getOpenFileName(this,trUtf8("Open an attack template"),trUtf8(""),trUtf8("(*.json)"),&filter,0);

    json_handler = new QFile(attack_tpl_file);
    json_handler->open(QFile::ReadOnly);
    QJsonDocument jdoc_tmp = QJsonDocument().fromJson(json_handler->readAll());
    QJsonObject attack_tpl = jdoc_tmp.object();

    QVariantMap mainmap = attack_tpl.toVariantMap();
    QVariantMap first_frame = mainmap["first_frame"].toMap();
    QVariantMap second_frame = mainmap["second_frame"].toMap();
    QVariantMap third_frame = mainmap["third_frame"].toMap();
    QVariantMap fourth_frame = mainmap["fourth_frame"].toMap();
    QVariantMap fifth_frame = mainmap["fifth_frame"].toMap();

    /* # Set first frame # */
    model->item(0,0)->setText(first_frame["ID"].toString());
    model->item(0,1)->setText(first_frame["DLC"].toString());
    model->item(0,2)->setText(first_frame["DATA1"].toString());
    model->item(0,3)->setText(first_frame["DATA2"].toString());
    model->item(0,4)->setText(first_frame["DATA3"].toString());
    model->item(0,5)->setText(first_frame["DATA4"].toString());
    model->item(0,6)->setText(first_frame["DATA5"].toString());
    model->item(0,7)->setText(first_frame["DATA6"].toString());
    model->item(0,8)->setText(first_frame["DATA7"].toString());
    model->item(0,9)->setText(first_frame["DATA8"].toString());
    model->item(0,10)->setText(first_frame["SMS"].toString());

    /* # Set second frame # */
    model->item(1,0)->setText(second_frame["ID"].toString());
    model->item(1,1)->setText(second_frame["DLC"].toString());
    model->item(1,2)->setText(second_frame["DATA1"].toString());
    model->item(1,3)->setText(second_frame["DATA2"].toString());
    model->item(1,4)->setText(second_frame["DATA3"].toString());
    model->item(1,5)->setText(second_frame["DATA4"].toString());
    model->item(1,6)->setText(second_frame["DATA5"].toString());
    model->item(1,7)->setText(second_frame["DATA6"].toString());
    model->item(1,8)->setText(second_frame["DATA7"].toString());
    model->item(1,9)->setText(second_frame["DATA8"].toString());
    model->item(1,10)->setText(second_frame["SMS"].toString());

    /* # Set thrid frame # */
    model->item(2,0)->setText(third_frame["ID"].toString());
    model->item(2,1)->setText(third_frame["DLC"].toString());
    model->item(2,2)->setText(third_frame["DATA1"].toString());
    model->item(2,3)->setText(third_frame["DATA2"].toString());
    model->item(2,4)->setText(third_frame["DATA3"].toString());
    model->item(2,5)->setText(third_frame["DATA4"].toString());
    model->item(2,6)->setText(third_frame["DATA5"].toString());
    model->item(2,7)->setText(third_frame["DATA6"].toString());
    model->item(2,8)->setText(third_frame["DATA7"].toString());
    model->item(2,9)->setText(third_frame["DATA8"].toString());
    model->item(2,10)->setText(third_frame["SMS"].toString());

    /* # Set fourth frame # */
    model->item(3,0)->setText(fourth_frame["ID"].toString());
    model->item(3,1)->setText(fourth_frame["DLC"].toString());
    model->item(3,2)->setText(fourth_frame["DATA1"].toString());
    model->item(3,3)->setText(fourth_frame["DATA2"].toString());
    model->item(3,4)->setText(fourth_frame["DATA3"].toString());
    model->item(3,5)->setText(fourth_frame["DATA4"].toString());
    model->item(3,6)->setText(fourth_frame["DATA5"].toString());
    model->item(3,7)->setText(fourth_frame["DATA6"].toString());
    model->item(3,8)->setText(fourth_frame["DATA7"].toString());
    model->item(3,9)->setText(fourth_frame["DATA8"].toString());
    model->item(3,10)->setText(fourth_frame["SMS"].toString());

    /* # Set fifth frame # */
    model->item(4,0)->setText(fifth_frame["ID"].toString());
    model->item(4,1)->setText(fifth_frame["DLC"].toString());
    model->item(4,2)->setText(fifth_frame["DATA1"].toString());
    model->item(4,3)->setText(fifth_frame["DATA2"].toString());
    model->item(4,4)->setText(fifth_frame["DATA3"].toString());
    model->item(4,5)->setText(fifth_frame["DATA4"].toString());
    model->item(4,6)->setText(fifth_frame["DATA5"].toString());
    model->item(4,7)->setText(fifth_frame["DATA6"].toString());
    model->item(4,8)->setText(fifth_frame["DATA7"].toString());
    model->item(4,9)->setText(fifth_frame["DATA8"].toString());
    model->item(4,10)->setText(fifth_frame["SMS"].toString());

}

void MainWindow::on_action_Save_Attack_Template_triggered()
{
    /* ## SAVE A JSON ATTACK TEMPLATE ## */

    QJsonObject attack_tpl;
    QJsonObject f1d;
    QJsonObject f2d;
    QJsonObject f3d;
    QJsonObject f4d;
    QJsonObject f5d;
    QStringList first_frame;
    QStringList second_frame;
    QStringList third_frame;
    QStringList fourth_frame;
    QStringList fifth_frame;

    for(int c=0;c <= 10;c++){
        first_frame << model->item(0,c)->text();
    }
    for(int c=0;c <= 10;c++){
        second_frame << model->item(1,c)->text();
    }
    for(int c=0;c <= 10;c++){
        third_frame << model->item(2,c)->text();
    }
    for(int c=0;c <= 10;c++){
        fourth_frame << model->item(3,c)->text();
    }
    for(int c=0;c <= 10;c++){
        fifth_frame << model->item(4,c)->text();
    }


    f1d["ID"] = first_frame[0];
    f1d["DLC"] = first_frame[1];
    f1d["DATA1"] = first_frame[2];
    f1d["DATA2"] = first_frame[3];
    f1d["DATA3"] = first_frame[4];
    f1d["DATA4"] = first_frame[5];
    f1d["DATA5"] = first_frame[6];
    f1d["DATA6"] = first_frame[7];
    f1d["DATA7"] = first_frame[8];
    f1d["DATA8"] = first_frame[9];
    f1d["SMS"] = first_frame[10];

    f2d["ID"] = second_frame[0];
    f2d["DLC"] = second_frame[1];
    f2d["DATA1"] = second_frame[2];
    f2d["DATA2"] = second_frame[3];
    f2d["DATA3"] = second_frame[4];
    f2d["DATA4"] = second_frame[5];
    f2d["DATA5"] = second_frame[6];
    f2d["DATA6"] = second_frame[7];
    f2d["DATA7"] = second_frame[8];
    f2d["DATA8"] = second_frame[9];
    f2d["SMS"] = second_frame[10];

    f3d["ID"] = third_frame[0];
    f3d["DLC"] = third_frame[1];
    f3d["DATA1"] = third_frame[2];
    f3d["DATA2"] = third_frame[3];
    f3d["DATA3"] = third_frame[4];
    f3d["DATA4"] = third_frame[5];
    f3d["DATA5"] = third_frame[6];
    f3d["DATA6"] = third_frame[7];
    f3d["DATA7"] = third_frame[8];
    f3d["DATA8"] = third_frame[9];
    f3d["SMS"] = third_frame[10];

    f4d["ID"] = fourth_frame[0];
    f4d["DLC"] = fourth_frame[1];
    f4d["DATA1"] = fourth_frame[2];
    f4d["DATA2"] = fourth_frame[3];
    f4d["DATA3"] = fourth_frame[4];
    f4d["DATA4"] = fourth_frame[5];
    f4d["DATA5"] = fourth_frame[6];
    f4d["DATA6"] = fourth_frame[7];
    f4d["DATA7"] = fourth_frame[8];
    f4d["DATA8"] = fourth_frame[9];
    f4d["SMS"] = fourth_frame[10];

    f5d["ID"] = fifth_frame[0];
    f5d["DLC"] = fifth_frame[1];
    f5d["DATA1"] = fifth_frame[2];
    f5d["DATA2"] = fifth_frame[3];
    f5d["DATA3"] = fifth_frame[4];
    f5d["DATA4"] = fifth_frame[5];
    f5d["DATA5"] = fifth_frame[6];
    f5d["DATA6"] = fifth_frame[7];
    f5d["DATA7"] = fifth_frame[8];
    f5d["DATA8"] = fifth_frame[9];
    f5d["SMS"] = fifth_frame[10];


    attack_tpl["first_frame"] = f1d;
    attack_tpl["second_frame"] = f2d;
    attack_tpl["third_frame"] = f3d;
    attack_tpl["fourth_frame"] = f4d;
    attack_tpl["fifth_frame"] = f5d;

    QString attack_tpl_file = QFileDialog::getSaveFileName(this,trUtf8("Save an attack template"),trUtf8("template_01.json"),trUtf8("(*.json)"));
    json_handler = new QFile(attack_tpl_file);
    json_handler->open(QFile::WriteOnly);
    json_handler->write(QJsonDocument(attack_tpl).toJson());
    json_handler->close();
}

void MainWindow::on_action_Exit_triggered()
{
    /* ## EXIT ## */
    this->close();
}

void MainWindow::on_actionConnect_triggered()
{
    /* ## GO TO CONNECT FUNCTION ## */
}

void MainWindow::on_actionDisconnect_triggered()
{
    /* ## GO TO DISCONNECT FUNCTION ## */
}

void MainWindow::on_actionWrite_Backdoor_Memory_triggered()
{
    /* ## GO TO WRITE BACKDOOR MEMORY FUNCTION ## */
}

void MainWindow::on_actionLook_for_Frames_triggered()
{

}

void MainWindow::on_actionClear_Frames_Table_triggered()
{
    /* ## CLEAR FRAME TABLE ## */
    model->clear();
    set_frames_table();

}

void MainWindow::on_actionOnline_Help_triggered()
{
    /* ## ONLINE HELP ## */
}

void MainWindow::on_actionAbout_Us_triggered()
{
    /* ## ABOUT US ## */
}

void MainWindow::on_actionCheck_for_Updates_triggered()
{
    /* ## CHECK FOR UPDATES ## */
}



/* ######################################################## */

/* ## # ADVANCED SETUP # ## */

void MainWindow::on_attacker_n_phone_editingFinished()
{
    /* ## ATTACKER TEL-NUMBER ## */

    /* # Get fun with SpeedGauge # */
    if(ui->attacker_n_phone->text() == ""){
        change_speedgauge(0,4);
    }else{
        change_speedgauge(4,0);
    }
}

void MainWindow::on_stop_checkbox_clicked()
{
    /* ## STOP COMMAND ## */

    /* # Get fun with SpeedGauge # */
    if(ui->stop_checkbox->isChecked()){
        change_speedgauge(4,0);
    }else{
        change_speedgauge(0,4);
    }
}

void MainWindow::on_id_match_editingFinished()
{
    /* ## FRAME MATCH ## */

    /* # Get fun with SpeedGauge # */
    if(ui->id_match->text() == ""){
        change_speedgauge(0,10);
    }else{
        change_speedgauge(10,0);
    }
}

void MainWindow::on_gps_long_editingFinished()
{
    /* ## GPS ## */

    /* # Get fun with SpeedGauge # */
    if(ui->gps_long->text() == ""){
        change_speedgauge(0,10);
    }else{
        change_speedgauge(10,0);
    }
}


/* ######################################################## */

/* ## # DEVICE # ## */


void MainWindow::on_btn_connect_clicked()
{
     /* ## CONNECT TO HARDWARE BACKDOOR ## */

    if(connected){
        /* # Disconnect # */
    }

    if(!connected){
        /* # Connect # */
    }
}

void MainWindow::on_btn_write_backdoor_memory_clicked()
{
    /* ## WRITE BACKDOOR MEMORY ## */


    /* # Check predefined frames quantity # */
    int predefined_frames_quantity = 0;

    for(int idq=0;idq <= 4; idq++){
        if(model->item(idq,0)->text() != ""){
            predefined_frames_quantity++;
        }
    }
    ui->progressBar->setValue(5);

    /* # Save frames table # */
    QVector<QStringList> frames(predefined_frames_quantity);

    for(int f=0;f <= predefined_frames_quantity-1; f++){
        QStringList temp;
        for(int c=0;c <= 10;c++){
            temp << model->item(f,c)->text();
        }
        frames[f] = temp;
    }
    ui->progressBar->setValue(10);

    /* # Input filter # */
    mInputFilter = new input_filter();

    /* Frames table */
    int frames_validator = mInputFilter->frames_validator(frames,predefined_frames_quantity);
    bool all_ok = true;

    switch(frames_validator){
        case 01:
            QMessageBox::critical(this,"Error!","Wrong ID in frames table!.");
            all_ok = false;
        break;
        case 02:
            QMessageBox::critical(this,"Error!","Wrong DLC in frames table!.");
            all_ok = false;
        break;
        case 31:
            QMessageBox::critical(this,"Error!","Wrong DATA at column #1 in frames table!.");
            all_ok = false;
        break;
        case 32:
            QMessageBox::critical(this,"Error!","Wrong DATA at column #2 in frames table!.");
            all_ok = false;
        break;
        case 33:
            QMessageBox::critical(this,"Error!","Wrong DATA at column #3 in frames table!.");
            all_ok = false;
        break;
        case 34:
            QMessageBox::critical(this,"Error!","Wrong DATA at column #4 in frames table!.");
            all_ok = false;
        break;
        case 35:
            QMessageBox::critical(this,"Error!","Wrong DATA at column #5 in frames table!.");
            all_ok = false;
        break;
        case 36:
            QMessageBox::critical(this,"Error!","Wrong DATA at column #6 in frames table!.");
            all_ok = false;
        break;
        case 37:
            QMessageBox::critical(this,"Error!","Wrong DATA at column #7 in frames table!.");
            all_ok = false;
        break;
        case 38:
            QMessageBox::critical(this,"Error!","Wrong DATA at column #8 in frames table!.");
            all_ok = false;
        break;
        case 41:
            QMessageBox::critical(this,"Error!","SMS commands must be 4 characters length and only letters in uppercase!");
            all_ok = false;
        break;
    }

    ui->progressBar->setValue(25);

    /* Attacker Tel-Number */
    QString string_number = ui->attacker_n_country->text() + ui->attacker_n_area->text() +
            ui->attacker_n_phone->text();
    if(string_number == ""){
        QMessageBox::critical(this,"Error!","Attacker tel-number must be defined!");
        all_ok = false;
    }else{
        bool number_validator_r = mInputFilter->tel_number_validator(string_number);
        if(!number_validator_r){
            QMessageBox::critical(this,"Error!","Attacker tel-number must be only numeric characters!");
            all_ok = false;
        }
    }

    /* Advanced features */
    bool match_frame = false;
    bool gps = false;

    if(ui->id_match->text() != "" && ui->gps_lat->text() != ""){
        QMessageBox::critical(this,"Error!","You can only use one of the advanced features (Please, unset GPS or Frame)");
        all_ok = false;
    }else{
        if(ui->id_match->text() != ""){
            match_frame = true;
        }
        if(ui->gps_lat->text() != ""){
            gps = true;
        }

    }

    /* Frame - Advanced feature */
    if(match_frame == true){

        int pre_frame_number = ui->af_pre_frame_number->value();

        if(model->item(pre_frame_number-1,0)->text() == ""){
            QMessageBox::critical(this,"Error!","Frame selected to inject in advanced features is not previously defined!");
            all_ok = false;
        }

        QString id_match = ui->id_match->text();
        QString dlc_match = ui->dlc_match->text();
        QString d1_match = ui->d1_match->text();
        QString d2_match = ui->d2_match->text();
        QString d3_match = ui->d3_match->text();
        QString d4_match = ui->d4_match->text();
        QString d5_match = ui->d5_match->text();
        QString d6_match = ui->d6_match->text();
        QString d7_match = ui->d7_match->text();
        QString d8_match = ui->d8_match->text();
        QStringList all_dt_match;
        all_dt_match << d1_match << d2_match << d3_match << d4_match <<
                        d5_match << d6_match << d7_match << d8_match;

        int match_frame_validator = mInputFilter->match_frame_validator(id_match,dlc_match,all_dt_match);

        switch(match_frame_validator){
            case 61:
                QMessageBox::critical(this,"Error!","Frame ID to inject in advanced features is wrong!");
                all_ok = false;
            break;
            case 62:
                QMessageBox::critical(this,"Error!","Frame DLC to inject in advanced features is wrong!");
                all_ok = false;
            break;
            case 63:
                QMessageBox::critical(this,"Error!","Frame DATA to inject in advanced features is wrong!");
                all_ok = false;
            break;
        }

        QStringList dt_position_to_do_match;

        if(ui->md1->isChecked()){ dt_position_to_do_match << "1";}
        if(ui->md2->isChecked()){ dt_position_to_do_match << "2";}
        if(ui->md3->isChecked()){ dt_position_to_do_match << "3";}
        if(ui->md4->isChecked()){ dt_position_to_do_match << "4";}
        if(ui->md5->isChecked()){ dt_position_to_do_match << "5";}
        if(ui->md6->isChecked()){ dt_position_to_do_match << "6";}
        if(ui->md7->isChecked()){ dt_position_to_do_match << "7";}
        if(ui->md8->isChecked()){ dt_position_to_do_match << "8";}

        qDebug() << dt_position_to_do_match;
    }

    /* GPS - Advanced feature */
    if(gps == true){
        int pre_frame_number = ui->ag_pre_frame_number->value();

        if(model->item(pre_frame_number-1,0)->text() == ""){
            QMessageBox::critical(this,"Error!","Frame selected to inject in advanced features is not previously defined!");
            all_ok = false;
        }

        QString gps_lat = ui->gps_lat->text();
        QString gps_long = ui->gps_long->text();

        if(gps_lat.isEmpty() || gps_long.isEmpty()){
            QMessageBox::critical(this,"Error!","GPS coordinates are not defined correctly!");
            all_ok = false;
        }else{

            int gps_validator = mInputFilter->gps_validator(gps_lat,gps_long);
            if(gps_validator == 51){
                QMessageBox::critical(this,"Error!","GPS latitude is wrong!");
                all_ok = false;
            }
            if(gps_validator == 52){
                QMessageBox::critical(this,"Error!","GPS longitude is wrong!");
                all_ok = false;
            }
        }
    }

    ui->progressBar->setValue(50);

    if(all_ok == false){
        ui->progressBar->setValue(0);
        ui->status_label->setText("ERROR");
    }else{

        /* # CONNECT TO THE BACKDOOR AND WRITE ITS MEMORY */
    }

}



/* ######################################################## */

/* ## # FINAL PROGRESS BAR # ## */
void MainWindow::on_progressBar_valueChanged(int value)
{
    mSpeedNeedle->setCurrentValue(value);
}
