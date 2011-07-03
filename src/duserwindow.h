#ifndef DUSERWINDOW_H
#define DUSERWINDOW_H

#include <QtGui>

class dListViewEx;
class dWindowFrame;
class dChatApplication;
class dSetting;
class dSettingUserWin;

class dUserWindow : public QObject
{
    Q_OBJECT
    private:
    // ��������� �� ������ ���������....
        dChatApplication *application;
        void makeAction();

    // ��������� �� �������� ����.   
        dWindowFrame *window;
    // ��������� ��������.
        QAction *allParametersAct;
        QAction *viewBarAct;
        QAction *viewIconAct;
        QAction *viewListAct;
        QAction *viewTableAct;
        QAction *refreshAct;
        QAction *sendMessageAct;
        QAction *sendBeepAct;
        QAction *userInfoAct;
        QAction *userInfoRefreshAct;
        QAction *sendPersonalMassAct;
        QAction *sendMassAct;
        QAction *logWindowAct;

        QActionGroup *viewActGroup;
    
    // ��������� ����.
        dSetting *settingWindow;
        dSettingUserWin* settingUserWindow; // ��� ������.
        
    // ����������� ����� �������(������) ������ � ����� �������.
        QSplitter *splitter;

    // ������ �������� ��� ������������ ����.
        QList<QAction *> contextListAct;

    // ������ ������� ������� � ���������� ������ ������ �������������.
        dListViewEx *createBarListView( bool searched = false );
        QListView *createIconView( bool searched = false );
        QListView *createListView( bool searched = false );
        QTableView *createTableView( bool searched = false );
        
    // ������ � ������ �������������..
        QLabel *numberUserLabel;
    // ������ �������� � ��������������.
        QActionGroup *usersActionGroup;
    public:
    // ������� ����.....
        QMainWindow *listWidget;

    // ��������� ����...
        QMenuBar *menuBar;   // �������� 
        QMenu   *actionsMenu,
                *pluginsMenu,
                *windowMenu;
    // ��������� �� ���� � ��������������.
        QMenu   *usersMenu;
    // ���� ����.....
        QToolBar *windowToolBar;
    
    
    // ���������� ������ �������������.
        dListViewEx * userBarListView;
        QListView * userIconView;
        QListView * userListView;
        QTableView * userTableView;
        
    // ������ "��������" �������������.
        dListViewEx * searchBarListView;
        QListView * searchIconView;
        QListView * searchListView;
        QTableView * searchTableView;    

    // ��������� ���� ����.
        QToolBar *toolbar;
        QToolBar *searchBar;
        QToolBar *numberUserBar;
        
    // ��� ��� ������.
        QLineEdit*searchLineEdit;
    // ****
        QWidget *currentUserView;

        dUserWindow( dWindowFrame *_window );
        ~dUserWindow();

        dWindowFrame *getWindowPtr() { return window; };
    
    // ���������� ��������� �� ���� � ���������� ��������������.
        QMenu *getUsersMenu() const { return usersMenu; };
    // ���������� ��������� �� ���� � ���������� ��������������.
        QActionGroup *getUsersActionGroup() const { return usersActionGroup; };
    
    public slots:
    
    // ��� ���� �� ����� ������� ���.....
    // ������� ���������� �� dUserEx, ��� ���� ����� ��������
    // ������ �����.
        void searchWidgetUpdate();
    
        void closed();
        void minimized();
        void show();
        
    // ��� ������ ����� ���� "������".
        void viewBarToggled ( bool checked );
        void viewIconToggled ( bool checked );
        void viewListToggled ( bool checked );
        void viewTableToggled ( bool checked );
    // ��� ������� �� ������ ���������� ���������� ������.
        void refreshTriggered ( bool checked = false );
    // ��� ������� ���������� ���������� ���������� � ������������.
        void refreshInfoTriggered ( bool checked = false );
    // ���������� ����� ����� �������� ���������� � ������������.
        void userInfoTriggered ( bool checked = false );
    // ��� ������� ������ ��������� ������.
        void sendBeepTriggered ( bool checked = false );
    // ��� ������� ������ �������� ���������.
        void sendMessageTriggered ( bool checked = false );
    // ��� ������� ������ ������� �������� ���������.
        void sendMassTriggered ( bool checked = false );
    // ��� ������� ������ ������� ������������� �������� ���������.
        void sendPersonalMassTriggered ( bool checked = false );
    // ��� ������ ������������ ����.
        void customContextMenuRequested ( const QPoint & pos );
    // ��� ��������� ������ ������.
        void searchTextChanged( const QString & );
    // ���������� ��� ����� ����� �������������...
        void countUserChange( int _count );
    // ����, ������� �� ����������� ��������.
        void splitterMoved( int pos, int index );
    // ����, ������� �� ��������� �������� ������� � �������,
    // � ����������� �� ����������(��������).
        void tableHeaderResize( int logicalIndex, int oldSize, int newSize );
    // ���������� ��� ������� ������� ���� �� ������ �������������.
        void itemDoubleClicked ( const QModelIndex & index );
//        void viewHovered( QAction * action );
};

#endif // DUSERWINDOW_H
