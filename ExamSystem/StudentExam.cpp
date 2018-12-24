#include "StudentExam.h"


StudentExam::StudentExam(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setWindowFlags(Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint); //������С����ť�͹رհ�ť
	StudentExam::dataGet(3);  //�����ݿ�����ȡ��Ŀ
	StudentExam::onTabChanged(0); //Ĭ����ʾ��ѡ��

	connect(this->ui.tabWindow, SIGNAL(currentChanged(int)), this, SLOT(onTabChanged(int)));
	connect(this->ui.choicePrevious, SIGNAL(clicked(bool)), this, SLOT(choicePrevious()));
	connect(this->ui.choiceNext, SIGNAL(clicked(bool)), this, SLOT(choiceNext()));
	connect(this->ui.multichoicePrevious, SIGNAL(clicked(bool)), this, SLOT(multichoicePrevious()));
	connect(this->ui.multichoiceNext, SIGNAL(clicked(bool)), this, SLOT(multichoiceNext()));
	connect(this->ui.judgePrevious, SIGNAL(clicked(bool)), this, SLOT(judgePrevious()));
	connect(this->ui.judgeNext, SIGNAL(clicked(bool)), this, SLOT(judgeNext()));
	connect(this->ui.choiceNum, SIGNAL(returnPressed()), this, SLOT(choiceJump()));
	connect(this->ui.multichoiceNum, SIGNAL(returnPressed()), this, SLOT(multichoiceJump()));
	connect(this->ui.judgeNum, SIGNAL(returnPressed()), this, SLOT(judgeJump()));
	connect(this->ui.submit, SIGNAL(clicked(bool)), this, SLOT(submit()));
}

/**
  * @author:Ӧ�о�
  * @brief:���ݵ����TabBar��ʾ��Ӧ������,0Ϊ��ѡ��,1Ϊ��ѡ��,2Ϊ�ж���
  * @date:2018/12/16
  * @version:1.0
  * ����QuestionBank
  */
void StudentExam::onTabChanged(int index) {
	switch (index) {
	case 0: {
		multichoiceStorage();
		judgeStorage();
		showChoice(); 
		break; 
	}
	case 1: {
		choiceStorage();
		judgeStorage();
		showMultichoice(); 
		break; 
	}
	case 2: {
		choiceStorage();
		multichoiceStorage();
		showJudge(); 
		break; 
	}
	default: break;
	}
}

/**
  * @author:�»�
  * @brief:�����Ծ���Ų�ѯ���ݿ�õ���Ŀ
  * @date:2018/12/24
  * @version:1.0
  */
void StudentExam::dataGet(int examCode) {
	StudentExamModel sql;
	if (!sql.isOpen()) {
		QMessageBox::critical(NULL, QStringLiteral("��ʾ"), QStringLiteral("����ʧ��"), QMessageBox::Yes);
	}
	else {
		this->choice = sql.searchChoice(0, examCode); //��ȡ����������ѡ��
		this->multichoice = sql.searchChoice(1, examCode);  //��ȡ����������ѡ��
		this->judge = sql.searchJudge(examCode);          //��ȡ���������ж���
		this->choiceAns = this->choice;
		this->multichoiceAns = this->multichoice;
		this->judgeAns = this->judge;
		for (int i = 0; i < this->choiceAns.size(); i++) {
			this->choiceAns[i].writeAnswer(QString());
		}
		for (int i = 0; i < this->multichoiceAns.size(); i++) {
			this->multichoiceAns[i].writeAnswer(QString());
		}
		for (int i = 0; i < this->judgeAns.size(); i++) {
			this->judgeAns[i].writeAnswer(QString());
		}
	}
}

/**
  * @author:�»�
  * @brief:��ʾ��ѡ��ҳ��
  * @date:2018/12/24
  * @version:1.0
  */
