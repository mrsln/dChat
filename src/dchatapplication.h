#ifndef DCHATCPPLICATION_H
#define DCHATCPPLICATION_H

#include <QtGui>
#include <QtXml>

#include "netex/dusersfactory.h"

class dManagerEx;
class dUserWindow;
class dTopicWindow;
class dPropertyWindow;
class dChannelWindow;
class dSettingGeneral; 
class dSetting;
class dWindow;
class dWarningWindow;
class dLogWindow;
class dFriendsWindow;
class dTrayIcon;
class dPUser;
class dSettingMessageEditor;
class dChatPluginInterface;
class dSettingStyle;

class dContextUserMenu: public QObject
{
    Q_OBJECT
    private:
        QList<QAction *> actions;
        QList<QWidget *> widgets;
    public:
        void addWidget( QWidget *_widget );
        void removeWidget( QWidget *_widget );
        
        void addAction( QAction *_action );
//        void removeAction( QAction *_action );
        void addActions( QList<QAction*> _actions );
    
        const QList<QAction *> &get_actions(){ return actions; };
    public slots:
        void destroyedWidget(QObject * obj);
        void destroyedAction(QObject * obj);
};

class dChatApplication : public QApplication
{
    Q_OBJECT
    private:
    // ���� ���������� ������ ���� � �������.
        QMenu *windowMenu;
    // ������ ���� ���� � "�������"
        QList<dWindow*> windowList;
    // ��������� �� ������ ������ � ������� � ����....
        dTrayIcon *trayIcon;
    // ��������� �� ��������� ����.
        dManagerEx      *chat_manager;
    // XML-��� �������� � ����������� ����.
        QDomDocument settingDocument; 
    // ����� ��������� ���� � �����������.
        QDomElement openSettingFile( const QString & _filename);
    // ����� ��������� �������� �������� �� ����� ��������.
        void loadKeyMap();
    // ����� ������...
        QMap<QChar,QChar> keyMap;
    
    // ����������� ����... ��� ����� �� ������ � ����...
        QAction *settingDChatAct,
                *raiseDChatAct,
                *quitDChatAct;
        
        QList<dChatPluginInterface*> pluginsList;
    public:
    
    // ���������� ������ �� ������ ��������...
        QList<dChatPluginInterface*> &getPluginsList(){ return pluginsList; };
    // ����������� ����.. ��� ������ �������������....
        dContextUserMenu contextUserMenu;
    // ��������������� ������... ��� ������������ ���������....
    // � ����������� �� �������... � �������....
        QString keyConverter( const QString &_value );
        
    //  ��������� ������������, ��� �������� ����� ������ ��� ������������� 
    // ����������.
        enum dApplicationError{  plugin_load_error,
                                 setting_parser_error};
        
        dChatApplication(int & argc, char ** argv);
        ~dChatApplication();
    // void start();
    
    // ��������� �� �������� ��������... ������ ��� ������ ������ ����
    // �������� ����� ����.
        dSettingGeneral  *settingGeneral; 
     // ��������� �� ���� �������� ���������.
        dSetting *settingPlugins;
    // ���� ��������� ����.
        dSetting *settingWindow;    
    // -------
        dSettingStyle *settingCommon;
    // ��������� �� ��������� ��������� ���������.
        dSettingMessageEditor *settingMessageEditor;
        
    // ������� ���� (�� ������� �������������).
        dUserWindow     *user_window;
    // ���� ������ (��� ������������ ���������).
        dTopicWindow    *topic_window;   
    // ���� �������.
        dPropertyWindow *property_window;
    // ���� ������.
        dChannelWindow  *channel_window;
    // ���� ����������� ���������.
        dWarningWindow  *warning_window;
    // ���� �����.
        dLogWindow      *log_window;
    // ���� � ��������.
        dFriendsWindow  *friends_window;
        
        QWidget *trayBarWindow;
        
    // ������� �������������, �������� ������ ��������� ����� ���������
    // �������������, ������� ����� ��������� � ������� ������� � ��������
    // � �������.
        dUsersFactory usersFactory;    
    // ���������� ��������� �� ��������� ����.
        dManagerEx *get_managerEx() const { return chat_manager; };
    // ���������� ������ ����.
        QList<dWindow*> getWindowList() const { return windowList; };
    //  ��������� ���� � ������ ����.
        bool addWindow( dWindow* _window);
    // ���������� ���� ���������� ������ ����.
        QMenu *getWindowMenu() const{ return windowMenu; };
        
    // ���� ������������ ��������... ��� ��������� ���������.
        enum typeMessage {
            msg_personal  = 0x1,
            msg_mass = 0x2,
        }; 
    // ����� ������� ���� � ����������� �� ��������� ������������.
        QWidget *createUserInfoWindow( dPUser _usr );
    // ����� ������� �������� ��������� ��� ������������.
    // _from - ��� ���������� ���������.
    // _to - ���� ���������� ���������(�������� �������� ��������� ���������� ������������� 
    //          ������������).
    // _msg - ����� ����������� ���������.
        QWidget *createMessageEditor( QList<dPUser> _to, 
                                      dPUser _from, 
                                      const QString &_msg = QString(), 
                                      const QString &_title = tr("���������"),
                                      typeMessage _tm = msg_personal, 
                                      bool _showed = true,
                                      bool _html = false);
                                      
        QWidget *createMessageEditor( dPUser _to, 
                                      dPUser _from, 
                                      const QString &_msg = QString(), 
                                      const QString &_title = tr("���������"),
                                      typeMessage _tm = msg_personal, 
                                      bool _showed = true,
                                      bool _html = false);
    

    public slots:
        void showPropertyWindow();
        void showLogWindow();
    
    // ���� ����������� ��� ����� ���� � ������ � ����....
        void trayIconMouseClick();
    // ����� ����� ��������� �����������....
        void quitChat();
    
};

#include "dsetting.h"

class dSettingStyle: public dSetting
{
    Q_OBJECT
    private:
        QString styleName;
        QCheckBox *startCheckBox;
        
    public:
    // �������� ��������� ����� ��-��������� ��� ���������...
        bool start_minimized();
        
        dSettingStyle( const QString &_key, dSetting *_parent );
        ~dSettingStyle(){};
        virtual QWidget *createWidget();
    
    public slots:
    // ��� ������ �����.
        void styleActivated( const QString & text );
    // ����� ��������� ������...    
        void startStateChanged( int _state );
};

#endif // DCHATCPPLICATION_H

