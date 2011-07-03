#ifndef DSERVICE_H
#define DSERVICE_H

// ���������� QT.
#include <QtXml>
#include <QUdpSocket>
#include <QAbstractSocket>
#include <QTextStream>
#include <QIODevice>

#include "duser.h"

class dService;     // ������ ����.... � ���� �����.

// ����������� �����...
// ������ ��� ���������, ������� ������ ���������� ����� ������ IP �������.
class dAbstractIPList
{
    private:
        dService *service;
   
    public:
        dAbstractIPList( dService *_service = 0);
        ~dAbstractIPList();
        void addListToService( dService *_service );
        virtual const QList<QHostAddress> &get_ip_list() const= 0;
};

// ����� ������������ ����� �������� IP �������.
class dRangeIP : public dAbstractIPList
{
    private:
        QList<QHostAddress> ip_list;

    public:
        dRangeIP( const QHostAddress& _border1, 
                  const QHostAddress& _border2,
                  dService *_service = 0 );
        virtual const QList<QHostAddress> &get_ip_list() const{ return ip_list; };

};

// ����� ������������ ���� IP �����.
class dSingleIP : public dAbstractIPList
{
    private:
        QList<QHostAddress> ip_list;
    public:
        dSingleIP( const QHostAddress& _ip, dService *_service = 0);
        virtual const QList<QHostAddress> &get_ip_list() const{ return ip_list; };
};


class dManager;
class dRemoteUser;
class dAbstractRemoteUserCreator;
class dUdpSocket;

class dService: public QObject
{
	Q_OBJECT			// ����������������, ����� ��� ������ ���������� Qt.
	friend class dManager;
	friend class dRemoteUser;
	friend class dAbstractIPList;
    
	public:
    //***************************************************************
    // ������ �������� ���������.
    // ��� �������� �������� ���������.
        enum dMessageSendType
        {  
            default_type,
            list_ip_type,
            broadcast_ip_type
        };

    private:
    // ������ �������, ������������ ��� �������� �������� ���������.
        QList<dAbstractIPList*> ip_lists;
        
    // �������� �������.
        dManager *manager;
    // �������� ��� �������� �������� ���������.
        dMessageSendType send_type;
        
    // ����� ������� ������ ���������� ������������.
        virtual dPUser createRemoteUser( const QHostAddress &_ip, const QString &_name );
	protected:         
                
    //***************************************************************
    // �������� �������� ��������� �� ��������� IP.
		int send( const QHostAddress &_ip, const QByteArray &_msg );
        int send( const QHostAddress &_ip, const QString &_msg );

    //********* ******************************************************
    // ������� �������� ���������.
    // �������� �������� ���-������.
		virtual void send_mass_echo( dMessageSendType _msg_send_type, dPUser _from );
    // �������� �������� ��������� � ����� ������������ � ���.
		virtual void send_mass_enter( dMessageSendType _msg_send_type, dPUser _from );
    // �������� �������� ��������� � ������ ������������ � ���.
		virtual void send_mass_exit( dMessageSendType _msg_send_type, dPUser _from );
    // �������� ��������� � �����.
		virtual void send_mass_msg_channel( dMessageSendType _msg_send_type, dPUser _from , const QString &_msg);
    // �������� me-������� � �����.
		virtual void send_mass_msg_channel_me( dMessageSendType _msg_send_type, dPUser _from , const QString &_msg);
    // �������� ��������� � ����� ������.
		virtual void send_mass_change_topic( dMessageSendType _msg_send_type,  const QString &_topic);
    // �������� ��������� � �������������� ������������.
        virtual void send_mass_rename( dMessageSendType _msg_send_type, dPUser _from, const QString &_oldname );
    //***************************************************************
    
    // �������������� ����������, ������� ������ XML ��������� ����.
		virtual void xmlParser( dPUser _from, dPUser _to, const QDomElement &messageElement ); 