void StudentExam::showChoice() {
	this->ui.choiceQuestion->setPlainText(this->choice.at(this->choiceCurrent).getDescription());
	this->ui.choiceQuestion->setAlignment(Qt::AlignCenter);
	this->ui.choiceA->setPlainText(this->choice.at(this->choiceCurrent).getChoiceA());
	this->ui.choiceB->setPlainText(this->choice.at(this->choiceCurrent).getChoiceB());
	this->ui.choiceC->setPlainText(this->choice.at(this->choiceCurrent).getChoiceC());
	this->ui.choiceD->setPlainText(this->choice.at(this->choiceCurrent).getChoiceD());
	
	if (this->choiceAns.at(this->choiceCurrent).getAnswer() != QString()) {
		switch (choiceAns.at(this->choiceCurrent).getAnswer().toStdString()[0]) {
		case 'A': {
			this->ui.selectA->setChecked(true);
			break;
		}
		case 'B': {
			this->ui.selectB->setChecked(true);
			break;
		}
		case 'C': {
			this->ui.selectC->setChecked(true);
			break;
		}
		case 'D': {
			this->ui.selectD->setChecked(true);
			break;
		}
		default: {
			break;
		}
		}
	}
	else {
		this->ui.selectA->setAutoExclusive(false);
		this->ui.selectB->setAutoExclusive(false);
		this->ui.selectC->setAutoExclusive(false);
		this->ui.selectD->setAutoExclusive(false);

		this->ui.selectA->setChecked(false);
		this->ui.selectB->setChecked(false);
		this->ui.selectC->setChecked(false);
		this->ui.selectD->setChecked(false);

		this->ui.selectA->setAutoExclusive(true);
		this->ui.selectB->setAutoExclusive(true);
		this->ui.selectC->setAutoExclusive(true);
		this->ui.selectD->setAutoExclusive(true);
	}
}

/**
  * @author:�»�
  * @brief:��ʾ��ѡ��ҳ��
  * @date:2018/12/24
  * @version:1.0
  */
void StudentExam::showMultichoice() {
	this->ui.multichoiceQuestion->setPlainText(this->multichoice.at(this->multichoiceCurrent).getDescription());
	this->ui.multichoiceQuestion->setAlignment(Qt::AlignCenter);
	this->ui.multichoiceA->setPlainText(this->multichoice.at(this->multichoiceCurrent).getChoiceA());
	this->ui.multichoiceB->setPlainText(this->multichoice.at(this->multichoiceCurrent).getChoiceB());
	this->ui.multichoiceC->setPlainText(this->multichoice.at(this->multichoiceCurrent).getChoiceC());
	this->ui.multichoiceD->setPlainText(this->multichoice.at(this->multichoiceCurrent).getChoiceD());

	this->ui.multiselectA->setChecked(false);
	this->ui.multiselectB->setChecked(false);
	this->ui.multiselectC->setChecked(false);
	this->ui.multiselectD->setChecked(false);

	if (this->multichoiceAns.at(this->multichoiceCurrent).getAnswer() != QString()) {
		int i = 0;
		while (multichoiceAns.at(this->multichoiceCurrent).getAnswer().toStdString()[i]) {
			switch (multichoiceAns.at(this->multichoiceCurrent).getAnswer().toStdString()[i]) {
			case 'A': {
				this->ui.multiselectA->setChecked(true);
				break;
			}
			case 'B': {
				this->ui.multiselectB->setChecked(true);
				break;
			}
			case 'C': {
				this->ui.multiselectC->setChecked(true);
				break;
			}
			case 'D': {
				this->ui.multiselectD->setChecked(true);
				break;
			}
			default: {
				break;
			}
			}
			i++;
		}
	}
}

/**
  * @author:�»�
  * @brief:��ʾ�ж���ҳ��
  * @date:2018/12/24
  * @version:1.0
  */
