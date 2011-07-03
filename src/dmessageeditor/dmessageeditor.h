#ifndef DMESSAGEEDITOR_H
#define DMESSAGEEDITOR_H

#include <QtGui>
#include "../net/duser.h"

class dSetting;
class dChatApplication;
class dSettingMessageEditor;

class dMessageEditor: public QMainWindow
{   
    Q_OBJECT
    private:

    QAction *actionSave,
            *actionTextBold,
            *actionTextUnderline,
            *actionTextItalic,
            *actionTextColor,
            *actionAlignLeft,
            *actionAlignCenter,
            *actionAlignRight,
            *actionAlignJustify,
            *actionUndo,
            *actionRedo,
            *actionCut,
            *actionCopy,
            *actionPaste;

    QComboBox   *comboStyle,
                *comboFont,
                *comboSize;

    // ������ ������ ���������.
        QString oldMsg;
    // �������� �� ������ ����������.
        dChatApplication *application;
    // ��������� �� ��������� ���������.
        dSettingMessageEditor * settingMessageEditor;
    // ������� - �����������......
        QSplitter *splitter;
    // ������ �������������, ��� ���� ������������� ������ ���������.
        QList<dPUser> to;
    // ������������, �� ����� ����� ����� ���������� ������ ���������.
        dPUser from;
    // �������� ��� ����������� ������ ���������.
        QTextEdit *oldMessageTextEdit;        
    // �������� ������ ���������.
        QTextEdit *newMessageTextEdit;       
    // �������� ��� ������� ���������.
        QComboBox *typeComboBox;
    // �������� ���� ����� ��� ��� �������� �������� ���������...
        QWidget * activeWindow;
    // ����, ���� �� �������,�� ���� ����� �������� �� ������.
    // ���� ��������, �� ���� �������� � ���� ���..
        bool showed;
    public:
        enum typeMessage {
            msg_personal  = 0x1,
            msg_mass = 0x2,
        };

    ///////////////////////// ����������� /////////////////////////////////////
    // _from - ��� ���������� ���������.
    // _to - ���� ���������� ���������.
    // _msg - ����� ����������� ���������.
        dMessageEditor( dSettingMessageEditor *_settingMessageEditor,
                        QList<dPUser> _to, 
                        dPUser _from, 
                        const QString &_msg,
                        const QString &_title,
                        typeMessage tm,
                        bool _showed = true,
                        bool _html=false,
                        QWidget *_parent = 0);
        ~dMessageEditor();
    
    protected:
    // ����������� ������� �� ��������.
        virtual void closeEvent ( QCloseEvent * _event );
    // ����������� ������� �� ������� �������, ���� �������� ������� CNTL+ENTER
        virtual void keyPressEvent ( QKeyEvent * _event );    
    // �� ��������!!!
        bool event ( QEvent * _event );
    public slots:
    // ���������� ��� ������� ������� "���������"....
        void clickedSendButton();
    // ����, ������� �� ����������� ��������.
        void splitterMoved( int pos, int index );
        
        void textBold();
        void textUnderline();
        void textItalic();
        void textAlign(QAction *);

        void textFamily(const QString &f);
        void textSize(const QString &p);
        
        void textColor();
        void saveMessage();
//    protected slots:
};
#endif // DMESSAGEEDITOR_H
