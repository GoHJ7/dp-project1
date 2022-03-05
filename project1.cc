// Copyright 2022 Wook-shin Han
#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
#include <unordered_map>
#include <utility>
#include <queue>
#include <list>

#include "project1.h"



int main(int argc, char* argv[]) {
	/* fill this */
	/* parsing */
	if(std::string(argv[1]) == "q1"){
		std::ifstream customerfile(argv[2]);
		Table customer_table(1);
		customer_table.read_file(customerfile);
		//customer_table.print();
		std::ifstream zonecostfile(argv[3]);
		Table zone_table(2);
		zone_table.read_file(zonecostfile);
		//zone_table.print();
		show(customer_table,zone_table);
	}
	else if(std::string(argv[1]) == "q2"){
		//std::cout<<"q2";
		std::ifstream linefile(argv[2]);
		Table line_table(3);
		line_table.read_file(linefile);
		//line_table.print();
		
		std::ifstream productfile(argv[3]);
		Table product_table(4);
		product_table.read_file(productfile);
		//product_table.print();

		show2(line_table, product_table);
	}
	return 0;
}

void show(Table customer, Table zone){
	int row;
	for(int i=0; i<customer.column_vector[12].data_vector.size();i++){
		//std::cout<<customer.column_vector[12].data_vector[i]<<std::endl;
		if(std::stoi(customer.column_vector[12].data_vector[i])==1){
			//active, check zone
			//std::cout<<"active"<<std::endl;
			int zone_num= std::stoi(customer.column_vector[5].data_vector[i]);
			//std::cout<<zone.column_vector[1].data_vector[zone_num-1];
			for(int j=0;j<zone.column_vector[0].data_vector.size();j++){
				//std::cout<<std::stoi(zone.column_vector[0].data_vector[j])<<std::endl;
				if(std::stoi(zone.column_vector[0].data_vector[j])==zone_num && !zone.column_vector[1].data_vector[j].compare("Toronto             ")){
					std::cout<<customer.column_vector[2].data_vector[i]<<std::endl;
				}
			}
		}
	}
}

void show2(Table line, Table product){
	//name -  barcode as key, value as purchase num
	std::unordered_map<int, std::list<std::string> > purchase;
	//store in the unorderedmap
	for(int i=0;i<line.column_vector[0].data_vector.size();i++){
		std::string name=line.column_vector[0].data_vector[i];
		int barcode= std::stoi(line.column_vector[3].data_vector[i]);
		std::unordered_map<int, std::list<std::string> >::iterator got = purchase.find(barcode);
		if(got == purchase.end()){
			//key not found
			std::list<std::string> l;
			l.push_back(name);
			purchase.insert(std::make_pair(barcode,l));
		}
		else{
			std::list<std::string>::iterator it; 
			for(it = got->second.begin(); it!=got->second.end();it++){
				if(*it==name)
					break;
			}
			if(it==got->second.end())
				got->second.push_back(name);
		}
	}
	
	//check more than 2 ordered
	std::unordered_map<int,std::list<std::string> >::iterator it;
	std::priority_queue<int,std::vector<int>,std::greater<int>> barcode_queue;
	for(it=purchase.begin();it!=purchase.end();it++){
		if(it->second.size()>1){
			barcode_queue.push(it->first);
		}
	}
	while(barcode_queue.size()){
		int barcode= barcode_queue.top();
		//find barcode in the product
		for(int i=0;i<product.column_vector[0].data_vector.size();i++){
			if(barcode==std::stoi(product.column_vector[0].data_vector[i])){
				std::cout<<barcode<<"                 ";
				std::cout<<product.column_vector[2].data_vector[i]<<std::endl;
				break;
			}
		}
		barcode_queue.pop();
	}
}