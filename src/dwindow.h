#ifndef DWINDOW_H
#define DWINDOW_H

#include <QtGui>

class dWindowFrame;
class dChatApplication;
class dSetting;
class dSettingWindow;

class dWindow : public QObject
{
    Q_OBJECT
    private:
    // ����� ����, ������� ���������� ��������� ����� ����.
        QAction *windowAct;
    // �������� �� ����� ����.
        dWindowFrame *windowFrame;
    // ��������� �� ����������.
        dChatApplication *application;
    // ��������� ����.        
        dSetting *settingWindow;
        
    public:
        dWindow(const QString &settingKey, dWindowFrame *_windowFrame, QObject *_parent = 0 );
        ~dWindow();
    
    // ���������� QAction ����� ����.
        QAction *getWindowAct()const{ return windowAct; };
    // ������ ������������� �������� ����.
        void setTitle( const QString & _title );
        void setIcon( const QIcon & _icon );
    // ����� ���������� ��������� ����.
        dSetting *getSettingWindow()const{ return settingWindow; };
    // ���� ����� ����������� ���� ��� ������.
        void start();
        
    public slots:
        void hide();        
        void show();
        void lower();
        void setVisible( bool _visible );
        bool isVisible() const;
        
    signals:
    // ������ ���������� � ��� ������ ���� ����� �������� ���� �������������
    // � ��� ��� ��������� ���� ������.
        void hideSignal( bool checked = false );
};
#endif // DWINDOW_H
