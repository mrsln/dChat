#ifndef DLOCALAUTOUSEREX_H
#define DLOCALAUTOUSEREX_H

#include <QtGui>

#include "dlocaluserex.h"
#include "dabstractusercreator.h"

#define AUTO_USER_KEY "AUTO_USER"

class dLocalAutoUserEx: public dLocalUserEx
{
	public:
		dLocalAutoUserEx(dManagerEx * _manager, const QString &_name,  QDomElement &_parentXmlElement, dSetting *_parentSetting = 0);
		~dLocalAutoUserEx();

	//	virtual QString get_type() const{ return tr(AUTO_USER_KEY); };

    ///////////////////// ����������� �������. /////////////////////
    // ������� ����������, ����� �������� �������� ������.
		virtual void event_msg_beep( dPUser _from );
    // ������� ����������, ����� �������� ������ ���������.
		virtual void event_msg_personal( dPUser _from, const QString & _msg, bool html = false);
    // ������� ����������, ��� ��������� ��������� ���������.
};

class dLocalAutoUserCreator : public dAbstractUserCreator
{
    public:
        dLocalAutoUserCreator(){};
        virtual dPUser create( dManagerEx * _manager, const QString &_name, QDomElement &_parentXmlElement, dSetting *_parentSetting = 0)
        {  
            dUser *usr = new dLocalAutoUserEx( _manager, _name, _parentXmlElement, _parentSetting );
            return usr->get_pointer();
        };
        QString getKey() const { return QString(AUTO_USER_KEY); };
        QString getTitle() const { return QString("������� ����-��������."); };
        QString getDescription() const { return QString("�������� ������� ����-����� � ���� �������� ���������."); };
};


#endif	//DLOCALAUTOUSEREX_H
