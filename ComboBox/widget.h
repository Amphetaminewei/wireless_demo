#ifndef WIDGET_H
#define  WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QObject>
#include <QString>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

class ComboBox;
class NetWidget : public QWidget
{
    Q_OBJECT
public:
    NetWidget(QWidget* parent = nullptr, ComboBox* box = nullptr);

    void      mouseReleaseEvent(QMouseEvent*);
    void      mousePressEvent(QMouseEvent*);
    void      enterEvent(QEvent *event);
    void      leaveEvent(QEvent *event);

    void      setSsid(QString);
    void      setMAC(QString);
    void      setStrength(QString);
    void      setDevicePath(QString);
    void      setApPath(QString);
    QString   getSsid();
    ComboBox *getParentBox();

private:
    QLabel          *ssidLabel;
    QLabel          *strengthLabel;
    QLabel          *macLabel;
    QPushButton     *connBtnPwd;
    QPushButton     *connectBtn;
    QLineEdit       *pwdEdit;

    QVBoxLayout     *labelLayout;
    QVBoxLayout     *btnLayout;
    QHBoxLayout     *layout;
    ComboBox        *parentBox;
    QString          device;
    QString          ap;

public slots:
    void connBtn();
    void connBtnWithPwd();
};


#endif // WIDGET_H
