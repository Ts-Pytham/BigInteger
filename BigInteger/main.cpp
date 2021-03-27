#include <iostream>
#include <stdio.h>
#include "BigInteger.hpp"
using std::string;

//Funciones

void probandoBigInteger();


int main()
{
    probandoBigInteger();

}


void probandoBigInteger() {
    BigInteger bi, bi2;

    std::cout << "Ingrese el valor del primer BigInteger" << std::endl;
    std::cin >> bi;
    std::cout << "Ingrese el valor del segundo BigInteger" << std::endl;
    std::cin >> bi2;

    BigInteger sum = bi + bi2;
    BigInteger res = bi - bi2;

    if (bi == bi2)
        std::cout << "Los numeros son iguales" << std::endl;

    std::cout << "La suma es: " << sum << std::endl;
    std::cout << "La resta es: " << res << std::endl;



    // Valor de suma incrementada y valor de suma con otro valor
    ++sum;
    std::cout << "el valor de suma incremento es: " << sum << std::endl;
    --sum;
    std::cout << "el valor de suma deincremento es: " << sum << std::endl;
    BigInteger suma = sum + 3;
    std::cout << "El valor de suma con un valor int es: " << suma << std::endl;
}
