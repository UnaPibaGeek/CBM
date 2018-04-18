#include "connection.h"

static bool conn = false;
static QextSerialPort *port;

connection::connection()
{
}

bool connection::open_connection(){

    static bool port_created = false;

    if(port_created == false){
        port = new QextSerialPort();
        port->setQueryMode(QextSerialPort::Polling);
        port_created = true;
    }

    if(conn){
        close_connection();
        conn = false;
    }

    port->setBaudRate (BAUD9600);
    port->setDataBits(DATA_8);
    port->setStopBits(STOP_1);
    port->setParity(PAR_NONE);
    port->setFlowControl(FLOW_OFF);
    port->setTimeout(10);


    QList<QString> ports;
    ports << "COM0" << "COM1" << "COM2" << "COM3" << "COM4" << "COM5" << "COM6" << "COM7" << "COM8" << "COM9"
            << "COM10" << "COM11" << "COM12" <<"COM13" << "COM14" << "COM15 "<< "COM16"
            << "/dev/ttyUSB0" << "/dev/ttyUSB1" << "/dev/ttyUSB2" << "/dev/ttyUSB3"
            << "/dev/ttyUSB4" << "/dev/ttyUSB5";

    QString COM;

    foreach(COM, ports){
        port->setPortName(COM);

        if(port->open(QextSerialPort::ReadWrite)){
              conn = true;
              break;
        }
     }

    if(conn){
        return true;
    }else{
        return false;
    }

}

void connection::close_connection(){

    if(conn){
        port->close();
    }

    conn = false;
}

bool connection::send_data(char bytes){

    if (conn){

        port->putChar(bytes);
        return true;

    }else{
        return false;
    }
}
