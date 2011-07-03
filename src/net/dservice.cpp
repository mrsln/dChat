#include <QFile>
#include <QStringList>
#include <QDateTime>

#include "dservice.h"
#include "duser.h"
#include "dremoteuser.h"
#include "dmanager.h"

#include "../dudpsocket/dudpsocket.h"

//***************************************************************
// ����� �������������.
dService::dService(	dManager *_manager,
                    const uint _port,
                    uint _useNetworkPath,
                    const QHostAddress &_local_ip):
		QObject(_manager),
		log_dev(NULL),
		local_ip(_local_ip),
	    port(_port),
	    useNetworkPath(_useNetworkPath),
		manager(_manager)
{
    bool res;
    absRtUsrCreator = new dRemoteUserCreator();

    if( _local_ip == QHostAddress())
        local_ip = manager->get_localAddress();
    localhost_ip.setAddress ( tr("127.0.0.1"));

	if( useNetworkPath == 0 )
        connecting();
    else
        connectingPath();

        manager->addService(this);
    // ������� ������������ ��������� �������������.
}

dService::dService( dManager *_manager,
          dAbstractRemoteUserCreator *_absRtUsrCreator, 
          const uint _port,
          uint _useNetworkPath,
          const QHostAddress &_local_ip ):
		QObject(_manager),
		absRtUsrCreator(_absRtUsrCreator),
		useNetworkPath(_useNetworkPath),
		log_dev(NULL),
		local_ip(_local_ip),
	    port(_port),
		manager(_manager)
{

    // ���� ��������� �������, �� ������� ������������ ��������� �������������.
    if( !absRtUsrCreator )
        absRtUsrCreator = new dRemoteUserCreator();

    if( _local_ip == QHostAddress())
        local_ip = manager->get_localAddress();
    
    localhost_ip.setAddress( tr("127.0.0.1"));

	if( useNetworkPath == 0 )
        connecting();
    else
        connectingPath();

        manager->addService(this);
}

dService::dService(	dManager *_manager,
                    const QString &_local_ip_qstring,
                    const uint _port,
                    uint _useNetworkPath ):
		QObject(_manager),
		log_dev(NULL),
		useNetworkPath(_useNetworkPath),
	    port(_port),
		manager(_manager)
{
    absRtUsrCreator = new dRemoteUserCreator();
    
    local_ip.setAddress(_local_ip_qstring);
	manager->addService(this);
	
	if( useNetworkPath == 0 )
        connecting();
    else
        connectingPath();

        manager->addService(this);
}

/****** ��� ����. ���������� ��� ����������� ������ �� �����. ******/
void dService::dataReceived()
{
//    qDebug() << "parser Begin:" << udpSocket->error(); 
 //   qDebug() << "+" ;
    while ( udpSocket->hasPendingDatagrams() ) 
    {
  //      qDebug() << "!" ;
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());
        QHostAddress ip;
        quint16 senderPort;
    
        udpSocket->readDatagram(datagram.data(), datagram.size(),
                                &ip, &senderPort);
        if( manager->get_main_user() == true ) 
        {
            if( !(ip.isNull()) && !(local_ip == ip ) && !(localhost_ip == ip ))
                parser(ip,datagram);
        }
    }
//qDebug() << "-" ;
//    qDebug() << "parser END:"; 
}

void dService::dataReceivedPath()
{
    QByteArray datagram;
    QHostAddress ip;
    uint senderPort;
    
    while ( udpSocketPath->hasPendingDatagrams() > 0 ) 
    {
        udpSocketPath->readDatagram(datagram,&ip, &senderPort);
        if( manager->get_main_user() == true ) 
        {
            if( !(ip.isNull()) && !(local_ip == ip ) && !(localhost_ip == ip ))
                parser(ip,datagram);
        }
    }
}

/****** ��� �����, ��� - ���������� ******/
dService::~dService() 	
{
    // ������ ���� ��������� ������������� ����� �������.
    dUser *usr; 
    QList<dPUser> users = manager->get_users();
    foreach( dPUser usr, users)
        usr->deleteRemoteUser(this);
    
	manager->deleteService(this);	// ������ ���� ������ �� ������ ��������.
	offLog();						// ������� ���.
	if( useNetworkPath == 0 )
        delete udpSocket;
    else
    {
        delete udpSocketPath;
    }
    
}

void dService::setReadBufferSize( const uint size)
{
	udpSocket->setReadBufferSize(size);
}


//***************************************************************
//  ������� ���������� �����.
void dService::onLog( QIODevice * _log_dev, uint _log_mode)
{
    log_mode = _log_mode;
    log_dev = _log_dev;
    log.setDevice(log_dev);
}
bool dService::onLog( const char *_file_name_pchar, uint _log_mode)
{
    log_mode = _log_mode;
    QString _file_name_qstring = QString::fromLocal8Bit(_file_name_pchar);
    onLog(_file_name_qstring,_log_mode);
}
bool dService::onLog( const QString & file_name_qstring, uint _log_mode)
{
    log_mode = _log_mode; 
    log_dev = new QFile(file_name_qstring);
    if ( !log_dev->open(QIODevice::WriteOnly) )			// file opened successfully
		return false;
    log.setDevice(log_dev);
    return true;

}
bool dService::onLog( FILE *file, uint _log_mode)
{
    log_mode = _log_mode;
    QFile * f = new QFile();
    if ( !f->open(file,QIODevice::WriteOnly) )			// file opened successfully
		return false;
    log_dev = f;
    log.setDevice(log_dev);
	return true;
}
void dService::offLog()
{
	if( log_dev )
	{
		log_dev->close();
		delete log_dev;
		log_dev = NULL;
	}
}
void dService::setLogMode( uint _log_mode)
{
    log_mode = _log_mode;
}

