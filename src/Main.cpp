/*
 *--------------------------------------------------------------------
 * AnomieVision | Plugin | ProjectM | WASM
 *--------------------------------------------------------------------
 */

#include "FPSLimiter.h"
#include "Settings.h"

#include <GL/gl.h>
#include <SDL.h>
#include <emscripten.h>
#include <emscripten/bind.h>
#include <libprojectM/projectM.h>

/*
 *--------------------------------------------------------------------
 * Variables
 *--------------------------------------------------------------------
 */

struct ProjectM {
  projectm_handle pm{nullptr};
  projectm_settings settings;
} projectm;

struct SDL {
  SDL_Window *window{nullptr};
  SDL_Renderer *renderer{nullptr};

  FPSLimiter limiter;
  int _renderWidth{0};
  int _renderHeight{0};

  SDL_AudioDeviceID audioInputDevice{0};
  int audioInputDevicesCount{0};
  int audioInputDeviceIndex{0};
  int audioChannelsCount{0};
} sdl;

/*
 *--------------------------------------------------------------------
 * Emscripten
 *--------------------------------------------------------------------
 */

EM_JS(int, getCanvasWidth, (), { return canvas.width; });
EM_JS(int, getCanvasHeight, (), { return canvas.height; });

/*
 *--------------------------------------------------------------------
 * Settings
 *--------------------------------------------------------------------
 */

Settings settings;

void initSettings() {
  projectm.settings.mesh_x = settings._options.mesh_x;
  projectm.settings.mesh_y = settings._options.mesh_y;
  projectm.settings.fps = settings._options.fps;
  projectm.settings.texture_size = settings._options.texture_size;
  projectm.settings.window_width = settings._options.window_width;
  projectm.settings.window_height = settings._options.window_height;
  projectm.settings.preset_duration = settings._options.preset_duration;
  projectm.settings.soft_cut_duration = settings._options.soft_cut_duration;
  projectm.settings.hard_cut_duration = settings._options.hard_cut_duration;
  projectm.settings.hard_cut_enabled = settings._options.hard_cut_enabled;
  projectm.settings.hard_cut_sensitivity =
      settings._options.hard_cut_sensitivity;
  projectm.settings.beat_sensitivity = settings._options.beat_sensitivity;
  projectm.settings.aspect_correction = settings._options.aspect_correction;
  projectm.settings.easter_egg = settings._options.easter_egg;
  projectm.settings.shuffle_enabled = settings._options.shuffle_enabled;
  projectm.settings.soft_cut_ratings_enabled =
      settings._options.soft_cut_ratings_enabled;
  projectm.settings.preset_url = settings._options.preset_path;
  projectm.settings.title_font_url = settings._options.title_font_path;
  projectm.settings.menu_font_url = settings._options.menu_font_path;
}

/*
 *--------------------------------------------------------------------
 * Audio
 *--------------------------------------------------------------------
 */

void generateRandomAudioData() {
  short pcm_data[2][512];

  for (int i = 0; i < 512; i++) {
    pcm_data[0][i] =
        static_cast<short>((static_cast<double>(rand()) /
                            (static_cast<double>(RAND_MAX)) * (pow(2, 14))));
    pcm_data[1][i] =
        static_cast<short>((static_cast<double>(rand()) /
                            (static_cast<double>(RAND_MAX)) * (pow(2, 14))));

    if (i % 2 == 1) {
      pcm_data[0][i] = -pcm_data[0][i];
      pcm_data[1][i] = -pcm_data[1][i];
    }
  }

  projectm_pcm_add_int16(projectm.pm, &pcm_data[0][0], 512, PROJECTM_STEREO);
}

/*
 *--------------------------------------------------------------------
 * ProjectM
 *--------------------------------------------------------------------
 */

void presetSwitchedEvent(bool isHardCut, unsigned int index, void *context) {
  auto presetName = projectm_get_preset_name(projectm.pm, index);
  SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Displaying preset: %s\n",
              presetName);

  std::string newTitle = "projectM ➫ " + std::string(presetName);
  projectm_free_string(presetName);

  SDL_SetWindowTitle(sdl.window, newTitle.c_str());
}

