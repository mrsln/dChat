#ifndef DTOPICWINDOW_H
#define DTOPICWINDOW_H

#include <QtGui>

#include "../dwindow.h"

class dChatApplication;
class dSetting;

class dTopicWindow : public dWindow
{   
    Q_OBJECT
    private:
        dWindowFrame *window;
        dChatApplication *application;
    public:
    // �������� ���������.
        QTextEdit *topicEditor;

        dTopicWindow( dWindowFrame *_window, QObject *_parent = 0);
        ~dTopicWindow();
        dWindowFrame *getWindowPtr() { return window; };

    public slots:
    
    // ������������� ����� ���������.
        void setTopic( const QString &_topic );

};

// ������� ������� ����� QTextEdit, ��� ��� ��� ���� ����������� �������
// ������� eNTER.
class dTopicTextEditEx : public QTextEdit
{
    Q_OBJECT
    private:
        dChatApplication *application;    
    // ������ � ���������� ���������.
        QWidget *topicEditor; 
    // ��������� ���� ��������� ���������.
        QTextEdit *topicEditorTextEdit;
    public:
        dTopicTextEditEx(  QWidget *_parent=0);
    protected:
        virtual void keyPressEvent ( QKeyEvent * _event );
    // ��� ���������� ��������.. ��� ������� ������� ����.
        virtual void mouseDoubleClickEvent ( QMouseEvent * _event );
    // ����� �������� ����� �����.
        void send( QString new_topic );

    public slots:
    // ������ ��������� ���������, ������� ������������ ����� �����.
        void clickedSendButton();
};

#endif // DTOPICWINDOW_H
