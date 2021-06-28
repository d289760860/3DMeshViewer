#include "SingleMark.h"

QPoint SingleMark::getfirst() const
{
	return this->begin;
}

QPoint SingleMark::getsecond() const
{
	return this->end;
}

QString SingleMark::getlabel() const
{
	return this->label;
}

SingleMark::SingleMark(QPoint fst, QPoint snd, QString str)
{
	this->begin = fst;
	this->end = snd;
	this->label = str;
}

void SingleMark::setfirst(QPoint p)
{
	this->begin = p;
}
void SingleMark::setsecond(QPoint p)
{
	this->end = p;
}

void SingleMark::setlabel(QString str)
{
	this->label = str;
}

int angle(QPoint p1, QPoint p2)
{
	if (p1.x() == p2.x() && p1.y() == p2.y())
		return 0;
	else if (p1.x() == p2.x())
		return 90;
	double tmp = double(p1.y() - p2.y()) / double(p1.x() - p2.x());
	double angarc = atan(tmp);
	int angle = int(RAD2DEG(angarc));
	return angle;
}