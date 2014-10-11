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
#include "Thread.h"


void* Thread::starter(void* args) {
	Thread* thread = (Thread*) args;
	thread->run_func(thread->run_data);
	return NULL;
}

Thread::Thread(thread_run_func_t run_func, thread_run_data_t run_data){

	this->_thread = 0;
	this->run_func = run_func;
	this->run_data = run_data;

}

Thread::~Thread(){
	this->join();
}

void Thread::start() {
	pthread_create(&this->_thread, NULL, starter,this);
}

void Thread::join() {
	pthread_join(this->_thread, NULL);
}
