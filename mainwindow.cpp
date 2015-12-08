#include "mainwindow.h"
#include <QtGui>
#include <QtGlobal>
#include <QDebug>


MainWindow::MainWindow(QWidget* parent):QWidget(parent)
{
    QSignalMapper *signalMapper = new QSignalMapper(this);
         connect(signalMapper, SIGNAL(mapped(int)), this, SIGNAL(buttonClicked(int)));
    textEdit=new QTextEdit;
    lineEdit=new QLineEdit;
    Advice=new QPushButton("Advice");
    Weather=new QPushButton("Weather");
    Reminder=new QPushButton("Reminder");
    Quit=new QPushButton("Quit");

  //  signalMapper->setMapping(lineEdit,4);
    //connect(lineEdit,SIGNAL(returnPressed()),signalMapper,SLOT(map()));

    signalMapper->setMapping(Advice,0);
    connect(Advice,SIGNAL(clicked()),signalMapper,SLOT(map()));

    signalMapper->setMapping(Weather,1);
    connect(Weather,SIGNAL(clicked()),signalMapper,SLOT(map()));

    signalMapper->setMapping(Reminder,2);
    connect(Reminder,SIGNAL(clicked()),signalMapper,SLOT(map()));

    signalMapper->setMapping(Quit,3);
    connect(Quit,SIGNAL(clicked()),signalMapper,SLOT(map()));
    connect(this,SIGNAL(buttonClicked(int)),this,SLOT(button(int)));
    layout = new QVBoxLayout;
    layout->addWidget(textEdit);
    layout->addWidget(lineEdit);
    layout->addWidget(Advice);
    layout->addWidget(Weather);
    layout->addWidget(Reminder);

    layout->addWidget(Quit);
    this->setLayout(layout);

    dialog=new QMessageBox;
    Yes=new QPushButton("Yes");
    No=new QPushButton("No");

    dialog->setText("Are you sure you want to quit?");

    dialog->setIcon(QMessageBox::Question);
    dialog->addButton(No,QMessageBox::ActionRole);
    dialog->addButton(Yes,QMessageBox::ActionRole);

    reminderMessage=new QMessageBox;
    check=new QCheckBox;
    OK=new QPushButton("OK");
    check->setText("Show this message again");

    reminderMessage->addButton(check,QMessageBox::ActionRole);
    reminderMessage->addButton(OK,QMessageBox::ActionRole);
    reminderMessage->setModal(1);


    QFile file("reminder.dat");

    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&file);

    while(!in.atEnd())
    {
    QString line;
    line.append(in.readLine());


    reminder.append(line);

    }

    if(reminder.last().endsWith('\\'))
    {
        textEdit->append("reminder.dat error");
        rError=1;

    }
if(!rError){
    for(int i=0;i<reminder.size();i++)
    {
        if(reminder[i].endsWith('\\'))
        {
            int j=i;
            reminder[j].chop(1);
            reminder[j]=reminder[j].append(reminder[i+1]);
            reminder[i+1].clear();
            i++;

            while(reminder[j].endsWith('\\'))
            {
            reminder[j].chop(1);
            reminder[j]=reminder[j].append(reminder[i+1]);
            reminder[i+1].clear();
            i++;

            }
        }
    }

    reminder.removeAll("");
    r=new QStringList;
    r[0]=reminder;
    //
}
    QFile file2("advice.dat");
    file2.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in2(&file2);
    QStringList advice;
    while(!in2.atEnd())
    {
    QString line;
    line.append(in2.readLine());


    advice.append(line);

    }
    if(advice.last().endsWith('\\'))
    {
        textEdit->append("advice.dat error");
        aError=1;

    }


    QFile file3("weather.dat");

    file3.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in3(&file3);
    QStringList weath;
    while(!in3.atEnd())
    {
    QString line;
    line.append(in3.readLine());


    weath.append(line);

    }
    if(weath.last().endsWith('\\'))
    {
        textEdit->append("weather.dat error");
        wError=1;

    }

}



void MainWindow::button(int i)
{

    if(i==0)
        handleAdviceButton();
    if(i==1)
        handleWeatherButton();
    if(i==2)
        handleReminderButton();
    if(i==3)
        handleQuitButton();
}


