#ifndef DFRIENDSWINDOW_H
#define DFRIENDSWINDOW_H

#include <QtGui>

#include "../dwindow.h"


// ��������� ����������� �����.
class dFriend
{
    public:
        bool operator== (dFriend &_friend);
        QString name;
        QString ip;
};
#include "dfriendview.h"        // <<<<<<<<<<<------- DFRIENDVIEW_H

class dChatApplication;
class dSetting;

class dFriendsWindow : public dWindow
{   
    Q_OBJECT
    private:
        dWindowFrame *window;
        dChatApplication *application;
    // ��������� �� ���������.
        dSetting *settingFriend;
    // ��������� �� ������ ������ ������.
        dFriendView<QListView> *friensList;
    // C����� ������.
        QList<dFriend> friends;
        
    public:
        dFriendsWindow( dWindowFrame *_window, QObject *_parent = 0);
        ~dFriendsWindow();
        
    // ���������� ������ �� ������ ������.
        QList<dFriend> &get_friends(){ return friends; };
    // ��������� � ������ ������.
        bool addFriend( const QString &_name, const QString &_ip );
    // �������� ������.
        bool deleteFriend( const QString &_name, const QString &_ip );
        void refreshFriendsList();
    
    public slots:
    // ��������� � ������ ������.
        void addFriendNameAndIP();
        void addFriendName();
        void addFriendIP();
    // �������� ������.
        void deleteFriend();
    // ��� ������� ������� ���� � ����� �������������.
        void itemDoubleClicked ( const QModelIndex & index );
    // ������������� ����� ���������.
  //      void setTopic( const QString &_topic );

};

#endif // DFRIENDSWINDOW_H


