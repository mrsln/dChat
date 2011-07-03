#ifndef DUSER_H
#define DUSER_H

// ���������� QT
#include <QtXml>
#include <QObject>
#include <QString>
#include <QHostAddress>
#include <QPixmap>
#include <QDateTime>
#include <QMetaType>
// ����������� ���������� �++. 
// #include <iostream.h>

class dManager;
class dService;
class dUser;

// ������� ��������������� �������� �� ������ dUser
class dPUser
{
    friend class dUser;
//    friend class dManager;
    private:
        dManager *manager;
        dUser *user;
    protected:
        dPUser( dManager *_manager, dUser *_user );
        dPUser( dUser *_user );

        operator dUser*();
    public:
        dPUser():user(NULL),manager(NULL){};
    // ���������� ����������� �����.
        dPUser( const dPUser &_user );
    // ���������� �������� ������������.
        dPUser & operator= ( const dPUser &_user );

    // ���������� ��������, ������� ���������� ��������� �� ������ ��� �����.
        virtual dUser*operator->();
        
    // ����� ���������� ��������� �� �������� ��������������.
        static dPUser main_user( dManager *_manager );
     //   static dPUser main_user( dManager *_manager );
     //   dPUser main_user();
   /*             
        operator bool()
        { 
            return (user == NULL && manager == NULL) ? true: false;
        };       
   */
        bool operator == ( bool b )
        { 
            if( b )
                return (user == NULL || manager == NULL) ? false: true;
            return (user == NULL || manager == NULL) ? true: false;
        }; 
            
        bool operator == ( const dPUser &usr)
        { 
            return (usr.user == user) ? true: false;
        };   
       
        bool operator !()
        { 
            return (user == NULL || manager == NULL) ? true:false;
        };

};

class dUser : public QObject
{
    friend class dService;
    
    private:
//--------------------------------------------------------------
// �������� ������������ ����.
		QString	login;		// ����� ��� ������� �� ����� �� ���������.
		QString	host;		// ��� ����������.
		QString	version;	// ������ ����.
		QString	auto_answer;// ����-�����.

		uint	sex;		// ���.
		QString	memory;		// ���������� ������ �� ����������.
		QString	percent;	// ������� ������������� �������.
		QString	topic;		// ��������� � ����.
        bool	activity;   // ���������� �����������: (1 - �������, 0 - ���������)
        uint	mode;       // ���������� �����������: (0 - ����������, 1 - DND, 2 - Avay, 3 - Offline)
        QPixmap	avatar;     // ��������.
        uint xml_protocol;   // ������ XML ���������.
        QHash<QString,QVariant> property; // �������������� �������� ������������,
                                         // ������� ��� ����������.
//--------------------------------------------------------------
//    �������� ���������, ������� �������� ������ ������������ ��
// �������, ��� ����� ������, � ��� ������������.

		QString	 name;		    // ���(nickname)
		QHostAddress ip;		// IP-������
								// ������� �������� �������� ����� �������.

        // ��������...
		// QDateTime time;			// ����� ���������� ���������� � ������������.

		dManager	* manager;		// ������ ��������� �� ����� dManager,
    protected:
    
    //***************************************************************
    // ��������� ������� ������������.
        
		virtual bool set_name(const QString &_name)       { name  =_name; return true;};
    //  ��������� �� �������������.  
    //  virtual void set_ip(const QHostAddress & _ip)     { ip    =_ip; };
		virtual void set_host(const QString & _host)      { host  =_host; };
		virtual void set_login(const QString &_login)     { login =_login; };
		virtual void set_version(const QString &_version) { version =_version; };
		virtual void set_percent(const QString &_percent) { percent =_percent; };
		virtual void set_memory(const QString &_memory)   { memory =_memory; };
		virtual void set_sex(const uint &_sex)            { sex   =_sex; };
		virtual void set_auto_answer(const QString &_auto_answer){  auto_answer=_auto_answer; };
		virtual void set_mode(const uint &_mode)          { mode =_mode; };
		virtual void set_activity(const bool &_activity)  {activity=_activity; };
		virtual void set_avatar(const QPixmap &_avatar)   { avatar =_avatar; };
		virtual void set_xml_protocol(uint _xml_protocol) { xml_protocol =_xml_protocol; };    
    public:
		virtual void set_property(const QString &key, const QVariant &value) 
                                                          { property.insert(key, value); };    
		virtual void set_topic(const QString &_topic)     { topic =_topic; };    
    protected:
    // ��������� ����� ���������� ���������� � ������������.
 		virtual void uptime(){};
    // ������� ����� ������� ����� ����� ������� ������������
    // � ������ ���������� �� ������.
    // ������������ ������ 1 ��� � ����������� dService, �����
    // ����� ������� ���� ������������� ������������� �����
    // �������.
        virtual void deleteRemoteUser(dService * srv){};
        
