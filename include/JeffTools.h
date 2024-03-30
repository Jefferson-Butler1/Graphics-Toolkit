#define NO_INTERSECTION 0
#include "vector.h"
#include "colors.h"


#define SPREAD_MAT4(array) \
    {                                \
        {array[0][0], array[0][1], array[0][2], array[0][3]}, \
        {array[1][0], array[1][1], array[1][2], array[1][3]}, \
        {array[2][0], array[2][1], array[2][2], array[2][3]}, \
        {array[3][0], array[3][1], array[3][2], array[3][3]}  \
    }

typedef enum {
    LINE = 0,
    CIRCLE = 1,
    HYPERBOLA = 2,
} Shape;

typedef union Ray {
    struct {
        Vector3 source;
        Vector3 tip;
    };
    struct {
        Vector3 worldSpace;
        Vector3 objectSpace;
    };
} Ray;


typedef struct ParametricObj
{
    double matrix  [4][4] ; // Matrix to transform the object from its own coordinate system into world coordinates.
    double matrixI [4][4] ;
    Shape type;
    Color3 color;
    double tLo;
    double tHi;
    int (*getPoint)(double, double[4][4], Vector3**);
}ParametricObj;


/**
 * @brief returns an int which signifies whether it intersected, and places the intersect in the pointer  provided.
 * @param obj The ParametricObj to be intersected
 * @param ray The ray which is intersecting it
 * @param result 
*/
int intersectRayWithObject(ParametricObj obj, Ray ray, Vector3 *result);




int printParametricObj(ParametricObj obj);
int drawRay(Ray ray, double length);
int tValid(ParametricObj obj, double t);