#ifndef DSETTINGFRIENDS_H
#define DSETTINGFRIENDS_H

#include <QtGui>
#include "../dsetting.h"

class dFriend;
class dFriendsWindow;

class dSettingFriends: public dSetting
{
    Q_OBJECT
    private:
    // ��������� �� ������ ������.
        QList<dFriend> *friends;
    // ������� �� ����� ��������.
        QTableWidget *friendsTable;
    // ����. �� ���� ������.
        dFriendsWindow *friendsWindow;
    public:
        dSettingFriends( const QString &_key, dSetting *_parent, dFriendsWindow *_friendsWindow );
        ~dSettingFriends();

        virtual QWidget *createWidget();
    
    public slots:
        // ���������� ��� ������� ������ �������� �����....
        void clickedDeleteButton();
};

#endif // DSETTINGFRIENDS_H

