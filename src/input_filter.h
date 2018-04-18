#ifndef INPUT_FILTER_H
#define INPUT_FILTER_H

#include <QRegularExpression>
#include <QDebug>

class input_filter
{
public:
    input_filter();
    int frames_validator(QVector<QStringList>, int);
    int gps_validator(QString,QString);
    int match_frame_validator(QString, QString, QStringList);
    bool tel_number_validator(QString);
};

#endif // INPUT_FILTER_H