//***************************************************************
//  ��� ����� ������ ����� ����� ������ - ������(��������������
// ����������).
void dService::parser(const QHostAddress &ip, const QByteArray &msg)
{
	dPUser usr;                    // ������������ �����.... ������, ����������� ��� ���� ������ ���������.
    dPUser usr_recep;             // ������������ �����.... ������, ������������ ��� ������� ������ ���������.
        
    QString buf[10];
//    log << msg << endl;
    QList<QByteArray> byte_msg_list = msg.split('\x00');
    char type_msg = msg[0];
    byte_msg_list[0].remove(0,1);
    for( int i = 0; i<10; i++ )
        byte_msg_list.size() > i ? buf[i] = QString::fromLocal8Bit(byte_msg_list[i])
                                 : buf[i] = ""; 

	switch( type_msg )
	{
//*************************************************************
//  ����������� ���-������ �� �������������.
//  ���� ������������ ��� � ����� ������, �� ������� ���,
// � ���� ����, �� ��������� �����.
		case '1':
            // ������ � ���.
            if( (log_mode & dUser::echo_answer) == dUser::echo_answer )
			{
                log << "<msg ip="<<ip.toString()<<" type=\"echo_answer\" code=\"1\" date=\"" <<
                QDateTime::currentDateTime().toString(Qt::TextDate) <<"\" >" << endl;
                log << "\t<to>"  <<escapeXml(buf[0])<<"</to>" << endl;
                log << "\t<from>"<<escapeXml(buf[1])<<"</from>" << endl;
                log << "\t<mode>"<<escapeXml((QString)buf[2][0])<<"</mode>" << endl;
                log << "\t<activity>"<<escapeXml((QString)buf[2][1])<<"</activity>" << endl;
                log << "\t<host>"<<escapeXml(buf[3])<<"</host>" << endl;
                log << "\t<login>"<<escapeXml(buf[4])<<"</login>" << endl;
                log << "\t<version>"<<escapeXml(buf[5])<<"</version>" << endl;
                log << "</msg>" <<endl;
            }
            
			usr = manager->find_user( ip, buf[1]);
			if( !usr ) 
                usr = createRemoteUser(ip,buf[1]);

            // ���� � ������, ��� ���� ���������....
         //   usr_recep = manager->find_user( local_ip, buf[0]);
            if( usr == true /*&& usr_recep == true */)
            {
                usr->set_host( buf[3] );
                usr->set_login( buf[4] );
                usr->set_version( buf[5] );
                usr->set_mode( QString(buf[2][0]).toUInt() );
                usr->set_activity( QString(buf[2][1]).toUInt() );
                usr->uptime();
			}
		break;

//*************************************************************
//  ����������� ���-������� �� �������������.
//  ������� ���� ������������� � ����� ������,	��� ���� �� �� 
// ���� ��������.
		case '0':
            // ������ � ���.
            if( (log_mode & dUser::echo_request) == dUser::echo_request )
			{
                log << "<msg ip="<<ip.toString()<<" type=\"echo_request\" code=\"0\" date=\"" <<
                QDateTime::currentDateTime().toString(Qt::TextDate) <<"\" >" << endl;
                log << "\t<from>"<<escapeXml(buf[0])<<"</from>" << endl;
                log << "</msg>" <<endl;
            }

			usr = manager->find_user( ip, buf[0]);
			if( !usr )	
                usr = createRemoteUser(ip,buf[0]);
			else
				usr->uptime();

            // ������� �������� �������.
             event_mass( dUser::echo_request, usr );
			
		break;

//*************************************************************
//  ����������� ������� ��������� ������������.
		case '6':
            // ������ � ���.
            if( (log_mode & dUser::msg_personal) == dUser::msg_personal )
			{
                log << "<msg ip="<<ip.toString()<<" type=\"msg_personal\" code=\"6\" date=\"" <<
                QDateTime::currentDateTime().toString(Qt::TextDate) <<"\" >" << endl;
                log << "\t<to>"<<escapeXml(buf[1])<<"</to>" << endl;
                log << "\t<from>"<<escapeXml(buf[0])<<"</from>" << endl;
                log << "\t<text>"<<escapeXml(buf[2])<<"</text>" << endl;
                log << "</msg>" <<endl;
            }

            // ���� � ������, ��� �������� ����
			usr = manager->find_user( ip, buf[0]);
			if( !usr ) 
                usr = createRemoteUser(ip,buf[0]);
			else
				usr->uptime();
				
            // ���� � ������, ���� ���������.
            usr_recep = manager->find_user( local_ip, buf[1]);
            if( usr_recep == true )
            {
                manager->event_msg_personal(usr,usr_recep,buf[2]);
                usr_recep->event(dUser::msg_personal,usr,&buf[2]);
                usr_recep->event_msg_personal(usr,buf[2]);
			}
			
		break;
		
//*************************************************************
//  ����������� ��������� ���������.
		case 'E':
            // ������ � ���.
            if( (log_mode & dUser::msg_mass) == dUser::msg_mass )
			{
                log << "<msg ip="<<ip.toString()<<" type=\"msg_mass\" code=\"E\" date=\"" <<
                QDateTime::currentDateTime().toString(Qt::TextDate) <<"\" >" << endl;
                log << "\t<to>"<<escapeXml(buf[1])<<"</to>" << endl;
                log << "\t<from>"<<escapeXml(buf[0])<<"</from>" << endl;
                log << "\t<text>"<<escapeXml(buf[2])<<"</text>" << endl;
                log << "</msg>" <<endl;
            }
					
            // ���� � ������, ��� �������� ����
			usr = manager->find_user( ip, buf[0]);
			if( !usr ) 
                usr = createRemoteUser(ip,buf[0]);
			else
				usr->uptime();
				
            // ���� � ������, ���� ���������.
            usr_recep = manager->find_user( local_ip, buf[1]);
            if( usr_recep == true )
            {
                manager->event_msg_mass(usr,usr_recep,buf[2]);            
                usr_recep->event(dUser::msg_mass,usr,&buf[2]);
                usr_recep->event_msg_mass(usr,buf[2]);
			}

		break;

//*************************************************************
//  ����������� info-������� �� ������������.
		case 'F':
            // ������ � ���.
            if( (log_mode & dUser::info_request) == dUser::info_request )
			{
                log << "<msg ip="<<ip.toString()<<" type=\"info_request\" code=\"F\" date=\"" <<
                QDateTime::currentDateTime().toString(Qt::TextDate) <<"\" >" << endl;
                log << "\t<to>"<<escapeXml(buf[0])<<"</to>" << endl;
                log << "\t<from>"<<escapeXml(buf[1])<<"</from>" << endl;
                log << "</msg>" <<endl;
            }
            		
            // ���� � ������, ��� �������� ����
			usr = manager->find_user( ip, buf[1]);
			if( !usr )	
                usr = createRemoteUser(ip,buf[1]);
			else
				usr->uptime();
				
            // ���� � ������, � ���� ��������� ����, �� ������� � ���� �������.
            usr_recep = manager->find_user( local_ip, buf[0]);
            if( usr_recep == true )
            {  
                //usr_recep->event(dUser::info_request,usr);
                usr_recep->event_info_request(usr);
			}

			
		break;

//*************************************************************
//	����������� info-������ �� ������������.
//	��� �������� info-������ ��������� ���������� � ������������.
		
		case 'G':
            if( (log_mode & dUser::info_answer) == dUser::info_answer )
			{
                log << "<msg ip="<<ip.toString()<<" type=\"info_answer\" code=\"G\" date=\"" <<
                QDateTime::currentDateTime().toString(Qt::TextDate) <<"\" >" << endl;
                log << "\t<to>"  <<escapeXml(buf[0])<<"</to>" << endl;
                log << "\t<from>"<<escapeXml(buf[1])<<"</from>" << endl;
                log << "\t<host>"<<escapeXml(buf[2])<<"</host>" << endl;
                log << "\t<login>"<<escapeXml(buf[3])<<"</login>" << endl;
                log << "\t<percent>"<<escapeXml(buf[4])<<"</percent>" << endl;
                log << "\t<memory>"<<escapeXml(buf[5])<<"</memory>" << endl;
                log << "\t<channel>"<<escapeXml(buf[6])<<"</channel>" << endl;
                log << "\t<auto_answer>"<<escapeXml(buf[7])<<"</auto_answer>" << endl;
                log << "</msg>" <<endl;
            }	
            		
			usr = manager->find_user( ip, buf[1]);

// ����� ������������ ��������� ������ ��� ��������� ���-������.
			if( !usr ) 
                usr = createRemoteUser(ip,buf[1]);
            if ( usr == true )
            {
                usr->set_host( buf[2] );
                usr->set_login( buf[3] );
                usr->set_percent( buf[4] );
                usr->set_auto_answer( buf[7] );
                usr->set_memory( buf[5] );
                
                usr->uptime();		// ������� ����� ���������� ���������.
			}
					
		break;
		

//*************************************************************
//  �������� ���������� � ������ ������������ �� ����.
//  ����� ��� ������� �� ������... destroy

		case '5':
            // ������ � ���.
            if( (log_mode & dUser::msg_exit) == dUser::msg_exit )
			{
                log << "<msg ip="<<ip.toString()<<" type=\"msg_exit\" code=\"5\" date=\"" <<
                QDateTime::currentDateTime().toString(Qt::TextDate) <<"\" >" << endl;
                log << "\t<from>"<<escapeXml(buf[0])<<"</from>" << endl;
                log << "\t<channel>"<<escapeXml(buf[1])<<"</channel>" << endl;
                log << "</msg>" <<endl;
            }		
			usr = manager->find_user( ip, buf[0]);
			if( usr == true )
			{
                // ������� �������� ������� � ������ ������������ �� ����.
                manager->event_msg_exit( usr );
                event_mass( dUser::msg_exit, usr );
                usr->delete_user();
            }

		break;

//*************************************************************
//  �������� ��������� � ������� �������� ������.
		case 'C':
                // ������ � ���.
            if( (log_mode & dUser::current_topic) == dUser::current_topic )
            {
                log << "<msg ip="<<ip.toString()<<" type=\"current_topic\" code=\"C\" date=\"" <<
                QDateTime::currentDateTime().toString(Qt::TextDate) <<"\" >" << endl;
                log << "\t<to>"<<escapeXml(buf[0])<<"</to>" << endl;
                log << "\t<topic>"<<escapeXml(buf[1])<<"</topic>" << endl;
                log << "</msg>" <<endl;
            }
            
			if( buf[1] != manager->get_main_user()->get_topic() )
			{
                // ������� �������� ������� � ����� ������. 
                manager->get_main_user()->set_topic(buf[1]);
                manager->event_current_topic( buf[1] );
                event_mass( dUser::current_topic,dPUser(),&buf[1]);
            }
        break;
//*************************************************************
//  �������� ��������� � ����� ������.
		case 'B':
            if( (log_mode & dUser::change_topic) == dUser::change_topic )
            {
                log << "<msg ip="<<ip.toString()<<" type=\"change_topic\" code=\"B\" date=\"" <<
                QDateTime::currentDateTime().toString(Qt::TextDate) <<"\" >" << endl;
                log << "\t<topic>"<<escapeXml(buf[0])<<"</topic>" << endl;
                log << "</msg>" <<endl;
            }
                
			if( buf[1] != manager->get_main_user()->get_topic() )
			{
                // ������� �������� ������� � ����� ������. 
                manager->get_main_user()->set_topic(buf[0]);
                manager->event_change_topic( buf[0] );
                event_mass( dUser::change_topic,dPUser(),&buf[0]);
                // ������ � ���.
            }

		break;

//*************************************************************
//	�������� ��������� � ����� ������������ � ���.
		case '4':
            // ������ � ���.            
            if( (log_mode & dUser::msg_enter) == dUser::msg_enter )
            {
                log << "<msg ip="<<ip.toString()<<" type=\"msg_enter\" code=\"4\" date=\"" <<
                QDateTime::currentDateTime().toString(Qt::TextDate) <<"\" >" << endl;
                log << "\t<from>"<<escapeXml(buf[0])<<"</from>" << endl;
                log << "\t<channel>"<<escapeXml(buf[1])<<"</channel>" << endl;
                log << "\t<sex>"<< escapeXml((QString)buf[2][1])<<"</sex>" << endl;
                log << "</msg>" <<endl;
            }
            
            usr = manager->find_user( ip, buf[0]);
			if( !usr ) 
                usr = createRemoteUser(ip,buf[0]);
            if( usr == true )
            {
                // ������� �������� ������� � ����� ������������ � ���.
                manager->event_msg_enter( usr );
                event_mass( dUser::msg_enter, usr );
                usr->set_sex( QString(buf[2][1]).toInt() );
				usr->uptime();
            }

		break;
		

//*************************************************************
//  �������� ��������� �������������� ������������.
		case '3':
            // ������ � ���.
            if( (log_mode & dUser::msg_rename) == dUser::msg_rename )
			{
                log << "<msg ip="<<ip.toString()<<" type=\"msg_rename\" code=\"3\" date=\"" <<
                QDateTime::currentDateTime().toString(Qt::TextDate) <<"\" >" << endl;
                log << "\t<from>"<<escapeXml(buf[0])<<"</from>" << endl;
                log << "\t<new_name>"<<escapeXml(buf[1])<<"</new_name>" << endl;
                log << "</msg>" <<endl;
            }
            usr = manager->find_user( ip, buf[0]);
			if( !usr )
			{
                usr = createRemoteUser(ip,buf[1]);
                manager->event_msg_rename( usr , buf[0]);
                event_mass( dUser::msg_rename, usr );
            }
			else
			{
                // ������� �������� ������� � �������������� ������������.
                usr->set_name( buf[1]);
                manager->event_msg_rename( usr , buf[0]);
                event_mass( dUser::msg_rename, usr );
			}
		break;

//*************************************************************
//	�������� ��������� � ����� ����������.
		case 'M':
            // ������ � ���.
            if( (log_mode & dUser::change_activity) == dUser::change_activity )
			{
                log << "<msg ip="<<ip.toString()<<" type=\"change_activity\" code=\"M\" date=\"" <<
                QDateTime::currentDateTime().toString(Qt::TextDate) <<"\" >" << endl;
                log << "\t<from>"<<escapeXml(buf[0])<<"</from>" << endl;
                log << "\t<activity>"<<escapeXml(buf[1])<<"</activity>" << endl;
                log << "</msg>" <<endl;
            }
            
			usr = manager->find_user( ip, buf[0]);
            if( !(!usr) )
            {
                usr->set_activity(buf[1].toInt());
				usr->uptime();
                manager->event_change_activity(usr);
                // ������� �������� ������� � ����� ����������.
//                event_mass( dUser::change_activity, usr );
            }
		break;
/*
//*************************************************************
//	�������� ��������� � ����� ������.
		case 'D':
			usr = manager->find_user( ip, buf[0]);
			if( !usr )
				usr = createRemoteUser(ip,buf[0]);
            // ������ � ���.
            if( (log_mode & dUser::change_mode) == dUser::change_mode )
			{
                log << "<msg ip="<<ip.toString()<<" type=\"change_mode\" code=\"D\" date=\"" <<
                QDateTime::currentDateTime().toString(Qt::TextDate) <<"\" >" << endl;
                log << "\t<from>"<<escapeXml(buf[0])<<"</from>" << endl;
                log << "\t<mode>"<<escapeXml((QString)buf[1][0])<<"</mode>" << endl;
                log << "</msg>" <<endl;
            }            
            
            if( usr )
            {
                
                usr->set_mode(buf[1]);
				usr->uptime();
				usr->event_change_mode(usr);
                // ������� �������� ������� � ����� ������.
                event_mass( dUser::change_mode, usr );
            }
		break;
*/
//*************************************************************
//	�������� ������ � �����.
		case '2':
            // ������ � ���.
            if( (log_mode & dUser::msg_channel) == dUser::msg_channel )
			{
                log << "<msg ip="<<ip.toString()<<" type=\"msg_channel\" code=\"2\" date=\"" <<
                QDateTime::currentDateTime().toString(Qt::TextDate) <<"\" >" << endl;
                log << "\t<channel>"<<escapeXml(buf[0])<<"</channel>" << endl;
                log << "\t<from>"<<escapeXml(buf[1])<<"</from>" << endl;
                log << "\t<text>"<<escapeXml(buf[2])<<"</text>" << endl;
                log << "</msg>" <<endl;
            }
            			
			usr = manager->find_user( ip, buf[1]);

			if( !usr ) 
                usr = createRemoteUser(ip,buf[1]);
            if( usr == true )
            {
                manager->event_msg_channel( usr, buf[2] );
                // ������ ���� ��� ������ ������ � �����.
                event_mass( dUser::msg_channel, usr, &buf[2]);
				usr->uptime();
            }

		break;
		
//*************************************************************
//	�������� ������ � �����, ���� - me. 
		case 'A':
            // ������ � ���.
            if( (log_mode & dUser::msg_channel_me) == dUser::msg_channel_me )
			{
                log << "<msg ip="<<ip.toString()<<" type=\"msg_channel_me\" code=\"A\" date=\"" <<
                QDateTime::currentDateTime().toString(Qt::TextDate) <<"\" >" << endl;
                log << "\t<channel>"<<escapeXml(buf[0])<<"</channel>" << endl;
                log << "\t<from>"<<escapeXml(buf[1])<<"</from>" << endl;
                log << "\t<text>"<<escapeXml(buf[2])<<"</text>" << endl;
                log << "</msg>" <<endl;
            }
            
			usr = manager->find_user( ip, buf[1]);

// ����� ������������ ��������� ������ ��� ��������� ���-������.
			if( !usr ) 
                usr = createRemoteUser(ip,buf[1]);           
            if( usr == true )
            {
                manager->event_msg_channel_me( usr, buf[2] );
                // ������ ���� ��� ������ ������ � �����.
                event_mass( dUser::msg_channel_me, usr, &buf[2]);
				usr->uptime();
            }

		break;
		
//*************************************************************
//	�������� ���� ����� �� ������������.

		case '7':
		{
            QString mode(buf[0][0]);
            QString to = buf[0].remove(0,1);
            QString from = buf[1];
            QString sex(buf[2][0]);
            QString auto_answer = buf[2].remove(0,1);
            
            // ������ � ���.
            if( (log_mode & dUser::msg_auto_answer) == dUser::msg_auto_answer )
			{
                log << "<msg ip="<<ip.toString()<<" type=\"msg_auto_answer\" code=\"7\" date=\"" <<
                QDateTime::currentDateTime().toString(Qt::TextDate) <<"\" >" << endl;
                log << "\t<to>"<<escapeXml(to)<<"</to>" << endl;
                log << "\t<from>"<<escapeXml(from)<<"</from>" << endl;
                log << "\t<mode>"<<escapeXml(mode)<<"</mode>" << endl;
                log << "\t<sex>"<<escapeXml(sex)<<"</sex>" << endl;
                log << "\t<auto_answer>"<<escapeXml(auto_answer)<<"</auto_answer>" << endl;
                log << "</msg>" <<endl;
            }
            
			usr = manager->find_user( ip, from);
			if( !usr ) 
                usr = createRemoteUser(ip,from);
			else
			{
                usr->set_sex( sex.toInt() );            
                usr->set_mode( mode.toInt() );            
				usr->uptime();
			}	
            // ���� � ������, ���� ���������.
            usr_recep = manager->find_user( local_ip, to);
            if( usr_recep == true )
            {
                manager->event_msg_auto_answer(usr,usr_recep, auto_answer );
                usr_recep->event_msg_auto_answer(usr,auto_answer);
            }
        }
		break;

//*************************************************************
//	����������� �������� � ����������. 

		case 'I':

           // ������ � ��������� ������������� ��������.
            if( buf[0] == "MGREQ" )
            {
                // ������ � ���.
                if( (log_mode & dUser::image_request) == dUser::image_request )
                {
                    log << "<msg ip="<<ip.toString()<<" type=\"image_request\" code=\"IMGREQ\" date=\"" <<
                    QDateTime::currentDateTime().toString(Qt::TextDate) <<"\" >" << endl;
                    log << "\t<code>"<<escapeXml(buf[1])<<"</code>" << endl;
                    log << "</msg>" <<endl;
                }     
                
                QList<dPUser> usr_ls = manager->find_users_by_ip( ip );
                usr = usr_ls.first();
                if( usr == true )
                    event_mass( dUser::image_request, usr, &buf[1] );
            } 
            // ����������� ��� ��������� �������� �� ������ ���� ������������.
            if( buf[0] == "MGOUT" )
            {
               // ������ � ���.
                if( (log_mode & dUser::image_answer) == dUser::image_answer )
                {
                    log << "<msg ip="<<ip.toString()<<" type=\"image_answer\" code=\"IMGREQ\" date=\"" <<
                    QDateTime::currentDateTime().toString(Qt::TextDate) <<"\" >" << endl;
                    log << "\t<code>"<<escapeXml(buf[2])<<"</code>" << endl;
                    log << "\t<from>"<<escapeXml(buf[1])<<"</from>" << endl;
                    log << "</msg>" <<endl;
                }     
                
                QByteArray cmsg = msg;
                usr = manager->find_user( ip, buf[1]);
                if( !usr )
                    usr = createRemoteUser(ip,buf[1]);
                
                if( usr == true && buf[2] != "0")
                {
                    usr->uptime();
                    cmsg.remove(0,9+buf[2].size()+buf[1].size() );
                    // ����� ��� ��� ��� "������" ��������� Avatar ����.
                    
                    QPixmap avatar;
                    avatar.loadFromData( cmsg );
                    usr->set_avatar(avatar);
                    // ������ ���� ��� ���������� �������� � ������������.
                    event_mass( dUser::image_answer, usr );
                }                
            }      

		break;
		
		case '<':
		
            QString xml =  QString::fromLocal8Bit(msg);
            if( (log_mode & dUser::msg_xml) == dUser::msg_xml )
			{
                log << "<msg ip="<<ip.toString()<<" type=\"msg_xml\" date=\"" <<
                QDateTime::currentDateTime().toString(Qt::TextDate) <<"\" >" << endl;
                log << xml << endl;
                log << "</msg>" <<endl;
            }

            QDomDocument msgXmlDocument;
            if ( !msgXmlDocument.setContent( xml) )
                break;
            
            QDomElement rootElement = msgXmlDocument.documentElement();
            if ( rootElement.tagName() != tr("messages") )
                break;

            QDomElement messageElement = rootElement.firstChildElement();
            while (!messageElement.isNull()) 
            {
            // ��������� �� ���� ������ ���������.
                QDomElement fromElement = messageElement.firstChildElement(tr("from"));
                if( fromElement.isNull() )
                    break;
                    
                if( !fromElement.hasAttribute(tr("name")) || !fromElement.hasAttribute(tr("ip")) )
                    break;
                QString from_name = fromElement.attribute(tr("name"));
                QHostAddress from_ip(fromElement.attribute(tr("ip")));
            // ���������� Ip ����������� � ��������� � IP ���������� �� ���� 
            // ������ �����.
                if( !(from_ip == ip) )
                    break;
            // ������ ������������ �� �������� ������ �����,
            // ���� �� �� ������, �� �������� ���.
                usr = manager->find_user( ip, from_name);
                if( !usr ) 
                    usr = createRemoteUser(ip,from_name);
                else
                    usr->uptime();
                      
            // ��������� ��� ���� ������ ���������.
                QDomElement toElement = messageElement.firstChildElement(tr("to"));
                if( toElement.isNull() )
                {
//                  xmlParser(usr,dPUser(),msgXmlDocument); 
                    break;
                }
                while (!toElement.isNull()) 
                {
                    if( toElement.hasAttribute(tr("name")) && toElement.hasAttribute(tr("ip")) )
                    {
                        QString to_name = toElement.attribute(tr("name"));
                        QHostAddress to_ip(toElement.attribute(tr("ip")));
                        // ���� � ������, ���� ���� ������������� ���������.
                        usr_recep = manager->find_user( to_ip, to_name);
                        if( usr_recep == true )
                        {
                            xmlParser(usr,usr_recep,messageElement); 
                            usr_recep->event_xml(usr,messageElement);
                        }
                        toElement = toElement.nextSiblingElement(tr("to"));
                    }
                }
                messageElement = messageElement.nextSiblingElement();
            }
		break;
	}
}

