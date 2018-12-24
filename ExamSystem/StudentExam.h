#pragma once
#include <QList>
#include <QFile>
#include <QDialog>
#include <QVariant> 
#include <QTabWidget>
#include <QTableView>
#include <QHeaderView>
#include <QModelIndex>
#include <QStandardItem>
#include <QAbstractItemView>
#include <QStandardItemModel>
#include <QWidget>
#include "ui_StudentExam.h"
#include"StudentExamModel.h"

class StudentExam : public QWidget
{
	Q_OBJECT

public:
	StudentExam(QWidget *parent = Q_NULLPTR);
	~StudentExam();

private slots:
	void onTabChanged(int index);

	void dataGet(int examCode);

	void showChoice();

	void showMultichoice();

	void showJudge();

	void choicePrevious();

	void choiceNext();

	void multichoicePrevious();

	void multichoiceNext();

	void judgePrevious();

	void judgeNext();

	void choiceJump();

	void multichoiceJump();

	void judgeJump();

	void submit();

	void choiceStorage();

	void multichoiceStorage();

	void judgeStorage();

	void getScore();

private:

	Ui::StudentExam ui;
	QList<Choice> choice;
	QList<Choice> multichoice;
	QList<Judge> judge;
	QList<Choice> choiceAns;
	QList<Choice> multichoiceAns;
	QList<Judge> judgeAns;
	QStandardItemModel* choicemodel;
	QStandardItemModel* multimodel;
	QStandardItemModel* judgemodel;
	int choiceCurrent =0;
	int multichoiceCurrent = 0;
	int judgeCurrent = 0;
	int objectScore = -1;
	int judgeScore = -1;
};