#include <stdio.h>
#include <stdlib.h>
#include "texture.h"
#include "xwd_tools.h"

Texture new_xwd_texture(char* filename){
    Texture result;
    result.id = init_xwd_map_from_file(filename);
    if(result.id == -1){
        fprintf(stderr, "Failed to load XWD file\n");
        exit(1);
    }
    int dimensions[2];
    int status = get_xwd_map_dimensions(result.id, dimensions);
    if(status == -1){
        fprintf(stderr, "Failed to get texture dimensions from file\n");
        exit(1);
    }
    result.width = dimensions[0];
    result.height = dimensions[1];
    return result;
}

Color3 get_texture_color(Texture texture, Vector2 position){
    if(position.x > texture.width || position.y > texture.height || position.x < 0 || position.y < 0){
        fprintf(stderr, "Texture sample out of bounds\n");
        exit(1);
    }
    Color3 result;
    get_xwd_map_color(texture.id, (int)position.x, (int)position.y, (double *)&result);
    return result;
}