#ifndef DMANAGER_H
#define DMANAGER_H

// ���������� Qt4.
#include <QList>
#include <QHostAddress>

// ����������� ���������� �++. 
#include <list>

#include "duser.h"
#include "dservice.h"

class dChatApplication;
class QStandardItemModel;
class QItemSelectionModel;

class dManager : public QObject
{
    // ������� ������ ������.
	friend dService::~dService();
	friend dService::dService(  dManager *_manager,
                                const uint _port,
                                uint _useNetworkPath,
                                const QHostAddress &_local_ip );
	friend dService::dService(  dManager *_manager,
                                dAbstractRemoteUserCreator *_absRtUsrCreator, 
                                const uint _port,
                                uint _useNetworkPath,
                                const QHostAddress &_local_ip );
	friend dService::dService(  dManager *_manager,
                                const QString &_local_ip_qstring,
                                const uint _port, 
                                uint _useNetworkPath );
	friend void dService::connecting();
	
	friend dUser::~dUser();
    friend dUser::dUser( dManager * _manager, 
                         const QHostAddress &_ip, 
                         const QString &_name );
    friend class dPUser;
    
	private:
    // �������� ������� � ��������, ����� ������� ���������� ���-����� ���� �������������
    // ����, �� ���� �����, ����� �������, ����������� �������� ���-�������.
    // �� ��������� 60 ���.
        uint interval_refresh;

    // �������� ������� � ��������, ����� ������� ���������� ���� ������������,
    // ���� ���������� ��� ����������.
    // �� ��������� 40 ���.
        uint interval_ping;
        
    // ����� ����� �� ��������� ������������( �� ��������� 150 ���).
        uint timeout;
        
	// ������ ���� ��������, �� ���� �����, �� ����� ���� ���������,
	// �� ������ ������.
		QList<dService*> services;
    // ������ ���� ������, ������� ��������� �� ���� ��������(�����),
    // � ��� ����� � ���������.
		QList<dUser*> users;	

    // ��������� �� "���������" ������������.
		dPUser main_user;		
    // ��������� �� ������� ������ ����������.
        dChatApplication *application;

    // ��������� ����� ������.
        QHostAddress localIP;
            
    // ����� ������� ���������� ������.
        int refreshTimerID;
    protected:		
    // ������� �������.
        void timerEvent(QTimerEvent *event);
    
    // ������������� ��������� ����� ������.
    //    void set_localAddress( const QHostAddress &_localIP ){ localIP = _localIP; };
        
    //***************************************************************
    // ������ ���������(�������) ������ � ������(�� ������).
	// ������������ � ������������ � ����������� ������ dService.
    // �� ����, ������� ������ dService, ��� �������� ���� ���������(�������)
	// ���� � ������.
		virtual void deleteService(dService * service);
		virtual dService *addService(dService * service);
    
    //***************************************************************
    // ������ ���������(�������) ������������ � ������(�� ������).
    // ��� ���� ���������� �������� �� ������������.
		virtual dUser *addUser(dUser * usr);
		virtual void deleteUser(dUser * usr);		
    
    public:
      
    // �������� ��������� ����� ������.
        QHostAddress get_localAddress() const{ return localIP; };

    // ������ ���������� � ������������� ����� ����� �� ��������� ������������, 
    // ����� ������� ����� ���� ��������� ����������� � �� �������� �� ���-�������.
        uint get_timeout() const{ return timeout; };
        void set_timeout( uint _timeout ){ timeout = _timeout; };

    // ������ ���������� � ������������� �������� ��������� �����
    // ������������ ��� �������� ��� ����������. 
        uint get_interval_ping() const{ return interval_ping; };
        void set_interval_ping( uint _interval_ping ){ interval_ping = _interval_ping; };

    // ������ ���������� � ������������� �������� ������� �����
    // ����� ���� �������� ��� �������.
        uint get_interval_refresh() const{ return interval_refresh; };
        void set_interval_refresh( uint _interval_refresh );
		
    // ������� ��������� �� ��������� ������������.
		virtual dPUser get_main_user() const { return main_user; };
    // ������ ��. ������������.(��������)
        virtual void set_main_user( dPUser _usr ){ main_user = _usr; };
		        
    // ���������� ���������� ������������� � ������.
		uint get_user_count() const;
		
    // ����� ������������ � ������ �� ��� IP � �����.
		virtual dPUser find_user( const QHostAddress &_ip, const QString &_name);
		virtual dPUser find_user( const QString & _ip, const QString &_name);
		virtual dPUser find_user( const char * _ip, const char * _name);
    // ����� ������������� �� IP-������.
		virtual QList<dPUser> find_users_by_ip( const QHostAddress &_ip );
    
    // ���� ����������� �������� ������ ������������� ��� ��������
    // �� ����������� �� ��������� �����������.
		virtual QList<dPUser> get_users() const;
		virtual const QList<dService*>& get_services() const { return services; };

    // ����������� � ����������.
		dManager( QObject  *_parent = 0 );
		~dManager();
        
