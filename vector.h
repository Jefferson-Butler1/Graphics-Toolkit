/**
 * @file vector.h
 * @author Carson Reader
 * @brief A library of functions for working with 2D and 3D vectors.
 * @version 0.1
 * @date 2024-01-23
 */

#ifndef VECTOR_H
#define VECTOR_H

/**
 * @struct Vector3
 * @brief Represents a 3D vector with x, y, and z components.
 */
typedef struct Vector3 {
  double x;
  double y;
  double z;
} Vector3;

/**
 * Creates a new Vector3 object with the specified coordinates.
 *
 * @param x The x-coordinate of the vector.
 * @param y The y-coordinate of the vector.
 * @param z The z-coordinate of the vector.
 * @return The newly created Vector3 object.
 */
Vector3 vec3_new(double x, double y, double z);

/**
 * Calculates the magnitude of a 3D vector.
 *
 * @param v The vector for which to calculate the magnitude.
 * @return The magnitude of the vector.
 */
double vec3_magnitude(Vector3 v);

/**
 * @brief Normalize a 3D vector.
 *
 * This function normalizes a given 3D vector, making its length equal to 1.
 *
 * @param v Pointer to the Vector3 structure representing the vector to be
 * normalized.
 */
void vec3_normalize(Vector3 *v);

/**
 * Normalizes a Vector3.
 *
 * This function takes a Vector3 as input and returns a normalized version of
 * it. The normalized vector has the same direction as the original vector, but
 * its length is 1.
 *
 * @param v The Vector3 to be normalized.
 * @return The normalized Vector3.
 */
Vector3 vec3_normalized(Vector3 v);

/**
 * Adds two 3D vectors.
 *
 * @param a The first vector.
 * @param b The second vector.
 * @return The sum of the two vectors.
 */
Vector3 vec3_add(Vector3 a, Vector3 b);

/**
 * Subtracts two vectors.
 *
 * @param a The first vector.
 * @param b The second vector.
 * @return The resulting vector after subtracting b from a.
 */
Vector3 vec3_sub(Vector3 a, Vector3 b);

/**
 * Multiplies two Vector3 objects element-wise.
 *
 * @param a The first Vector3 object.
 * @param b The second Vector3 object.
 * @return The resulting Vector3 object after element-wise multiplication.
 */
Vector3 vec3_mult(Vector3 a, Vector3 b);

/**
 * Divides two vectors element-wise.
 *
 * @param a The first vector.
 * @param b The second vector.
 * @return The resulting vector after element-wise division.
 */
Vector3 vec3_div(Vector3 a, Vector3 b);

/**
 * Scales a Vector3 by a given scale factor.
 *
 * @param scale The scale factor to multiply the Vector3 by.
 * @return The scaled Vector3.
 */
Vector3 vec3_scale(double scale);

/**
 * Creates a list of Vector3 objects.
 *
 * This function takes arrays of x, y, and z coordinates and creates a list of
 * Vector3 objects.
 *
 * @param x An array of x coordinates.
 * @param y An array of y coordinates.
 * @param z An array of z coordinates.
 * @param n The number of elements in the arrays.
 * @return A pointer to the created list of Vector3 objects.
 */
Vector3 *vec3_create_list(double x[], double y[], double z[], int n);

/**
 * @struct Vector2
 * @brief Represents a 2D vector with x and y components.
 */
typedef struct Vector2 {
  double x;
  double y;
} Vector2;

/**
 * Calculates the magnitude of a 2D vector.
 *
 * @param v The 2D vector.
 * @return The magnitude of the vector.
 */
double vec2_magnitude(Vector2 v);

/**
 * @brief Normalize a 2D vector.
 *
 * This function normalizes a 2D vector, making its length equal to 1.
 *
 * @param v The vector to be normalized.
 */
void vec2_normalize(Vector2 *v);

/**
 * Calculates the normalized vector of a given Vector2.
 *
 * @param v The Vector2 to be normalized.
 * @return The normalized Vector2.
 */
Vector2 vec2_normalized(Vector2 v);

/**
 * Adds two 2D vectors.
 *
 * @param a The first vector.
 * @param b The second vector.
 * @return The sum of the two vectors.
 */
Vector2 vec2_add(Vector2 a, Vector2 b);

/**
 * Subtracts two 2D vectors.
 *
 * @param a The first vector.
 * @param b The second vector.
 * @return The result of subtracting vector b from vector a.
 */
Vector2 vec2_sub(Vector2 a, Vector2 b);

/**
 * Multiplies two 2D vectors element-wise.
 *
 * @param a The first vector.
 * @param b The second vector.
 * @return The resulting vector after element-wise multiplication.
 */
Vector2 vec2_mult(Vector2 a, Vector2 b);
/**
 * Divides two 2D vectors.
 *
 * @param a The first vector.
 * @param b The second vector.
 * @return The result of dividing vector a by vector b.
 */
Vector2 vec2_div(Vector2 a, Vector2 b);

/**
 * @brief Scales a 2D vector by a given scale factor.
 *
 * This function multiplies both the x and y components of the vector by the
 * given scale factor.
 *
 * @param scale The scale factor to multiply the vector by.
 * @return The scaled vector.
 */
Vector2 vec2_scale(Vector2 v, double scale);

#endif