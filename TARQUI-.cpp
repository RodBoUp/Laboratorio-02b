#include <iostream>
#include <bitset>
#include <cmath>
#include <limits>

using namespace std;
void imprimirBitsFlotante(float valor, const string& proceso);
float multiplicarFlotantes(float a, float b);


int main() {
	float valor1, valor2;
	cout << "Ingrese el primer valor: ";
	cin >> valor1;
	cout << "Ingrese el segundo valor: ";
	cin >> valor2;
	
	//->>>MULTIPLICACION
	float resultado = multiplicarFlotantes(valor1, valor2);
	
	cout << "Patrones de bits de cada proceso:" << endl;
	imprimirBitsFlotante(valor1, "Valor 1");
	imprimirBitsFlotante(valor2, "Valor 2");
	imprimirBitsFlotante(resultado, "Resultado");
	
	return 0;
}

//->>>función para visualizar los patrones de bits de un float
void imprimirBitsFlotante(float valor, const string& proceso) {
	bitset<32> bits(*reinterpret_cast<unsigned*>(&valor));
	cout << proceso << ": " << bits << endl;
}

//->>>multiplicar dos valores en punto flotante
float multiplicarFlotantes(float a, float b) {
	//->>>Proceso para obtener los componentes de los valores
	int signo_a = (a < 0) ? 1 : 0;
	int signo_b = (b < 0) ? 1 : 0;
	int exp_a = log2(abs(a));
	int exp_b = log2(abs(b));
	float mantisa_a = frexp(abs(a), &exp_a);
	float mantisa_b = frexp(abs(b), &exp_b);
	
	//->>>multiplicación de las mantisas
	float resultado_mantisa = mantisa_a * mantisa_b;
	
	//->>>calcular el exponente del resultado
	int resultado_exponente = exp_a + exp_b;
	
	//->>>ensamblar el resultado final
	float resultado = ldexp(resultado_mantisa, resultado_exponente);
	
	//->>>aplicar el signo
	if (signo_a != signo_b) {
		resultado = -resultado;
	}
	
	//->>>Verificar underflow
	if (resultado == 0.0f || abs(resultado) < numeric_limits<float>::min()) {
		cout << "¡Underflow detectado!" << endl;
	}
	//->>>Verificar overflow
	if (isinf(resultado) || resultado > numeric_limits<float>::max()) {
		cout << "¡Overflow detectado!" << endl;
	}
	
	return resultado;
}

