#ifndef DWINDOWFRAME_H
#define DWINDOWFRAME_H

#include <QtGui>

#include "dpixmapbutton.h"
#include "dpixmapview.h"

class dWindowFrame;         // ������ ����.... � ���� �� �����. 
class dWindowFrameResize;   // ������ ����.... � ���� �� �����.
class dWindowConnection;    // ������ ����.... � ���� �� �����.
class dEmptyFrame;          // ������ ����.... � ���� �� �����.

Q_DECLARE_INTERFACE(dWindowFrame,"dWindowFrame/1.0")

/****************************************************************
    ����� dWindowFrame.
    ����� ��������� ���� � ������������� ������, ������� �����������
 �� ��������� ����������� ������(������). ����� ������ ����� ������
 ���������� ����� ����������, �� ���� ��� ������� ��������� ���� ����
 � ������ ��� ����������� (����� ����� �� ��� � � Winamp). ����
 ����� ���� ���� ��������� "�������" (����� setLeading), �� ��� ��� 
 �����������, ����� ��� �� ����������� ��� ����������� � ��� ����.
    ��������� ��������� ���� ���������� ���� ������ �� ������
 ������ ����.(���� ��� ����������� ������������� ������!).
*****************************************************************/
class dWindowFrame : public QWidget
{
    Q_OBJECT
    Q_INTERFACES(dWindowFrame)
    private:
    // ������ ����� ������(�������� ��������� ������). 
        static QList<QWidget*> dwindows_list;          
    // ���������� ��������� ����, ����� ��� ����������� ����.
        int dx,dy;
    // ��������� �� �� ��� ��� ���� �����������........ ���� independented = true
        bool independented;
    // �������� � ������������ �����.
        QPixmap pm_hat_left_active;
        QPixmap pm_hat_left_not_active;
        QPixmap pm_hat_center_active;
        QPixmap pm_hat_center_not_active;
        QPixmap pm_hat_right_active;
        QPixmap pm_hat_right_not_active;
    // ��������� �� ������ ����� �����. ����� ��� ��������� ����� 
    // ����������.
        dPixmapView *hat_left_image;
        dPixmapView *hat_center_image;
        dPixmapView *hat_right_image;
    // ��������� �� ������ � �����.
        dPixmapButton *close_button;
        dPixmapButton *min_button;
        dPixmapButton *max_button;
    // ��������� �� �����;
        dPixmapView *frame_left;
        dPixmapView *frame_right;
    // ����������� Widget � ����� ����, ��������� ��� ������������� �
    // ����� ����.
        dEmptyFrame *center_frame;  
    // ��������� �� �������� �� ������ ����.
        dPixmapView *status_bar_left;
        dPixmapView *status_bar_center;
        dWindowFrameResize * status_bar_right;

    // ���� ������� ��������� ��������� ���� � ���� ����. 
     //   QWidget *task_bar_window;

    // ������ ���� ��������( �� ��������), �� ���� ������ �������� 
    // � �����.
        void activate();
        void deactivate();
    // ����, ������� ����������, �����-�� �������� ��������� ����.
        bool title_visibility;

        QString skin_dir;       // ����������, ��� ����� ���� � ini-���� 
                                // c �����������.
        QString skin_ini_file;  // ��� ini-����� c ����������� skin-�.
    
    // ������� ������������. ���������� �������� ����� �������� �����������
    // ��������������� ����.
        int magnet;

    // ������ �������� �����, ����� ��� �� ����� ��� ������ � ������.
        QDesktopWidget desktop;

    // ����... ��������������� � true ����� �������������� ����. ����� 
    // ���������� ����� ������� ���� ����� �������������� � false.
        bool moved;

    // ���� ����������, ������� �� ��� ����.
        bool leading;
    // ��������������� �������. ��������� ������� ���������� � ������� ������,
    // � ���� ����� ��� ���������� �� ��� ��� ������.
        void checkConnection();
        
    // ��� ������� ����� ����, ����������� ������ ���� ������� ��������� �
    // ������� �����. ���� ��� ���� �� �������� �������, �� ���� ������ ��������
    // ������.
        QList<QWidget*> moveable_windows_list;          

    // ���� ���������� ��������� ������ ������������ ����.
        bool min_button_visible;
    // ���������� ����������� �����, �� ������ ��� ������ �������������.
        bool max_button_visible;
    
    protected slots:
    // �������� ����������� �����... �� �������� ������� ���� �� ����.
         void pressMinimizedKey();
         void pressMaximizedKey();
         void pressClosedKey();
    
        
    protected:
    // ���������� �������. �������������� �� ������ QWidget.
        virtual void mousePressEvent ( QMouseEvent * _event );
        virtual void mouseMoveEvent( QMouseEvent * _event );
        virtual void mouseReleaseEvent ( QMouseEvent * _event );
        virtual bool event( QEvent * _event );
        virtual void hideEvent ( QHideEvent * event );
        virtual void showEvent ( QShowEvent * _event );        
        
    // �������� �������, ������� ���������� ��� �������� ����(������� �� ������
    // � �������), ��� ������� �� ������ ������������ ����, � ��� ������� ��
    // ������ ������������� ���� �� ���� �����.
    signals:
        void minimized();
        void maximized();         
        void closed();