//***************************************************************
// ����� ����������� XML ��������� ����.
void dService::xmlParser( dPUser _from, dPUser _to, const QDomElement &messageElement )
{

        if ( messageElement.tagName() == tr("ping") )
        {
            QDomElement verElement = messageElement.firstChildElement(tr("version"));
//            qDebug("PING");
            qDebug() << verElement.text().toInt();

            if( !verElement.text().isEmpty() )
                _from->set_xml_protocol(verElement.text().toInt());
            else
                _from->set_xml_protocol(1);

            // ������� ��� �������� ��������� ��� ������.
            if (!_to)
                // ������� �� ����.
                // ������� �������� �������.
                event_mass( dUser::echo_request, _from );            
            else
                // ���� ������, �� �������� ������� ������ � ����� ������������.
                _to->event_echo_request(_from);
                 
        }
// ��� ��������� � �������... �������� � ����� �� PING.

        if ( messageElement.tagName() == tr("echo") )
        {
        // ������������� ������ xml ���������.
            qDebug("ECHO");
            QDomElement verElement = messageElement.firstChildElement(tr("version"));
            if( !verElement.text().isEmpty() )
                _from->set_xml_protocol(verElement.text().toInt());
            else
                _from->set_xml_protocol(1);
           
    
        // ��� ����� �����������...
            QDomElement hostElement = messageElement.firstChildElement(tr("host"));
            _from->set_host( hostElement.text() );
        // ������ ���� �����������.
            QDomElement chatVersionElement = messageElement.firstChildElement(tr("chat_version"));
            _from->set_version( chatVersionElement.text() );
        // ����� ����� � �������.
            QDomElement loginElement = messageElement.firstChildElement(tr("login"));
            _from->set_login( loginElement.text() );
        // ����� � ������ ���������� ��������� ������������.
            QDomElement modeElement = messageElement.firstChildElement(tr("mode"));
            _from->set_mode( modeElement.text().toUInt() );
        // ���������� ���������� ������������.
            QDomElement activityElement = messageElement.firstChildElement(tr("activity"));
            _from->set_activity( activityElement.text().toUInt() );
        // ����-����� ���������� ������������.
            QDomElement autoAnswerElement = messageElement.firstChildElement(tr("auto_answer"));
            _from->set_auto_answer( autoAnswerElement.text() );
        }

        if ( messageElement.tagName() == tr("message") )
        {
            // ������. ����� ���������� �� ������.
            if( _to == false )
                return;
  //          qDebug("Message");
            
            // ����� ���������...
            QDomElement dataElement = messageElement.firstChildElement(tr("data"));
            bool html = dataElement.attribute(tr("type"),tr("html")) == tr("html")? true: false;
            // ��� ���������...
            QDomElement typeElement = messageElement.firstChildElement(tr("message_type"));
            
            //------------------------------------------------------
            // ������������� � ����������� ��������...
            if( typeElement.isNull() )
                QDomElement typeElement = messageElement.firstChildElement(tr("type"));
            //------------------------------------------------------
            
            if( typeElement.text() == tr("mass") )
            {
                manager->event_msg_mass(_from,_to,dataElement.text(),html);            
                _to->event_msg_mass(_from,dataElement.text(),html);        
            }
            else if( typeElement.text() == tr("personal") )
            {
                manager->event_msg_personal(_from,_to,dataElement.text(),html);            
                _to->event_msg_personal(_from,dataElement.text(),html);        
            }
        }

}