void initProjectM() {
  if (settings._options.shuffle_enabled) {
    projectm_select_random_preset(projectm.pm, true);
  } else {
    projectm_select_next_preset(projectm.pm, true);
  }

  projectm_set_preset_switched_event_callback(projectm.pm, &presetSwitchedEvent,
                                              nullptr);

  projectm_set_window_size(projectm.pm, settings._options.window_width,
                           settings._options.window_height);
}

void projectmRestart() {
  printf("Restarting Instance!\n");

  projectm_destroy(projectm.pm);

  initSettings();
  projectm.pm =
      projectm_create_settings(&(projectm.settings), PROJECTM_FLAG_NONE);

  initProjectM();

  sdl.limiter.TargetFPS(settings._options.fps);
}

/*
 *--------------------------------------------------------------------
 * ProjectM Interface
 *--------------------------------------------------------------------
 */

// MeshX
int projectmGetMeshX() {
  size_t *meshX;
  size_t *meshY;
  projectm_get_mesh_size(projectm.pm, meshX, meshY);

  return *meshX;
};
void projectmSetMeshX(size_t mesh_x) {
  settings._options.mesh_x = mesh_x;
  projectm_set_mesh_size(projectm.pm, mesh_x, settings._options.mesh_y);
};

// MeshY
int projectmGetMeshY() {
  size_t *meshX;
  size_t *meshY;
  projectm_get_mesh_size(projectm.pm, meshX, meshY);

  return *meshY;
};
void projectmSetMeshY(size_t mesh_y) {
  settings._options.mesh_y = mesh_y;
  projectm_set_mesh_size(projectm.pm, settings._options.mesh_x, mesh_y);
};

// FPS
int projectmGetFps() { return projectm_get_fps(projectm.pm); };

void projectmSetFps(int fps) {
  settings._options.fps = fps;
  projectm.settings.fps = settings._options.fps;
}

// TextureSize
int projectmGetTextureSize() { return projectm_get_texture_size(projectm.pm); };
void projectmSetTextureSize(int texture_size) {
  settings._options.texture_size = texture_size;
  projectm_set_texture_size(projectm.pm, texture_size);
}

// PresetDuration
int projectmGetPresetDuration() { return settings._options.preset_duration; };
void projectmSetPresetDuration(double seconds) {
  settings._options.preset_duration = seconds;
  projectm_set_preset_duration(projectm.pm, seconds);
};

// SoftCutDuration
int projectmGetSoftCutDuration() {
  return projectm_get_soft_cut_duration(projectm.pm);
};
void projectmSetSoftCutDuration(double seconds) {
  settings._options.soft_cut_duration = seconds;
  projectm_set_soft_cut_duration(projectm.pm, seconds);
};

// HardCutDuration
int projectmGetHardCutDuration() {
  return projectm_get_hard_cut_duration(projectm.pm);
};
void projectmSetHardCutDuration(double seconds) {
  settings._options.hard_cut_duration = seconds;
  projectm_set_hard_cut_duration(projectm.pm, seconds);
};

// HardCutEnabled
int projectmGetHardCutEnabled() {
  return projectm_get_hard_cut_enabled(projectm.pm);
};
void projectmSetHardCutEnabled(bool enabled) {
  settings._options.hard_cut_enabled = enabled;
  projectm_set_hard_cut_enabled(projectm.pm, enabled);
};

// HardCutSensitivity
float projectmGetHardCutSensitivity() {
  return projectm_get_hard_cut_sensitivity(projectm.pm);
};
void projectmSetHardCutSensitivity(float sensitivity) {
  settings._options.hard_cut_sensitivity = sensitivity;
  projectm_set_hard_cut_sensitivity(projectm.pm, sensitivity);
};

// BeatSensitivity
float projectmGetBeatSensitivity() {
  return settings._options.beat_sensitivity;
};
void projectmSetBeatSensitivity(float sensitivity) {
  settings._options.beat_sensitivity = sensitivity;
};

// AspectCorrection
int projectmGetAspectCorrection() {
  return projectm_get_aspect_correction(projectm.pm);
};
void projectmSetAspectCorrection(bool enabled) {
  settings._options.aspect_correction = enabled;
  projectm_set_aspect_correction(projectm.pm, enabled);
};

