#ifndef UTILERIA_H_INCLUDED
#define UTILERIA_H_INCLUDED

/** \brief función que captura un entero con formato adecuado
 *
 * \param solicitud Cadena de caracteres que solicita el dato a capturar
 *
 * \return El entero capturado
*/
int capturarEntero(const char solicitud[]);

/** \brief función que captura un real doble con formato adecuado
 *
 * \param solicitud Cadena de caracteres que solicita el dato a capturar
 *
 * \return El real capturado
*/
double capturarReal(const char solicitud[]);

#endif // UTILERIA_H_INCLUDED