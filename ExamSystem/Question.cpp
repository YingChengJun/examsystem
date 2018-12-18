#include "Question.h"
#include <QSqlQuery>
#include <QString>

Question::Question(int id , QString description , QString answer , int value , QString author) {
	this->questionId = id;
	this->description = description;
	this->answer = answer;
	this->value = value;
	this->author = author;
}

int Question::getValue() const {
	return value;
}

int Question::getQuestionId() const {
	return questionId;
}

QString Question::getDescription() const {
	return description;
}

QString Question::getAnswer() const {
	return answer;
}

QString Question::getAuthor() const {
	return author;
}

Question::~Question() {

}

Choice::Choice(int id , QString description , QString choiceA , QString choiceB , QString choiceC ,
	QString choiceD , QString answer , int value , QString author) :
	Question(id , description , answer , value , author) {
	this->choiceA = choiceA;
	this->choiceB = choiceB;
	this->choiceC = choiceC;
	this->choiceD = choiceD;
}

QString Choice::getChoiceA() const {
	return choiceA;
}

QString Choice::getChoiceB() const {
	return choiceB;
}

QString Choice::getChoiceC() const {
	return choiceC;
}

QString Choice::getChoiceD() const {
	return choiceD;
}

Choice::~Choice() {

}

Judge::Judge(int id , QString description , QString answer , int value , QString author)
	: Question(id , description , answer , value , author) {

}

QString Judge::getChoiceA() const {
	return choiceA;
}
QString Judge::getChoiceB() const {
	return choiceB;
}

Judge::~Judge() {

}



Exam::Exam(int oScore, int jScore, int flag, QString Name, int Code, int Duration) :objectScore(oScore), judgeScore(jScore),isSubmit(flag),name(Name), code(Code), duration(Duration)
{
	if (flag) {
		score = objectScore + judgeScore;
	}else {
		score = NULL;
	}
}

QString Exam::getName() const
{
	return name;
}


int Exam::getCode() const
{
	return code;
}

int Exam::getDuration() const
{
	return duration;
}

int Exam::getObjectScore() const
{
	return objectScore;
}

int Exam::getJudgeScore() const
{
	return judgeScore;
}

int Exam::getScore() const
{
	return score;
}

int Exam::getIsSubmit() const
{
	return isSubmit;
}

Exam::~Exam(){

}