//***************************************************************
//  �������� ������.

int dService::send( const QHostAddress &_ip, const QByteArray &_msg )
{
    if( useNetworkPath == 0 )
        return udpSocket->writeDatagram(_msg.data(),_msg.size(),_ip,port);
    else
        return udpSocketPath->writeDatagram(_msg,_ip,port);
};

int dService::send( const QHostAddress &_ip, const QString &_msg )
{
//	return this->send(_ip,_msg.toLocal8Bit());
 //   qDebug() <<"IP" << _ip.toString() << " DatA: " << _msg;
    QByteArray _msg_data = _msg.toLocal8Bit();
    if( useNetworkPath == 0 )
        return udpSocket->writeDatagram(_msg_data.data(),_msg_data.size(),_ip,port);
    else
        return udpSocketPath->writeDatagram(_msg_data,_ip,port);
};


//***************************************************************
//  ��������� �������.

void dService::connecting()
{
	broadcast_ip.setAddress( local_ip.toIPv4Address()|0x000000FF);  
  
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(local_ip, port);
    
    if (udpSocket->state() == QAbstractSocket::UnconnectedState)
    {
        qDebug() << "Network error.";
        throw( dServiceError(init) );
    }
    connect(udpSocket, SIGNAL(readyRead()),
            this, SLOT(dataReceived()));
    
}

