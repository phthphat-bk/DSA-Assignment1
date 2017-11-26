/*
 * =========================================================================================
 * Name        : dbLib.cpp
 * Author      : Duc Dung Nguyen, Nguyen Hoang Minh
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - Bach Khoa University
 * Description : library for Assignment 1 - Data structures and Algorithms - Fall 2017
 *               This file implements functions used for database management
 * =========================================================================================
 */

#include "dbLib.h"

#include <time.h>
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <cmath>
#include <iomanip>
#define pi 3.14159265358979323846
#define earthRadiusKm 6371.0

using namespace std;

void    strPrintTime(char* des, time_t& t) {
    tm *pTime = localtime(&t);
    strftime(des, 26, "%Y-%m-%d %H:%M:%S", pTime);
}

void loadNinjaDB(char* fName, L1List<NinjaInfo_t> &db) {
	// TODO: write code to load information from file into db
	fstream filein(fName, ios::in | ios::out);
	string temp, timestamp, id, longitude, latitude;
	getline(filein, temp);
	NinjaInfo_t nj;
	while (getline(filein, temp, ','))
	{
		getline(filein, timestamp, ',');
		struct tm tm;
		istringstream ss(timestamp);
		ss >> get_time(&tm, "%d/%m/%Y %H:%M:%S");
		nj.timestamp = mktime(&tm);

		getline(filein, id, ',');
		while(id.length() < 4)
		{
			id = "0" + id;
		}
		strcpy(nj.id, id.c_str());
		getline(filein, longitude, ',');
		istringstream(longitude) >> nj.longitude;
		getline(filein, latitude, ',');
		istringstream(latitude) >> nj.latitude;
		getline(filein, temp, '\n');
		db.push_back(nj);
	}
	filein.close();
}

bool parseNinjaInfo(char* pBuf, NinjaInfo_t& nInfo) {
   // TODO: write code to parse information from a string buffer, ignore if you don't use it
   return true;
}


void process(L1List<ninjaEvent_t>& eventList, L1List<NinjaInfo_t>& bList) {
	void* pGdata = NULL;
	//static_cast <L1List<ninjaEvent>*> (pGdata = &eventList);
	pGdata = &eventList;
	L1List<ninjaEvent_t>*eList = static_cast<L1List<ninjaEvent_t>*>(pGdata);
	initNinjaGlobalData(&pGdata);
	
    while (!eventList.isEmpty()) {
        if(!processEvent(eventList[0], bList, pGdata))
            cout << eventList[0].code << " is an invalid event\n";
        eventList.removeHead();
    }
	
	releaseNinjaGlobalData(pGdata);
}

bool initNinjaGlobalData(void** pGData) {
    /// TODO: You should define this function if you would like to use some extra data
    /// the data should be allocated and pass the address into pGData
    return true;
}
void releaseNinjaGlobalData(void* pGData) {
    /// TODO: You should define this function if you allocated extra data at initialization stage
    /// The data pointed by pGData should be released
}
void printNinjaInfo(NinjaInfo_t& b) {
    printf("%s: (%0.5f, %0.5f), %s\n", b.id, b.longitude, b.latitude, ctime(&b.timestamp));
}

/// This function converts decimal degrees to radians
double deg2rad(double deg) {
    return (deg * pi / 180);
}

///  This function converts radians to decimal degrees
double rad2deg(double rad) {
    return (rad * 180 / pi);
}

/**
 * Returns the distance between two points on the Earth.
 * Direct translation from http://en.wikipedia.org/wiki/Haversine_formula
 * @param lat1d Latitude of the first point in degrees
 * @param lon1d Longitude of the first point in degrees
 * @param lat2d Latitude of the second point in degrees
 * @param lon2d Longitude of the second point in degrees
 * @return The distance between the two points in kilometers
 */
double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d) {
    double lat1r, lon1r, lat2r, lon2r, u, v;
    lat1r = deg2rad(lat1d);
    lon1r = deg2rad(lon1d);
    lat2r = deg2rad(lat2d);
    lon2r = deg2rad(lon2d);
    u = sin((lat2r - lat1r)/2);
    v = sin((lon2r - lon1r)/2);
    return 2.0 * earthRadiusKm * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));
}
