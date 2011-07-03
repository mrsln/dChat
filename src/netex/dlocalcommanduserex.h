#ifndef DLOCALCOMMANDUSEREX_H
#define DLOCALCOMMANDUSEREX_H

#include <QtGui>

#include "dlocaluserex.h"
#include "dabstractusercreator.h"

#include "../dsetting.h"

#define COMMAND_USER_KEY "COMMAND_USER"

class dLocalCommandUserEx: public dLocalUserEx
{
    Q_OBJECT
    private:
        QHash<QProcess*,dPUser> processHash;
        
        QString command;
	public:
        const QString &get_command() const { return command; };
        void set_command(const QString &_command){ command = _command; };
	
		dLocalCommandUserEx(dManagerEx * _manager, const QString &_name,  QDomElement &_parentXmlElement, dSetting *_parentSetting = 0);
		~dLocalCommandUserEx();
    
	//	virtual QString get_type() const{ return tr(STD_USER_KEY); };
		
    ///////////////////// ����������� �������. /////////////////////
    // ������� ����������, ����� �������� ������ ���������.
		virtual void event_msg_personal( dPUser _from, const QString & _msg, bool html = false);
		
    public slots:
    // ��������� ������ �� ���������� ��������.
        void readyReadStandardOutput();
    // ������� ��������.
        void finishedProcess ( int _exitCode );
};

class dSettingCommandLocalUserEx: public dSetting
{
    Q_OBJECT
    private:
        dLocalCommandUserEx *localCommandUserEx;
    public:
        dSettingCommandLocalUserEx( dSetting *_parent, 
                                    dLocalCommandUserEx *_localCommandUserEx);
        virtual QWidget *createWidget();

    public slots:
        void commandEdited( const QString& _inemName);        
};

class dLocalCommandUserCreator : public dAbstractUserCreator
{
    public:
//        dLocalCommandUserCreator(){};
        virtual dPUser create( dManagerEx * _manager, const QString &_name, QDomElement &_parentXmlElement, dSetting *_parentSetting = 0)
        {  
            dUser *usr = new dLocalCommandUserEx( _manager, _name, _parentXmlElement, _parentSetting ); 
            return usr->get_pointer();            
        };
        QString getKey() const { return QString(COMMAND_USER_KEY); };
        QString getTitle() const { return QString("��������� �����������."); };
        QString getDescription() const { return QString("��������� ������� ������� ��� ����������� ���������, ������� ������ �� ������������ ������."); };
};

#endif	//DLOCALCOMMANDUSEREX_H
