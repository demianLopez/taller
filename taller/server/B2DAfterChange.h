/*
 * B2DAfterChange.h
 *
 *  Created on: 01/12/2014
 *      Author: demian
 */

#ifndef B2DAFTERCHANGE_H_
#define B2DAFTERCHANGE_H_

class B2DAfterChange {
public:
	//CLASE PARA COSAS QUE TIENE QUE MODIFICAR COSAS DE BOX 2D QUE NO PUEDEN SER
	//MODIFICADAS DENTRO DEL LOOP!
	B2DAfterChange();
	virtual void change() = 0;
	virtual ~B2DAfterChange();
};

#endif /* B2DAFTERCHANGE_H_ */
