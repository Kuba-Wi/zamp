#ifndef VECTOR3D_HH
#define VECTOR3D_HH

#include "geomVector.hh"

#include <istream>

/*!
 * \file
 * \brief Deklaracja instacji szablonu geom::Vector
 */

 /*!
  * \brief Instacja szablonu geom::Vector<typename,int> dla przestrzeni 3D.
  */
 typedef geom::Vector<double,3>  Vector3D;

inline
std::istream& operator>>(std::istream& stream, Vector3D& vec) {
    stream >> vec[0];
    stream >> vec[1];
    stream >> vec[2];
    return stream;
}

#endif
