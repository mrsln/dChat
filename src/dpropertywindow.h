#ifndef DPROPERTYWINDOW_H
#define DPROPERTYWINDOW_H

#include <QtGui>
#include "dsetting.h"

class dPropertyWindow : public QMainWindow
{   
    Q_OBJECT
    private:
    
        QHash<dSetting* ,QTreeWidgetItem *> itemForSetting;
        
        dSetting *setting;
        dSetting *curentSelectedSetting;
        void parseSetting( dSetting *_seting, QTreeWidgetItem *parentItem = 0);
    
    // ������ �� ������� ����������.
        QTreeWidget * contentsTree;
    // ������ �� ������� ���� ��� ��������.
        QScrollArea * propertyList;
        QWidget * propertyList_second;

    // ���� � ������� ��������.
        QDockWidget * contentsWidget;
    protected:
        virtual void hideEvent ( QHideEvent * event );
        
    public:
        dPropertyWindow(dSetting *_seting ,QWidget * _parent = 0, Qt::WFlags _flags = 0);
        ~dPropertyWindow();
    // ��� ����� ���, ��������.....
        void setSeting(dSetting *_setting){ setting = _setting; };
        dSetting *getSeting(){ return setting; };
        
        
    public slots:
        void openSetting();
        void saveSetting();
        void closeSideWindow( bool _checked );

    // ����� ������ ����� ���� ���������� �� ������ ���������.
    // � �������� ����� �.
        void goSetting( dSetting *_setting );

    // ���������� ����� ���� ����������� ������ ��������.
        void reParsing();    

    protected slots:
        void itemChanged( QTreeWidgetItem * current, QTreeWidgetItem * previous  );
    
};

#endif // DPROPERTYWINDOW_H
