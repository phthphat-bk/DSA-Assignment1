/*
 * =========================================================================================
 * Name        : eventLib.cpp
 * Author      : Duc Dung Nguyen, Nguyen Hoang Minh
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - Bach Khoa University
 * Description : library for Assignment 1 - Data structures and Algorithms - Fall 2017
 *               This library contains functions used for event management
 * =========================================================================================
 */

#include "eventLib.h"


/// NOTE: each event will be separated by spaces, or endline character
void loadEvents(char* fName, L1List<ninjaEvent_t> &eList) {
	string str;
	fstream filein(fName, ios::in | ios::out);
	while (getline(filein, str))
	{
		istringstream ss(str);
		ninjaEvent_t nje;
		while (ss >> nje.code) eList.push_back(nje);
	}
	filein.close();
}
