/**
 * @file scene.h
 * @author Carson Reader
 * @brief Functions and structs to manage and draw objects in the scene. Handles z-buffer and different view modes
 * @version 0.1
 * @date 2024-02-19
 */
#ifndef SCENE_H
#define SCENE_H

#include "FPToolkit.h"
#include "vector.h"
#include "camera.h"
#include "lightmodel.h"

enum ViewMode {
    LIT,
    UNLIT,
    Z_BUFF,
    NORMAL
};

typedef struct {
    Vector3 (*f)(double, double);
    double u_start;
    double u_end;
    double u_step;
    double v_start;
    double v_end;
    double v_step;
    double transform[4][4];
    PhongMaterial material;
} ParametricObject3D;

/**
 * @brief Creates a window with the specified width and height, and initializes the z-buffer
 * 
 * @param width The desired width of the window
 * @param height The desired height of the window
 */
// void init_window(int width, int height);

/**
 * @brief Draws a parametric 3D object in the scene
 * 
 * @param object The Parametric object to draw
 * @param cam The camera to use for the drawing
 * @param lights An array of lights that will be applied to the object
 * @param num_lights The number of lights
 * @param mode the view mode to draw the objects in
 */
void draw_parametric_object3D(ParametricObject3D object, Camera cam, PhongLight* lights, int num_lights,int width, int height, double z_buffer[width][height], enum ViewMode mode);

/**
 * @brief Draws a gizmo to dispaly point lights in the scene
 * 
 * @param light The light to draw
 */
void draw_light(PhongLight light, Camera cam);

/**
 * @brief Clears the screen and resets the z-buffer
 * 
 * @param background_color The background color to set when the screen is cleared
 */
// void clear_frame(Vector3 background_color, int width, int height, double z_buffer[width][height]);

// char wait_key();

#endif