/*
 * LogManager.h
 *
 *  Created on: 15/9/2014
 *      Author: FireHorse
 */

#ifndef LOGMANAGER_H_
#define LOGMANAGER_H_

#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
#include <ctime>
using namespace std;

class LogManager {
public:
	LogManager();
	virtual ~LogManager();
	void reportarProblema(string descripcionError, int nivel);

};

#endif /* LOGMANAGER_H_ */
