#ifndef _QUESTION_H
#define _QUESTION_H

/*
 * Qustion类封装了试题的相关信息以及操作
 */
#include<QString>
#include<QSqlQuery>

class Question{
public:
	Question(int id , QString description , QString answer , int value , QString author = "admin");
	int getValue() const;
	int getQuestionId() const;
	QString getDescription() const;
	QString getAnswer() const;
	QString getAuthor() const;
	~Question();
private:
	int value;
	int questionId;
	QString description;
	QString answer;
	QString author;
	Question() {}; //不允许使用默认无参构造函数
};

/*
 * Choice类封装了选择题(单选和多选)的相关信息以及操作
 */
class Choice :public Question {
public:
	Choice(int id , QString description , QString choiceA , QString choiceB , QString choiceC ,
		QString choiceD , QString answer , int value , QString author = "admin");
	QString getChoiceA() const;
	QString getChoiceB() const;
	QString getChoiceC() const;
	QString getChoiceD() const;
	~Choice();
private:
	Choice(); //不允许使用默认无参构造函数
	QString choiceA;
	QString choiceB;
	QString choiceC;
	QString choiceD;
};

/*
 * Jugde类封装了判断题的相关信息以及操作
 */
class Judge :public Question {
public:
	Judge(int id , QString description , QString answer , int value , QString author = "admin");
	QString getChoiceA() const;
	QString getChoiceB() const;
	~Judge();
private:
	QString choiceA;
	QString choiceB;
	Judge(); //不允许使用默认无参构造函数
};

/*
 * Exam类封装了一场考试的相关信息以及操作
 */
class Exam {
public:
	Exam(int oScore, int jScore, int flag, QString Name, int Code, int Duration);
	QString getName() const;
	int getCode() const;
	int getDuration() const;
	int getObjectScore() const;
	int getJudgeScore() const;
	int getScore() const;
	int getIsSubmit() const;
	~Exam(); 
private:
	QString name;
	int code;
	int duration;
	int objectScore;
	int judgeScore;
	int score;
	int isSubmit;
	Exam();//不允许使用默认无参构造函数
};
#endif