void dService::connectingPath()
{
	broadcast_ip.setAddress( local_ip.toIPv4Address()|0x000000FF);  
    
    qDebug("Load network plugin.");
    QPluginLoader networkplugin(tr("dudpsocket.dll"),this);
    QObject *plugin = networkplugin.instance();
    udpSocketPath = qobject_cast<dUdpSocket*>(plugin);
    if( !udpSocketPath ) {
        qDebug() << "Load plagin error.";
        throw( dServiceError(load_plugin) );  // ������� ����������, ��� ���� � �������� �������.
    }

  //  udpSocketPath = new dUdpSocket(this);
    if( !udpSocketPath->bind(local_ip, port) )
    {
        qDebug() << "(NetworkPath)Network error.";
        throw( dServiceError(init) );
    }
    connect(udpSocketPath, SIGNAL(readyRead()), this, SLOT(dataReceivedPath()));
    
}
//***************************************************************
//  ����� �������� html-���� �� ������.
QString dService::escapeXml(QString xml)
{
    xml.replace("&", "&amp;");
    xml.replace("<", "&lt;");
    xml.replace(">", "&gt;");
    xml.replace(" ", "&apos;");
    xml.replace("\"", "&quot;");
    return xml;
}

//***************************************************************
//  ������� �������� ���������.
void dService::send_mass_echo( dMessageSendType _msg_send_type, dPUser _from )
{
    QString msg;
    QTextStream in( &msg, QIODevice::WriteOnly );
	in << "0" << _from->get_name() <<'\x00';
	
	if( _msg_send_type == default_type )
        _msg_send_type = get_send_type();
	if( _msg_send_type == list_ip_type )
        foreach( QHostAddress ip ,get_ip_list() )
        {
      //      qDebug() << ip.toString();
            send(ip,msg);
        }
	if( _msg_send_type == broadcast_ip_type )
        send(broadcast_ip,msg);
}
void dService::send_mass_enter( dMessageSendType _msg_send_type, dPUser _from )
{
	QString msg;
	QTextStream in( &msg, QIODevice::WriteOnly );

	in <<"4"<<_from->get_name()<<'\x00'<<"#Main"<<'\x00'<<"1"
	   <<_from->get_sex()<<'\x00'<<_from->get_host()<<'\x00'
	   <<_from->get_login()<<'\x00'<<_from->get_version()<<'\x00';

	if( _msg_send_type == default_type )
        _msg_send_type = get_send_type();
	if( _msg_send_type == list_ip_type )
        foreach( QHostAddress ip ,get_ip_list() )
            send(ip,msg);
	if( _msg_send_type == broadcast_ip_type )
        send(broadcast_ip,msg);
	
}
void dService::send_mass_exit( dMessageSendType _msg_send_type, dPUser _from )
{
	QString msg;
	QTextStream in( &msg, QIODevice::WriteOnly );
	
	in <<"5"<<_from->get_name()<<'\x00'<<"#Main"<<'\x00'<<"0"<<'\x00';
	
	if( _msg_send_type == default_type )
        _msg_send_type = get_send_type();
	if( _msg_send_type == list_ip_type )
        foreach( QHostAddress ip ,get_ip_list() )
            send(ip,msg);
	if( _msg_send_type == broadcast_ip_type )
        send(broadcast_ip,msg);
}
void dService::send_mass_msg_channel( dMessageSendType _msg_send_type, dPUser _from , const QString &_msg)
{
	QString msg;
	QTextStream in( &msg, QIODevice::WriteOnly );
	in <<"2#Main"<<'\x00'<<_from->get_name()<<'\x00'<<_msg<<'\x00';
	
	if( _msg_send_type == default_type )
        _msg_send_type = get_send_type();
	if( _msg_send_type == list_ip_type )
        foreach( QHostAddress ip ,get_ip_list() )
            send(ip,msg);
	if( _msg_send_type == broadcast_ip_type )
        send(broadcast_ip,msg);
}
void dService::send_mass_msg_channel_me( dMessageSendType _msg_send_type, dPUser _from , const QString &_msg)
{
	QString msg;
	QTextStream in( &msg, QIODevice::WriteOnly );
	in <<"A#Main"<<'\x00'<<_from->get_name()<<'\x00'<<_msg<<'\x00';
	
	if( _msg_send_type == default_type )
        _msg_send_type = get_send_type();
	if( _msg_send_type == list_ip_type )
        foreach( QHostAddress ip ,get_ip_list() )
            send(ip,msg);
	if( _msg_send_type == broadcast_ip_type )
        send(broadcast_ip,msg);
}
void dService::send_mass_change_topic( dMessageSendType _msg_send_type, const QString &_topic)
{
	QString msg;
	QTextStream in( &msg, QIODevice::WriteOnly );
	in <<"B"<<_topic<<'\x00';
	
	if( _msg_send_type == default_type )
        _msg_send_type = get_send_type();
	if( _msg_send_type == list_ip_type )
        foreach( QHostAddress ip ,get_ip_list() )
            send(ip,msg);
	if( _msg_send_type == broadcast_ip_type )
        send(broadcast_ip,msg);   

};
void dService::send_mass_rename( dMessageSendType _msg_send_type, dPUser _from, const QString &_oldname )
{
	QString msg;
	QTextStream in( &msg, QIODevice::WriteOnly );
	in <<"3"<<_oldname<<'\x00'<<_from->get_name();
	
	if( _msg_send_type == default_type )
        _msg_send_type = get_send_type();
	if( _msg_send_type == list_ip_type )
        foreach( QHostAddress ip ,get_ip_list() )
            send(ip,msg);
	if( _msg_send_type == broadcast_ip_type )
        send(broadcast_ip,msg);   
};
//***************************************************************
//   ����� ������ �������� �������.
// ���������� �������������!
void dService::event_mass( dUser::dMsgType _event_type, dPUser _from, const QString *_msg)
{
    if( _event_type == dUser::echo_request ||
        _event_type == dUser::change_activity || _event_type == dUser::change_mode ||
        _event_type == dUser::change_topic || _event_type == dUser::current_topic ||
        _event_type == dUser::msg_channel_me || _event_type == dUser::msg_channel ||
        _event_type == dUser::msg_enter || _event_type == dUser::msg_exit ||
        _event_type == dUser::msg_rename || _event_type == dUser::image_request ||
        _event_type == dUser::image_answer)
    {
        QList<dPUser> users = manager->get_users();
        foreach( dPUser usr, users)
        {
            usr->event(_event_type,_from,_msg);
            switch( _event_type )
            {
                case dUser::echo_request:
                    usr->event_echo_request(_from);
                break;
                case dUser::change_activity:
                    usr->event_change_activity(_from);
                break;
                case dUser::change_mode:
                    usr->event_change_mode(_from);
                break;
                case dUser::msg_exit:
                    usr->event_msg_exit(_from);
                break;
                case dUser::msg_enter:
                    usr->event_msg_enter(_from);
                break;
                case dUser::msg_rename:
                    usr->event_msg_rename(_from);
                break;
                case dUser::change_topic:
 // ����� ���������� ������
 //                   usr->set_topic( *_msg);
                    usr->event_change_topic(*_msg);
                break;
                case dUser::current_topic:
 // ����� ���������� ������
  //                  usr->set_topic( *_msg);
                    usr->event_current_topic(*_msg);
                break;
                case dUser::msg_channel:
                    usr->event_msg_channel(_from,*_msg);
                break;
                case dUser::msg_channel_me:
                    usr->event_msg_channel_me(_from,*_msg);
                break;
                case dUser::image_request:
                    usr->event_image_request(_from,*_msg);
                break;
                case dUser::image_answer:
                    usr->event_image_answer(_from);
                break;
            }
        }
    }
}