    public:
        dWindowFrame( QWidget *parent=0 );
    // �����������, �� ��� ����������.
        virtual ~dWindowFrame();

    // ���������� ������� ������������, �� ��������� � ��������, �� �������
    // ���������� ���������� ��������������� ���� ����.
        virtual uint getMagnet();
    // ������������� ������� ������������.
        virtual void setMagnet( uint _magnet );
    // ��������� ������ ��������� ����.
        virtual void setFontWindowTitle( const QFont & _title_font );
    // ����� ���������� ����� ��������� ����.
        virtual const QFont &getFontWindowTitle() const;
    // ��������� ����� ����� ����.
        virtual void setSkin( const QString &_skin_ini_file );
    // ����� ���������� ��� ����� � ������������� �����.
        virtual QString getSkin() const;
    // ����� ������� ����, � ��������� ����������� ����.
        virtual void clearSkin();
    // ��������� ������������ Widget-� ������� ����.
        virtual void setCentralWidget ( QWidget * widget );
    // ������������� ������������ ���� � ���� ����.
        virtual void setLayout ( QLayout *layout );
    // ���������� ���������� ��������. ���������, ����� ������� ����������
    // ��������� ��������� ��������.
        virtual void setSizeIncrement( const QSize & _size );
        virtual void setSizeIncrement( int _width, int _height );
    // ������ ��� ���� ������� ( true - ������� ).
    // ���� ���� �������, �� ��� �������������� ����� ����, ����� ��� ��
    // ����������� ��� ������������� � ���� ����.
        virtual void setLeading( bool _leading = true );
        virtual bool getLeading();
    // ������������� ��������� ������ ������������ ����.
        virtual void setMinButton( bool _min_button = true );
        virtual bool getMinButton();
    // ������������� ��������� ������ ������������� ����.
        virtual void setMaxButton( bool _max_button = true );
        virtual bool getMaxButton();
    // ������������� ����������� ���������� ����, ����� ��� �� ����� �����,
    // � �� ������ �� �����.
        virtual void overloadMoveEvent( bool _overload = true );
    // ����� ������ ���� �����������, ������ ��� �� ���������������� � ���� ��������.
        virtual void setIndependent( bool _independented = true );

    // ������� ����� ����... ������ �������� �������� new dWindowFrame( _parent ),
    // ��������� ��� ������ ������� Qt. ������� �������� �������� ����� 
    // ��������� ������ ���� ������ ����� ������, � ����� ��� �� ��������
    // ��� ������������. ��� �������!
        virtual dWindowFrame *make( QWidget *_parent = 0);
        
};

/****************************************************************
    ����� dWindowFrameResize
    ��������������� �����. ��������� ������ ���������� �������� �
 �����. �������� �������� dPixmapButton.
*****************************************************************/
class dWindowFrameResize: public dPixmapButton
{
    private:
    // ���������� ����.
        int x,y;
    // ��� ���������� ��������.
        QSize step;
        
    protected:
    // ���������� �������.
        virtual void mousePressEvent( QMouseEvent * e );
        virtual void mouseMoveEvent( QMouseEvent * e );
    public:
        dWindowFrameResize( const QPixmap &_pm_button,
                            QWidget *_parent = 0);
        void setStep( const QSize &_step );
        void setStep( int _width, int _height );
        
};

/****************************************************************
    ����� dWindowConnection
    ��������������� �����. ��������� ���������� �������������� ����.
 �������� ��������� ���� ���� ������� ��������� � ��������� ���� �
 ������. �� ���� ������ ������ ���� ������ ��������� ����� �����,
 ������ �������� �������� ����(��������� �� ���).
*****************************************************************/
class dWindowConnection
{
    public:
    // ������ ����������. 
        static QList<dWindowConnection> dwindows_connection;

        QWidget * winA;
        QWidget * winB;
    
        dWindowConnection(QWidget *_winA,QWidget *_winB);
        bool operator ==( const dWindowConnection& _connection ) const;
        bool operator ==( QWidget *_win ) const;
        
    // ����� ���� ����������� � ��������� ����� �� ������.
        static QList<QWidget*> findWindows( QWidget *_win );
    // ����� ���� ����������� � ��������� ����� �� ����� ��� ��������,
    // �� ���� ����������� ������� ����.
        static void globalFindWindows( QWidget *_win, QList<QWidget*>&_global_win_list );
};

/****************************************************************
    ����� dEmptyFrame
    ��������������� �����.
    ����� ��������� ������ �����(���� ��� �����), ������� �� 
 ��������� ��������� ��� ������������ � ������ ������ ����.
 ��� �������� ������������, ��� ���� ��� �� ����������� �������
 ����, ������� �� ����� ����������� �� ������, �� ���� dWindowFrame.
*****************************************************************/
class dEmptyFrame: public QFrame
{
    private:
        bool overload;
    protected:    
        virtual void mousePressEvent ( QMouseEvent * _event );
        virtual void mouseMoveEvent( QMouseEvent * _event );
        virtual void mouseReleaseEvent ( QMouseEvent * _event );  
        
    public:
        void overloadMoveEvent( bool _overload = true );
        dEmptyFrame( QWidget *_parent = 0, Qt::WFlags _f = 0 ):
                QFrame(_parent,_f),overload(false){};
};

#endif // DWINDOWFRAME_H
