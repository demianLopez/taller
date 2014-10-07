/*
 * LogManager.cpp
 *
 *  Created on: 15/9/2014
 *      Author: FireHorse
 */

#include "LogManager.h"
#include "../common/Logger.h"

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
	if(nivel == ERROR)
		Logger::customLog("JSonParser",Logger::ERROR, descripcionError);
	if(nivel == WARNING)
		Logger::customLog("JSonParser",Logger::WARNING, descripcionError);
	if(nivel == FATAL_ERROR)
		Logger::customLog("JSonParser",Logger::ERROR, descripcionError);

}
