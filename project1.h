// Copyright 2022 Wook-shin Han
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#ifndef WHY_DBMS_PROJECT1_H_
#define WHY_DBMS_PROJECT1_H_

class Column{
    public:
    std::string name;
    int max_length;
    std::vector<std::string> data_vector;
    Column(std::string  name_,int max_length_ ){
        name=name_;
        max_length=max_length_;
    }
};


class Table{
    public:
    std::vector<Column> column_vector;
    int column_size;
    Table(int flag){
        if(flag==1){
		column_vector.push_back(Column("UNAME",20));
		column_vector.push_back(Column("PASSWD",20));
		column_vector.push_back(Column("LNAME",20));
		column_vector.push_back(Column("FNAME",20));
		column_vector.push_back(Column("ADDR",50));
		column_vector.push_back(Column("ZONE",6));
		column_vector.push_back(Column("SEX",3));
		column_vector.push_back(Column("AGE",6));
		column_vector.push_back(Column("LIMIT",6));
		column_vector.push_back(Column("BALANCE",10));
		column_vector.push_back(Column("CREDITCARD",20));
		column_vector.push_back(Column("EMAIL",50));
		column_vector.push_back(Column("ACTIVE",6));
        column_size=this->column_vector.size();
        }
        else if(flag==2){
            column_vector.push_back(Column("ZONEID",6));
            column_vector.push_back(Column("ZONEDESC",20));
            column_vector.push_back(Column("PRICE",7));
            column_size=this->column_vector.size();
        }
        else if(flag==3){
            column_vector.push_back(Column("UNAME",20));
            column_vector.push_back(Column("DATE",10));
            column_vector.push_back(Column("TIME",8));
            column_vector.push_back(Column("BARCODE",20));
            column_vector.push_back(Column("QUANTITY",8));
            column_vector.push_back(Column("PRICE",9));
            column_size=this->column_vector.size();
        }
        else if(flag==4){
            column_vector.push_back(Column("BARCODE",20));
            column_vector.push_back(Column("PRICE",10));
            column_vector.push_back(Column("PRODDESC",50));
            column_vector.push_back(Column("MFG",20));
            column_vector.push_back(Column("SUPPLIER",20));
            column_vector.push_back(Column("TAXABLE",7));
            column_vector.push_back(Column("CATEGORY",20));
            column_vector.push_back(Column("SALE_PERCENT",12));
            column_size=this->column_vector.size();
        }
    }
    void read_file(std::ifstream& file){
        std::string read_line;
        std::getline(file, read_line);//name of cols
        std::getline(file, read_line);//---s
        while(std::getline(file,read_line)){
            std::istringstream iss(read_line);
            for(int i=0;i<column_size;i++){
                char *s= (char*)malloc(sizeof(char)*column_vector[i].max_length);
                iss.readsome(s,column_vector[i].max_length);
                column_vector[i].data_vector.push_back(s);
                //one space
                iss.readsome(s,1);
                free (s);
            }
        }
    }
    void print(){
        for(int i=0;i<column_vector[0].data_vector.size();i++){
            //std::cout<<"rownum: "<<i<<std::endl;
            for(int j=0;j<column_size;j++){
                std::cout<<column_vector[j].data_vector[i];
            }
            std::cout<<'\n';
        }
    }
};
void show(Table customer, Table zone);
void show2(Table line,Table product);

#endif  // WHY_DBMS_PROJECT1_H_