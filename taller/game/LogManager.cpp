/*
 * LogManager.cpp
 *
 *  Created on: 15/9/2014
 *      Author: FireHorse
 */

#include "LogManager.h"

const char* RUTA_LOG = "Resources/log.txt";

const int ERROR = 1;
const int WARNING = 2;
const int FATAL_ERROR = 3;

LogManager::LogManager() {
	// TODO Auto-generated constructor stub

}

LogManager::~LogManager() {
	// TODO Auto-generated destructor stub
}

void LogManager::reportarProblema(string descripcionError, int nivel){
	ofstream log(RUTA_LOG, ios::out | ios::app);
	if (log.is_open()){
		if(nivel == ERROR)
			log << "\nERROR: " << descripcionError;
		if(nivel == WARNING)
			log << "\nWARNING: " << descripcionError;
		if(nivel == FATAL_ERROR)
			log << "\nFATAL_ERROR: " << descripcionError;
	}
	log.close();
}

void LogManager::setearFecha(){
	time_t rawtime;
	struct tm * timeinfo;
	ofstream log(RUTA_LOG, ios::out | ios::app);
	time ( &rawtime );
	timeinfo = localtime ( &rawtime );
	log << "\n************************NUEVO LOG***************************\n";//La hora solo se coloca para un nuevo log
	log << "Fecha: " <<  asctime (timeinfo);
	log.close();
}
