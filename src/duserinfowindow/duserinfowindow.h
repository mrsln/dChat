#ifndef DUSERINFOWINDOW_H
#define DUSERINFOWINDOW_H

#include <QtGui>

class dPUser;
class dChatApplication;

class dUserInfoWindow: public QWidget
{   
 //   Q_OBJECT
    public:
    // �������� �� ������ ����������.
    //    dChatApplication *application;

    // ���� � �������� ���� ������.
    //    QTextEdit * auto_answer;        

        dUserInfoWindow( dPUser usr,QWidget *_parent = 0);
//        ~dMessageEditor();
    
    protected:
    // ����������� ������� �� ��������.
        virtual void closeEvent ( QCloseEvent * _event );
};
#endif // DUSERINFOWINDOW_H
