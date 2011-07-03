#ifndef DLOGWINDOW_H
#define DLOGWINDOW_H

#include <QtGui>
#include <QtXml>

#include "../net/duser.h"

class dChatApplication;
class dSetting;

class dLogWindow : public QMainWindow
{   
    Q_OBJECT
    private:
        dChatApplication *application;
    // ���� � ������� ��������.
        QDockWidget * contentsWidget;
        QStackedWidget *centralWidget;
    // ���� � ���������� �����������.
        QTextEdit *systemMessageEditor;
    // ������� � ��������� �����������.
        QTableWidget *massMessageTable;
    // ������� � ����� ���������.
        QTableWidget *messageLogTable;
    // ������������ ��������� �������, ������� ������ ������������ � XML.
        QString escapeXml(QString xml);
    // ��������� ���� � ������.
        dSetting *settingLogWindow;
    // ������� - "������ �������������".
        QCheckBox *doubleCheckBox;
    // XML-��� �������� � ������ ���������.
        QDomDocument logDocument; 
    // ��������� ������ � ������� ���� ���������...
        void addLogTable(   const QString & _date_time,
                            const QString & _fromName,
                            const QString & _fromIp,
                            const QString & _toName,
                            const QString & _toIp,
                            const QString & _msg,
                            bool _html = false );   
    public:
        dLogWindow( QWidget * _parent = 0, Qt::WFlags _flags = 0 );
        ~dLogWindow();
    
    public slots:
    // ��� ������� ����� � ������� ���������.
        void tableDoubleClicked ( QTableWidgetItem * item );
    // ��� ������� ������ �������� ������ �����.
        void closeSideWindow( bool _checked );
    // ��� ������� ������ ����
        void itemChanged ( int _index );
    // ����������� ��� ��������� ������� "������ �������������".
        void doubleMassStateChanged ( int _state );
    // ���������� ��� ������� ������� ������� ����.
        void clearLog();
    // ����� ���������� ��� ��������� ����������� ���������. c� dUser � dManagerEx.        
        void slot_msg_channel( dPUser _from, const QString & _msg );
        void slot_msg_channel_me( dPUser _from, const QString & _msg );
        void slot_change_topic( const QString & _topic );
        void slot_msg_enter( dPUser _from );
        void slot_msg_exit( dPUser _from );
        void slot_msg_beep( dPUser _from, dPUser _to);
        void slot_msg_personal( dPUser _from, dPUser _to , const QString & _msg, bool _html);
        void slot_msg_mass( dPUser _from, dPUser _to, const QString & _msg, bool _html);
        void slot_msg_rename( dPUser _from, const QString &_oldname);
        void slot_msg_auto_answer( dPUser _from, dPUser _to, const QString & _msg);
};

#endif // DLOGWINDOW_H
