#ifndef VMCONTROL_H
#define VMCONTROL_H

#include <QtCore>
#include <QtGui>

#include "comcontrols_global.h"

class LCONTROLSSHARED_EXPORT VmmComboBox : public QComboBox
{
//    Q_OBJECT
    
public:

    VmmComboBox(QWidget *parent = 0, QString hint = "");
    ~VmmComboBox();

    void setHint(const QString &hint)
    {
        _hint = hint;
        repaint();
    }

    void setError(const bool &error);
    //void setImgs(QImage *strLeft, QImage *strCenter,QImage *strRight);
    void setDefaultText(const QString &text) { _defaultText = text; }
    QString defaultText()    { return _defaultText; }
    void setDefault()        { setCurrentIndex(-1); }
    void resizeWidth(const int &width) { resize(width, height()); }
    void hidePopup() {QComboBox::hidePopup();}
protected:

    void paintEvent(QPaintEvent *event);
    void focusInEvent(QFocusEvent *event);
    void focusOutEvent(QFocusEvent *event);
private:

    void setImgs(QImage *img);

private:

    QImage *_input;
    QImage *_hover;
    QImage *_errorImg;

    QImage *_dropDownButton;

    QImage *_showImg;

    QString _defaultText;
    QString _hint;
    bool _error;

};

class LCONTROLSSHARED_EXPORT VmmTextEdit : public QTextEdit
{
    Q_OBJECT

public :

    VmmTextEdit(QString hint = "", QWidget *parent = NULL);
    ~VmmTextEdit();

    void setHint(const QString &hint)
    {
        _hint = hint;
        repaint();
    }

    void setError(const bool &error);

protected:
    void paintEvent ( QPaintEvent * event );
    void focusInEvent(QFocusEvent *event);
    void focusOutEvent(QFocusEvent *event);

private:

    QImage* _img;
    QString _hint;

    bool _error;

};

class LCONTROLSSHARED_EXPORT VmmLineEdit : public QLineEdit
{
    Q_OBJECT

public :

    VmmLineEdit(QString hint = "", QWidget *parent = NULL, const bool &showImg = true);
    ~VmmLineEdit();

    void setHint(const QString &hint)
    {
        _hint = hint;
        repaint();
    }

    void setError(const bool &error);
    bool isError() { return _error; }

    void resizeWidth(const int &width);

    void setImgs(const QString &img, const QString &hoverImg,
                 const QString &focusImg, const QString &abnormal);
signals:
    //void loseFocus();

protected:

    void paintEvent(QPaintEvent *event);
    void focusInEvent(QFocusEvent *event);
    void focusOutEvent(QFocusEvent *event);

    void enterEvent ( QEvent * event );
    void leaveEvent ( QEvent * event );

private:

    void setImgs(QImage *img);

private:

    QImage *_input;
    QImage *_hover;
    QImage *_focus;
    QImage *_abnormal;

    QImage *_center;

    QString _hint;

    bool _error;
    bool _focusFlag;
};

class CustomBtn;
class LCONTROLSSHARED_EXPORT VmmButtonLineEdit : public VmmLineEdit
{
    Q_OBJECT
public:

    VmmButtonLineEdit(QString hint = "", QWidget *parent = NULL, const bool &showImg = true) ;

    void setButtonText(const QString &text);
    QString buttonText();

    void setPreDsp(const QString &dsp);

    QString preDspText();
    void setSize();

signals:
    //void loseFocus();
    void buttonClicked();

protected:

    void paintEvent ( QPaintEvent * );

    void resizeEvent(QResizeEvent *event);

public slots:


private:

    CustomBtn* _btn;
    QLabel* _preDsp;
};
/********************************************************************/
class LCONTROLSSHARED_EXPORT BtnEdit : public QLineEdit
{
    Q_OBJECT
public:

    BtnEdit(QWidget *parent = 0);
    ~BtnEdit();

signals:

    void focusOut();

protected:

    void paintEvent(QPaintEvent *event);
    void focusInEvent(QFocusEvent *event);
    void focusOutEvent(QFocusEvent *event);

};

class LCONTROLSSHARED_EXPORT VmmLabel : public QLabel
{
    Q_OBJECT
public :

    VmmLabel(QWidget *parent = 0);
    ~VmmLabel();

    void setError(const bool &error);
    bool isError() { return _error; }

    void setColor(const bool &out);

    void resizeWidth(const int &width);

    void setButtonText(const QString &text);

    QString buttonText();

    void setPreDsp(const QString &dsp);
    void setLineEdit(const QString &text);

    QString preDspText();
    QString lineEditText();
    void setSize();

    void setLineEditShow(const bool &show);

signals:

    void textChanged(const QString &text);
    void focusOut();
    void buttonClicked();

public slots:

protected:

    void paintEvent(QPaintEvent *event);

    void resizeEvent(QResizeEvent *event);

private:

    void setImgs(QImage *strLeft, QImage *strCenter, QImage *strRight);

private:

    QImage *_inputLeft;
    QImage *_inputRight;
    QImage *_inputCenter;
    QImage *_hoverLeft;
    QImage *_hoverRight;
    QImage *_hoverCenter;
    QImage *_errorLeft;
    QImage *_errorRight;
    QImage *_errorCenter;

    QImage *_left;
    QImage *_center;
    QImage *_right;

    CustomBtn* _btn;
    QLabel* _preDsp;
    BtnEdit *_lineEdit;

    bool _error;
};

/*********************************************************************/
class LCONTROLSSHARED_EXPORT VmmSpinBox : public QSpinBox
{
    Q_OBJECT

public:

    VmmSpinBox(QWidget *parent = 0);
    ~VmmSpinBox();

public slots:

    void valChanged(int i);

protected:

    void paintEvent(QPaintEvent *event);
    void focusInEvent(QFocusEvent * event);
    void focusOutEvent(QFocusEvent *event);

    QValidator::State validate(QString &input, int &pos) const;
private:

    void setImgs(QImage *strLeft, QImage *strCenter, QImage *strRight);

private:

    QImage *_inputLeft;
    QImage *_inputRight;
    QImage *_inputCenter;
    QImage *_hoverLeft;
    QImage *_hoverRight;
    QImage *_hoverCenter;
    QImage *_errorLeft;
    QImage *_errorRight;
    QImage *_errorCenter;

    QImage *_upButton;
    QImage *_dropDownButton;

    QImage *_left;
    QImage *_center;
    QImage *_right;

};

class LCONTROLSSHARED_EXPORT VmmDoubleSpinBox : public QDoubleSpinBox
{
//    Q_OBJECT

public:

    VmmDoubleSpinBox(QWidget *parent = 0);
    ~VmmDoubleSpinBox();

protected:

    void paintEvent(QPaintEvent *event);
    void focusInEvent(QFocusEvent * event);
    void focusOutEvent(QFocusEvent *event);

private:

    void setImgs(QImage *strLeft, QImage *strCenter, QImage *strRight);

private:

    QImage *_inputLeft;
    QImage *_inputRight;
    QImage *_inputCenter;
    QImage *_hoverLeft;
    QImage *_hoverRight;
    QImage *_hoverCenter;
    QImage *_errorLeft;
    QImage *_errorRight;
    QImage *_errorCenter;

    QImage *_upButton;
    QImage *_dropDownButton;

    QImage *_left;
    QImage *_center;
    QImage *_right;

};


#endif
