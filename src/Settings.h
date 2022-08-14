#pragma once

#include <string>

/**
 * @brief Collects settings from the EM-JS layer and writes them to WASM
 */
class Settings {

public:
  Settings();

  struct Options {
    int mesh_x;                     // Option 0
    int mesh_y;                     // Option 1
    int fps;                        // Option 2
    int texture_size;               // Option 3
    int window_width;               // Option 4
    int window_height;              // Option 5
    double preset_duration;         // Option 6
    double soft_cut_duration;       // Option 7
    double hard_cut_duration;       // Option 8
    bool hard_cut_enabled;          // Option 9
    float hard_cut_sensitivity;     // Option 10
    float beat_sensitivity;         // Option 11
    bool aspect_correction;         // Option 12
    float easter_egg;               // Option 13
    bool shuffle_enabled;           // Option 14
    bool soft_cut_ratings_enabled;  // Option 15
    char* preset_path;              // Option 16
    char* title_font_path;          // Option 17
    char* menu_font_path;           // Option 18
    bool random_preset_enabled;     // Option 19
  };

  Options _options;

protected:
  /**
  * @brief Query EM-JS layer for setting by index
  */
  void Query(unsigned int index);

};