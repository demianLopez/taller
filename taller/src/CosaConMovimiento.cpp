#include "CosaConMovimiento.h"

// Inicializa cosa quieta en (x,y), (0,0) por defecto.
CosaConMovimiento::CosaConMovimiento(float x, float y) {
	posicion.set(x, y);
	velocidad.set(0, 0);
	mirandoParaLaDerecha = true;
}

// Mueve la posicion de la cosa dependiendo de su velocidad.
void CosaConMovimiento::mover(int delta) {
	posicion.aumentarEn(velocidad.x * delta, velocidad.y * delta);
	if (velocidad.x < 0) {
		mirandoParaLaDerecha = false;
	}
	if (velocidad.x > 0) {
		mirandoParaLaDerecha = true;
	}
	/* x == 0: queda como estaba*/
}

// Devuelve la posicion actual.
VectorXY CosaConMovimiento::verPosicionActual() {
	return VectorXY(posicion);
}

// Devuelve la posicion a la que se movera la cosa.
VectorXY CosaConMovimiento::siguientePosicion() {
	VectorXY vector = VectorXY(posicion);
	vector.aumentarEn(velocidad);
	return vector;
}

// Frena la cosa en X y/o Y
void CosaConMovimiento::frenar(bool frenarEnX, bool frenarEnY) {
	if (frenarEnX) {
		velocidad.x = 0;
	}
	if (frenarEnY) {
		velocidad.y = 0;
	}
}

// Devuelve true si esta mirando para la derecha.
bool CosaConMovimiento::estaMirandoParaLaDerecha() {
	return mirandoParaLaDerecha;
}

