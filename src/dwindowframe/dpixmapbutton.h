#ifndef DPIXMAPBUTTON_H
#define DPIXMAPBUTTON_H

#include <QtGui>
#include "dpixmapview.h"

class dPixmapButton: public dPixmapView
{
    Q_OBJECT
    private:
    // ��������� ���������� ������.
        bool active;
        
    // �������� ��� ������.
        QPixmap pm_disabled_button;         
        QPixmap pm_button;
        QPixmap pm_over_button;
        QPixmap pm_pressed_button;

    protected:
    // ���������� ������� QWidget.
        virtual void mousePressEvent( QMouseEvent * e );
        virtual void mouseReleaseEvent( QMouseEvent * e );
        virtual void mouseMoveEvent( QMouseEvent * e ){};   // ������ ����������.
        virtual bool event(QEvent * e );
    
    public:
        dPixmapButton( const QPixmap &_pm_button = QPixmap(),
                 QWidget *_parent = 0 );
    // ���������� ������ ��������� �������.
        void setOverButton( const QPixmap &_pm_over_button ); 
        void setButton( const QPixmap &_pm_button ); 
        void setDisabledButton( const QPixmap &_pm_disabled_button ); 
        void setPressedButton( const QPixmap &_pm_pressed_button ); 
        
        virtual QSize sizeHint () const;

    // ��������� ��������� �������.
        void setActive( bool _active);

// ��������� �������.
    signals:
        void clicked();
        void pressed();
};

#endif // DPIXMAPBUTTON_H
