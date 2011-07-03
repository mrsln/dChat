#ifndef DCHANNELWINDOW_H
#define DCHANNELWINDOW_H

#include <QtGui>

#include "../dwindow.h"
#include "../net/duser.h"

class dChatApplication;
class dSettingWindow;
class dSettingChannel;
class dMessageTable;

//********************************************************
// �������� ��������� ���
//********************************************************
class dMessageText;

class dChannelWindow : public dWindow
{   
    Q_OBJECT
    private:
        dWindowFrame *window;
        dChatApplication *application;
        
    // ����� ����, �������� ���� ��������.
        QAction *settingAct;

    // ��������� ���� ������.
        dSettingChannel *settingChannel;
    
    // �����������.
        QSplitter *splitter;
        QMainWindow *stackedWidget;
    // ��������� �������� � ��������.
        dMessageText *messageText;        
    // �������� �������.
        QTextEdit *editorMessage;
        
    public:
    // ������� � ��������.
        dMessageTable *messageTable;    

        dChannelWindow( dWindowFrame *_window );
        ~dChannelWindow();
        dWindowFrame *getWindowPtr() { return window; };
    
    // ������������� ����� ��������� ���������.
        void setViewMode( bool isTable );
        
    public slots:
    
        void addNameToEdit( const QString &_name );                    
    // ���� ������� ��������� ���� ������.
        void settingToggled( bool _clickable );
    
    // ��������� ��������� �� ������.
        void addMessage( dPUser _usr, const QString &_msg);
    // ��������� ��������� ���� "Me" �� ������.
        void addMessageMe( dPUser _usr, const QString &_msg);
};

#endif // DCHANNELWINDOW_H