// EasterEgg
float projectmGetEasterEgg() { return projectm_get_easter_egg(projectm.pm); };
void projectmSetEasterEgg(float value) {
  settings._options.easter_egg = value;
  projectm_set_easter_egg(projectm.pm, value);
};

// ShuffleEnabled
int projectmGetShuffleEnabled() {
  return projectm_get_shuffle_enabled(projectm.pm);
};
void projectmSetShuffleEnabled(bool enabled) {
  settings._options.shuffle_enabled = enabled;
  projectm_set_shuffle_enabled(projectm.pm, enabled);
};

// SoftCutRatingsEnabled
int projectmGetSoftCutRatingsEnabled() {
  return settings._options.soft_cut_ratings_enabled;
};
void projectmSetSoftCutRatingsEnabled(bool enabled) {
  settings._options.soft_cut_ratings_enabled = enabled;
};

// SendToastMessage
void projectmSendToastMessage(int message) {
  const char *messageStr = (const char *)message;
  projectm_set_toast_message(projectm.pm, messageStr);
};

// GetPlaylistSize
int projectmGetPlaylistSize() {
  return projectm_get_playlist_size(projectm.pm);
}

// GetPresetIndex
int projectmGetPresetIndex(int preset_name) {
  const char *presetNameStr = (const char *)preset_name;
  return projectm_get_preset_index(projectm.pm, presetNameStr);
}

// IsPresetActive
int projectmIsPresetActive(unsigned int index) {
  return projectm_get_selected_preset_index(projectm.pm, (unsigned int *)index);
}

// GetPresetFilename
int projectmGetPresetFilename(unsigned int index) {
  const char *filename = projectm_get_preset_filename(projectm.pm, index);
  return (int)filename;
}

// GetPresetName
int projectmGetPresetName(unsigned int index) {
  const char *filename = projectm_get_preset_name(projectm.pm, index);
  return (int)filename;
}

// // AddPresetFile
// void projectmAddPresetFile(int preset_file_path, int preset_name, int
// rating_list, int rating_list_length) {
//   // const char* presetFilepathStr = (const char*)preset_file_path;
//   // const char* presetNameStr = (const char*)preset_name;
//   projectm_add_preset_url(projectm.pm, (const char*)preset_file_path, (const
//   char*)preset_name, (int*)rating_list, (unsigned int)rating_list_length);
// }

// // InsertPresetFile
// void projectmInsertPresetFile(int preset_file_path, int preset_name, int
// rating_list, int rating_list_length) {
//   // const char* presetFilepathStr = (const char*)preset_file_path;
//   // const char* presetNameStr = (const char*)preset_name;
//   projectm_insert_preset_url(projectm.pm, (const char*)preset_file_path,
//   (const char*)preset_name, (int*)rating_list, (unsigned
//   int)rating_list_length);
// }

// IsPresetPositionValid
int projectmIsPresetPositionValid() {
  return projectm_preset_position_valid(projectm.pm);
}

// ClearPresetPlaylist
void projectmClearPresetPlaylist() { projectm_clear_playlist(projectm.pm); }

// SelectPreviousPreset
void projectmSelectPreviousPreset(bool hard_cut = false) {
  projectm_select_previous_preset(projectm.pm, hard_cut);
}

// SelectNextPreset
void projectmSelectNextPreset(bool hard_cut = false) {
  projectm_select_next_preset(projectm.pm, hard_cut);
}

// SelectRandomPreset
void projectmSelectRandomPreset(bool hard_cut = false) {
  projectm_select_random_preset(projectm.pm, hard_cut);
}

// IsPresetLocked
void projectmIsPresetLocked() { projectm_is_preset_locked(projectm.pm); }

// LockPreset
void projectmLockPreset(bool lock = false) {
  projectm_lock_preset(projectm.pm, lock);
}

// GetPresetRating
int projectmGetPresetRating(int index, int type) {
  int ratingType;
  if (type == 0) {
    return projectm_get_preset_rating(projectm.pm, (unsigned int)index,
                                      PROJECTM_SOFT_CUT_RATING_TYPE);
  } else if (type == 1) {
    return projectm_get_preset_rating(projectm.pm, (unsigned int)index,
                                      PROJECTM_HARD_CUT_RATING_TYPE);
  }
}

