#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <QLabel>
#include <QMessageBox>
#include <QCheckBox>
#include <QLineEdit>
class MainWindow: public QWidget
{
    Q_OBJECT

public:
     explicit MainWindow(QWidget *parent = 0);

    QTextEdit *textEdit;
    QLineEdit *lineEdit;
    QPushButton* Advice;
    QPushButton* Weather;
    QPushButton* Reminder;
    QPushButton* Quit;
    QVBoxLayout *layout;
    QMessageBox *dialog;
    QPushButton *Yes;
    QPushButton * No;
    QMessageBox *reminderMessage;
    QPushButton *OK;
    QCheckBox * check;
    bool checkState;
    QStringList reminder;
    QMessageBox *test;
    QStringList *r;
    int ran;
    int error;
    bool rError;
    bool wError;
    bool aError;
signals:
    void buttonClicked(int i);
private slots:
    void button(int i);
    void handleAdviceButton();
    void handleWeatherButton();
    void handleReminderButton();
    void handleQuitButton();
    void handleYesButton();
    void handleNoButton();
    void handleReturn();
   // void handleCheck();
    //void handleOKButton();

};
class message:public QWidget
{
    Q_OBJECT
public:
    explicit message(QWidget *parent =0);
    QMessageBox *reminderMessage;
    QPushButton *OK;
    QCheckBox * check;
    QVBoxLayout *layout;
    QLabel *label;
    QStringList reminder;
    QStringList *r;
    int ran;
private slots:
    void handleCheck();
    void handleOKButton();
};

#endif // MAINWINDOW_H
