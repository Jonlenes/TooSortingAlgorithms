#ifndef WIDPAINTGRAPHIC_H
#define WIDPAINTGRAPHIC_H

//includes Qt
#include <QWidget>
#include <QTableWidget>

/*
 * Criação:         Jonlenes Silva de Castro
 * Objetivo:        Essa classe foi projetada para plotar gráfico linear dos tempos dos algoritimos de ordenação
 * Funcionamento:   As informações para plotar o gráfico é obtivo aparti do Dao da ordenação. Apos a busca
 * dos dados a mesma monta o gráfico.
*/

class WidPaintGraphic : public QWidget
{
    Q_OBJECT
public:
    explicit WidPaintGraphic(QWidget *parent);

    /*Metodos para desenho*/
    void paintEvent(QPaintEvent *) override final;
    void paintPlan(QPainter &p);
    void paintGraphic(QPainter &p);
    void paintValues(QPainter &p);
    void setColor(QPainter &p, QString strAlgo);

    /*Auciliares no desenho*/
    double xReal(double xBase);
    double yReal(double yBase);

    void printMe(int algorithm, int index);
    void printMeAll(int order);

    const QMap<int, QString> getMyMap() const;

signals:

public slots:

private:
    QMap<int, QString> mapAlgo;
    QMap<long long, long long> mapValues;
    int sizeMax;
    double timeMax;
};

#endif // WIDPAINTGRAPHIC_H
