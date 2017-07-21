#ifndef CONNECTION_H
#define CONNECTION_H

#include <qextserialport.h>
#include <QStringList>

class connection
{
public:
    connection();
    bool open_connection();
    bool send_data(char bytes);
    void close_connection();
};

#endif // CONNECTION_H