void MainWindow::handleAdviceButton()
{
    if(!aError){

    QFile file("advice.dat");

    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&file);
    QStringList advice;
    while(!in.atEnd())
    {
    QString line;
    line.append(in.readLine());


    advice.append(line);

    }

    for(int i=0;i<advice.size();i++)
    {
        if(advice[i].endsWith('\\'))
        {
            int j=i;
            advice[j].chop(1);
            advice[j]=advice[j].append(advice[i+1]);
            advice[i+1].clear();
            i++;

            while(advice[j].endsWith('\\'))
            {
            advice[j].chop(1);
            advice[j]=advice[j].append(advice[i+1]);
            advice[i+1].clear();
            i++;

            }
        }
    }
    advice.removeAll("");

    int random=qrand() % advice.size();
    textEdit->append(advice[random].prepend("Advice: "));
    }
}

void MainWindow::handleWeatherButton()
{
    if(!wError){

        QProcess p;
        QStringList params;
        QString scriptFile =  QDir::currentPath()+"/weather.py";
        qDebug()<<scriptFile;
        QString lineText="\""+lineEdit->text()+"\"";
        QString command= "python " + scriptFile+" -s "+lineText;
        p.start(command);
        p.waitForFinished(-1);

        QString p_stdout = p.readAll();
        qDebug()<<p_stdout;
        qDebug()<<p.errorString();
    QFile file("weather.dat");

    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&file);
    QStringList advice;
    while(!in.atEnd())
    {
    QString line;
    line.append(in.readLine());


    advice.append(line);

    }

    for(int i=0;i<advice.size();i++)
    {
        if(advice[i].endsWith('\\'))
        {
            int j=i;
            advice[j].chop(1);
            advice[j]=advice[j].append(advice[i+1]);
            advice[i+1].clear();
            i++;

            while(advice[j].endsWith('\\'))
            {
            advice[j].chop(1);
            advice[j]=advice[j].append(advice[i+1]);
            advice[i+1].clear();
            i++;

            }
        }
    }
    advice.removeAll("");
    ///RANDOMLY
    ///
    //
   for(int test_var=0;test_var<advice.size();test_var++)
     {
    //int random=qrand() % advice.size();
    textEdit->append(advice[test_var].prepend("Weather: "));

   }
    file.close();
}
}

void MainWindow::handleReminderButton()
{
    if(!rError){
if(!r[0].isEmpty()){
    message *message1;
    message1=new message;
    ran=qrand() % r[0].size();
    message1->label->setText(r[0].at(ran));
    message1->ran=ran;
    message1->reminder=reminder;
    message1->r=r;
    message1->show();

}
else{
    textEdit->append("There are no more reminders");
}
    }
}

void MainWindow::handleQuitButton()
{

    dialog->setFixedWidth(300);
    dialog->show();
    connect(Yes,SIGNAL(clicked()),this,SLOT(handleYesButton()));
    connect(No,SIGNAL(clicked()),this,SLOT(handleNoButton()));
}

void MainWindow::handleYesButton()
{
    dialog->close();
    this->close();
}

void MainWindow::handleNoButton()
{
    dialog->close();
}


message::message(QWidget *parent):QWidget(parent)
{


    layout=new QVBoxLayout;
    check=new QCheckBox;
    OK=new QPushButton("OK");
    check->setText("Show this message again");
    label=new QLabel;


    layout=new QVBoxLayout;
    layout->addWidget(label);
    layout->addWidget(check);
    layout->addWidget(OK);

    this->setLayout(layout);

    connect(OK,SIGNAL(clicked()),this,SLOT(handleOKButton()));
    connect(check,SIGNAL(clicked()),this,SLOT(handleCheck()));


}

void message::handleCheck()
{

}

void message::handleOKButton()
{


    if(!r[0].isEmpty()){
    if(!check->isChecked())
    {
        r[0].removeAt(ran);
    }

}
    this->close();

}
void MainWindow::handleReturn()
{
    QProcess p;
    QStringList params;
    qDebug()<<lineEdit->text();
    qDebug()<<"dsdasdsad";
    params << "weather.py -z 24060";
    p.start("python", params);
    p.waitForFinished(-1);
}
