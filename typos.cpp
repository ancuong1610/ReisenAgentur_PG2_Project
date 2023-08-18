#include "typos.h"
#include "ui_typos.h"
#include "kundenprofil.h"
Typos::Typos(std::shared_ptr<TravelAgency> travelAgency,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Typos),
  travelAgency(travelAgency)
{
    ui->setupUi(this);
}

Typos::~Typos()
{
    delete ui;
}

void Typos::on_pushButton_clicked()
{
    ui->listWidget->clear();
    map.clear();
    for(auto &obj : travelAgency->KundenName){
        map.insert(std::pair<double,std::string> (typos(ui->lineEdit->text(),obj),obj));
    }

    for (auto const& x : map)
    {
        ui->listWidget->addItem(QString::fromStdString(x.second));
    }
}


void Typos::on_listWidget_itemDoubleClicked()
{
    std::string eingabe = ui->listWidget->currentItem()->text().toStdString();
    KundenProfil *popup=new KundenProfil(travelAgency->returnKunde(eingabe),travelAgency);
    popup->exec();
}

double Typos::typos(QString input, std::string data){
    std::string eingabe = input.toStdString();
    int matrix[data.size()+1][eingabe.size()+1];
    for(int i = 0; i < data.size() + 1; i++){
        for(int j = 0; j < eingabe.size() + 1;j++){
            if(j == 0 && i == 0)
                matrix[i][j] = 0;
            else if(j == 0 && i > 0)
                matrix[i][j] = i;
            else if(j > 0 && i == 0)
                matrix[i][j] = j;
            else{
               if(data[i-1] == eingabe[j-1])
                   matrix[i][j] =  matrix[i-1][j-1];
               else{
                   int a = matrix[i-1][j-1];
                   int b = matrix[i][j-1];
                   int c = matrix[i-1][j];
                   int val = std::min(a,std::min(b,c));
                   matrix[i][j] = val + 1;
                   }
               }
        }
    }
    int x = data.size();
    int y = eingabe.size();
    double varianz = matrix[x][y];
    double result = varianz/(x+y);
    return result;
}
