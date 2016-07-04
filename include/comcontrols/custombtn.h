#ifndef CUSTOMBTN_H
#define CUSTOMBTN_H

#include <QWidget>
#include <QFont>
#include <QRadioButton>
#include <QUrl>
#include "comcontrols_global.h"

class LCONTROLSSHARED_EXPORT CustomLabel : public QWidget
{
    Q_OBJECT
public:
    explicit CustomLabel(QWidget* parent = 0);
    void setEnable(bool);
protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
public slots:
    void refresh();
signals:
    void clicked();
private:
    bool _enable;
    bool _bePressed;
    bool _beHovered;
};

class QLabel;
class LCONTROLSSHARED_EXPORT CustomBtn : public QWidget
{
    Q_OBJECT
public:

    enum style {
        current_stay, normal
    };


    enum text_pos {
        left, right, top, bottom, center
    };

    explicit CustomBtn(QWidget *parent = 0, const style &stl = normal);
    
public:

    void SetImgs(const QString &strHover, const QString &strNormal,
                 const QString &strDisable, const QString &strCurrent,
                 const int &imgWidth = -1, const int &imgHeight = -1);

    void SetHoverImg(const QString &strHover,
                     const int &imgWidth = -1, const int &imgHeight = -1);
    void SetNormalImg(const QString &strNormal,
                      const int &imgWidth = -1, const int &imgHeight = -1);
    void SetDisabledImg(const QString &strDisable,
                        const int &imgWidth = -1, const int &imgHeight = -1);
    void SetCurrentImg(const QString &strCurrent,
                       const int &imgWidth = -1, const int &imgHeight = -1);
    void setErrorImg(const QString &errorImg,
                     const int &imgWidth = -1, const int &imgHeight = -1);

    void setBackgroundColor(QColor backColor, QColor backHoverColor);

    void setBePressed(bool bpressd) {_bPressed = bpressd;}

    void setText(const QString &strText,
                 const QColor &textColor = Qt::white,
                 const QColor &textCurColor = Qt::white,
                 const QFont &font  = QFont("", 10, QFont::Normal),
                 const text_pos &text_pos = center,
                 const bool &underLine = false);

    void setTextShowLength(const int &len) { _textLength = len; }
    QString text();

    void setKey(const int &key) { _key = key; }

    void SetHover(const bool &bHover);

    void enabled(const bool &bEnable);
    void setCurrent(const bool &cur);
    void setError(const bool &err);

    int ID();
    void setID(const int &id);

    bool isHovered() { return _bHover; }

    void setToolTipText(const QString &text) { _tooltipText = text; }
    void showGif(const bool &Gif = true);
    void setGif(const QString &fileName);

    void clearState();

    void setData(void* data) { _data = data; }
    void* data() { return  _data; }

signals:
    
    void mousePressed();
    void clicked();
    void clicked(CustomBtn* btn);

public slots:

    void currentRelease();

public:

    void resizeEvent ( QResizeEvent * event );
    void focusOutEvent ( QFocusEvent * event );
    void focusInEvent ( QFocusEvent * event );

    void mouseReleaseEvent ( QMouseEvent * event );
    void mousePressEvent ( QMouseEvent * event);
    void enterEvent ( QEvent * event );
    void leaveEvent ( QEvent * event );
    void paintEvent(QPaintEvent *event);

    void closeEvent ( QCloseEvent * event );
    void keyPressEvent ( QKeyEvent * event );
    void setCurentStyle(style state) {_style = state;}

private:

    QString _strHover;
    QString _strNormal;
    QString _strDisable;
    QString _strCurrent;//选中时的图片
    QString _errorImg;//错误提示时的图片

    QPixmap _hoverImage;
    QPixmap _normalImage;
    QPixmap _disableImage;
    QPixmap _currentImage;
    QPixmap _errorNoteImage;

    bool _bHover;//是否在窗口上
    bool _bEnabled;//是否可用
    bool _bPressed;//是否被选中
    bool _bCurrent;//是否停留选中状态
    bool _bError;//是否为提示状态
    bool _textUnderLine;

    QString _text;
    QString _showText;
    int _id;

    style _style;

    QColor _textColor;
    QColor _textHoverColor;

    QColor _backColor;
    QColor _backHoverColor;
    bool _fillColor;

    QFont _font;

    int _key;

    text_pos _text_pos;

    int _textLength;

    QString _tooltipText;

    QLabel* _movieLabel;
    QMovie* _movie;
    void* _data;
};


class LCONTROLSSHARED_EXPORT CustomRadioButton: public QRadioButton
{
    Q_OBJECT
public:

    CustomRadioButton(QWidget * parent = 0);

    void setData(void* data) {_data = data;}
    void* data() { return _data;}

    void setText(const QString &text, const QColor &textColor = Qt::black);

signals:

    void checked(void *data);

public slots :

    void choosen(const bool &che);
protected:
    void paintEvent ( QPaintEvent * );

private:

    QColor _textColor;
    void* _data;
    QString _text;
    int _showTextCount;
};

#endif // CUSTOMBTN_H
