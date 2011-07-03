#ifndef DCHATGEMSTONE_H
#define DCHATGEMSTONE_H

#include <QtGui>

class dManager;
class dChatApplication;
class dSetting;
class dChatPluginInterface;
class dUserWindow;
class dWindowFrame;

// ����� ������������� ��������� �������������� � ������� ����.
class dChatInterface
{
    private:
        dChatApplication *application;
    public:
        dChatInterface();
    // ���������� ��������� �� ��������� ����.
        virtual dManager *manager();
    // ���������� ��������� �� ������ ��������.
        virtual dSetting *settingGeneral();
    // ���������� ��������� �� ���� ��������� ��������.
        virtual dSetting *settingPlugins();
    // ���������� ������ �� ������ ����������� ��������.
        virtual QList<dChatPluginInterface*> &pluginList();
        
};

// ��������� �������������� � ������� ����� ���.
class dUserWindowInterface
{
    private:
        dUserWindow *userWindow;
    public:
        dUserWindowInterface();
    // ����� ���������� ��������� �� ������ �������� ����.
        virtual QMainWindow *mainWindow();
    // ���������� ��������� �� ����� ����.
        virtual dWindowFrame *windowFrame();
    // ��������� �� ��������� ����...
    // ���� �� ������� ����.
        virtual QMenu *windowsMenu();
    // ���� ��� ��������.
        virtual QMenu *pluginsMenu();
    // ���� �� ������� ��������� �������������.
        virtual QMenu *usersMenu();

    // ����������� �� ���� ��� � �������� ����.
        virtual QToolBar *windowToolBar();
};

// ��������� ��������� �������� �������������� ��������(������) � �����������
// ����... ������� ��������� ��� ������� ������ ������� ���� �� �����-����
// ������������.
class dContextUserMenuInterface
{
    private:
        dChatApplication *application;
    public:
        dContextUserMenuInterface();
        virtual void addWidget( QWidget *_widget );
        virtual void removeWidget( QWidget *_widget );
        
        virtual void addAction( QAction *_action );
        virtual void addActions( QList<QAction*> _actions );
        
};


class dChatGemstone  
{
    public:
        virtual operator dChatInterface*();
        virtual operator dContextUserMenuInterface*();
        virtual operator dUserWindowInterface*();
};

#endif // DCHATGEMSTONE_H