	public:
	// ����� ������ ������� ������� ������, ������� ����������.
        void delete_user(){ delete this; };
        
	// ���������� ��������������� �������� �� ������� ������.
       dPUser get_pointer();

    // ����� ������������� �������� ������������ �� ����� �������� ��������
    // ���. 
		virtual bool set_main_user(){ return false; };
    // ���������� �������� ������������.
		virtual dPUser get_main_user()const;

    // �������� �� ���������� ������� ��������, ���� ����� �������,
    // �� ������������ ��������� �� ������.	
	//	virtual void check_time_out();	
        
    //***************************************************************
	// ��������� ������� ������������.
		virtual const QHostAddress &get_ip()    const{ return ip; };
		virtual const QString &get_name()       const{ return name; };
		virtual const QString &get_host()       const{ return host; };
		virtual const QString &get_login()      const{ return login; };
		virtual const QString &get_version()    const{ return version; };
		virtual const QString &get_percent()    const{ return percent; };
		virtual const QString &get_memory()     const{ return memory; };
		virtual uint           get_sex()        const{ return sex; };
		virtual const QString &get_auto_answer()const{ return auto_answer; };
		virtual const QString &get_topic()      const{ return topic; };
		virtual uint           get_mode()       const{ return mode; };
		virtual bool           get_activity()   const{ return activity; };
		virtual const QPixmap &get_avatar()     const{ return avatar; };
		virtual uint           get_xml_protocol()const{ return xml_protocol; };    
        virtual       QVariant  get_property(const QString &key ){ return property.value(key); };
        virtual const QHash<QString,QVariant> &get_properties(){ return property; };
		virtual QPixmap        avatarToPixmap() const{ return avatar; };

    // ���������� ��� ���������� ������������...
        virtual QString get_type() const{ return tr("USER"); };

    // ���������� ��������� �� ��������� ������(dManager).
		virtual dManager *get_manager()        const{ return manager; };
            
    // ����������� � ����������.
		dUser( dManager * _manager, const QHostAddress &_ip, const QString &_name);
		virtual ~dUser();

    // ������������ �������� ���������, ��� ������ qUser �����,
    // ����� � ��� ����� ����� � Ip.
		int operator== (dUser &usr); 

    // ������� Info � Echo - ������� ��� ������������.
    // � �������� ��������� ���������� ��������� �� ������ ����������.
		virtual void send_info_request( dPUser _from ){};
		virtual void send_echo( dPUser _from ){};
    // ������� ������ �� �������� ��������(�������) �� ������������.
		virtual void send_image_request( dPUser _from ){};
    // ����� �� ������ ��������, �������� ������� ������.
		virtual void send_image_answer( const QString &_id, dPUser _from ){};
    // ������� Info � Echo - ������ ��� ������������.
    // � �������� ��������� ���������� ��������� �� ������ ����������.
		virtual void send_info_answer( dPUser _from ){};
		virtual void send_echo_answer( dPUser _from ){};
    // ������� ��������� � ����-�������.
		virtual void send_auto_answer( dPUser _from ){};
    // ������� ���������(������) ������������.
    // � �������� ��������� ���������� ��������� �� ������ �����������
    // � ����� ���������.
		virtual void send_msg( const QString & msg, dPUser _from, bool html = false ){};
    // ������� ��������� ������������ � �����.
		virtual void send_msg_channel( const QString & msg, dPUser _from ){};
		virtual void send_msg_channel_me(const QString &_msg, dPUser _from ){};	
    // ������� �������� ������ ������������.
		virtual void send_msg_beep( dPUser _from ){};
    // ������� "��������" ���������.
		virtual void send_msg_mass( const QString & msg, dPUser _from, bool html = false ){};
    // �������� � ������� ������.
		virtual void send_current_topic( const QString &_topic ){};
    // ����� ������.
		virtual void send_change_topic( const QString &_topic ){};
    // ������� ��������� � ��������� ����� ������������.
        virtual void send_rename( const QString &_oldname , dPUser _from ){};

