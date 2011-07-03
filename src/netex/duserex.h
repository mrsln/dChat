//*********************************************************************
//  ���� �������� ����� dUserEx, �������������� ����� ���������� ������ 
// dUser. ��������� ����������� ���������� �������� ������ � �����������
// ��������. � ����� � ���� � ����� dUser, ���� ��������� ��������� 
// ����������� ������� ��� ���������� ����������. �������� ������ dUser 
// ����� �������� � ����� duser.h
// ��������� ���� ������� ��� �� � �������� dLocalUser � dRemoteUser, � ���
// ��� ������� ������� �����.

#ifndef DUSEREX_H
#define DUSEREX_H

#include <QtGui>
#include "../net/duser.h"

class dChatApplication;

class dUserEx : public dUser
{
//    Q_OBJECT
    private:
        dChatApplication *application;
    // ��������� ����� ����� � ������(� QListWidget), ������� ������� 
    // ���������� ����������.
        void addItemToList();
    // ��������� �� ������ ������ (�������).
        QAbstractItemModel *model;
    // ������������ ����� ����� ������� � ���� ������( � ������ ).
        QModelIndex find_index();
    // �������� ToolTip ��� ����������� ������������ � ������.
        void set_tool_tip( QModelIndex index );
    protected:
    // ���������� ��������� ����������� �������, ���� �������� ���������
    // ��� �� ������.

		virtual void set_avatar(const QPixmap &_avatar);
		virtual bool set_name(const QString &_name);
		virtual void set_host(const QString & _host);
		virtual void set_login(const QString &_login);
		virtual void set_version(const QString &_version);
        virtual void set_auto_answer(const QString & _auto_answer);
		virtual void set_sex(const uint &_sex);
		virtual void set_mode(const uint &_mode);
		virtual void set_activity(const bool &_activity);
		virtual void set_xml_protocol(uint _xml_protocol);   

    // ���������� �������...
//        virtual void event_msg_image( dUser *_from ){};        

    public:
		dUserEx( dManager * _manager, const QHostAddress &_ip, const QString &_name);
        virtual ~dUserEx();
            
};

#endif	//DUSEREX_H
