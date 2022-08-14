#include "Settings.h"

#include <emscripten.h>
#include <libprojectM/projectM.h>

Settings::Settings() {
  for (int i = 0; i <= 19; i++) {
    Settings::Query(i);
  }
}

void Settings::Query(unsigned int index) {
  char *key{NULL};
  int currentValue{NULL};
  int value{NULL};
  double dValue{NULL};
  char *sValue{NULL};

  switch (index) {
  case 0:
    key = (char *)"mesh_x";
    value = EM_ASM_INT({ return loadSetting($0); }, index);
    _options.mesh_x = value;
    break;

  case 1:
    key = (char *)"mesh_y";
    value = EM_ASM_INT({ return loadSetting($0); }, index);
    _options.mesh_y = value;
    break;

  case 2:
    key = (char *)"fps";
    value = EM_ASM_INT({ return loadSetting($0); }, index);
    _options.fps = value;
    break;

  case 3:
    key = (char *)"texture_size";
    value = EM_ASM_INT({ return loadSetting($0); }, index);
    _options.texture_size = value;
    break;

  case 4:
    key = (char *)"window_width";
    value = EM_ASM_INT({ return loadSetting($0); }, index);
    _options.window_width = value;
    break;

  case 5:
    key = (char *)"window_height";
    value = EM_ASM_INT({ return loadSetting($0); }, index);
    _options.window_height = value;
    break;

  case 6:
    key = (char *)"preset_duration";
    value = EM_ASM_INT({ return loadSetting($0); }, index);
    _options.preset_duration = value;
    break;

  case 7:
    key = (char *)"soft_cut_duration";
    value = EM_ASM_INT({ return loadSetting($0); }, index);
    _options.soft_cut_duration = value;
    break;

  case 8:
    key = (char *)"hard_cut_duration";
    value = EM_ASM_INT({ return loadSetting($0); }, index);
    _options.hard_cut_duration = value;
    break;

  case 9:
    key = (char *)"hard_cut_enabled";
    value = EM_ASM_INT({ return loadSetting($0); }, index);
    _options.hard_cut_enabled = value;
    break;

  case 10:
    key = (char *)"hard_cut_sensitivity";
    dValue = EM_ASM_DOUBLE({ return loadSetting($0); }, index);
    _options.hard_cut_sensitivity = dValue;
    break;

  case 11:
    key = (char *)"beat_sensitivity";
    dValue = EM_ASM_DOUBLE({ return loadSetting($0); }, index);
    _options.beat_sensitivity = dValue;
    break;

  case 12:
    key = (char *)"aspect_correction";
    value = EM_ASM_INT({ return loadSetting($0); }, index);
    _options.aspect_correction = value;
    break;

  case 13:
    key = (char *)"easter_egg";
    dValue = EM_ASM_DOUBLE({ return loadSetting($0); }, index);
    _options.easter_egg = dValue;
    break;

  case 14:
    key = (char *)"shuffle_enabled";
    value = EM_ASM_INT({ return loadSetting($0); }, index);
    _options.shuffle_enabled = value;
    break;

  case 15:
    key = (char *)"soft_cut_ratings_enabled";
    value = EM_ASM_INT({ return loadSetting($0); }, index);
    _options.soft_cut_ratings_enabled = value;
    break;

  case 16:
    key = (char *)"preset_path";
    sValue = (char *)EM_ASM_INT(
        {
          const temp = loadSetting($0);
          const byteCount = (Module.lengthBytesUTF8(temp) + 1);

          const tempPointer = Module._malloc(byteCount);
          Module.stringToUTF8(temp, tempPointer, byteCount);

          return tempPointer;
        },
        index);
    _options.preset_path = sValue;
    break;

  case 17:
    key = (char *)"title_font_path";
    sValue = (char *)EM_ASM_INT(
        {
          const temp = loadSetting($0);
          const byteCount = (Module.lengthBytesUTF8(temp) + 1);

          const tempPointer = Module._malloc(byteCount);
          Module.stringToUTF8(temp, tempPointer, byteCount);

          return tempPointer;
        },
        index);
    _options.title_font_path = sValue;
    break;

  case 18:
    key = (char *)"menu_font_path";
    sValue = (char *)EM_ASM_INT(
        {
          const temp = loadSetting($0);
          const byteCount = (Module.lengthBytesUTF8(temp) + 1);

          const tempPointer = Module._malloc(byteCount);
          Module.stringToUTF8(temp, tempPointer, byteCount);

          return tempPointer;
        },
        index);
    _options.menu_font_path = sValue;
    break;

  case 19:
    key = (char *)"random_preset_enabled";
    value = EM_ASM_INT({ return loadSetting($0); }, index);
    _options.random_preset_enabled = value;
    break;
  }

  if (sValue != NULL) {
    printf("Settings > [Key: %s | Value: %s]\n", key, sValue);
  } else if (dValue != NULL) {
    printf("Settings > [Key: %s | Value: %f]\n", key, dValue);
  } else {
    printf("Settings > [Key: %s | Value: %d]\n", key, value);
  }
}
