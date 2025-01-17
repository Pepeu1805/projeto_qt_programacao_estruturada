#include "fm_novavenda.h"
#include "ui_fm_novavenda.h"
#include <QMessageBox>
#include <fm_editarprodutovenda.h>
#include "fm_principal.h"
#include "variaveis_globais.h"
#include <QDebug>

QString fm_novavenda::g_idprod;
QString fm_novavenda::g_prod;
QString fm_novavenda::g_qtde;
QString fm_novavenda::g_valuni;
QString fm_novavenda::g_valtotal;
bool fm_novavenda::alterou;

fm_novavenda::fm_novavenda(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::fm_novavenda)
{
    ui->setupUi(this);

    if(!con.aberto()){
        if(!con.abrir()){
            QMessageBox::warning(this,"ERRO","Erro ao abrir banco de dados");
        }
    }

    ui->tw_listaprodutos->setColumnCount(5);
    ui->tw_listaprodutos->setColumnWidth(0,100);
    ui->tw_listaprodutos->setColumnWidth(1,200);
    ui->tw_listaprodutos->setColumnWidth(2,100);
    ui->tw_listaprodutos->setColumnWidth(3,100);
    ui->tw_listaprodutos->setColumnWidth(4,100);
    QStringList cabecalhos={"Código","Produto","Valor Un.","Qtde","Total"};
    ui->tw_listaprodutos->setHorizontalHeaderLabels(cabecalhos);
    ui->tw_listaprodutos->setStyleSheet("QTableView{selection-background-color:red;}");
    ui->tw_listaprodutos->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tw_listaprodutos->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tw_listaprodutos->verticalHeader()->setVisible(false);

    ui->txt_codproduto->setFocus();
    contlinhas=0;
}

fm_novavenda::~fm_novavenda()
{
    delete ui;
}

void fm_novavenda::on_txt_codproduto_returnPressed()
{
    QSqlQuery query;
    QString id=ui->txt_codproduto->text();
    double valtot;
    query.prepare("select id_produto,produto,valor_venda from tb_produtos where id_produto="+id);
    if(query.exec()){
        query.first();
        if(query.value(0).toString()!=""){
            ui->tw_listaprodutos->insertRow(contlinhas);
            ui->tw_listaprodutos->setItem(contlinhas,0,new QTableWidgetItem(query.value(0).toString()));
            ui->tw_listaprodutos->setItem(contlinhas,1,new QTableWidgetItem(query.value(1).toString()));
            ui->tw_listaprodutos->setItem(contlinhas,2,new QTableWidgetItem(query.value(2).toString()));
            ui->tw_listaprodutos->setItem(contlinhas,3,new QTableWidgetItem(ui->txt_qtde->text()));
            valtot=ui->txt_qtde->text().toDouble()*query.value(2).toDouble();
            ui->tw_listaprodutos->setItem(contlinhas,4,new QTableWidgetItem(QString::number(valtot)));
            ui->tw_listaprodutos->setRowHeight(contlinhas,20);
            contlinhas++;
            ui->lb_totalvenda->setText("R$"+QString::number(calculaTotal(ui->tw_listaprodutos,4)));
        }else{
           QMessageBox::warning(this,"ERRO","Produto não encontrado");
        }
        resetaCampos();
    }else{
        QMessageBox::warning(this,"ERRO","Erro ao inserir novo produto");
    }
}

void fm_novavenda::resetaCampos(){
    ui->txt_codproduto->clear();
    ui->txt_qtde->setText("1");
    ui->txt_codproduto->setFocus();
}

void fm_novavenda::removerLinhas(QTableWidget *tw){
    while(tw->rowCount()>0){
        tw->removeRow(0);
    }
}

double fm_novavenda::calculaTotal(QTableWidget *tw, int coluna){
    int totallinhas;
    double total;

    totallinhas=tw->rowCount();
    for(int i=0;i<totallinhas;i++){
        total+=tw->item(i,coluna)->text().toDouble();
    }
    return total;
}

