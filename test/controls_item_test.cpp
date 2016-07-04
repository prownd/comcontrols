#include <QApplication>
#include <QWidget>
#include "custombtn.h"

int main(int argc,char* argv[]){
    QApplication app(argc,argv);
    QWidget w;
    w.resize(300,400);
    
    
    //CustomLabel* label=new CustomLabel(&w);
    //label->setEnable(true);
    //custombtn;
    CustomBtn * btn=new CustomBtn(&w);
    btn->SetImgs(":/resources/images/btn15_bg_hover.png",":/resources/images/btn15_bg.png","","");
    btn->SetHover(true);
    btn->setCursor(Qt::ArrowCursor);
    btn->move(100,100);
    btn->show();
    

    //custom radio button
    CustomRadioButton * rbtn=new CustomRadioButton(&w);
    rbtn->setText("radiobtn1");
    rbtn->move(95,130);
    rbtn->show();

    w.show();
    return app.exec();
}
