#include "MarkManager.h"

MarkManagerWindow::MarkManagerWindow(QImage* img, std::vector<SingleMark> *lines) :
	QWidget()
{
	//parent->m_pkItemNum->currentIndex();
	
	origin = img;
	pix = QPixmap::fromImage(*img);
	linesvec.clear();
	linesvec.assign(lines->begin(),lines->end());
	linesvec.push_back(SingleMark(QPoint(10,10),QPoint(60,60), QString::fromLocal8Bit("!!!!!!!!!")));
	setWindowTitle(tr("Paint Demo"));
	if (pix.width() < 600 && pix.height() < 400)
	{
		resize(650,450);
		width = 650;
		height = 450;

	}
	else
	{
		resize(pix.width() + 50, pix.height() + 50);
		width = pix.width() + 50;
		height = pix.height() + 50;
	}
}

MarkManagerWindow::~MarkManagerWindow()
{
}

void MarkManagerWindow::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	painter.drawPixmap(0,0, pix.width(), pix.height(), pix);
	painter.setPen(QPen(Qt::green, 2));
	int a = linesvec.size();
	/*
	painter.setPen(Qt::red);
	painter.drawRect(10, 10, 100, 400);
	painter.setBrush(Qt::blue);
	painter.drawEllipse(50, 150, 400, 200);
	*/
	painter.save();
	QFont font;
	font.setPointSize(6);
	font.setFamily("Microsoft YaHei");
	font.setLetterSpacing(QFont::AbsoluteSpacing, 0);
	painter.setFont(font);
	for (std::vector<SingleMark>::const_iterator iter = linesvec.cbegin(); iter != linesvec.cend(); iter++)
	{
		painter.drawLine(iter->getfirst(),iter->getsecond());

		QFontMetricsF fontMetrics(font);
		qreal wid = fontMetrics.width(iter->getlabel());
		qreal hei = fontMetrics.height();
		//将原点移动到要画文字的地方
		painter.translate((iter->getfirst().x()+iter->getsecond().x())/2 - wid / 2,
			(iter->getfirst().y() + iter->getsecond().y()) / 2 - hei);
		//旋转
		painter.rotate(angle(iter->getfirst(),iter->getsecond()));
		painter.drawText(0, 0, iter->getlabel());
	}
	painter.restore();
}