void fm_novavenda::on_btn_excluirproduto_clicked()
{
    if(ui->tw_listaprodutos->currentColumn()!=-1){
      QMessageBox::StandardButton opc=QMessageBox::question(this,"Exclusão?","Confirma exclusão do produto?",QMessageBox::Yes|QMessageBox::No);
      if(opc==QMessageBox::Yes){
          ui->tw_listaprodutos->removeRow(ui->tw_listaprodutos->currentRow());
          ui->lb_totalvenda->setText("R$ "+QString::number(calculaTotal(ui->tw_listaprodutos,4)));
          contlinhas--;
      }
    }else{
        QMessageBox::warning(this,"ERRO","Selecione um produto primeiro");
    }
}

void fm_novavenda::on_btn_editarproduto_clicked()
{
    if(ui->tw_listaprodutos->currentColumn()!=-1){
        int linha=ui->tw_listaprodutos->currentRow();

        g_idprod=ui->tw_listaprodutos->item(linha,0)->text();
        g_prod=ui->tw_listaprodutos->item(linha,1)->text();
        g_valuni=ui->tw_listaprodutos->item(linha,2)->text();
        g_qtde=ui->tw_listaprodutos->item(linha,3)->text();

        fm_editarprodutovenda f_editarprodutovenda;
        f_editarprodutovenda.exec();

        if(alterou){
            ui->tw_listaprodutos->item(linha,2)->setText(g_valuni);
            ui->tw_listaprodutos->item(linha,3)->setText(g_qtde);
            ui->tw_listaprodutos->item(linha,4)->setText(g_valtotal);
            ui->lb_totalvenda->setText("R$ "+QString::number(calculaTotal(ui->tw_listaprodutos,4)));
        }
    }
}

void fm_novavenda::on_btn_finalizarvenda_clicked()
{
    if(ui->tw_listaprodutos->rowCount()>0){
        int idVenda;
        QString msgFimVenda;
        double total=calculaTotal(ui->tw_listaprodutos,4);
        QString data=QDate::currentDate().toString("dd/MM/yyyy");
        QString hora=QTime::currentTime().toString("hh:mm:ss");
        QSqlQuery query;
        query.prepare("insert into tb_vendas (data_venda,hora_venda,id_colaborador,valor_total,id_tipo_pagamento) values ('"+data+"', '"+hora+"', "+QString::number(variaveis_globais::id_colab)+", "+QString::number(total)+",1)");
        if(!query.exec()){
            QMessageBox::warning(this,"ERRO","Erro ao registrar nova venda");
        }else{
            query.prepare("select id_venda from tb_vendas order by id_venda desc limit 1");
            query.exec();
            query.first();
            idVenda=query.value(0).toInt();
            msgFimVenda="ID Venda: "+QString::number(idVenda)+"\nValor total: R$"+QString::number(total);

            int totalLinhas=ui->tw_listaprodutos->rowCount();
            int linha=0;
            while(linha<totalLinhas){
                QString prod=ui->tw_listaprodutos->item(linha,1)->text();
                QString qtde=ui->tw_listaprodutos->item(linha,3)->text();
                QString valUn=ui->tw_listaprodutos->item(linha,2)->text();
                QString valTot=ui->tw_listaprodutos->item(linha,4)->text();
                query.prepare("insert into tb_produtoVendas (id_venda,produto,qtde,valor_un,valor_total)values("+QString::number(idVenda)+",'"+prod+"',"+qtde+","+valUn+","+valTot+")");
                if(!query.exec()){
                    qDebug() << "ERRO:" <<query.lastError().text();
                }
                linha++;
            }

            QMessageBox::information(this,"Venda Concluída",msgFimVenda);
            resetaCampos();
            removerLinhas(ui->tw_listaprodutos);
            ui->lb_totalvenda->setText("R$ 0,00");
        }
    }else{
        QMessageBox::warning(this,"ERRO","Não existem produtos nesta venda\nPrimeiro adicione um produto");
    }
}

