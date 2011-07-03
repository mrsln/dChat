#ifndef DLOCALUSER_H
#define DLOCALUSER_H

#include "../netex/duserex.h"

class dLocalUser: public dUserEx
{

	public:

    // ����� ������������� ���� (�� ���� ����� ������ �������),
    // ��������� "��������" ������������.
		virtual bool set_main_user();

        virtual void uptime(){};
    
    protected:    
        
    // ����� ������������� � ����������.
		dLocalUser(dManager * _manager, const QString &_name );
		virtual ~dLocalUser();

    // ����������� ���-������.
		virtual void event_echo_request( dPUser _from );
    // ����������� Info-������.
		virtual void event_info_request( dPUser _from );
    // ����������� �������, ���������� ��� ����� ������ ���� ������������ � ���.
		virtual void event_msg_enter( dPUser _from );
    // ����������� ������� ����������, ����� �������� ������ ��������(�������).
		virtual void event_image_request( dPUser _from, const QString &id );
    // ����������� ������� ����������, ����� �������� ������ ���������.
		virtual void event_msg_personal( dPUser _from, const QString &_msg, bool html = false);
    // ����������� ������� ����������, ��� ��������� ��������� ���������.
		virtual void event_msg_mass( dPUser _from, const QString & _msg, bool html = false);
    // ����������� ������� ���������� ,����� �������� Xml - ���������.
        virtual void event_xml( dPUser _from, const QDomElement &messageElement );
    
    public:
    // ���������� ��� ���������� ������������...
        virtual QString get_type() const{ return tr("LOCAL_USER"); };
        
    //  ������������� ������... � ������ dUser ��� ��������� � ������� protected,
    // �� ���� �������. ��� �� �� ���������� � ������ public.
		virtual bool set_name(const QString &_name){ dUserEx::set_name(_name); };
		virtual void set_host(const QString & _host){ dUserEx::set_host(_host); };
		virtual void set_login(const QString &_login){ dUserEx::set_login(_login); };
		virtual void set_version(const QString &_version){ dUserEx::set_version(_version); };
		virtual void set_percent(const QString &_percent){ dUserEx::set_percent(_percent); };
		virtual void set_memory(const QString &_memory){ dUserEx::set_memory(_memory); };
		virtual void set_sex(const uint &_sex){ dUserEx::set_sex(_sex); };
		virtual void set_auto_answer(const QString &_auto_answer){ dUserEx::set_auto_answer(_auto_answer); };
		virtual void set_topic(const QString &_topic){ dUserEx::set_topic(_topic); };
		virtual void set_mode(const uint &_mode){ dUserEx::set_mode(_mode); };
		virtual void set_activity(const bool &_activity){ dUserEx::set_activity(_activity); };
		virtual void set_avatar(const QPixmap &_avatar){ dUserEx::set_avatar(_avatar); };

    // ��������� ������� �� dUser.
    // ������� "��������" ���������.
		virtual void send_msg_mass( const QString & msg, dPUser _from, bool html = false );
    // ������� ���������(������) ������������.
    // � �������� ��������� ���������� ��������� �� ������ �����������
    // � ����� ���������.
		virtual void send_msg( const QString & msg, dPUser _from , bool html = false);
    // ������� ��������� ������������ � �����.
		virtual void send_msg_beep( dPUser _from );
    // ������� ��������� � ����-�������.
		virtual void send_auto_answer( dPUser _from );
		
};

#endif	//DLOCALUSER_H
