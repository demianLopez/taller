/**
 logger.cpp

 Copyright 2014 Gaston Martinez Gaston.martinez.90@gmail.com

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses
 */

#include "logger.h"

#include <ctime>
#include <sstream>
#include <iomanip>

using std::string;
using std::stringstream;
using std::setw;
using std::setfill;

string get_date() {
    time_t t = time(0);

    stringstream date;

	struct tm * now = localtime(&t);
	date << setfill('0');

	date << setw(2) << now->tm_mday << "/" << setw(2) << now->tm_mon + 1 << "/"
			<< setw(4) << now->tm_year + 1900 << "   " << setw(2)
			<< now->tm_hour << ":" << setw(2) << now->tm_min << ":" << setw(2)
			<< now->tm_sec;

    return date.str();
}

/*

#Inicializo archivo de log
initializeLog() {

        echo -e "Inicia ejecucion de Installer\n"
        log $0 "INFO" "Inicia ejecucion de Installer"
        echo -e "Log de instalacion: grupo07/conf/installer.log\n"
        log $0 "INFO" "Log de instalacion: grupo07/conf/installer.log"
        echo -e "Directorio de configuracion: grupo07/conf\n"
        log $0 "INFO" "Directorio de configuracion: grupo07/conf"

}


GNU nano 2.2.6                                           Fichero: ../SisopEntrega/grupo07/exe/logging.sh

#!/usr/bin/env bash

CONF_FILE="$CONFDIR/installer.conf" #Hay que poner el que corresponda
TRIM_LOG_SIZE=50

# Receives the name of the env variable to get the value, returns it
getEnvVarValue() {
  VAR_NAME="$1"
  grep "$VAR_NAME" "$CONF_FILE" | sed "s/^[^=]*=\([^=]*\)=.*\$/\1/"
}

# Gets the process calling the logger, returns the correspondant log file
getFilePath() {
  CALLER="$1"
  #LOGDIR=$(getEnvVarValue LOGDIR)
 # LOGEXT=$(getEnvVarValue LOGEXT)
  echo "$LOGDIR/$CALLER.$LOGEXT"
}

# Trims the log file to the last TRIM_LOG_SIZE lines
trimLogFile() {
  FILE="$1"
  AUX_FILE="$1.aux"
  DATE=$(date +"%d/%m/%Y %H:%M:%S")
  echo "$DATE - Log excedido" > "$AUX_FILE"
  tail --lines="$TRIM_LOG_SIZE" "$FILE" >> "$AUX_FILE"
  rm "$FILE"
  mv "$AUX_FILE" "$FILE"
}

# Obtains the file name and LOGSIZE
FILE=$(getFilePath "$1")

touch "$FILE"
LOGSIZE=$(getEnvVarValue LOGSIZE)
# Checks for trimming
FILE_LINES=$(wc -l < "$FILE")
if [ "$FILE_LINES" -gt "$LOGSIZE" ]
then
    trimLogFile "$FILE"
fi
# Logs
if [ "$#" -lt 2 ]
then
    echo -e "\nUso: logging comando mensaje [tipo_mensaje]\n\n\tTipo de mensaje puede ser INFO, WAR o ERR.\n\tSi se omite, por defecto es INFO.\n"
    exit -1
elif [ "$#" -eq 2 ]
then
    log "$1" "$2" "INFO"
else
    log "$1" "$2" "$3"
fi
exit 0
*/
void Logger::log(string log_file,string caller, error_type_t error_type,string error_message)
{
	  string date = get_date();

	  //FILE=$(getFilePath "$CALLER")
	  //echo -e "$DATE - $USER $CALLER $TYPE:$MSG" >> "$FILE"

}
