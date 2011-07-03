#ifndef DMESSAGETABLE_H
#define DMESSAGETABLE_H

#include <QtGui>
#include "../net/duser.h"

class dChatApplication;

class dMessageItemWidget : public QStackedWidget
{
    private:
        QLabel *labelWidget;
        QTextEdit *editWidget;
            
    public:
        dPUser from;
        QString name;   
             
        dMessageItemWidget( const QString &_msg, QWidget * _parent = 0 );
        virtual QSize sizeHint () const;
    protected:
        virtual void mousePressEvent ( QMouseEvent * _event );
    //    virtual void keyPressEvent ( QKeyEvent * _event );
};

class dTextEditMessageEx : public QTextEdit
{
    private:
        dChatApplication *application; 
        dMessageItemWidget * messageItemWidget;   
    public:
        dTextEditMessageEx( dMessageItemWidget * _messageItemWidget ):messageItemWidget(_messageItemWidget),QTextEdit(_messageItemWidget){};
    protected:
        bool event ( QEvent * _event );
};

//******************************************************************
//                          dMessageTable
//******************************************************************
class dMessageTable : public QTableWidget
{
    Q_OBJECT
    private:
        dChatApplication *application;
        int scrollTimerID;

    // ��������, ������� ��� ������������ ����.
        QAction *sendMessageAct;
        QAction *sendBeepAct;
        QAction *userInfoAct;
        QAction *findToListAct;
        QAction *clearAct;
        
    // ������������ ���������� ����� � �������.
        uint maxString;
    // ������������ ���������� �������� � ����� ������������.
        uint maxName;
    // ����� ���������� ������������ �� �������� ��������� ������� ������ �������.
        dPUser getUserInTable();

    public:
        dMessageTable( QWidget * _parent = 0 );

    // ��������� ��������� �� ������.
        void addMessage( dPUser _from, const QString &_mgs);
    // ���������� ������������ ���������� ����� � �������.
    //    uint getMaximumString(){ return maxString; };
    // ������������� ������������ ���������� ����� � �������.
        void setMaximumName( uint _maxName ){ maxName=_maxName; };
    // ������������� ������������ ���������� ����� � �������.
        void setMaximumMessage( uint _maxString ){ maxString=_maxString; };

    protected:
        virtual void timerEvent ( QTimerEvent * _event );        
    // ��� ������� ����� �������� ������ �������.
        virtual void resizeEvent ( QResizeEvent * _event );
    
    public slots:
    // ���������� ��� ����� ���� �� ���������.
        void sectionClicked( int logicalIndex );
    // ����� ����� �������� �����
        void clearToggled( bool _clickable );
    // ���� ����� ����� ������������ � ������.
        void findToListToggled( bool _clickable );
    // ���� ����� ����� ������� ��������� ������������.
        void sendMessageToggled( bool _clickable );
    // �������� �����....
        void sendBeepToggled( bool _clickable );

    signals:
    // ������ �������� ���� ����� �������� ��� ������������ � ������ ��������������
    // ���������.
        void addNameSignal( const QString &_name );
};

#endif // DMESSAGETABLE_H

