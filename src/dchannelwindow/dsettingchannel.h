#ifndef DSETTINGCHANNEL_H
#define DSETTINGCHANNEL_H

#include <QtGui>
#include <QtXml>
#include "../dsetting.h"

class dWindowFrame;
class dChannelWindow;

class dSettingChannel: public dSetting
{
    Q_OBJECT
    private:
        dChannelWindow *channelWindow;
    // ����� � �������� ���� ��������� ���������.
        QComboBox *viewTypeComboBox;
        
        QSpinBox *messageMaxSpinBox;
        QSpinBox *nameMaxSpinBox;
    public:
        bool isTableView();    
        dSettingChannel( const QString &_key, dSetting *_parent, dChannelWindow *_channelWindow );
        ~dSettingChannel();

        virtual QWidget *createWidget();
    
    public slots:
        void viewTypeActivated( int _index );
    // ��� ��������� ���������� �����.
        void messageMaxChanged( int _value );
    // ��� ��������� ���������� �������� � �����.
        void nameMaxChanged( int _value );
};

#endif // DSETTINGCHANNEL_H

