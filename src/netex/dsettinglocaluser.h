#ifndef DSETTINGLOCALUSER_H
#define DSETTINGLOCALUSER_H

#include <QtGui>
#include <QtXml>
#include "../dsetting.h"

class dLocalUser;

class dSettingLocalUser: public dSetting
{
    Q_OBJECT
    private:
    // ������ ������ �����.
        QLineEdit *nameLineEdit;
    // �������� ���� ������.
        QTextEdit * auto_answerEdit;
    // ������ ������ ������.
        QLineEdit * loginLineEdit;
    // ����� � ��������
        QLabel *avatarLabel;
    // ������ �������� ����-������.
        QPushButton *avatarPushButton;
    // ��. ����.
        dLocalUser *user;
    // ����� � ����������� ����.
        QComboBox *sexComboBox;
    // CheckBox � ���������� ���������� ������.
        QCheckBox *passiveModeCheckBox;
//        dChatApplication *application;    
    public:
    
        dSettingLocalUser( QDomElement &_parentXmlElement, dSetting *_parent, dLocalUser *_usr);
//        ~dSettingUsers();
        virtual QWidget *createWidget();
    
    // ���������� true ���� ������������ ���������� � ��������� ������.
        bool hasPassiveMode(){ return toInt(tr("passive_mode"),tr("value"),0); };
    
    public slots:
    // ��� ������� ������ ������ �������.
        void clickedAvatarButton ( bool checked );
    // ��� ����� �����.        
        void nameEdited();
    // ��� ����� ������.        
        void loginEdited( const QString& _login);
    // ��� ����� ����-������
        void autoAnswerChanged();
    // ��� ����� ����.
        void sexActivated ( int index );
    // ��� ����� ������ �����������.
        void passiveModeChanged( int _state);
    
};

#endif // DSETTINGLOCALUSER_H

