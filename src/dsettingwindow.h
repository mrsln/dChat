#ifndef DSETTINGWINDOW_H
#define DSETTINGWINDOW_H

#include <QtGui>
#include <QtXml>
#include "dsetting.h"

class dWindowFrame;

class dSettingWindow: public dSetting
{
    Q_OBJECT
    private:
    // ������ ����� �����.
        QPushButton *skinPushButton;

    // ��� �����.
        QString styleName;
    // ���� �����.
        QString skinFileName;
        
    // �������� �������� ���
        QDomElement positionElement;
        QDomElement sizeElement;
        QDomElement opacityElement;
        QDomElement skinElement;
        
    // ��������� �� ����.     
        dWindowFrame *window;
    public:
    
        dSettingWindow( const QString &_key, dSetting *_parent, dWindowFrame *_window );
        ~dSettingWindow();
        virtual void saveSetting();
        virtual QWidget *createWidget();
    
    public slots:
    // ���������� ��� ��������� ������������.
        void opacityValueChanged ( int i );
    // ��� ������� ������ ����� �����.
        void clickedSkinButton ( bool checked );
    // ������������ ��. �����.
        void stateChanged ( int state );
};

#endif // DSETTINGWINDOW_H

