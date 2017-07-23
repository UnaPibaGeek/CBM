#include "input_filter.h"

input_filter::input_filter()
{
}

int input_filter::frames_validator(QVector<QStringList> frames, int pfq){

    for (int f=0; f <= pfq-1; f++){ // for each frame

        QString id = "";
        QString dlc = "";
        QString dt1 = "";
        QString dt2 = "";
        QString dt3 = "";
        QString dt4 = "";
        QString dt5 = "";
        QString dt6 = "";
        QString dt7 = "";
        QString dt8 = "";
        QString sms = "";

        id = frames[f][0];
        dlc = frames[f][1];
        dt1 = frames[f][2];
        dt2 = frames[f][3];
        dt3 = frames[f][4];
        dt4 = frames[f][5];
        dt5 = frames[f][6];
        dt6 = frames[f][7];
        dt7 = frames[f][8];
        dt8 = frames[f][9];
        sms = frames[f][10];

        bool conversion_ok = false;

        if (id != "" or id != 00){

            const unsigned int id_hex = id.toUInt(&conversion_ok, 16);
            if(conversion_ok){
                conversion_ok = false; // It's ok!.
            }else{
                return 01; // Something wrong!.
            }


            // DLC validator
            int dlc_i;
            dlc_i = dlc.toInt();
            if (dlc_i >= 9){
                return 02; // Something wrong!.
            }


            // DATA validator

            //Data 01
            if(dlc_i >= 1){
                const unsigned int dt1_hex = dt1.toUInt(&conversion_ok, 16);
                if(conversion_ok){
                    conversion_ok = false; // It's ok!.
                }else{
                    return 31; // Something wrong!.
                }
            }

            //Data 02
            if(dlc_i >= 2){
                const unsigned int dt2_hex = dt2.toUInt(&conversion_ok, 16);
                if(conversion_ok){
                    conversion_ok = false; // It's ok!.
                }else{
                    return 32; // Something wrong!.
                }
            }

            //Data 03
            if(dlc_i >= 3){
                const unsigned int dt3_hex = dt3.toUInt(&conversion_ok, 16);
                if(conversion_ok){
                    conversion_ok = false; // It's ok!.
                }else{
                    return 33; // Something wrong!.
                }
            }

            //Data 04
            if(dlc_i >= 4){
                const unsigned int dt4_hex = dt4.toUInt(&conversion_ok, 16);
                if(conversion_ok){
                    conversion_ok = false; // It's ok!.
                }else{
                    return 34; // Something wrong!.
                }
            }

            //Data 05
            if(dlc_i >= 5){
                const unsigned int dt5_hex = dt5.toUInt(&conversion_ok, 16);
                if(conversion_ok){
                    conversion_ok = false; // It's ok!.
                }else{
                    return 35; // Something wrong!.
                }
            }

            //Data 06
            if(dlc_i >= 6){
                const unsigned int dt6_hex = dt6.toUInt(&conversion_ok, 16);
                if(conversion_ok){
                    conversion_ok = false; // It's ok!.
                }else{
                    return 36; // Something wrong!.
                }
            }

            //Data 07
            if(dlc_i >= 7){
                const unsigned int dt7_hex = dt7.toUInt(&conversion_ok, 16);
                if(conversion_ok){
                    conversion_ok = false; // It's ok!.
                }else{
                    return 37; // Something wrong!.
                }
            }

            //Data 08
            if(dlc_i >= 8){
                const unsigned int dt8_hex = dt8.toUInt(&conversion_ok, 16);
                if(conversion_ok){
                    conversion_ok = false; // It's ok!.
                }else{
                    return 38; // Something wrong!.
                }
            }


            // SMS validator
            QRegExp upperMatcher("^[A-Z]{4}$");
            if (!upperMatcher.exactMatch(sms)){
                return 41; //Something wrong!
            }

        }else{
            return 0;
        }

    }

}

bool input_filter::tel_number_validator(QString string_number){

    QRegExp numericMatcher("^[0-9]*$");
    if (!numericMatcher.exactMatch(string_number)){
        return false; //Something wrong!
    }

    return true;
}

int input_filter::gps_validator(QString gps_lat, QString gps_long){

    if(gps_lat.size() >= 15){
        return 51; //Something wrong!
    }

    if(gps_long.size() >= 15){
        return 52; //Something wrong!
    }
}

int input_filter::match_frame_validator(QString id, QString dlc, QStringList data){


    // ID validator
    bool conversion_ok = false;
    const unsigned int id_hex = id.toUInt(&conversion_ok, 16);
    if(conversion_ok){
        conversion_ok = false; // It's ok!.
    }else{
        return 61; // Something wrong!.
    }

    // DLC validator
    int dlc_i;
    dlc_i = dlc.toInt();
    if (dlc_i >= 9){
        return 62; // Something wrong!.
    }

    for(int f=0; f<= 7; f++){

        if(!data[f].isEmpty()){

            bool dt_conversion_ok = false;
            const unsigned int dt_hex = data[f].toUInt(&dt_conversion_ok, 16);
            if(dt_conversion_ok){
                dt_conversion_ok = false; //It's ok!.
            }else{
                return 63;
            }

        }
    }
}
