#include "normal.h"
#include "math.h"

Normal::Normal()
{

}

double Normal::GetLength()
{
    return sqrt(pow(n_vec.x(), 2) + pow(n_vec.y(), 2) + pow(n_vec.z(), 2));
}
