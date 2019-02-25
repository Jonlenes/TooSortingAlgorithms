//includes proprios
#include "WidPaintGraphic.h"
#include "DataBase/Dao/DAOOrdenation.h"
#include "Util/Web.h"
#include "Sort/Sort.h"

//includes c++
#include <list>
#include <math.h>

//includes Qt
#include <QTableWidget>
#include <QPainter>
#include <QFile>

using namespace std;

static const double Pi = 3.14159265358979323846264338327950288419717;

WidPaintGraphic::WidPaintGraphic(QWidget *parent) :
    QWidget(parent)
{
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(1);

    mapAlgo.insert(IndexVector::Bubble, "Bubble");
    mapAlgo.insert(IndexVector::Insertion, "Insertion");
    mapAlgo.insert(IndexVector::Selection, "Selection");
    mapAlgo.insert(IndexVector::Merge, "Merge");
    mapAlgo.insert(IndexVector::Quick, "Quick");
    mapAlgo.insert(IndexVector::Heap, "Heap");
}

void WidPaintGraphic::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);
    paintPlan(p);
    paintValues(p);
    paintGraphic(p);
}

void WidPaintGraphic::paintPlan(QPainter &p)
{
    p.setPen(QPen(Qt::black, 1));
    p.setBrush(QBrush(Qt::black));
    QLineF *lines = new QLineF[2];
    QPointF PtFinal[2];
    PtFinal[0] = QPoint(10, 10);
    PtFinal[1] = QPoint(width() - 10, height() - 20);
    lines[0].setPoints(QPoint(10, height() - 10), PtFinal[0]);
    lines[1].setPoints(QPoint(0, height() - 20), PtFinal[1]);

    double angulo;
    for(int i = 0; i < 2; i++)
    {
        p.drawLine(lines[i]);
        angulo = acos(lines[i].dx() / lines[i].length());
        QPointF FinalSetaP1 = PtFinal[i] + QPointF(sin(angulo - Pi / 3) * 10,
                                                  cos(angulo - Pi / 3) * 10);
        QPointF FinalSetaP2 = PtFinal[i] + QPointF(sin(angulo - Pi + Pi / 3) * 10,
                                                cos(angulo - Pi + Pi / 3) * 10);

        p.drawPolygon(QPolygonF() << lines[i].p2() << FinalSetaP1 << FinalSetaP2);
    }
    delete [] lines;
}

void WidPaintGraphic::paintGraphic(QPainter &p)
{
    QPointF pointPrev = QPointF(xReal(0), yReal(0));
    QPointF pointAct = QPointF(-1, -1);
    QString strAlgo;

    sizeMax = DAOOrdenation::maxSize();
    timeMax = DAOOrdenation::maxTime();

    list<MOrdenation> listMedium = DAOOrdenation::mediumTime();

    for (auto i : listMedium) {
        if (static_cast<MOrdenation> (i).getAlgorithm() != strAlgo) {
            strAlgo = static_cast<MOrdenation> (i).getAlgorithm();
            pointPrev = QPointF(xReal(0), yReal(0));
            pointAct = QPointF(-1, -1);
            setColor(p, strAlgo);
        }
        pointAct.setX(mapValues[static_cast<MOrdenation> (i).getSize()]);
        pointAct.setY(yReal(static_cast<MOrdenation> (i).getTime()));
        p.drawEllipse(pointAct, 2, 2);
        p.drawLine(pointPrev, pointAct);
        pointPrev = pointAct;
    }
}

void WidPaintGraphic::paintValues(QPainter &p)
{
    list<long long> listValues = DAOOrdenation::getSizes();
    mapValues.clear();

    if (listValues.empty()) return;
    sizeMax = DAOOrdenation::maxSize();

    long long iteracao = static_cast<long long> (listValues.back()) / (listValues.size());
    long long i = iteracao;
    for (auto item : listValues) {
        mapValues[item] = xReal(i);
        if (item == listValues.back())
            p.drawText(mapValues[item] - 40, height() - 8, QString::number(item));
        else
            p.drawText(mapValues[item], height() - 8, QString::number(item));
        i += iteracao;
    }
}

void WidPaintGraphic::setColor(QPainter &p, QString strAlgo)
{
    float sizePen = 2;
    switch (mapAlgo.key(strAlgo)) {
    case Bubble:
        p.setPen(QPen(Qt::green, sizePen));
        p.setBrush(QBrush(Qt::green));
        break;
    case Insertion:
        p.setPen(QPen(Qt::blue, sizePen));
        p.setBrush(QBrush(Qt::blue));
        break;
    case Selection:
        p.setPen(QPen(Qt::red, sizePen));
        p.setBrush(QBrush(Qt::red));
        break;
    case Merge:
        p.setPen(QPen(QColor("#27eaff"), sizePen));
        p.setBrush(QBrush(QColor("#27eaff")));
        break;
    case Quick:
        p.setPen(QPen(Qt::yellow, sizePen));
        p.setBrush(QBrush(Qt::yellow));
        break;
    case Heap:
        p.setPen(QPen(Qt::magenta, sizePen));
        p.setBrush(QBrush(Qt::magenta));
        break;
    default:
        break;
    }
}

double WidPaintGraphic::xReal(double xBase)
{
    return (((double)(xBase * (width() - 20)) / sizeMax) + 10);
}

double WidPaintGraphic::yReal(double yBase)
{
    if(timeMax == 0) return (height() - 20);
    return (height() - (((double)(yBase * (height() - 20)) / timeMax) + 20));
}

void WidPaintGraphic::printMe(int algorithm, int index)
{
    QFile file;
    QPixmap pixmap(this->size());

    repaint();

    file.setFileName("../projectWeb/_imagens/" + mapAlgo.value(algorithm) + "_"
                     + QString::number(index) + ".png");

    this->render(&pixmap);
    pixmap.save(&file, "png", 100);
    file.close();
}
void WidPaintGraphic::printMeAll(int order)
{
    QStringList listAlgo;
    QStringList listSize;

    for (int i = 0; i <= countAlgo; i++) {
        listAlgo.clear();
        listAlgo.append(mapAlgo[i]);
        DAOOrdenation::setFilter(order, listAlgo, listSize);
        repaint();
        printMe(i, order);
    }
}

const QMap<int, QString> WidPaintGraphic::getMyMap() const
{
    return static_cast< const QMap<int, QString> > (mapAlgo);
}
