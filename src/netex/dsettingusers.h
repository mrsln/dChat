#ifndef DSETTINGUSERS_H
#define DSETTINGUSERS_H

#include <QtGui>
#include <QtXml>

#include "../dsetting.h"
#include "../net/duser.h"

class dChatApplication;

class dSettingUsers: public dSetting
{
    Q_OBJECT
    private:
        dChatApplication *application;
    
    // ������� � ������ �������������.
        QTableWidget *typeTable;
    // ������� � ��� ���������� ��������������.
        QTableWidget *userTable;
    // ������ ���������� �� ����������� ��������� �������������.    
        QList<dPUser> user_list;
    public:
    
        dSettingUsers( dSetting *_parent );
//        ~dSettingUsers();
        virtual QWidget *createWidget();
    
    public slots:
    // ��� ������� ������ ���������� ������������.
        void clickedAddButton ( bool checked );
    // ��� ������� ������ �������� ������������.
        void clickedDeleteButton ( bool checked );
    // ��� ������� ������� �� ������������ � �������.
        void userDoubleClicked ( const QModelIndex & index );

};

#endif // DSETTINGUSERS_H

