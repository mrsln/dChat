#ifndef DLOCALUSEREX_H
#define DLOCALUSEREX_H

#include <QtGui>

#include "../net/dlocaluser.h"

class dSettingLocalUser;
class dSetting;
class dChatApplication;
class dManagerEx;

class dLocalUserEx: public dLocalUser
{
    Q_OBJECT
    private:
    // ��������� ����� ������������.
        QAction *userMenuAct;
        QString user_type;
    protected:
        dSettingLocalUser *setting;     // �������� ��������� ������������.
        dChatApplication *application;  // ��������� �� ����� ����������.

    // ����������� ��-�� ���������� �������� ���������� ������
    // ����������� ���-������.
		virtual void event_echo_request( dPUser _from );
    // ����������� Info-������.
		virtual void event_info_request( dPUser _from );
        
	public:
		dLocalUserEx(   dManagerEx * _manager, 
                        const QString &_name,
                        const QString &_user_type, 
                        QDomElement &_parentXmlElement, 
                        dSetting *_parentSetting = 0);
		~dLocalUserEx();

    // ������ ������������� � ���������� ��� ������������.
        virtual QString get_type() const{ return user_type; };
        virtual void set_type(QString &_user_type) { user_type = _user_type; };
    // ���������� ����� ��������� �������� ������������.
        virtual bool set_main_user();
    // ���������� ��������� ������ ��������� ������� ������������.
		virtual bool set_name(const QString &_name);
		virtual void set_avatar(const QPixmap &_avatar);
    
    public slots:
    // ���������� ��� ����� ��. ������������ �� ����.
        void setMainUserTriggered( bool _checked );
};
#endif	//DLOCALUSEREX_H
