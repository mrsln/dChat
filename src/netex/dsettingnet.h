#ifndef DSETTINGNET_H
#define DSETTINGNET_H

#include <QtGui>
#include <QtXml>
#include "../dsetting.h"

class dChatApplication;
class dService;
class dAbstractIPListEx;

class dSettingNet: public dSetting
{
    Q_OBJECT
    private:
        dChatApplication *application;
    // ������ �������� ����� �����.
        QSpinBox *portSpinBox;
    // ������ �������� ����� ����� �� ��������� ������������ � ������.
        QSpinBox *timeoutSpinBox;
    // ������ �������� �������� ��������� �������� ���-��������.
        QSpinBox *refreshSpinBox;
    // ������ �������� �������� ���������� ���������� � ������������.
        QSpinBox *refreshInfoSpinBox;
    // ������ �������� ����������������� �����.
        QLineEdit *broadcastIPLineEdit;  
    // ��������� �� ������ ����.
        dService * dchat;     
    // ������ IP ������� ��������.
        QList<dAbstractIPListEx*> ip_lists;
    // ������ �� �������.
        QListWidget*ipList;
    // ������ � ��������.
        QLineEdit *IP1LineEdit;
        QLineEdit *IP2LineEdit;
        QLineEdit *IP3LineEdit;
    // ���� �������������� ���������.
        QWidget * rangeIPWindow;
    // ���� �������������� ���������.
        QWidget * singleIPWindow;
    // ������ � ������� ������� ����������.
        QComboBox *networkModuleComboBox;
    public:
   
        dSettingNet( dSetting *_parent );
        ~dSettingNet();

        virtual QWidget *createWidget();
    
    public slots:
    // ��� ������� ������ "���������".
        void clickedUseButton( bool _checked );  
    // ��� ����� ����������.
        void timeoutChanged( int _value );
        void refreshChanged( int _value );
        void refreshInfoChanged( int _value );
    // ��� ������� ������� ���������� ��������� �������.
        void clickedAddRangeIPWindowButton();
        void clickedAddRangeIPButton();
    // ��� ������� ������� ���������� ������.
        void clickedAddSingleIPWindowButton();
        void clickedAddSingleIPButton();
    // ��� ������� ������� �������� ������.
        void clickedDeleteIPButton();
    // ��� ������ �������� ���� ��������� ������� ���������.
        void sendTypeActivated( int _index );
};

#endif // DSETTINGNET_H

