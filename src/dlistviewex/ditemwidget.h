#ifndef DITEMWIDGET_H
#define DITEMWIDGET_H

#include <QtGui>

class dItemWidget : public QWidget
{
    // ��������� �� ������(QLabel) � �������.... 
        QLabel *label_avatar;
    // ��������� �� ������(QLabel) � ����������� � ������������.... 
        QLabel *label_info;
        
        QString name;
        QString ip;
        QString host;
        QString version;
        QString login;
        QString auto_answer;
    
    // ���� ����������� ������.
        QColor selectColor;
    // ���� ���� ������.
        QColor bgColor;
        
    public:
        dItemWidget( QWidget *parent = 0 );
        void set();
    // ������������� ��������� ������������ �� �����������.
        void set_name( QString _name );
        void set_ip( QString _ip );
        void set_host( QString _host );
        void set_login( QString _login );
        void set_version( QString _version );
        void set_auto_answer( QString _auto_answer );
        void set_avatar( QIcon _avatar );

    // ������������� ��� ��������� ������������
        void set_all( const QString &_name, 
                      const QString &_ip, 
                      const QString &_host,
                      const QString &_version,
                      const QString &_login,
                      const QString &_auto_answer,
                      const QIcon   &_avatar);
    // ���������� ��� ��������� ������, ������� ������������ ����� ������������.
        void select();
    // ���������� ��� ������ ��������� � ������.
        void unselect();
    
    // ������������� ���� ��������� ������.
        void set_select_color( const QColor & _selectColor ){   
                    if( selectColor != _selectColor ) 
                    {
                        selectColor = _selectColor;
                        select();
                    }
                };
    // ������������� ���� ���� ������.
        void set_background_color( const QColor & _bgColor ){ 
                    if( _bgColor != bgColor ) 
                    {
                        bgColor = _bgColor;
                        unselect();
                    }
                };
};

#endif // DITEMWIDGET_H
