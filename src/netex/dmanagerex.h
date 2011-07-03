//*********************************************************************
//  ���� �������� ����� dManagerEx, �������������� ����� ���������� ������ 
// dManager. ��������� ����������� ���������� �������� ������ � �����������
// ��������. � ����� � ���� � ����� dManager, ���� ��������� ��������� 
// ����������� ������� ��� ���������� ����������. �������� ������ dManager 
// ����� �������� � ����� dmanager.h
//  � �������� ���� ������������ ������� ��������� �� ������ "����������",
// � ���������� ��� �������� ���������� � ������ ����(widget-�) � ���������.

#ifndef DMANAGEREX_H
#define DMANAGEREX_H

#include <QtGui>

#include "../net/dmanager.h"

class dManagerEx : public dManager
{
    // ������� ������ ������.
	friend dUser::~dUser();
    friend dUser::dUser( dManager * _manager, 
                         const QHostAddress &_ip, 
                         const QString &_name );

    Q_OBJECT
    private:
        QStandardItemModel *model;
        QItemSelectionModel *selectionModel;

     //   dChatApplication * application;
    
    protected:
    // ������ ���������(�������) ������������ � ������(�� ������).
    // ������������ � ����� � ���������� ������������.
		virtual dUser *addUser(dUser * usr);
		virtual void deleteUser(dUser * usr);
    
    public:
    // ����������� � ����������.
        dManagerEx( dChatApplication * _application );
        ~dManagerEx();

    // ���������� ������������ ������� �������� ������� � ������.
        dPUser getCurrentUserToModel(/* QModelIndex &_index */);

    // ���������� ������ ������������� ������� �������� � ������.
        QList<dPUser> getSelectedUserToModel();
        		    
    // ���������� ��������� �� ������ ������ � �� 
    // ������ ��������� ������    
        virtual QStandardItemModel *get_model() const{ return model; };
        virtual QItemSelectionModel *get_selectionModel() const{ return selectionModel; };
        
    ///////////////////// ����������� �������. /////////////////////    
    // ����������� ������� �� dManager, ����� ����� ����������� 
    // ������� �������.
    // ������� ���������� ��� ����� ����������.
		virtual void event_change_activity( dPUser _from )
                { emit signal_change_activity(_from); };
    // ������� ���������� ��� ����� ������.
		virtual void event_change_mode( dPUser _from )
                { emit signal_change_mode(_from); };
    // ������� ����������, ��� ����� ������ ���� ������������ � ���.
		virtual void event_msg_enter( dPUser _from )
                { emit signal_msg_enter(_from); };
    // ������� ����������, ��� ������ ������������ �� ����.
		virtual void event_msg_exit( dPUser _from )
                { emit signal_msg_exit(_from); };
    // ������� ����������, ��� ������ ������������ �� ����.
		virtual void event_msg_rename( dPUser _from, const QString & _oldname )
                { emit signal_msg_rename(_from,_oldname); };
    // ������� ����������, ����� �������� ������ ���������.
		virtual void event_msg_personal( dPUser _from, dPUser _to ,const QString & _msg, bool _html = false)
                { emit signal_msg_personal(_from,_to,_msg,_html); };
    // ������� ����������, ����� �������� ��������� � �����.
		virtual void event_msg_channel( dPUser _from, const QString & _msg)
                { emit signal_msg_channel(_from,_msg); };
    // ������� ����������, ����� �������� �������� ������.
		virtual void event_msg_beep( dPUser _from, dPUser _to )
                { emit signal_msg_beep(_from,_to); };
    // ������� ����������, ��� ��������� ��������� ���������.
		virtual void event_msg_mass( dPUser _from, dPUser _to, const QString & _msg, bool _html = false )
                {  emit signal_msg_mass(_from,_to,_msg,_html);  };
    // ������� ����������, ��� ����� ������.
		virtual void event_change_topic( const QString &_topic )
                { emit signal_change_topic(_topic); };
    // ������� ����������, ����� �������� ��������� � ������� �������.
		virtual void event_current_topic( const QString &_topic)
                { emit signal_current_topic(_topic); };
    // ������� ����������, ����� �������� ��������� � ����� � �������� 
    // ������� (Me-���������).event_change_topic
		virtual void event_msg_channel_me( dPUser _from, const QString &_msg)
                { emit signal_msg_channel_me(_from,_msg); };
    // ������� ����������, ��� ��������� ����-������.
		virtual void event_msg_auto_answer( dPUser _from, dPUser _to, const QString & _msg)
                { emit signal_msg_auto_answer(_from,_to,_msg); };
    // ������� ���������� ,����� �������� Xml - ���������.
		virtual void event_xml( dPUser _from, dPUser _to, const QString & _msg)
                { emit signal_xml(_from,_to,_msg); };
        
    public slots:
    // ����, ���������� ��� ����� ����������� ������ � ������ �������������.
    // ������� ������ �������� ����� �������, ���� �������.
    // void userListItemChanged( QListWidgetItem * current, QListWidgetItem * previous);
    
    signals:
    // ������, �������� ��� ��������� ���������� �������������.
    // � ������ �������� ������ ������������.
        void signal_count_user_change( int _count );    
        
    // �������, ������� ���������� ���������������� ���������.
    // �����. ����.............
		void signal_change_activity( dPUser _from );
		void signal_change_mode( dPUser _from );
		void signal_msg_enter( dPUser _from );
		void signal_msg_exit( dPUser _from );
		void signal_msg_rename( dPUser _from, const QString & _oldname );
		void signal_msg_personal( dPUser _from, dPUser _to ,const QString & _msg, bool _html = false);
		void signal_msg_channel( dPUser _from, const QString & _msg);
		void signal_msg_beep( dPUser _from, dPUser _to );
		void signal_msg_mass( dPUser _from, dPUser _to ,const QString & _msg, bool _html = false);
		void signal_change_topic( const QString &_topic );
		void signal_current_topic( const QString &_topic);
		void signal_msg_channel_me( dPUser _from, const QString &_msg);
		void signal_msg_auto_answer( dPUser _from, dPUser _to, const QString & _msg);
		void signal_xml( dPUser _from, dPUser _to, const QString & _msg);
    
    // ������� ���������� ��� ���������� � �������� �����������.
        void signal_delete_user( dPUser _user );
        void signal_add_user( dPUser _user );

};
#endif	//DMANAGEREX_H
