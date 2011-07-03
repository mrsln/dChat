#ifndef DSETTING_H
#define DSETTING_H

#include <QtGui>
#include <QtXml>

class dSetting : public QObject
{
    Q_OBJECT
    private:
    // �������� ��������.
        QString title;
        bool node;
    // ������ ��������������� ���������.
        QIcon icon;
    protected:    
    // ������� xml ������� �������� ��� ��������.
        QDomElement element;
        QDomElement parentElement;
    public:
    // �������� ������� xml ������
        QDomElement getXmlElement() const { return element; };
    //  ������� xml ������
        QDomElement getChildXmlElement( const QString & _childName );
    //  ������� xml ������
        QDomElement getParentXmlElement()const { return parentElement; };
    
    // ������ � ��������� ��������� �������� ���������.]
    // ������� ������������� ��� ��������.
        QString get(const QString &_elementName, const QString &_attributeName, const QString &_defValue = QString() );
        QString toString(const QString &_elementName, const QString &_attributeName, const QString &_defValue = QString() );
        int toInt(const QString &_elementName, const QString &_attributeName, int _defValue = 0 );
        QSize toSize( const QString &_elementName, const QSize &_defValue);
        QFont toFont( const QString &_elementName, const QFont &_defValue);
        QByteArray toByteArray( const QString &_elementName, const QByteArray &_defValue );
        void set(const QString &_elementName, const QString &_attributeName, const QString &_value);
        void set(const QString &_elementName, const QString &_attributeName, int _value);
        void set( const QString &_elementName, const QSize &_value);
        void set( const QString &_elementName, const QFont &_value);
        void set( const QString &_elementName, const QByteArray& _value);
    // �������������� ������� ���������� �������.
    // �������� _header ��������....
        void getHeaderSize( const QString &_elementName, QHeaderView *_header );
    // ��������� ������� ���������� �������.
    // �������� _header ��������....
        void setHeaderSize( const QString &_elementName, QHeaderView *_header );
        
    // key - �����, ������� �� ��������� ���� ���������������� ������� ���������.
    // �� ����� ���������� ��� ����� ��������� ����.
        dSetting( const QString &_key, QDomElement &_element, dSetting *_parent = 0 );
        dSetting( const QString &_key, dSetting *_parent );
        ~dSetting();

    // �������� �����.
        QString get_key() const;
    // ������ ��������.
        dSetting *parent () const;
    // ����� ������ �����.
        QList<dSetting*> children() const;
    // ����� ������ � ������.
        dSetting* findChild ( const QString & name) const;
    // ��������(����������) ��������� ���������.
        QString &getTitle( void ){ return title; };
        void setTitle( QString _title ){ title = _title; };
    // �������� ������� � ��������  �� ���������� ����.
        bool addChild( dSetting *_child, QString &_path = QString());

    // ��� �������� �������� �������� �� ��� ��������� ����� �����,
    // ��� �������� ������������ � ������� ����.
        bool isNode()const { return node; };
    // ����� ������������ ���������� ��������.
        void setNode( const bool &_node ){ node = _node; };

    // ��������(����������) ������ ���������������� ���������.
        const QIcon &getIcon() const { return icon; };
        void setIcon( const QIcon &_icon ){ icon = _icon; };
                            
    // ����� ����������� �������. ���������� ��������� �� ������,
    // � ������� ����� ������������� ���������� ��������.
    //  virtual QWidget *getWidget() = 0;
        virtual QWidget *createWidget(){ return 0; };
    
    // ����� ����������� �������. ���������� ���������.
    // virtual void activatingSetting() = 0;
    // ����������� �������. ��������� ���������.
        virtual void saveSetting();
    
    // ����� ����������� �������. ��������������� ���������.
    // virtual void restoreSetting() = 0;
        
    // ����� ������� ���� ���� ����������� ������ ��������.
        virtual void reParsing();
        
    signals:
    // ������ ������ ���������� ���� ����� ����������� ������ ��������.
        void reParsingSignal();
};
#endif // DSETTING_H
