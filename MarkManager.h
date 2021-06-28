#ifndef __MARK__MANAGER__
#define __MARK__MANAGER__

#include <QWidget>
#include <QPainter>
#include <QPoint>
#include <QImage>
#include <QPixmap>
#include <vector>
#include "SingleMark.h"

class MarkManagerWindow : public QWidget
{
public:
	MarkManagerWindow(QImage* img, std::vector<SingleMark> *lines);
	~MarkManagerWindow();
protected:
	void paintEvent(QPaintEvent *e);
	QImage* origin;
	QPixmap pix;
	std::vector<SingleMark> linesvec;
	int height;
	int width;
};


#endif