#ifndef VECTORXY_H_
#define VECTORXY_H_

// Vector de dos coordenadas, x e y,
// se acceden/modifican sus valores directamente.
class VectorXY {
public:
	float x;
	float y;

	// Se crea por defecto en (0, 0)
	VectorXY(float x = 0, float y = 0);

	// Se crea en la misma posicion que vector.
	VectorXY(VectorXY vector);

	// Setea valores de x e y.
	void set(float x, float y);

	// Aumenta valores en x e y.
	void aumentarEn(float x, float y);
	void aumentarEn(VectorXY vector);
};

#endif /* VECTORXY_H_ */