void StudentExam::showJudge() {
	this->ui.judgeQuestion->setPlainText(this->judge.at(this->judgeCurrent).getDescription());
	this->ui.judgeQuestion->setAlignment(Qt::AlignCenter);

	if (this->judgeAns.at(this->judgeCurrent).getAnswer() != QString()) {
		switch (judgeAns.at(this->judgeCurrent).getAnswer().toStdString()[0]) {
		case 'T': {
			this->ui.selectT->setChecked(true);
			break;
		}
		case 'F': {
			this->ui.selectF->setChecked(true);
			break;
		}
		default: {
			break;
		}
		}
	}
	else {
		this->ui.selectT->setAutoExclusive(false);
		this->ui.selectF->setAutoExclusive(false);

		this->ui.selectT->setChecked(false);
		this->ui.selectF->setChecked(false);

		this->ui.selectT->setAutoExclusive(true);
		this->ui.selectF->setAutoExclusive(true);
	}
}

/**
  * @author:�»�
  * @brief:��ѡ��ҳ����ʾ��һ��
  * @date:2018/12/24
  * @version:1.0
  */
void StudentExam::choicePrevious() {
	if (this->choiceCurrent > 0) {
		choiceStorage();
		this->choiceCurrent--;
		showChoice();
	}
}

/**
  * @author:�»�
  * @brief:��ѡ��ҳ����ʾ��һ��
  * @date:2018/12/24
  * @version:1.0
  */
void StudentExam::choiceNext() {
	if (this->choiceCurrent < this->choice.size()-1) {
		choiceStorage();
		this->choiceCurrent++;
		showChoice();
	}
}

/**
  * @author:�»�
  * @brief:��ѡ��ҳ����ʾ��һ��
  * @date:2018/12/24
  * @version:1.0
  */
void StudentExam::multichoicePrevious() {
	if (this->multichoiceCurrent > 0) {
		multichoiceStorage();
		this->multichoiceCurrent--;
		showMultichoice();
	}

}

/**
  * @author:�»�
  * @brief:��ѡ��ҳ����ʾ��һ��
  * @date:2018/12/24
  * @version:1.0
  */
void StudentExam::multichoiceNext() {
	if (this->multichoiceCurrent < this->multichoice.size() - 1) {
		multichoiceStorage();
		this->multichoiceCurrent++;
		showMultichoice();
	}
}

/**
  * @author:�»�
  * @brief:�ж���ҳ����ʾ��һ��
  * @date:2018/12/24
  * @version:1.0
  */
void StudentExam::judgePrevious() {
	if (this->judgeCurrent > 0) {
		judgeStorage();
		this->judgeCurrent--;
		showJudge();
	}
}

/**
  * @author:�»�
  * @brief:�ж���ҳ����ʾ��һ��
  * @date:2018/12/24
  * @version:1.0
  */
void StudentExam::judgeNext() {
	if (this->judgeCurrent < this->judge.size() - 1) {
		judgeStorage();
		this->judgeCurrent++;
		showJudge();
	}
}

/**
  * @author:�»�
  * @brief:��ѡ��ҳ����תָ������
  * @date:2018/12/24
  * @version:1.0
  */
void StudentExam::choiceJump() {
	int num;
	num = this->ui.choiceNum->text().toInt();
	if (num > 0 && num <= this->choice.size()) {
		choiceStorage();
		this->choiceCurrent = num - 1;
		showChoice();
	}
}

/**
  * @author:�»�
  * @brief:��ѡ��ҳ����תָ������
  * @date:2018/12/24
  * @version:1.0
  */
void StudentExam::multichoiceJump() {
	int num;
	num = this->ui.multichoiceNum->text().toInt();
	if (num > 0 && num <= this->multichoice.size()) {
		multichoiceStorage();
		this->multichoiceCurrent = num - 1;
		showMultichoice();
	}
}

/**
  * @author:�»�
  * @brief:�ж���ҳ����תָ������
  * @date:2018/12/24
  * @version:1.0
  */
void StudentExam::judgeJump() {
	int num;
	num = this->ui.judgeNum->text().toInt();
	if (num > 0 && num <= this->judge.size()) {
		judgeStorage();
		this->judgeCurrent = num - 1;
		showJudge();
	}
}

/**
  * @author:�»�
  * @brief:��ѡ���ݴ��
  * @date:2018/12/24
  * @version:1.0
  */
