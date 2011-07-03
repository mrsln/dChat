#ifndef DREMOTEUSER_H
#define DREMOTEUSER_H

#include "dabstractremoteusercreator.h"

#include "../netex/duserex.h"

class dService;

class dRemoteUser: public dUserEx
{
	friend class dService;
	friend class dRemoteUserCreator;
	
	private:
        
        QDateTime last_uptime;

    // ID ��������.
        int timerCheckID;
        int timerInfoSendID;
    // �������� �����.
        int interval_ping;
        
        void send_xml_msg( const QString & _msg, dPUser _from, bool _html = true, bool mass = false );
	protected:
		dService * service;		// ��������� �� ������ � ������� ����� ������������.

		dRemoteUser(dService * _service, const QHostAddress &_ip, const QString &_name );
		~dRemoteUser();
    
    // ������� ������ � ������� �� ��� ������������. ��� �������������
    // ���� �����, ���������� �� ������������ � ����.
        virtual void timerEvent(QTimerEvent *event);

    // ��������� ����� ���������� ���������� � ������������.
 		virtual void uptime();
 			
    // ������� ����� ������� ����� ����� ������� ������������
    // � ������ ���������� �� ������.
    // ������������ ������ 1 ��� � ����������� dService, �����
    // ����� ������� ���� ������������� ������������� �����
    // �������.        
        virtual void deleteRemoteUser(dService * srv);
	public:
    // ���������� ��� ���������� ������������...
        virtual QString get_type() const{ return tr("REMOTE_USER"); };

    // ���������� �������
    // ����������� �������� �������� ���-��������.
		virtual void send_echo( dPUser _from );
		virtual void send_info_request( dPUser _from );
    // ����������� �������� �������� ���-�������.
		virtual void send_info_answer( dPUser _from );
		virtual void send_echo_answer( dPUser _from );
    // ������� ��������� � ����-�������.
		virtual void send_auto_answer( dPUser _from );
    // ������� ���������(������) ������������.
		virtual void send_msg( const QString & _msg, dPUser _from, bool html = false);
    // ������� "��������" ���������.
		virtual void send_msg_mass( const QString & _msg, dPUser _from , bool html = false);
    // ������� ������ �� �������� ��������(�������) �� ������������.
		virtual void send_image_request( dPUser _from );
    // ������� ��. ����� �� ������������(���� �������� ������, �� ��������� 
    // ���������� �� ����� ��. ������������).
		virtual void send_msg_beep( dPUser _from  );
    // �������� � ������� ������.
		virtual void send_current_topic( const QString &_topic );
    // ����� ������.
		virtual void send_change_topic( const QString &_topic );		
    // ����� �� ������ ��������, �������� ������� ������.
		virtual void send_image_answer( const QString &_id, dPUser _from );
    // ������� ��������� ������������ � �����.
		virtual void send_msg_channel( const QString & msg, dPUser _from );
		virtual void send_msg_channel_me(const QString &_msg, dPUser _from );
    // ������� ��������� � ��������� ����� ������������.
        virtual void send_rename( const QString &_oldname , dPUser _from );

    //***************************************************************
    // XML ���������...
    // ������� Xml - ���������.
        virtual void send_xml( QDomDocument &_msgXmlDocument, dPUser _from );
    // Xml ping ���������� ���� ������ ������������ �� ��������� ������������
    // ��� ��� ���� ��� ���������.
        virtual void send_xml_ping( dPUser _from );

    // �����. ��������� �� ������ ���������� ������������ .
        const dService *get_service() const { return service; };
};

class dRemoteUserCreator : public dAbstractRemoteUserCreator
{
    public:
        dRemoteUserCreator(){};
        virtual dPUser create( dService * _service, const QHostAddress &_ip, const QString &_name ) const
        {
                dRemoteUser * remoteUser = new dRemoteUser(_service,_ip,_name);
                return remoteUser->get_pointer();
        };
};

#endif	//DREMOTEUSER_H