    public:
        int useNetworkPath;
    // ����� ������������� ��� �������� �������� ���������.
        void set_send_type( dMessageSendType _send_type ){ send_type = _send_type; };
    // ����� ���������� ��� �������� �������� ���������.
        dMessageSendType get_send_type(){ return send_type; };
    
    // ���������� ��������� �������.
        dManager *get_manager(){ return manager; };
    
    // ��� ����������� ����, ����� ��� ��������� ����������, 
    // ����������� ��� ����������� ������ � ������ ����.
        enum dServiceError{ init,
                            load_plugin };
        
	// ������� ������� ����.
        uint log_mode;                          

    // ����� ������������� � ����������.
		dService( dManager *_manager, const uint _port = 8167, uint _useNetworkPath = 0, const QHostAddress &_local_ip = QHostAddress() );
		dService( dManager *_manager, const QString &_local_ip_qstring, const uint _port = 8167, uint _useNetworkPath = 0);
		dService( dManager *_manager, dAbstractRemoteUserCreator *_absRtUsrCreator, const uint _port = 8167, uint _useNetworkPath = 0, const QHostAddress &_local_ip = QHostAddress() );
		~dService();

    // ���������� ������ ������� �������� ��������.
        virtual QList<QHostAddress> get_ip_list() const;
		
    // ��������� ������� ������ � ������. �� ��������� size = 49152.
		void setReadBufferSize( const uint size );

    //***************************************************************
    //  ������� ���������� �����.
    // ����� ���� �� �������� ���� ����������.
		void onLog( QIODevice * _log_dev, uint _log_mode = 0xFFFFFFFF);	
    // ����� ���� � ����.
		bool onLog( const char * file_name, uint _log_mode = 0xFFFFFFFF);	
		bool onLog( const QString & file_name_qstring, uint _log_mode = 0xFFFFFFFF);
	// ������� ��� ���� ����� �������� ��� � ���������� ����� (stdout).
		bool onLog( FILE * file, uint _log_mode = 0xFFFFFFFF);
    // ����� ������������� ������� ������� ����.
		void dService::setLogMode( uint _log_mode );
    // ��������� ������� ����.
		void offLog(void);						            
		
		void set_broadcast_ip( const QHostAddress &_broadcast_ip ){ broadcast_ip = _broadcast_ip; };
		
	private:
		QHostAddress	broadcast_ip;			// �������� ����������������� ����� ������.			
		QHostAddress	localhost_ip;			// 127.0.0.1			

    // ��������� �� �����.        
		QUdpSocket      *udpSocket;         	
    // ��������� �� ���� ����������� ����� ������� �������� � UPD.
    // ��� ��� ���������� �� �������� �� ���������,
    // ������ ��������� ������.....
        dUdpSocket      *udpSocketPath;
        
		QHostAddress	local_ip;			// �������� ��������� ����� ������.
		uint			port;				// ���� �� ������� ������ ������(���).

		QIODevice		*log_dev;			// ��������� �� ���-����������.
		QTextStream		log;				// ������ ����.

    // ��������� �� ����������� ����� ��������� ��������� �������������.
        dAbstractRemoteUserCreator *absRtUsrCreator;

    // �������������� ����������, ������� ������ ��������� ����.
    // ���������� �������������!
		void parser( const QHostAddress &_ip, const QByteArray &_msg); 
        
    // �������� �������� ������� � ���� ������������� � ������.
    // ���������� �������������!
        void event_mass( dUser::dMsgType _event_type, dPUser _from, const QString *_msg = NULL );
    // ������������� �����.
    // ���������� �������������!
        void connecting();                  
        void connectingPath();        // ���� ����� �� ������ ���� ����������.
    // ��������� ����� �� ������.
    // ���������� �������������!
        QString escapeXml( QString _xml );
													     
	private slots:
        void dataReceived();				// ����. ����������, ����� �������� ������ �� ����.
        void dataReceivedPath();			// ����. ����������, ����� �������� ������ �� ����.
};

#endif	//DSERVICE_H
