#include "widget.h"
#include "ui_Widget.h"
#include<QCamera>
#include<QCameraViewfinder>
#include<QCameraImageCapture>
#include<QVBoxLayout>
#include<QMenu>
#include<QAction>
#include<QFileDialog>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->setupUi(this);
    mCamera = new QCamera(this);
    mCameraViewfinder = new QCameraViewfinder(this);
    mCameraImageCapture = new QCameraImageCapture(mCamera,this);
   mLayout = new QVBoxLayout ;


   mOptionsMenu = new QMenu("options",this);
    mAllumerAction= new QAction("allumer",this);
   mEteindreAction = new QAction("eteindre",this);
   mCapturerAction = new QAction("capturer",this);
   mOptionsMenu ->addActions({ mAllumerAction,mEteindreAction,mCapturerAction});
   ui->pushButton_options->setMenu(mOptionsMenu);
   mCamera->setViewfinder(mCameraViewfinder);
   mLayout->addWidget (mCameraViewfinder);
   mLayout->setMargin(0);

  ui->scrollArea->setLayout(mLayout);
   connect(mAllumerAction, &QAction:: triggered,[&]()
   {
       mCamera->start();

   });
   connect(mEteindreAction, &QAction::triggered,[&]()
   {
       mCamera->stop();

       });
       connect(mCapturerAction, &QAction::triggered,[&]()
       {
          auto filename = QFileDialog::getSaveFileName(this,"capturer","/","Image(*.jpg;*.jpeg)");
          if (filename.isEmpty())
          {
               return ;
          }
           mCameraImageCapture ->setCaptureDestination(QCameraImageCapture::CaptureToFile);
           QImageEncoderSettings imageEncoderSettings;
           imageEncoderSettings.setCodec("image.jpeg");
           imageEncoderSettings.setResolution(1600,1200);
           mCameraImageCapture -> setEncodingSettings(QImageEncoderSettings());
           mCamera->setCaptureMode(QCamera::CaptureStillImage);
           mCamera->start();
           mCamera->searchAndLock();
           mCameraImageCapture ->capture(filename);
           mCamera->unlock();

       });

}

Widget::~Widget()
{
    delete ui;
}