//***************************************************************
// ����� ������� ������ ���������� ������������.
dPUser dService::createRemoteUser( const QHostAddress &_ip, const QString &_name )
{
    return absRtUsrCreator->create(this,_ip,_name);
}

dAbstractIPList::dAbstractIPList( dService *_service ):
            service(_service)
{
    addListToService(_service);
};

dAbstractIPList::~dAbstractIPList()
{
    if( service && service->ip_lists.contains(this) )
        service->ip_lists.removeAll(this);
};

void dAbstractIPList::addListToService( dService *_service )
{
    if( _service )
        _service->ip_lists << this;
}

dRangeIP::dRangeIP( const QHostAddress& _border1, 
                    const QHostAddress& _border2,
                    dService *_service ):
            dAbstractIPList(_service)
{
    quint32 ip1 = _border1.toIPv4Address();
    quint32 ip2 = _border2.toIPv4Address();
    if( ip1 > ip2 )
    {
        quint32 ip3 = ip1;
        ip1 = ip2;
        ip2 = ip3;
    }
    
    for( quint32 i = ip1; i <= ip2; i++ )
    {
        if( !QHostAddress(i).toString().contains(QObject::tr("255")))
            ip_list << QHostAddress(i);
    }
    
}
dSingleIP::dSingleIP( const QHostAddress& _ip, dService *_service):
            dAbstractIPList(_service)
{
    ip_list << _ip;
}

QList<QHostAddress> dService::get_ip_list() const 
{ 
    QList<QHostAddress> ip_adrs;
    foreach( dAbstractIPList *ip_list ,ip_lists )
        ip_adrs << ip_list->get_ip_list();
            
    return ip_adrs; 
};
