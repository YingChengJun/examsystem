#ifndef _MAINWINDOW_H
#define _MAINWINDOW_H

#include <QDebug>
#include <QAction>
#include <QtWidgets/QMainWindow>
#include <QAbstractItemView>
#include "ui_MainWindow.h"
#include "AddChoice.h"
#include "AddMultiChoice.h"
#include "AddJudge.h"
#include "QuestionBank.h"
#include "Exam.h"
#include "AddExam.h"
#include "AdminModel.h"
#include "ScoreReport.h"

class MainWindow : public QMainWindow {

	Q_OBJECT

public:
	MainWindow(QWidget *parent = Q_NULLPTR);
	~MainWindow();
	friend class LoginDialog;

signals: void sendExamCode(int code);

public slots:
	void receiveAddChoicePage(AddChoice*);
	void receiveAddMultiChoicePage(AddMultiChoice*);
	void receiveAddJudgePage(AddJudge*);

private slots:
	void dataRefresh();
	void showExamTable();
	void choiceTriggered();
	void judgeTriggered();
	void multichoiceTriggered();
	void goQuestionBankTriggered();
	void createExamTriggered();
	void setTableHeader(QStandardItemModel* model);
	void setExamTableItemView(QStandardItemModel* model);
	void examClicked(const QModelIndex& index);

private:
	Ui::MainWindowClass ui;
	AddChoice* choice;
	AddMultiChoice* multichoice;
	AddJudge* judge;
	AddExam* newexam;
	QuestionBank* questionbank;
	ScoreReport* scoreReport;
	QStandardItemModel* exammodel;
	QList<Exam> exam;
	int clickedExamCode;
};

#endif