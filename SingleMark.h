#ifndef __SINGLE__MARK__
#define __SINGLE__MARK__

#include <QPoint>
#include <QImage>
#include <QPixmap>
#include <vector>
#include <QString>

constexpr auto M_PI_D = 3.14159;
#define RAD2DEG(x) ((x)*180./M_PI_D) 

class SingleMark
{
public:
	QPoint getfirst() const;
	QPoint getsecond() const;
	QString getlabel() const;
	void setfirst(QPoint p);
	void setsecond(QPoint p);
	void setlabel(QString str);
	SingleMark(QPoint fst, QPoint snd, QString str);
private:
	QPoint begin;
	QPoint end;
	QString label;
};

int angle(QPoint p1, QPoint p2);


#endif