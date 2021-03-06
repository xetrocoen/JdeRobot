#include "velwidget.h"
#include <iostream>

VelWidget::VelWidget(QWidget *parent) :
    QWidget(parent)
{

    //setAutoFillBackground(true);

    setFixedSize(530, 230);

    vx = vy = vz = 0.0;

    setWindowTitle("Velocities");
    setUI();
}

VelWidget::~VelWidget(){}

void VelWidget::setSensors(Sensors* sensors){
    this->sensors=sensors;
}

void VelWidget::update()
{
    jderobot::NavdataDataPtr navdata = this->sensors->getNavdata();
    drawVelocitiesValues(navdata->vx,navdata->vy,navdata->vz);
}

void VelWidget::setUI()
{

    mainLayout = new QGridLayout();

    velXLabel = new QLabel();
    velXLabel->setObjectName(QString::fromUtf8("velXLabel"));
    velXLabel->setGeometry(QRect(10, 10, 51, 21));
    velYLabel = new QLabel();
    velYLabel->setObjectName(QString::fromUtf8("velYLabel"));
    velYLabel->setGeometry(QRect(220, 190, 51, 21));
    velZLabel = new QLabel();
    velZLabel->setObjectName(QString::fromUtf8("velZLabel"));
    velZLabel->setGeometry(QRect(370, 190, 51, 21));

    velXLabel->setText(QApplication::translate("VelWidget", "Lineal X", 0, QApplication::UnicodeUTF8));
    velYLabel->setText(QApplication::translate("VelWidget", "Lineal Y", 0, QApplication::UnicodeUTF8));
    velZLabel->setText(QApplication::translate("VelWidget", "Lineal Z", 0, QApplication::UnicodeUTF8));

    velLinZ = createDial(1);
    velLinZ->setGeometry(QRect(1050,400,150,150));

    velLinY = createDial(1);
    velLinY->setGeometry(QRect(900,400,150,150));

    velLinX = createDial(1);
    velLinX->setGeometry(QRect(750,400,150,150));

    mainLayout->addWidget(velLinX,0,0,Qt::AlignCenter);
    mainLayout->addWidget(velXLabel,1,0,Qt::AlignCenter);
    mainLayout->addWidget(velLinY,0,1,Qt::AlignCenter);
    mainLayout->addWidget(velYLabel,1,1,Qt::AlignCenter);
    mainLayout->addWidget(velLinZ,0,2,Qt::AlignCenter);
    mainLayout->addWidget(velZLabel,1,2,Qt::AlignCenter);


    setLayout(mainLayout);


}

QwtDial *VelWidget::createDial(int pos)
{
    QwtDial *dial = NULL;

    d_speedo = new SpeedoMeter(this);
    d_speedo->setRange(0.0,8.0);
    d_speedo->setLabel("m/s");
    d_speedo->setOrigin(180);
    d_speedo->setScaleArc(0.0,270.0);
    d_speedo->setScale(-1, 2, 1.0);
    dial = d_speedo;

    if ( dial )
    {
        dial->setReadOnly(true);
        dial->scaleDraw()->setPenWidth(3);
        dial->setLineWidth(4);
        dial->setFrameShadow(QwtDial::Sunken);
    }
    return dial;
}

void VelWidget::drawVelocitiesValues(float vlx,float vly,float vlz)
{
    //mm/sec to m/s
    float result=0.0;
   /* if(vlx<0.0){
        velXLabel->setStyleSheet("QLabel {background-color: red}");
    }else{
        velXLabel->setStyleSheet("QLabel {background-color: green}");
    }*/
    vlx=std::abs(vlx);
    vlx=vlx/1000.0;
    result=(0.6*vx)+((1-0.6)*vlx);
    velLinX->setValue(result);
    vx=vlx;

    /*if(vly<0.0){
        velYLabel->setStyleSheet("QLabel {background-color: red}");
    }else{
        velYLabel->setStyleSheet("QLabel {background-color: green}");
    }*/
    vly=std::abs(vly);
    vly=vly/1000.0;
    result=(0.6*vy)+((1-0.6)*vly);
    velLinY->setValue(result);
    vy=vly;

    /*if(vlz<0.0){
        velZLabel->setStyleSheet("QLabel {background-color: red}");
    }else{
        velZLabel->setStyleSheet("QLabel {background-color: green}");
    }*/
    vlz=std::abs(vlz);
    vlz=vlz/1000.0;
    result=(0.6*vz)+((1-0.6)*vlz);
    velLinZ->setValue(result);
    vz=vlz;
}
