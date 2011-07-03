#ifndef DUDPSOCKET_H
#define DUDPSOCKET_H

#include <QtGui>
#include <QHostAddress>
#include <winsock.h>

class dUdpSocket;
Q_DECLARE_INTERFACE(dUdpSocket,"dUdpSocket/1.0")

struct dBuffer
{
// ������.
    QByteArray data;
// ����� ������ �����������.
    QHostAddress address;
// ���� � �������� ������ ������.
    uint port;
};

class dUdpSocket : public QThread
{
    Q_OBJECT
    Q_INTERFACES(dUdpSocket)
    private:
    // ���������� ��� �����.
        SOCKET sock;
    // ������ ���������� ������.
        QMutex  mutexSend;
        QMutex  mutexRead;
        QMutex  mutexReconnect;
    // ����� ��� ��������� ������ ��������� � ������.
        QByteArray buffer;
    // ����� �������, ��� �������� �������.
        QList<dBuffer> outBuffers;
        QList<dBuffer> inBuffers;
    // �������� ��������� ��������.
        bool connected;
    // ������ ��������� ������.
        int datagramSize;
    
    // ��������� ��������������� ��� ������ ������ ����.
        QHostAddress listen_ip;
        uint listen_port;
    public: 
        dUdpSocket(QObject * _parent = 0);
        ~dUdpSocket();
        virtual bool bind( const QHostAddress &_local_ip , uint _port );
        virtual int pendingDatagramSize() const{ return datagramSize; };
 //       virtual int readDatagram( char* _buffer, int _buffer_size, QHostAddress *_address, uint *_port );
        virtual int readDatagram( QByteArray &_datagram, QHostAddress *_address, uint *_port );
        virtual int writeDatagram ( const QByteArray & datagram, const QHostAddress & host, uint port );
        virtual int hasPendingDatagrams();
    
    protected:
        void run();
    // �������.... ����� ��� �������������� ����������������....
        virtual void timerEvent ( QTimerEvent * event );
        
    signals:
    // ������ ��������, ����� ������ ������ � ������.
        void readyRead();
};
#endif // DUDPSOCKET_H