void StudentExam::choiceStorage() {
	int i;
	QString ans;
	QList<QAbstractButton*> radioBtn = this->ui.choiceGroup->buttons();
	if (this->ui.selectA->isChecked()) {
		ans = this->ui.selectA->text();
	}
	else if (this->ui.selectB->isChecked()) {
		ans = this->ui.selectB->text();
	}
	else if (this->ui.selectC->isChecked()) {
		ans = this->ui.selectC->text();
	}
	else if (this->ui.selectD->isChecked()) {
		ans = this->ui.selectD->text();
	}
	if (!ans.isEmpty()) {
		this->choiceAns[this->choiceCurrent].writeAnswer(ans);
	}
}

/**
  * @author:�»�
  * @brief:��ѡ���ݴ��
  * @date:2018/12/24
  * @version:1.0
  */
void StudentExam::multichoiceStorage() {
	QString ans;
	if (this->ui.multiselectA->isChecked()) {
		ans.append(this->ui.multiselectA->text());
	}
	if (this->ui.multiselectB->isChecked()) {
		ans.append(this->ui.multiselectB->text());
	}
	if (this->ui.multiselectC->isChecked()) {
		ans.append(this->ui.multiselectC->text());
	}
	if (this->ui.multiselectD->isChecked()) {
		ans.append(this->ui.multiselectD->text());
	}

	if (!ans.isEmpty()) {
		this->multichoiceAns[this->multichoiceCurrent].writeAnswer(ans);
	}
}

/**
  * @author:�»�
  * @brief:�ж����ݴ��
  * @date:2018/12/24
  * @version:1.0
  */
void StudentExam::judgeStorage() {

	if (this->ui.selectT->isChecked()) {
		this->judgeAns[this->judgeCurrent].writeAnswer("T");
	}
	else if (this->ui.selectF->isChecked()) {
		this->judgeAns[this->judgeCurrent].writeAnswer("F");
	}
}

/**
  * @author:�»�
  * @brief:����ύ��ť���ݴ�Ĵ𰸲��
  * @date:2018/12/24
  * @version:1.0
  */
void StudentExam::submit() {
	StudentExamModel sql;
	int flag;
	choiceStorage();
	multichoiceStorage();
	judgeStorage();
	getScore();
	if (!sql.isOpen()) {
		QMessageBox::critical(NULL, QStringLiteral("��ʾ"), QStringLiteral("����ʧ��"), QMessageBox::Yes);
	}
	else {
		int num = this->choice.size();
		flag=sql.submit(this->choice, this->multichoice, this->judge, 3,this->objectScore,this->judgeScore);
		if (flag) {
			QMessageBox::information(NULL, QStringLiteral("��ʾ"), QStringLiteral("�ύ�ɹ���"), QMessageBox::Yes);
			this->close();
		}
		else {
			QMessageBox::warning(NULL, QStringLiteral("��ʾ"), QStringLiteral("�ύʧ�ܣ�"), QMessageBox::Yes);
		}
	}
}

/**
  * @author:�»�
  * @brief:���ݴ�Ĵ����׼�𰸱Ƚϣ��ó�����
  * @date:2018/12/24
  * @version:1.0
  */
void StudentExam::getScore() {
	int i;
	int objectSum = 0;
	int judgeSum = 0;
	for (i = 0; i < this->choice.size(); i++) {
		if (this->choice.at(i).getAnswer() == this->choiceAns.at(i).getAnswer()) {
			objectSum += choice.at(i).getValue();
		}
	}
	for (i = 0; i < this->multichoice.size(); i++) {
		if (this->multichoice.at(i).getAnswer() == this->multichoiceAns.at(i).getAnswer()) {
			objectSum += multichoice.at(i).getValue();
		}
	}
	for (i = 0; i < this->judge.size(); i++) {
		if (this->judge.at(i).getAnswer() == this->judgeAns.at(i).getAnswer()) {
			judgeSum += judge.at(i).getValue();
		}
	}
	this->objectScore = objectSum;
	this->judgeScore = judgeSum;
}

StudentExam::~StudentExam()
{
}