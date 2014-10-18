/**
 Thread.cpp

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

#ifndef THREAD_H
#define THREAD_H

#include <pthread.h>

/**
 * Tipo de datos que recibe un thread como parametro
 */
typedef void* thread_run_data_t;
/**
 * Tipo de funcion que recibe un thread como inicio
 */
typedef void (*thread_run_func_t)(thread_run_data_t run_data);

class Thread {
private:
	pthread_t _thread;
	thread_run_func_t run_func;
	thread_run_data_t run_data;

public:
	Thread(thread_run_func_t run_func, thread_run_data_t run_data);
	~Thread();
	void start();
	void join();

public:
	static void* starter(void* thread);

};
#endif
