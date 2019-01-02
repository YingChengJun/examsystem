#ifndef _STUDENTWINDOW_H
#define _STUDENTWINDOW_H

#include <QList>
#include <QFile>
#include <QDialog>
#include <QVariant> 
#include <QTabWidget>
#include <QModelIndex>
#include <QStandardItem>
#include <QAbstractItemView>
#include <QStandardItemModel>
#include <QTableView>
#include <QHeaderView>
#include "User.h"
#include "Question.h"
#include "StudentExam.h"
#include "ui_StudentWindow.h"


class StudentWindow : public QDialog {

	Q_OBJECT

public:
	StudentWindow(QWidget *parent = Q_NULLPTR);
	~StudentWindow();
	void dataGet();
	void showExam();
	void showStudent(QString username);
	friend class LoginDialog;

signals: void sendExamInformation(QString , int);

public slots:
	void receiveUserName(QString name);

private slots:
	void examTableClicked(const QModelIndex&);
	void dataRefresh();

private:
	Ui::StudentWindow ui;
	QList<Config> exam;
	QString userName;
	QStandardItemModel* examModel;
	StudentExam newExam;

};

#endif