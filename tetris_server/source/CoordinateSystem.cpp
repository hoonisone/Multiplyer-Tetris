#include <windows.h>
#include "CoordinateSystem.h"
CoordinateSystem &createCuusor() {
	static CoordinateSystem object = CoordinateSystem(1, 1);
	return object;
}
CoordinateSystem &createPoint() {
	static CoordinateSystem object = CoordinateSystem(2, 1);
	return object;
}