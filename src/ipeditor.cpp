#include "ipeditor.h"

#include <QPainter>
#include <QGraphicsProxyWidget>
#include <QValidator>

const int CELL_WIDTH = 46;
const int CELL_HEIGHT = 36;

const int CELL_SPACE = 3;

EditorSubItem::EditorSubItem(QGraphicsItem *parent)
    : _focusIn(false)
    , _enabled(false)
{
    setAlignment(Qt::AlignHCenter);
    _normal.load(":/resources/images/input_small.png");
    _disable.load(":/resources/images/input_small_disabled.png");
    _focus.load(":/resources/images/input_small_focus.png");

    setContextMenuPolicy(Qt::NoContextMenu);
    _proxy = new QGraphicsProxyWidget(parent);
    _proxy->setWidget(this);

    QValidator* validator = new QIntValidator( 0, 255, this );
    this->setValidator( validator );

    this->setEnabled(_enabled);
    setStyleSheet("QLineEdit{border-width:0;border-style:outset;background-color: rgba(0,0,0,0)}");
}

void EditorSubItem::paintEvent ( QPaintEvent * event)
{
    QPainter painter(this);

    if (!_enabled)
        painter.drawPixmap(QRect(0,0,CELL_WIDTH, CELL_HEIGHT), _disable);
    else if (_focusIn)
        painter.drawPixmap(QRect(0,0,CELL_WIDTH, CELL_HEIGHT) , _focus);
    else
        painter.drawPixmap(QRect(0,0,CELL_WIDTH, CELL_HEIGHT), _normal);

    QRect rt = rect();
    painter.setPen(QPen(Qt::black));
    painter.drawText(rt.translated(0,0), Qt::AlignCenter| Qt::AlignVCenter | Qt::TextHideMnemonic, text());
    QLineEdit::paintEvent(event);
}

void EditorSubItem::focusInEvent ( QFocusEvent * event )
{
    _focusIn = true;
    QLineEdit::focusInEvent(event);
}

void EditorSubItem::focusOutEvent ( QFocusEvent * event )
{
    _focusIn = false;
    QLineEdit::focusOutEvent(event);
}

///////////////////////////////////////////////////
IPEditor::IPEditor(QGraphicsItem *parent)
    : QGraphicsItem(parent)
{
    _ip.append(new EditorSubItem(this));
    _ip.append(new EditorSubItem(this));
    _ip.append(new EditorSubItem(this));
    _ip.append(new EditorSubItem(this));

    for (int i = 0;i < _ip.count();i++) {
        _ip[i]->move((CELL_WIDTH + CELL_SPACE) * i, 0);
        _ip[i]->resize(CELL_WIDTH, CELL_HEIGHT);
    }

}

QRectF IPEditor::boundingRect() const
{
    return QRectF(0,0, CELL_WIDTH * 4 + 10,CELL_HEIGHT);
}

void IPEditor::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
           QWidget *widget)
{
    painter->drawLine(CELL_WIDTH, CELL_HEIGHT / 2, CELL_WIDTH + 2, CELL_HEIGHT / 2);
    painter->drawLine(CELL_WIDTH * 2 + CELL_SPACE, CELL_HEIGHT / 2, CELL_WIDTH * 2 + CELL_SPACE + 2, CELL_HEIGHT / 2);
    painter->drawLine(CELL_WIDTH * 3 + CELL_SPACE * 2, CELL_HEIGHT / 2, CELL_WIDTH * 3 + CELL_SPACE * 2 + 2, CELL_HEIGHT / 2);
}

QString IPEditor::getVal()
{
    for (int i = 0;i < _ip.size();i++)
        if (_ip.at(i)->text().isEmpty())
            return "";

    return QString("%1.%2.%3.%4").arg(_ip[0]->text()).arg(_ip[1]->text()).arg(_ip[2]->text()).arg(_ip[3]->text());
}

void IPEditor::setVal(const QString &val)
{
    QStringList vals = val.split(".");
    for (int i = 0;i < vals.size();i++) {
        if (i >= _ip.size())
            return;
        _ip[i]->setText(vals.at(i));
    }
}

void IPEditor::setEnableEdit(const bool &enable)
{
    for (int i = 0;i < _ip.count();i++)
        _ip[i]->setEnableEdit(enable);
}

void IPEditor::setSubValidator(int index, QValidator* validator)
{
    if (index >= 0 && index < _ip.size()) {
        validator->setParent(_ip.at(index));
        _ip.at(index)->setValidator(validator);
    }
}