    // ���� �������� ���������.
        enum dMessageMassType
        {  
            msg_echo,
            msg_enter,
            msg_exit,
            msg_channel,
            msg_channel_me,
            msg_mass,
            msg_rename,
            change_topic
        };
    // ���������� ����� �������� �������� ���������.
		bool send_mass( dService::dMessageSendType _msg_send_type,
                        dMessageMassType _msg_mass_type, 
                        dPUser _from = dPUser(), 
                        const QString* _msg = NULL );    
    // ����� ���� ������, ������� ������ �������� ��������� ���� �����
    // � ��������� ����������� _msg_type.
    // �������� �������� ���-������ �� ����� "����������" ������������,
		bool send_mass_echo( dService::dMessageSendType _msg_send_type  = dService::default_type );
    // �������� �������� ��������� � ����� ������������ � ���.
		void send_mass_enter( dPUser _from = dPUser(), dService::dMessageSendType _msg_send_type = dService::default_type );
    // �������� �������� ��������� � ������ ������������ � ���.
		void send_mass_exit( dPUser _from = dPUser(), dService::dMessageSendType _msg_send_type = dService::default_type);	

/*======================================================================
        ��������.... � ������ ����� �� ������������...
    // �������� �������� ��������� � �����.
		void send_mass_msg_channel( const QString &_msg, dUser *_from = 0, dService::dMessageSendType _msg_send_type = dService::default_type );	
    // �������� �������� ��������� � �����.
		void send_mass_msg_channel_me(const QString &_msg, dUser *_from = 0,  dService::dMessageSendType _msg_send_type = dService::default_type );	
    // ������� ��������� � �������������� ������������
        void send_mass_rename( const QString &_oldname , dUser *_from , dService::dMessageSendType _msg_send_type = dService::default_type);
    // �������� �������� ������ ������.
        void send_mass_change_topic( const QString &_topic , dService::dMessageSendType _msg_send_type = dService::default_type);
*/
    //***************************************************************
        
    // ��������� ������ ������� ��� ��������, �� �������� ����� ����� 
    // � dUser. � ������� ��� �������� ��������� ����� ����������
    // �������������.
		bool send_info_request( const QList<dPUser> &_to, dPUser _from );
		bool send_image_request( const QList<dPUser> &_to, dPUser _from );
		bool send_msg( const QList<dPUser> &_to,const QString & msg, dPUser _from, bool _html = false);
        bool send_msg_mass( const QList<dPUser> &_to,const QString & msg, dPUser _from, bool _html = false);
		bool send_msg_beep( const QList<dPUser> &_to, dPUser _from );		
		bool send_auto_answer( const QList<dPUser> &_to, dPUser _from );
		bool send_change_topic( const QList<dPUser> &_to, const QString & _topic );
		bool send_msg_channel( const QList<dPUser> &_to,const QString & msg, dPUser _from );
		bool send_msg_channel_me( const QList<dPUser> &_to,const QString & msg, dPUser _from );
        bool send_rename( const QList<dPUser> &_to, const QString &_oldname , dPUser _from );
        
    //***************************************************************
    // ��������� ������� ����.
    // ������� ���������� ��� ����� ����������.
		virtual void event_change_activity( dPUser _from ){};
    // ������� ���������� ��� ����� ������.
		virtual void event_change_mode( dPUser _from ){};
    // ������� ����������, ��� ����� ������ ���� ������������ � ���.
		virtual void event_msg_enter( dPUser _from ){};
    // ������� ����������, ��� ������ ������������ �� ����.
		virtual void event_msg_exit( dPUser _from ){};
    // ������� ����������, ��� ������ ������������ �� ����.
		virtual void event_msg_rename( dPUser _from, const QString & _oldname ){};
    // ������� ����������, ����� �������� ������ ���������.
		virtual void event_msg_personal( dPUser _from, dPUser _to ,const QString & _msg, bool _html = false){};
    // ������� ����������, ����� �������� ��������� � �����.
		virtual void event_msg_channel( dPUser _from, const QString & _msg){};
    // ������� ����������, ����� �������� �������� ������.
		virtual void event_msg_beep( dPUser _from, dPUser _to ){};
    // ������� ����������, ��� ��������� ��������� ���������.
		virtual void event_msg_mass( dPUser _from, dPUser _to, const QString & _msg, bool _html = false){};
    // ������� ����������, ��� ����� ������.
		virtual void event_change_topic( const QString &_topic ){};
    // ������� ����������, ����� �������� ��������� � ������� �������.
		virtual void event_current_topic( const QString &_topic){};
    // ������� ����������, ����� �������� ��������� � ����� � �������� 
    // ������� (Me-���������).event_change_topic
		virtual void event_msg_channel_me( dPUser _from, const QString &_msg){};
    // ������� ����������, ��� ��������� ����-������.
		virtual void event_msg_auto_answer( dPUser _from, dPUser _to, const QString & _msg){};
    // ������� ���������� ,����� �������� Xml - ���������.
		virtual void event_xml( dPUser _from, dPUser _to, const QDomElement &messageElement ){};
    
    //***************************************************************
    //  ���������� � ���������� �������������� ����������� �������.
    // ������� ��� ���������� ����������, ������������� � ������ dManagerEx
    // �eader file: dManagerEx.h
    // ���������: 08.08.2005
    public:
    // ���������� ��������� �� ������ ������ � �� 
    // ������ ��������� ������    
        virtual QStandardItemModel *get_model() const{ return 0; };
        virtual QItemSelectionModel *get_selectionModel() const{ return 0; };

    // ���������� ������ ������������� ������� �������� � ������.
        virtual QList<dPUser> getSelectedUserToModel(){ return QList<dPUser>(); };
    // ���������� ������������ ������� �������� ������� � ������.
        virtual dPUser getCurrentUserToModel(/* QModelIndex &_index */){ return dPUser(); };

};

#endif	//DMANAGER_H

