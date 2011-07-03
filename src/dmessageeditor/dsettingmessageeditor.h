#ifndef DSETTINGMESSAGEEDITOR_H
#define DSETTINGMESSAGEEDITOR_H

#include <QtGui>
#include <QtXml>
#include "../dsetting.h"

class dSettingMessageEditor: public dSetting
{
    Q_OBJECT
    private:
    // �����������........
        QRadioButton *radio1;
        QRadioButton *radio2;
        QRadioButton *radio3;
        uint quoting;
    //-------
    
    public:
        dSettingMessageEditor( const QString &_key, dSetting *_parent );
        ~dSettingMessageEditor();

        virtual QWidget *createWidget();
        uint getQuoting(){ return quoting; };
        
    public slots:
    //��� ������ ������ �����������...
        void quotingToggled ( bool _on ); 
};

#endif // DSETTINGMESSAGEEDITOR_H

