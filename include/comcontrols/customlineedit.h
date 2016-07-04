#ifndef CUSTOMLINEEDIT_H
#define CUSTOMLINEEDIT_H
#include <QtCore>
#include <QtGui>

#include "comcontrols_global.h"
enum LineEditState{edit_normal = 0, edit_hover, edit_focus, edit_abnormal};
typedef struct LineEditImage{
   QImage*   left; 
   QImage*   right;
   QImage*   top;
   QImage*   bottom;
   QImage*   leftTop;
   QImage*   leftBottom;
   QImage*   rightTop;
   QImage*   rightBottom;
   LineEditState state;
   void scaled(const int& width, const int& height){
       *left = (*left).scaled(left->width(), height - leftTop->height() - leftBottom->height());
       *right = (*right).scaled(left->width(), height - rightTop->height() - rightBottom->height());
       *top = (*top).scaled(width - leftTop->width() - rightTop->width(), top->height());
       *bottom = (*bottom).scaled(width - leftBottom->width() - rightBottom->width(), bottom->height());
       
   }
} LineEditImage;
class CustomLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    CustomLineEdit(QString hint = "", QWidget *parent = NULL, const bool &showImg = true);
    ~CustomLineEdit();

    void setHint(const QString &hint)
    {
        _hint = hint;
        repaint();
    }

    void setError(const bool &error);
    bool isError() { return _error; }
signals:
    void focusIn();
protected:

    void paintEvent(QPaintEvent *event);
    void focusInEvent(QFocusEvent *event);
    void focusOutEvent(QFocusEvent *event);

    void enterEvent ( QEvent * event );
    void leaveEvent ( QEvent * event );
    void resizeEvent(QResizeEvent*);
private:

    void setState(LineEditState state);
    void loadImage(LineEditImage* image, QString left, QString right,
             QString top,  QString bottom, QString leftTop,QString leftBottom,QString rightTop,QString rightBottom);

    LineEditImage* creLineEditImage(LineEditState state);
    LineEditImage* getLineEditImage(LineEditState state);

private:

    QString _hint;

    bool _error;
    bool _focusFlag;
    bool _showImg;
    LineEditState _state;
    QList<LineEditImage*> _imageList;

};
#endif