    //***************************************************************
    // XML ���������...
    // ������� Xml - ���������.
        virtual void send_xml( QDomDocument &_msgXmlDocument, dPUser _from ){};
    // Xml ping ���������� ���� ������ ������������ �� ��������� ������������
    // ��� ��� ���� ��� ���������.
        virtual void send_xml_ping( dPUser _from ){};
        
    //***************************************************************
    // ���� ���������.
        enum dMsgType
        {
            echo_answer         = 1,        
            info_answer         = 2,        
            info_request        = 4,
            echo_request        = 8,
            change_activity     = 16,
            change_mode         = 32,
            msg_personal        = 64,
            msg_channel         = 128,
            msg_beep            = 256,
            msg_mass            = 512,
            change_topic        = 1024,
            current_topic       = 2048,
            msg_channel_me      = 4096,
            msg_enter           = 8192,
            msg_exit            = 16384,
            msg_rename          = 32768,
            msg_beep_answer     = 65536,       
            msg_auto_answer     = 131072,       
            image_request       = 262144,
            image_answer        = 524288,
            msg_xml             = 1048576,
            msg_all             = 0xFFFFFFFF       
        };
    
    protected:
    //***************************************************************
    //  �������, ������� ���������� ��� ��������� ������������
    // ���������.
        
    // ��������� �����, ������� ���������� ��� ��������� ���� �������,
    // ������, � ��������� ���������� _event_type.
		virtual void event( dMsgType _event_type, dPUser _from, const QString *_msg = NULL){};

	// ����� ���� ������� ������, ����������� ���� �������.
    // ������� ����������, ��� ��������� info-�������.
		virtual void event_info_request( dPUser _from ){};
    // ������� ����������, ��� ��������� echo-�������.
		virtual void event_echo_request( dPUser _from ){};
    // ������� ���������� ��� ����� ����������.
		virtual void event_change_activity( dPUser _from ){};
    // ������� ���������� ��� ����� ������.
		virtual void event_change_mode( dPUser _from ){};
    // ������� ����������, ��� ����� ������ ���� ������������ � ���.
		virtual void event_msg_enter( dPUser _from ){};
    // ������� ����������, ��� ������ ������������ �� ����.
		virtual void event_msg_exit( dPUser _from ){};
    // ������� ����������, ��� ������ ������������ �� ����.
		virtual void event_msg_rename( dPUser _from ){};
    // ������� ����������, ����� �������� ������ ���������.
		virtual void event_msg_personal( dPUser _from, const QString & _msg, bool html = false){};
    // ������� ����������, ����� �������� ��������� � �����.
		virtual void event_msg_channel( dPUser _from, const QString & _msg){};
    // ������� ����������, ����� �������� �������� ������.
		virtual void event_msg_beep( dPUser _from ){};
    // ������� ����������, ��� ��������� ��������� ���������.
		virtual void event_msg_mass( dPUser _from, const QString & _msg, bool html = false){};
    // ������� ����������, ��� ��������� ����-������.
		virtual void event_msg_auto_answer( dPUser _from, const QString & _msg){};
    // ������� ����������, ��� ����� ������.
		virtual void event_change_topic( const QString &_topic ){};
    // ������� ����������, ����� �������� ��������� � ������� �������.
		virtual void event_current_topic( const QString &_topic){};
    // ������� ����������, ����� �������� ��������� � ����� � �������� 
    // ������� (Me-���������).event_change_topic
		virtual void event_msg_channel_me( dPUser _from, const QString & msg){};
    // ������� ����������, ����� �������� ������ ��������(�������).
		virtual void event_image_request( dPUser _from, const QString &id ){};
    // ������� ����������, ����� ��������(������) �� ������������.
		virtual void event_image_answer( dPUser _from ){};
    // ������� ����������, Xml - ���������.
        virtual void event_xml( dPUser _from, const QDomElement &messageElement ){};

};

Q_DECLARE_METATYPE(dPUser)

#endif	//DUSER_H

