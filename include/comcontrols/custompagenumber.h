#ifndef _CLUSTERPAGENUMBER_H_
#define _CLUSTERPAGENUMBER_H_

#include <QtGui>
#include "custombtn.h"
#include "comcontrols_global.h"
class CustomBtnSELF;
class LCONTROLSSHARED_EXPORT CustomPageNumber : public QWidget
{
    Q_OBJECT
public:
    explicit CustomPageNumber(QWidget *parent = 0);
    ~CustomPageNumber();
    void setTitle(const QString &strTitle, const int sum);
    void setColor(const QColor & currentColor, const QColor & hoverColor);
    void setHomeAndLastText(const QString &home, const QString& last);

public:
    void setCurrentPage(int currentPageNumber);
    void setTotalPage(int totalPageNumber);
    void setCurrentAndTotalPage(int currentPageNumber, int totalPageNumber);
    void setBackgroundColor(const QColor & color);
    int  getCurrent() {return _currentPageNumber;}
    QRectF boundingRect();

protected:
    void paintEvent(QPaintEvent *event);
    void resizeEvent (QResizeEvent * event);

private:
    void updatePageNumber();

    QLabel *currentPageLabel;

    CustomBtnSELF *forwardBtn;
    CustomBtnSELF *backwardBtn;
    CustomBtnSELF *firstPageBtn;
    CustomBtnSELF *lastPageBtn;

    QPoint dragPosition;

    int _currentPageNumber;
    int _totalPageNumber;
    QColor backgroundColor;
    QString pageTitle;
    int sumNumber;
    QString _homeText;
    QString _lastText;
    QColor  _currentColor;
    QColor  _hoverColor;

signals:
    void currentPageChanged(int);
private slots:
    void slotForwardPage();
    void slotBackwardPage();
    void slotFirstPage();
    void slotLastPage();
};
/////////////////////////////////////////////////////////////
class LCONTROLSSHARED_EXPORT CustomPageNodeItem :  public QGraphicsProxyWidget
{
    Q_OBJECT
public:
    explicit CustomPageNodeItem(QGraphicsItem *parent = 0);

    void update(const int &sum, const int &cur = 0);
    void setCurrent(const int &cur);
    int getCurrent();
    void setSum(const int &sum);
    void setTitle(const QString &strTitle, const int sum);
    void setColor(const QColor & currentColor, const QColor & hoverColor);
    void setHomeAndLastText(const QString &home, const QString& last);
protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

signals:
    
    void choosePage(const int &page);
    void hoverEnter(bool);
private:

    CustomPageNumber* _nodes;
};


class LCONTROLSSHARED_EXPORT CustomBtnSELF : public QWidget
{
    Q_OBJECT
public:
    enum style {
        current_stay, normal
    };
    enum text_pos {
        left, right, top, bottom, center
    };
    explicit CustomBtnSELF(QWidget *parent = 0, const style &stl = normal);

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

    void setUnableColor(const QColor & color);
signals:

    void clicked();
    void clicked(CustomBtnSELF* btn);

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

    QColor unableColor;
};

#endif // CULSTERPAGENUMBER_H
