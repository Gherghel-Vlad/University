#include "SimulationExam.h"
#include <QLabel>
#include <QHBoxLayout>

SimulationExam::SimulationExam(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

	this->h = new QHBoxLayout(this);
	this->lbl = new QLabel( "Hahaha" );
	this->h->addWidget(this->lbl);
	/*for (int i = 1; i < 5; i++) {
		w = new QWidget();
		 v=new QVBoxLayout{};
		for (int j = 1; j < 5; j++) {
			std::string str = "Nume " + i;
			lbl = new QLabel{ QString::fromStdString(str) };
			lbl->setGeometry(20 * i + 30 * j, 20 * i + 30 * j, 30, 30);
			v->addWidget(lbl);
		}
		w->setLayout(v);
		h->addWidget(w);
	}*/
	
	
}

void SimulationExam::start_program()
{
}

void SimulationExam::paintEvent(QPaintEvent* event)
{

	//QPainter painter{ this };
	//// draw an ellipse
	//for (int i = 1; i < 5; i++) {
	//	for (int j = 1; j < 5; j++) {
	//		QPen pen2{ Qt::white, 1, Qt::SolidLine, Qt::RoundCap };
	//		painter.setPen(pen2);
	//		QBrush brush{ Qt::red };
	//		painter.setBrush(brush);
	//		painter.drawEllipse(QPointF(20 * i + 30 * j, 20 * i + 30 * j), 20, 20);
	//	}
	//}
}