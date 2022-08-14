# Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`class `[`FPSLimiter`](#classFPSLimiter) | Limits FPS by adding a delay if necessary. Also keeps track of actual FPS.
`class `[`Settings`](#classSettings) | Collects settings from the EM-JS layer and writes them to WASM.
`struct `[`Settings::Options`](#structSettings_1_1Options) | 
`struct `[`ProjectM`](#structProjectM) | 
`struct `[`SDL`](#structSDL) | 

<br>

# class `FPSLimiter`

Limits FPS by adding a delay if necessary. Also keeps track of actual FPS.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public void `[`TargetFPS`](#classFPSLimiter_1a435f36a86caa55d4bce24d593ace0b6b)`(int fps)` | Sets the target frames per second value.
`public float `[`FPS`](#classFPSLimiter_1ad61b184779b4d4f027db8d4b212a0b53)`() const` | Calculates the current real FPS.
`public void `[`StartFrame`](#classFPSLimiter_1afa33b038f875419986c72001b356b07e)`()` | Marks the start of a new frame.
`public void `[`EndFrame`](#classFPSLimiter_1a0ac95aabedde05df204a49b69af1abc8)`()` | Marks the end of a frame.
`protected uint32_t `[`_lastTickCount`](#classFPSLimiter_1a51f7adf76396f5a379c0804715b9fe5a) | Last [SDL](#structSDL) tick count, when a new frame was started.
`protected uint32_t `[`_targetFrameTime`](#classFPSLimiter_1a2bfc202fa431ef4ea7ff0a9a4df84432) | Targeted time per frame in milliseconds.
`protected uint32_t `[`_lastFrameTimes`](#classFPSLimiter_1a287a2921af8d05283bb34be690b64ca2) | Actual tick time of the last ten frames, including limiting delay.
`protected int `[`_nextFrameTimesOffset`](#classFPSLimiter_1a2b1b60a767325d36c2bebca7a417e7b6) | Next offset to overwrite the _lastFrameTimes ring buffer.

## Members

#### `public void `[`TargetFPS`](#classFPSLimiter_1a435f36a86caa55d4bce24d593ace0b6b)`(int fps)`

Sets the target frames per second value.

#### Parameters
* `fps` The targeted frames per second. Set to 0 for unlimited FPS.

#### `public float `[`FPS`](#classFPSLimiter_1ad61b184779b4d4f027db8d4b212a0b53)`() const`

Calculates the current real FPS.

Frames with zero time are not considered.

#### Returns
The frames per second value as an average over the last ten frames. Zero if all frame times are zero.

#### `public void `[`StartFrame`](#classFPSLimiter_1afa33b038f875419986c72001b356b07e)`()`

Marks the start of a new frame.

Should be the first call in the render loop.

#### `public void `[`EndFrame`](#classFPSLimiter_1a0ac95aabedde05df204a49b69af1abc8)`()`

Marks the end of a frame.

Will pause if required to lower FPS to target value. Also records the last frame time for FPS calculation.

#### `protected uint32_t `[`_lastTickCount`](#classFPSLimiter_1a51f7adf76396f5a379c0804715b9fe5a)

Last [SDL](#structSDL) tick count, when a new frame was started.

#### `protected uint32_t `[`_targetFrameTime`](#classFPSLimiter_1a2bfc202fa431ef4ea7ff0a9a4df84432)

Targeted time per frame in milliseconds.

#### `protected uint32_t `[`_lastFrameTimes`](#classFPSLimiter_1a287a2921af8d05283bb34be690b64ca2)

Actual tick time of the last ten frames, including limiting delay.

#### `protected int `[`_nextFrameTimesOffset`](#classFPSLimiter_1a2b1b60a767325d36c2bebca7a417e7b6)

Next offset to overwrite the _lastFrameTimes ring buffer.

<br>

# class `Settings`

Collects settings from the EM-JS layer and writes them to WASM.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public `[`Options`](#structSettings_1_1Options)` `[`_options`](#classSettings_1a4e585bbfa50d5b0cca9bc064512e315f) | 
`public  `[`Settings`](#classSettings_1ab7169a6eefce79566dd07db3b1e5e967)`()` | 
`protected void `[`Query`](#classSettings_1a04d8d1ce0ab7f3e48102d3f54d4459aa)`(unsigned int index)` | Query EM-JS layer for setting by index.

## Members

#### `public `[`Options`](#structSettings_1_1Options)` `[`_options`](#classSettings_1a4e585bbfa50d5b0cca9bc064512e315f)

#### `public  `[`Settings`](#classSettings_1ab7169a6eefce79566dd07db3b1e5e967)`()`

#### `protected void `[`Query`](#classSettings_1a04d8d1ce0ab7f3e48102d3f54d4459aa)`(unsigned int index)`

Query EM-JS layer for setting by index.

<br>

# struct `Settings::Options`

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public int `[`mesh_x`](#structSettings_1_1Options_1a6687fc58aa7b8d76bf00610bc9e437c9) | 
`public int `[`mesh_y`](#structSettings_1_1Options_1aecb21a4d69332956f3ca86fda83ded0f) | 
`public int `[`fps`](#structSettings_1_1Options_1a417cad20f9fefd444ea214f40e2299f4) | 
`public int `[`texture_size`](#structSettings_1_1Options_1a1da7195c9081e5116952b79b1e458b18) | 
`public int `[`window_width`](#structSettings_1_1Options_1a254376bd86e151e8581e99ab6b9c21ad) | 
`public int `[`window_height`](#structSettings_1_1Options_1af9431cb7d2c84e4f682c6f6b9f9730c7) | 
`public double `[`preset_duration`](#structSettings_1_1Options_1af099bc41d773495c6e44c18142c35ea3) | 
`public double `[`soft_cut_duration`](#structSettings_1_1Options_1a5be6ffb74f4b95400707f4af2073815f) | 
`public double `[`hard_cut_duration`](#structSettings_1_1Options_1a34785ea9e805ddd41cd0c3ccb0919175) | 
`public bool `[`hard_cut_enabled`](#structSettings_1_1Options_1aea296af0b8af34ec88784615b83ccf07) | 
`public float `[`hard_cut_sensitivity`](#structSettings_1_1Options_1a2462c412403b77a22a68024c92a44c45) | 
`public float `[`beat_sensitivity`](#structSettings_1_1Options_1ab2749b7c3e392728e5e22a6707edef4a) | 
`public bool `[`aspect_correction`](#structSettings_1_1Options_1a7be152c37e7cacb8d37bc9e40de6c652) | 
`public float `[`easter_egg`](#structSettings_1_1Options_1a6c85da251424a386873f9598c3270a30) | 
`public bool `[`shuffle_enabled`](#structSettings_1_1Options_1a28ee5074c33aa10a7f3248bc01e44359) | 
`public bool `[`soft_cut_ratings_enabled`](#structSettings_1_1Options_1a7170e6c1a7083c195d608f38821b8b9c) | 
`public char * `[`preset_path`](#structSettings_1_1Options_1af9d3541a5eceb34279bd340a0c6e85cb) | 
`public char * `[`title_font_path`](#structSettings_1_1Options_1a5e27517fdacc4f84738804dc2bfcfdb2) | 
`public char * `[`menu_font_path`](#structSettings_1_1Options_1aa89e8b425afe39958d439d5b7f59d317) | 
`public bool `[`random_preset_enabled`](#structSettings_1_1Options_1a77a3227c8267b97737dc3ea01b7d5a5f) | 

## Members

#### `public int `[`mesh_x`](#structSettings_1_1Options_1a6687fc58aa7b8d76bf00610bc9e437c9)

#### `public int `[`mesh_y`](#structSettings_1_1Options_1aecb21a4d69332956f3ca86fda83ded0f)

#### `public int `[`fps`](#structSettings_1_1Options_1a417cad20f9fefd444ea214f40e2299f4)

#### `public int `[`texture_size`](#structSettings_1_1Options_1a1da7195c9081e5116952b79b1e458b18)

#### `public int `[`window_width`](#structSettings_1_1Options_1a254376bd86e151e8581e99ab6b9c21ad)

#### `public int `[`window_height`](#structSettings_1_1Options_1af9431cb7d2c84e4f682c6f6b9f9730c7)

#### `public double `[`preset_duration`](#structSettings_1_1Options_1af099bc41d773495c6e44c18142c35ea3)

#### `public double `[`soft_cut_duration`](#structSettings_1_1Options_1a5be6ffb74f4b95400707f4af2073815f)

#### `public double `[`hard_cut_duration`](#structSettings_1_1Options_1a34785ea9e805ddd41cd0c3ccb0919175)

#### `public bool `[`hard_cut_enabled`](#structSettings_1_1Options_1aea296af0b8af34ec88784615b83ccf07)

#### `public float `[`hard_cut_sensitivity`](#structSettings_1_1Options_1a2462c412403b77a22a68024c92a44c45)

#### `public float `[`beat_sensitivity`](#structSettings_1_1Options_1ab2749b7c3e392728e5e22a6707edef4a)

#### `public bool `[`aspect_correction`](#structSettings_1_1Options_1a7be152c37e7cacb8d37bc9e40de6c652)

#### `public float `[`easter_egg`](#structSettings_1_1Options_1a6c85da251424a386873f9598c3270a30)

#### `public bool `[`shuffle_enabled`](#structSettings_1_1Options_1a28ee5074c33aa10a7f3248bc01e44359)

#### `public bool `[`soft_cut_ratings_enabled`](#structSettings_1_1Options_1a7170e6c1a7083c195d608f38821b8b9c)

#### `public char * `[`preset_path`](#structSettings_1_1Options_1af9d3541a5eceb34279bd340a0c6e85cb)

#### `public char * `[`title_font_path`](#structSettings_1_1Options_1a5e27517fdacc4f84738804dc2bfcfdb2)

#### `public char * `[`menu_font_path`](#structSettings_1_1Options_1aa89e8b425afe39958d439d5b7f59d317)

#### `public bool `[`random_preset_enabled`](#structSettings_1_1Options_1a77a3227c8267b97737dc3ea01b7d5a5f)

<br>

# struct `ProjectM` {#structProjectM}

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public projectm_handle `[`pm`](#structProjectM_1a90a10ee95dd600f3e119a2e5ca38bafc) | 
`public projectm_settings `[`settings`](#structProjectM_1ac4dbf8ed3aadee6ca80ead4a36d81b80) | 

## Members

#### `public projectm_handle `[`pm`](#structProjectM_1a90a10ee95dd600f3e119a2e5ca38bafc)

#### `public projectm_settings `[`settings`](#structProjectM_1ac4dbf8ed3aadee6ca80ead4a36d81b80)

<br>

# struct `SDL`

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public SDL_Window * `[`window`](#structSDL_1a1c76b719378ee62643e0109a3c2868a6) | 
`public SDL_Renderer * `[`renderer`](#structSDL_1a68caa2287d045bb863281dfd6a18aece) | 
`public `[`FPSLimiter`](#classFPSLimiter)` `[`limiter`](#structSDL_1a60b0f974e0c3768d2062e7a623c53957) | 
`public int `[`_renderWidth`](#structSDL_1a73f654b3d4871881a101bdb56f140f4d) | 
`public int `[`_renderHeight`](#structSDL_1aae5a6a0a36492b8ede29bc29582e7485) | 
`public SDL_AudioDeviceID `[`audioInputDevice`](#structSDL_1ae8a6df0d3e37b831f6f89e6a1929ceee) | 
`public int `[`audioInputDevicesCount`](#structSDL_1afd57d4f14a9937d2006ba447f4e00e0d) | 
`public int `[`audioInputDeviceIndex`](#structSDL_1a24954e5ab690b8543f69c0883e39ff00) | 
`public int `[`audioChannelsCount`](#structSDL_1a1e55278622d89073dc8cc9a79ebd63a3) | 

## Members

#### `public SDL_Window * `[`window`](#structSDL_1a1c76b719378ee62643e0109a3c2868a6)

#### `public SDL_Renderer * `[`renderer`](#structSDL_1a68caa2287d045bb863281dfd6a18aece)

#### `public `[`FPSLimiter`](#classFPSLimiter)` `[`limiter`](#structSDL_1a60b0f974e0c3768d2062e7a623c53957)

#### `public int `[`_renderWidth`](#structSDL_1a73f654b3d4871881a101bdb56f140f4d)

#### `public int `[`_renderHeight`](#structSDL_1aae5a6a0a36492b8ede29bc29582e7485)

#### `public SDL_AudioDeviceID `[`audioInputDevice`](#structSDL_1ae8a6df0d3e37b831f6f89e6a1929ceee)

#### `public int `[`audioInputDevicesCount`](#structSDL_1afd57d4f14a9937d2006ba447f4e00e0d)

#### `public int `[`audioInputDeviceIndex`](#structSDL_1a24954e5ab690b8543f69c0883e39ff00)

#### `public int `[`audioChannelsCount`](#structSDL_1a1e55278622d89073dc8cc9a79ebd63a3)