// SetPresetRating
void projectmSetPresetRating(int index, int rating, int type) {
  int ratingType;
  if (type == 0) {
    projectm_set_preset_rating(projectm.pm, (unsigned int)index, rating,
                               PROJECTM_SOFT_CUT_RATING_TYPE);
  } else if (type == 1) {
    projectm_set_preset_rating(projectm.pm, (unsigned int)index, rating,
                               PROJECTM_HARD_CUT_RATING_TYPE);
  }
}

// SelectPresetPosition
void projectmSelectPresetPosition(int index) {
  projectm_select_preset_position(projectm.pm, (unsigned int)index);
}

// SelectPreset
void projectmSelectPreset(int index, bool hard_cut = false) {
  projectm_select_preset(projectm.pm, (unsigned int)index, hard_cut);
}

// RemovePreset
void projectmRemovePreset(int index) {
  projectm_remove_preset(projectm.pm, (unsigned int)index);
}

// PopulatePresetMenu
void projectmPopulatePresetMenu() {
  projectm_populate_preset_menu(projectm.pm);
}

// GetErrorLoadingCurrentPreset
int projectmGetErrorLoadingCurrentPreset() {
  return projectm_get_error_loading_current_preset(projectm.pm);
}

//
/*
 *--------------------------------------------------------------------
 * SDL
 *--------------------------------------------------------------------
 */

/*
 *--------------------------------------------------------------------
 * RenderLoop
 *--------------------------------------------------------------------
 */

void checkViewportSize() {
  int renderWidth = getCanvasWidth();
  int renderHeight = getCanvasHeight();

  if (renderWidth != settings._options.window_width ||
      renderHeight != settings._options.window_height) {
    projectm_set_window_size(projectm.pm, renderWidth, renderHeight);
    settings._options.window_width = renderWidth;
    settings._options.window_height = renderHeight;
  }
}

