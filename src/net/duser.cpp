#include <QtGui>

#include "duser.h"
#include "dmanager.h"

dUser::dUser( dManager * _manager, const QHostAddress &_ip, const QString &_name ):
		QObject(_manager),
		manager(_manager),
		name(_name),
		ip(_ip)
{ 
	if( !get_manager()->addUser(this) )
	{
        qDebug("Error: user already exists.");
        throw(int(0));
    }
    set_xml_protocol(0);        // �� ��������� �������� ��������.
};

dUser::~dUser()
{
	// ������ ������������ �� ������.
	get_manager()->deleteUser(this);
//    qDebug() << "+++++++++++++++++++++++++++++++++++++++";	
};

int dUser::operator== (dUser & usr)
{
	if( name == usr.name && ip == usr.ip )
		return 1;
	return 0;
}
// ���������� ��������������� �������� �� ������� ������.
dPUser dUser::get_pointer()
{ 
    return dPUser(get_manager(),this); 
};
// ���������� �������� ������������� ��������� ����� ������������, ��� ��� ��������...
dPUser dUser::get_main_user()const
{ 
    return manager->get_main_user(); 
};

//*****************************************************************
//*****************************************************************
dPUser::dPUser( dManager *_manager, dUser *_user ):
        manager(_manager),
        user(_user){};

dPUser::dPUser( dUser *_user )
{
    if( _user != NULL )
    {
        user = _user;
        manager = _user->get_manager();
    }
};

dPUser::dPUser( const dPUser &_user )
{
    user = _user.user;
    manager = _user.manager;
};

dPUser &dPUser::operator= ( const dPUser &_user )
{
    user = _user.user;
    manager = _user.manager;
    return *this;
}

dUser*dPUser::operator->()
{   
    if( user == NULL || manager == NULL )
    {
        if( QMessageBox::critical(0, QObject::tr("Pointer ERROR!"),
                                QObject::tr("������� ������������ ������ ���������.\n ���� �� ������� ���������� ������ � ���������� ������� Ignore, �� ��� ����� ��������� � � �������?"),QMessageBox::Abort,QMessageBox::Ignore,0) == QMessageBox::Abort )
            QApplication::exit(-1);
    }
    if( !manager->users.contains(user) )
    {
        if (QMessageBox::critical(0, QObject::tr("Pointer ERROR!"),
                                QObject::tr("������� ������������ �������������� ���������.\n ���� �� ������� ���������� ������ � ���������� ������� Ignore, �� ��� ����� ��������� � � �������?"),QMessageBox::Abort,QMessageBox::Ignore,0) == QMessageBox::Abort )
            QApplication::exit(-1);
    }
            
    return user; 
};

dPUser::operator dUser*()
{
/*
    if( user == NULL || manager == NULL )
    {
        QMessageBox::critical(0, QObject::tr("Pointer ERROR!"),
                            QObject::tr("������� ��������� �� ������ ���������."),QMessageBox::Ok,0,0);
        throw(int(-1));
    }
    if( !manager->users.contains(user) )
    {
        QMessageBox::critical(0, QObject::tr("Pointer ERROR!"),
                                QObject::tr("������� ��������� �� ������������ ���������."),QMessageBox::Ok,0,0);
        throw(int(-1));
    }
 */            
    return user;
}

dPUser dPUser::main_user( dManager *_manager )
{
    return _manager->get_main_user();
}

/*
dPUser dPUser::main_user()
{
    return manager->get_main_user();
}
*/

