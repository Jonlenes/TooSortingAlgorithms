#include "Web.h"
#include "Sort/Sort.h"
#include "DataBase/Dao/DAOOrdenation.h"

#include <fstream>
#include <string>

#include <QStringList>

using namespace std;

QString Web::html = "";
QString *Web::strOrder = nullptr;

void Web::generetareHtml(const QMap<int, QString> &mapAlgo)
{
    QStringList listAlgo, listSize;
    list<MOrdenation> listOrdenation;

    strOrder = new QString[3];
    strOrder[0] = "Crescente";
    strOrder[1] = "Decrecente";
    strOrder[2] = "Aleatório";

    //Monta header
    mountHeader();

    //monta tables
    for (int i = 0; i < 3; i++)
        mountTableMedium(i, listAlgo, listSize, listOrdenation, mapAlgo);

    //Finalizando... fechando as tags
    mountFooter();

    saveHtml(html);
}

void Web::mountHeader()
{
    html=  "<!DOCTYPE html>";
    html += "<html lang = \"pt-br\">";
    html += "<head>";
    html += "    <meta charset=\"UTF-8\"/>";
    html += "    <title>Ordenetion</title>";
    html += "    <link rel=\"stylesheet\" type=\"text/css\" href=\"_css/estilo.css\"/>";
    html += "      <script type=\"text/javascript\">";
    html += "        function showPopUpGraphic(strPhoto, titleGraphic)";
    html += "        {";
    html += "        document.getElementById(\"imageG\").src = \"_imagens/\" + strPhoto;";
    html += "        document.all.titleWindow.innerText = \"Gráfico -\" + titleGraphic;";
    html += "        window.open(\"#openPhoto\", \"_parent\");";
    html += "        }";
    html += "     </script>";
    html += "</style>";
    html += "</head>";
    html += "<body>";
    html += "    <div id=\"interface\">";
    html += "         <header id=\"cabecalho\">";
    html += "             <hgroup>";
    html += "                 <h1>Dados dos algoritimos de ordenação</h1>";
    html += "                 <h2>Parte teórica do trabalho</h2>";
    html += "             </hgroup>";
    html += "         </header>";
    html += "        <section id=\"corpo\" align=\"center\">";
    html += "            <div id=\"openPhoto\" class=\"modalDialog\">";
    html += "                <div>";
    html += "                <a href=\"#close\" title=\"Close\" class=\"close\">X</a>";
    html += "                <h2><label id=\"titleWindow\">Err function of set title</label></h2>";
    html += "                <img id=\"imageG\" class=\"imageGraphic\" align=rigth>";
    html += "                </div>";
    html += "            </div>";
}

void Web::mountTableMedium(const int &order, QStringList &listAlgo, QStringList &listSize, list<MOrdenation> listOrdenation, const QMap<int, QString> &mapAlgo)
{
    for(int i = 1; i <= countAlgo; i++)
    {
        //Filtrando apenas 1 algoritmo e todos os sizes
        listAlgo.clear();
        listAlgo.append(mapAlgo[i]);
        DAOOrdenation::setFilter(order, listAlgo, listSize);
        listOrdenation = DAOOrdenation::mediumTime();

        //cabeçalho da tabela
        html += "<center><table id=\"tabelaDados\">";
        html += "    <caption>Média de tempo - Algoritimo " + mapAlgo.value(i) + " - " + strOrder[order] + "</caption>";
        html += "        <tr><td class=\"cellHeader\">Tamanho do vetor</td><td class=\"cellHeader\">Tempo médio</td><td class=\"cellHeader\">Frêquencia</td></tr>";

        for (auto i : listOrdenation)
        {
            html += "<tr><td class=\"cellTable\">" + QString::number(static_cast<MOrdenation> (i).getSize()) +
                  + "</td><td class=\"cellTable\">" + QString::number(static_cast<MOrdenation> (i).getTime()) +
                  + "</td><td class=\"cellTable\">" + QString::number(static_cast<MOrdenation> (i).getFrequency()) + "</td></tr>";
        }

        //fechando tabela e adicionando o button de visualizar o gráfico
        html += "</table></center> ";
        html += "<img src=\"_imagens\\" + mapAlgo.value(i) + "_" + QString::number(order) + ".png\" width=\"900px\">";
        html += "<center><button id=\"btnGraphic\" onclick=\"showPopUpGraphic('" + mapAlgo.value(i) + "_" + QString::number(order) + ".png', ' Média de tempo - Algoritimo " + mapAlgo.value(i) + "')\">Gráfico</button></center>";
    }
}

void Web::mountFooter()
{
    html += "        </section>";
    html += "    </div>";
    html += "</body>";
    html += "</html>";
}

void Web::saveHtml(QString html)
{
    const char *path = static_cast <string> ("../projectWeb/OrdenationWeb.html").c_str();
    fstream stdFileHtml;
    stdFileHtml.open(path, ios::out | ios::binary);
    stdFileHtml << html.toStdString();
    stdFileHtml.close();

    system("start ../projectWeb/OrdenationWeb.html");
}