void renderLoop() {
  sdl.limiter.StartFrame();

  checkViewportSize();

  // _audioCapture.FillBuffer();

  if (sdl.audioChannelsCount > 2 || sdl.audioChannelsCount < 1) {
    generateRandomAudioData();
  }

  glClearColor(0.0, 0.0, 0.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  projectm_render_frame(projectm.pm);
  glFlush();

  SDL_RenderPresent(sdl.renderer);

  sdl.limiter.EndFrame();
}

/*
 *--------------------------------------------------------------------
 * Main
 *--------------------------------------------------------------------
 */

int main(int argc, char *argv[]) {
  // Init Settings
  initSettings();

  // Init SDL
  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

  // Init Emscripten Loop
  emscripten_set_main_loop(renderLoop, 0, 0);

  sdl.window =
      SDL_CreateWindow("projectM", SDL_WINDOWPOS_UNDEFINED,
                       SDL_WINDOWPOS_UNDEFINED, settings._options.window_width,
                       settings._options.window_height, SDL_WINDOW_RESIZABLE);

  sdl.renderer = SDL_CreateRenderer(
      sdl.window, 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  if (!sdl.renderer) {
    fprintf(stderr, "Failed to create renderer: %s\n", SDL_GetError());
    return 1;
  }

  // Init ProjectM
  projectm.pm =
      projectm_create_settings(&(projectm.settings), PROJECTM_FLAG_NONE);

  initProjectM();

  // Set FPS
  sdl.limiter.TargetFPS(settings._options.fps);

  return 0;
}

EMSCRIPTEN_BINDINGS(avPluginProjectMLibrary) {
  emscripten::function("projectmRestart", &projectmRestart);
  emscripten::function("projectmGetMeshX", &projectmGetMeshX);
  emscripten::function("projectmSetMeshX", &projectmSetMeshX);
  emscripten::function("projectmGetMeshY", &projectmGetMeshY);
  emscripten::function("projectmSetMeshY", &projectmSetMeshY);
  emscripten::function("projectmGetFps", &projectmGetFps);
  emscripten::function("projectmSetFps", &projectmSetFps);
  emscripten::function("projectmGetTextureSize", &projectmGetTextureSize);
  emscripten::function("projectmSetTextureSize", &projectmSetTextureSize);
  emscripten::function("projectmGetPresetDuration", &projectmGetPresetDuration);
  emscripten::function("projectmSetPresetDuration", &projectmSetPresetDuration);
  emscripten::function("projectmGetSoftCutDuration",
                       &projectmGetSoftCutDuration);
  emscripten::function("projectmSetSoftCutDuration",
                       &projectmSetSoftCutDuration);
  emscripten::function("projectmGetHardCutDuration",
                       &projectmGetHardCutDuration);
  emscripten::function("projectmSetHardCutDuration",
                       &projectmSetHardCutDuration);
  emscripten::function("projectmGetHardCutEnabled", &projectmGetHardCutEnabled);
  emscripten::function("projectmSetHardCutEnabled", &projectmSetHardCutEnabled);
  emscripten::function("projectmGetHardCutSensitivity",
                       &projectmGetHardCutSensitivity);
  emscripten::function("projectmSetHardCutSensitivity",
                       &projectmSetHardCutSensitivity);
  emscripten::function("projectmGetBeatSensitivity",
                       &projectmGetBeatSensitivity);
  emscripten::function("projectmSetBeatSensitivity",
                       &projectmSetBeatSensitivity);
  emscripten::function("projectmGetAspectCorrection",
                       &projectmGetAspectCorrection);
  emscripten::function("projectmSetAspectCorrection",
                       &projectmSetAspectCorrection);
  emscripten::function("projectmGetEasterEgg", &projectmGetEasterEgg);
  emscripten::function("projectmSetEasterEgg", &projectmSetEasterEgg);
  emscripten::function("projectmGetShuffleEnabled", &projectmGetShuffleEnabled);
  emscripten::function("projectmSetShuffleEnabled", &projectmSetShuffleEnabled);
  emscripten::function("projectmGetSoftCutRatingsEnabled",
                       &projectmGetSoftCutRatingsEnabled);
  emscripten::function("projectmSetSoftCutRatingsEnabled",
                       &projectmSetSoftCutRatingsEnabled);
  emscripten::function("projectmSendToastMessage", &projectmSendToastMessage);
  emscripten::function("projectmGetPlaylistSize", &projectmGetPlaylistSize);
  emscripten::function("projectmGetPresetIndex", &projectmGetPresetIndex);
  emscripten::function("projectmIsPresetActive", &projectmIsPresetActive);
  emscripten::function("projectmGetPresetFilename", &projectmGetPresetFilename);
  emscripten::function("projectmGetPresetName", &projectmGetPresetName);
  // emscripten::function("projectmAddPresetFile", &projectmAddPresetFile);
  // emscripten::function("projectmInsertPresetFile",
  // &projectmInsertPresetFile);
  emscripten::function("projectmIsPresetPositionValid",
                       &projectmIsPresetPositionValid);
  emscripten::function("projectmClearPresetPlaylist",
                       &projectmClearPresetPlaylist);
  emscripten::function("projectmSelectPresetPosition",
                       &projectmSelectPresetPosition);
  emscripten::function("projectmSelectPreset", &projectmSelectPreset);
  emscripten::function("projectmRemovePreset", &projectmRemovePreset);
  emscripten::function("projectmSelectPreviousPreset",
                       &projectmSelectPreviousPreset);
  emscripten::function("projectmSelectNextPreset", &projectmSelectNextPreset);
  emscripten::function("projectmSelectRandomPreset",
                       &projectmSelectRandomPreset);
  emscripten::function("projectmIsPresetLocked", &projectmIsPresetLocked);
  emscripten::function("projectmLockPreset", &projectmLockPreset);
  emscripten::function("projectmGetPresetRating", &projectmGetPresetRating);
  emscripten::function("projectmSetPresetRating", &projectmSetPresetRating);
  emscripten::function("projectmPopulatePresetMenu",
                       &projectmPopulatePresetMenu);
  emscripten::function("projectmGetErrorLoadingCurrentPreset",
                       &projectmGetErrorLoadingCurrentPreset);
};