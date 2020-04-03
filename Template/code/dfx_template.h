// ---------------------------------------------------------------------
// STARTHEADER
//
// ver: 0.0007
// engineReq: 7.82
// date: 200403
//
// title: Default materials overwrite
// help: Overwrite default materials by a set of pixel side shaded materials
// class: D3DFX
// type: USER
//
// prefix: dfx_
// idcode: 1008
//
// ENDHEADER
// ---------------------------------------------------------------------

#ifndef _DFX_MTL_DEFAULT_H_
	#define _DFX_MTL_DEFAULT_H_
	
	#define PRAGMA_PATH "%EXE_DIR%\\templates\\dfx_template"
	
	#include <d3d9.h>
	
	STRING *dfx_str_temp = "";
	
	/********************************************************************/
	
	//section:
	//section: General settings
	//-------------------------------------------
	
	STRING *dfx_str_gbl_header = "
		//enable: Enable albedo texture
		//id:1
		#define _DFX_ALBEDO_
		
		//enable: Enable lightmapping
		//id:2
		#define _DFX_LIGHTMAP_
		
		//enable: Enable normalmapping
		//id:3
		#define _DFX_NORMALMAP_
		
		//section:
		
		//enable: Enable sun lighting
		//id:10
		#define _DFX_SUN_LIGHT_
		
		//enable: Enable ambient lighting
		//id:11
		#define _DFX_AMBIENT_
		
		//enable: Enable diffuse lighting
		//id:12
		#define _DFX_DIFFUSE_
		
		//enable: Enable specular reflections
		//id:13
		#define _DFX_SPECULAR_
		
		//enable: Enable emissive color
		//id:14
		#define _DFX_EMISSIVE_
		
		//enable: Enable PRV
		//id:15
		#define _DFX_PRV_
		
		//enable: Enable dynamic lights
		//id:16
		#define _DFX_DYN_LIGHTS_
		
		//enable: Enable SPOTLIGHT entity flag
		//id:17
		#define _DFX_SPOTLIGHT_
		
		//entry: Dynamic lights power
		//cntl: slider -100 100 1
 		//id:18
		float lightsPower = 25;
		
		//section:
		
		//enable: Enable fog
		//id:20
		#define _DFX_FOG_
		
		//section:
		
		//enable: Enable gamma
		//id:21
		#define _DFX_GAMMA_
		
		//entry: Gamma (x10)
		//cntl: spin 0.1 4 0.1
 		//id:22
		float gamma = 1.5;
		
		//section:
		
		//enable: Enable brightness correction
		//id:21
		#define _DFX_CONTRAST_BRIGHTNESS_
		
		//entry: Contrast
		//cntl: slider -100 100 1
 		//id:22
		float contrast = 30;
		
		//entry: Brightness
		//cntl: slider -100 100 1
 		//id:23
		float brightness = 5;
	";
	
	//section:
	//section: debug
	//-------------------------------------------
	
	STRING *dfx_str_debug = "
		//enable: Enable debug layers
		//id:48
//		#define _DFX_DEBUG_
		
		#define AMB_COLOR          0.0
		#define AMB_PRV            1.0
		#define DIF_COLOR          2.0
		#define SPEC_COLOR         3.0
		#define SPEC_TERM          4.0
		#define WORLD_NORMALS      5.0
		#define TAN_NORMALS        6.0
		#define LIGHTMAP           7.0
		
		//entry_drop: Select layer
		//id:49
		//cntl: drop_list AMB_COLOR AMB_PRV DIF_COLOR SPEC_COLOR SPEC_TERM WORLD_NORMALS TAN_NORMALS LIGHTMAP
		float debug_layer = WORLD_NORMALS;
		
	";
	
	// effect template
	STRING *dfx_str_include = "
		//section:
		//-------------------------------------------
		#include \"dfx_template.fx\"
	";
	
	/********************************************************************/
	
	//section:
	//section: mtl_flat settings
	//-------------------------------------------
	
	STRING *dfx_str_flat = "
		//enable: Disable albedo texture
		//id:51
//		#undef _DFX_ALBEDO_
		
		//enable: Disable lightmapping
		//id:52
		#undef _DFX_LIGHTMAP_
		
		//enable: Disable normalmapping
		//id:53
		#undef _DFX_NORMALMAP_
		
		//section:
		//-------------------------------------------
		
		//enable: Disable sun lighting
		//id:60
		#undef _DFX_SUN_LIGHT_
		
		//enable: Disable ambient lighting
		//id:61
		#undef _DFX_AMBIENT_
		
		//enable: Disable diffuse lighting
		//id:62
		#undef _DFX_DIFFUSE_
		
		//enable: Disable specular reflections
		//id:63
		#undef _DFX_SPECULAR_
		
		//enable: Disable emissive color
		//id:64
		#undef _DFX_EMISSIVE_
		
		//enable: Disable PRV
		//id:65
		#undef _DFX_PRV_
		
		//enable: Disable dynamic lights
		//id:66
		#undef _DFX_DYN_LIGHTS_
		
		//section:
		//-------------------------------------------
		
		//enable: Disable fog
		//id:70
//		#undef _DFX_FOG_
		
	";
	
	void dfx_mtl_flat_startup () {
		// section: 
		//-------------------------------------------
		
		//entry: albedo
		//id:80
		//cntl: slider -100 100 1
		mtl_flat->albedo = 0;
		
		// section: 
		//-------------------------------------------
		
		//entry: ambient_red
		//id:81
		//cntl: slider 0 255 1
		mtl_flat->ambient_red = 200;
		
		//entry: ambient_green
		//id:82
		//cntl: slider 0 255 1
		mtl_flat->ambient_green = 200;
		
		//entry: ambient_blue
		//id:83
		//cntl: slider 0 255 1
		mtl_flat->ambient_blue = 200;
		
		// section: 
		//-------------------------------------------
		
		//entry: diffuse_red
		//id:84
		//cntl: slider 0 255 1
		mtl_flat->diffuse_red = 200;
		
		//entry: diffuse_green
		//id:85
		//cntl: slider 0 255 1
		mtl_flat->diffuse_green = 200;
		
		//entry: diffuse_blue
		//id:86
		//cntl: slider 0 255 1
		mtl_flat->diffuse_blue = 200;
		
		// section: 
		//-------------------------------------------
		
		//entry: specular_red
		//id:87
		//cntl: slider 0 255 1
		mtl_flat->specular_red = 0;
		
		//entry: specular_green
		//id:88
		//cntl: slider 0 255 1
		mtl_flat->specular_green = 0;
		
		//entry: specular_blue
		//id:89
		//cntl: slider 0 255 1
		mtl_flat->specular_blue = 0;
		
		//entry: power
		//id:90
		//cntl: slider 1 16 1
		mtl_flat->power = 2;
		
		// section: 
		//-------------------------------------------
		
		//entry: emissive_red
		//id:91
		//cntl: slider 0 255 1
		mtl_flat->emissive_red = 0;
		
		//entry: emissive_green
		//id:92
		//cntl: slider 0 255 1
		mtl_flat->emissive_green = 0;
		
		//entry: emissive_blue
		//id:93
		//cntl: slider 0 255 1
		mtl_flat->emissive_blue = 0;
	}
	
	/********************************************************************/
	
	//section:
	//section: mtl_shaded settings
	//-------------------------------------------
	
	STRING *dfx_str_shaded = "
		#define _DFX_BLOCK_
		
		//enable: Disable albedo texture
		//id:101
//		#undef _DFX_ALBEDO_
		
		//enable: Disable lightmapping
		//id:102
//		#undef _DFX_LIGHTMAP_
		
		//enable: Disable normalmapping
		//id:103
		#undef _DFX_NORMALMAP_
		
		//section:
		//-------------------------------------------
		
		//enable: Disable sun lighting
		//id:110
//		#undef _DFX_SUN_LIGHT_
		
		//enable: Disable ambient lighting
		//id:111
//		#undef _DFX_AMBIENT_
		
		//enable: Disable diffuse lighting
		//id:112
//		#undef _DFX_DIFFUSE_
		
		//enable: Disable specular reflections
		//id:113
		#undef _DFX_SPECULAR_
		
		//enable: Disable emissive color
		//id:114
		#undef _DFX_EMISSIVE_
		
		//enable: Disable PRV
		//id:115
//		#undef _DFX_PRV_
		
		//enable: Disable dynamic lights
		//id:116
//		#undef _DFX_DYN_LIGHTS_
		
		//section:
		//-------------------------------------------
		
		//enable: Disable fog
		//id:120
//		#undef _DFX_FOG_
		
	";
	
	void dfx_mtl_shaded_startup () {
		// section: 
		//-------------------------------------------
		
		//entry: albedo
		//id:130
		//cntl: slider -200 200 1
		mtl_shaded->albedo = 50;
		
		// section: 
		//-------------------------------------------
		
		//entry: ambient_red
		//id:131
		//cntl: slider 0 255 1
		mtl_shaded->ambient_red = 200;
		
		//entry: ambient_green
		//id:132
		//cntl: slider 0 255 1
		mtl_shaded->ambient_green = 200;
		
		//entry: ambient_blue
		//id:133
		//cntl: slider 0 255 1
		mtl_shaded->ambient_blue = 200;
		
		// section: 
		//-------------------------------------------
		
		//entry: diffuse_red
		//id:134
		//cntl: slider 0 255 1
		mtl_shaded->diffuse_red = 200;
		
		//entry: diffuse_green
		//id:135
		//cntl: slider 0 255 1
		mtl_shaded->diffuse_green = 200;
		
		//entry: diffuse_blue
		//id:136
		//cntl: slider 0 255 1
		mtl_shaded->diffuse_blue = 200;
		
		// section: 
		//-------------------------------------------
		
		//entry: specular_red
		//id:137
		//cntl: slider 0 255 1
		mtl_shaded->specular_red = 0;
		
		//entry: specular_green
		//id:138
		//cntl: slider 0 255 1
		mtl_shaded->specular_green = 0;
		
		//entry: specular_blue
		//id:139
		//cntl: slider 0 255 1
		mtl_shaded->specular_blue = 0;
		
		//entry: power
		//id:140
		//cntl: slider 1 16 1
		mtl_shaded->power = 2;
		
		// section: 
		//-------------------------------------------
		
		//entry: emissive_red
		//id:141
		//cntl: slider 0 255 1
		mtl_shaded->emissive_red = 0;
		
		//entry: emissive_green
		//id:142
		//cntl: slider 0 255 1
		mtl_shaded->emissive_green = 0;
		
		//entry: emissive_blue
		//id:143
		//cntl: slider 0 255 1
		mtl_shaded->emissive_blue = 0;
	}
	
	/********************************************************************/
	
	//section:
	//section: mtl_terrain settings
	//-------------------------------------------
	
	STRING *dfx_str_terrain = "
		//enable: Disable albedo texture
		//id:151
//		#undef _DFX_ALBEDO_
		
		//enable: Disable lightmapping
		//id:152
//		#undef _DFX_LIGHTMAP_
		
		//enable: Disable normalmapping
		//id:153
		#undef _DFX_NORMALMAP_
		
		//section:
		//-------------------------------------------
		
		//enable: Disable sun lighting
		//id:160
//		#undef _DFX_SUN_LIGHT_
		
		//enable: Disable ambient lighting
		//id:161
//		#undef _DFX_AMBIENT_
		
		//enable: Disable diffuse lighting
		//id:162
//		#undef _DFX_DIFFUSE_
		
		//enable: Disable specular reflections
		//id:163
		#undef _DFX_SPECULAR_
		
		//enable: Disable emissive color
		//id:164
		#undef _DFX_EMISSIVE_
		
		//enable: Disable PRV
		//id:165
		#undef _DFX_PRV_
		
		//enable: Disable dynamic lights
		//id:166
//		#undef _DFX_DYN_LIGHTS_
		
		//section:
		//-------------------------------------------
		
		//enable: Disable fog
		//id:170
//		#undef _DFX_FOG_
		
	";
	
	void dfx_mtl_terrain_startup () {
		// section: 
		//-------------------------------------------
		
		//entry: albedo
		//id:180
		//cntl: slider -200 200 1
		mtl_terrain->albedo = 50;
		
		// section: 
		//-------------------------------------------
		
		//entry: ambient_red
		//id:181
		//cntl: slider 0 255 1
		mtl_terrain->ambient_red = 200;
		
		//entry: ambient_green
		//id:182
		//cntl: slider 0 255 1
		mtl_terrain->ambient_green = 200;
		
		//entry: ambient_blue
		//id:183
		//cntl: slider 0 255 1
		mtl_terrain->ambient_blue = 200;
		
		// section: 
		//-------------------------------------------
		
		//entry: diffuse_red
		//id:184
		//cntl: slider 0 255 1
		mtl_terrain->diffuse_red = 200;
		
		//entry: diffuse_green
		//id:185
		//cntl: slider 0 255 1
		mtl_terrain->diffuse_green = 200;
		
		//entry: diffuse_blue
		//id:186
		//cntl: slider 0 255 1
		mtl_terrain->diffuse_blue = 200;
		
		// section: 
		//-------------------------------------------
		
		//entry: specular_red
		//id:187
		//cntl: slider 0 255 1
		mtl_terrain->specular_red = 0;
		
		//entry: specular_green
		//id:188
		//cntl: slider 0 255 1
		mtl_terrain->specular_green = 0;
		
		//entry: specular_blue
		//id:189
		//cntl: slider 0 255 1
		mtl_terrain->specular_blue = 0;
		
		//entry: power
		//id:190
		//cntl: slider 1 16 1
		mtl_terrain->power = 2;
		
		// section: 
		//-------------------------------------------
		
		//entry: emissive_red
		//id:191
		//cntl: slider 0 255 1
		mtl_terrain->emissive_red = 0;
		
		//entry: emissive_green
		//id:192
		//cntl: slider 0 255 1
		mtl_terrain->emissive_green = 0;
		
		//entry: emissive_blue
		//id:193
		//cntl: slider 0 255 1
		mtl_terrain->emissive_blue = 0;
	}
	
	/********************************************************************/
	
	//section:
	//section: mtl_model settings
	//-------------------------------------------
	
	STRING *dfx_str_model = "
		//enable: Disable albedo texture
		//id:201
//		#undef _DFX_ALBEDO_
		
		//enable: Disable lightmapping
		//id:202
		#undef _DFX_LIGHTMAP_
		
		//enable: Disable normalmapping
		//id:203
		#undef _DFX_NORMALMAP_
		
		//section:
		
		//enable: Disable sun lighting
		//id:210
//		#undef _DFX_SUN_LIGHT_
		
		//enable: Disable ambient lighting
		//id:211
//		#undef _DFX_AMBIENT_
		
		//enable: Disable diffuse lighting
		//id:212
//		#undef _DFX_DIFFUSE_
		
		//enable: Disable specular reflections
		//id:213
		#undef _DFX_SPECULAR_
		
		//enable: Disable emissive color
		//id:214
		#undef _DFX_EMISSIVE_
		
		//enable: Disable PRV
		//id:215
//		#undef _DFX_PRV_
		
		//enable: Disable dynamic lights
		//id:216
//		#undef _DFX_DYN_LIGHTS_
		
		//section:
		
		//enable: Disable fog
		//id:220
//		#undef _DFX_FOG_
		
	";
	
	function dfx_mtl_model_startup () {
		// section: 
		//-------------------------------------------
		
		//entry: albedo
		//id:230
		//cntl: slider -200 200 1
		mtl_model->albedo = 50;
		
		// section: 
		//-------------------------------------------
		
		//entry: ambient_red
		//id:231
		//cntl: slider 0 255 1
		mtl_model->ambient_red = 200;
		
		//entry: ambient_green
		//id:232
		//cntl: slider 0 255 1
		mtl_model->ambient_green = 200;
		
		//entry: ambient_blue
		//id:233
		//cntl: slider 0 255 1
		mtl_model->ambient_blue = 200;
		
		// section: 
		//-------------------------------------------
		
		//entry: diffuse_red
		//id:234
		//cntl: slider 0 255 1
		mtl_model->diffuse_red = 200;
		
		//entry: diffuse_green
		//id:235
		//cntl: slider 0 255 1
		mtl_model->diffuse_green = 200;
		
		//entry: diffuse_blue
		//id:236
		//cntl: slider 0 255 1
		mtl_model->diffuse_blue = 200;
		
		// section: 
		//-------------------------------------------
		
		//entry: specular_red
		//id:237
		//cntl: slider 0 255 1
		mtl_model->specular_red = 0;
		
		//entry: specular_green
		//id:238
		//cntl: slider 0 255 1
		mtl_model->specular_green = 0;
		
		//entry: specular_blue
		//id:239
		//cntl: slider 0 255 1
		mtl_model->specular_blue = 0;
		
		//entry: power
		//id:240
		//cntl: slider 1 16 1
		mtl_model->power = 2;
		
		// section: 
		//-------------------------------------------
		
		//entry: emissive_red
		//id:241
		//cntl: slider 0 255 1
		mtl_model->emissive_red = 0;
		
		//entry: emissive_green
		//id:242
		//cntl: slider 0 255 1
		mtl_model->emissive_green = 0;
		
		//entry: emissive_blue
		//id:243
		//cntl: slider 0 255 1
		mtl_model->emissive_blue = 0;
		
	}
	
	/********************************************************************/
	
	//section:
	//section: mtl_sprite settings
	//-------------------------------------------
	
	STRING *dfx_str_sprite = "
		//enable: Disable albedo texture
		//id:251
//		#undef _DFX_ALBEDO_
		
		//enable: Disable lightmapping
		//id:252
		#undef _DFX_LIGHTMAP_
		
		//enable: Disable normalmapping
		//id:253
		#undef _DFX_NORMALMAP_
		
		//section:
		//-------------------------------------------
		
		//enable: Disable sun lighting
		//id:260
//		#undef _DFX_SUN_LIGHT_
		
		//enable: Disable ambient lighting
		//id:261
//		#undef _DFX_AMBIENT_
		
		//enable: Disable diffuse lighting
		//id:262
//		#undef _DFX_DIFFUSE_
		
		//enable: Disable specular reflections
		//id:263
		#undef _DFX_SPECULAR_
		
		//enable: Disable emissive color
		//id:264
		#undef _DFX_EMISSIVE_
		
		//enable: Disable PRV
		//id:265
//		#undef _DFX_PRV_
		
		//enable: Disable dynamic lights
		//id:266
//		#undef _DFX_DYN_LIGHTS_
		
		//section:
		//-------------------------------------------
		
		//enable: Disable fog
		//id:270
//		#undef _DFX_FOG_
		
	";
	
	void dfx_mtl_sprite_startup () {
		// section: 
		//-------------------------------------------
		
		//entry: albedo
		//id:280
		//cntl: slider -200 200 1
		mtl_sprite->albedo = 50;
		
		// section: 
		//-------------------------------------------
		
		//entry: ambient_red
		//id:281
		//cntl: slider 0 255 1
		mtl_sprite->ambient_red = 200;
		
		//entry: ambient_green
		//id:282
		//cntl: slider 0 255 1
		mtl_sprite->ambient_green = 200;
		
		//entry: ambient_blue
		//id:283
		//cntl: slider 0 255 1
		mtl_sprite->ambient_blue = 200;
		
		// section: 
		//-------------------------------------------
		
		//entry: diffuse_red
		//id:284
		//cntl: slider 0 255 1
		mtl_sprite->diffuse_red = 200;
		
		//entry: diffuse_green
		//id:285
		//cntl: slider 0 255 1
		mtl_sprite->diffuse_green = 200;
		
		//entry: diffuse_blue
		//id:286
		//cntl: slider 0 255 1
		mtl_sprite->diffuse_blue = 200;
		
		// section: 
		//-------------------------------------------
		
		//entry: specular_red
		//id:287
		//cntl: slider 0 255 1
		mtl_sprite->specular_red = 0;
		
		//entry: specular_green
		//id:288
		//cntl: slider 0 255 1
		mtl_sprite->specular_green = 0;
		
		//entry: specular_blue
		//id:289
		//cntl: slider 0 255 1
		mtl_sprite->specular_blue = 0;
		
		//entry: power
		//id:290
		//cntl: slider 1 16 1
		mtl_sprite->power = 2;
		
		// section: 
		//-------------------------------------------
		
		//entry: emissive_red
		//id:291
		//cntl: slider 0 255 1
		mtl_sprite->emissive_red = 0;
		
		//entry: emissive_green
		//id:292
		//cntl: slider 0 255 1
		mtl_sprite->emissive_green = 0;
		
		//entry: emissive_blue
		//id:293
		//cntl: slider 0 255 1
		mtl_sprite->emissive_blue = 0;
	}
	
	/********************************************************************/
	
	//section:
	//section: mtl_metal settings
	//-------------------------------------------
	
	STRING *dfx_str_metal = "
		//enable: Disable albedo texture
		//id:301
//		#undef _DFX_ALBEDO_
		
		//enable: Disable lightmapping
		//id:302
		#undef _DFX_LIGHTMAP_
		
		//enable: Disable normalmapping
		//id:303
		#undef _DFX_NORMALMAP_
		
		//section:
		
		//enable: Disable sun lighting
		//id:310
//		#undef _DFX_SUN_LIGHT_
		
		//enable: Disable ambient lighting
		//id:311
//		#undef _DFX_AMBIENT_
		
		//enable: Disable diffuse lighting
		//id:312
//		#undef _DFX_DIFFUSE_
		
		//enable: Disable specular reflections
		//id:313
//		#undef _DFX_SPECULAR_
		
		//enable: Disable emissive color
		//id:314
		#undef _DFX_EMISSIVE_
		
		//enable: Disable PRV
		//id:315
//		#undef _DFX_PRV_
		
		//enable: Disable dynamic lights
		//id:316
//		#undef _DFX_DYN_LIGHTS_
		
		//section:
		
		//enable: Disable fog
		//id:320
//		#undef _DFX_FOG_
		
	";
	
	function dfx_mtl_metal_startup () {
		// section: 
		//-------------------------------------------
		
		//entry: albedo
		//id:330
		//cntl: slider -200 200 1
		mtl_metal->albedo = 50;
		
		// section: 
		//-------------------------------------------
		
		//entry: ambient_red
		//id:331
		//cntl: slider 0 255 1
		mtl_metal->ambient_red = 200;
		
		//entry: ambient_green
		//id:332
		//cntl: slider 0 255 1
		mtl_metal->ambient_green = 200;
		
		//entry: ambient_blue
		//id:333
		//cntl: slider 0 255 1
		mtl_metal->ambient_blue = 200;
		
		// section: 
		//-------------------------------------------
		
		//entry: diffuse_red
		//id:334
		//cntl: slider 0 255 1
		mtl_metal->diffuse_red = 200;
		
		//entry: diffuse_green
		//id:335
		//cntl: slider 0 255 1
		mtl_metal->diffuse_green = 200;
		
		//entry: diffuse_blue
		//id:336
		//cntl: slider 0 255 1
		mtl_metal->diffuse_blue = 200;
		
		// section: 
		//-------------------------------------------
		
		//entry: specular_red
		//id:337
		//cntl: slider 0 255 1
		mtl_metal->specular_red = 255;
		
		//entry: specular_green
		//id:338
		//cntl: slider 0 255 1
		mtl_metal->specular_green = 255;
		
		//entry: specular_blue
		//id:339
		//cntl: slider 0 255 1
		mtl_metal->specular_blue = 255;
		
		//entry: power
		//id:340
		//cntl: slider 1 16 1
		mtl_metal->power = 10;
		
		// section: 
		//-------------------------------------------
		
		//entry: emissive_red
		//id:341
		//cntl: slider 0 255 1
		mtl_metal->emissive_red = 0;
		
		//entry: emissive_green
		//id:342
		//cntl: slider 0 255 1
		mtl_metal->emissive_green = 0;
		
		//entry: emissive_blue
		//id:343
		//cntl: slider 0 255 1
		mtl_metal->emissive_blue = 0;
		
	}
	
	/********************************************************************/
	
	//section:
	//section: mtl_unlit settings
	//-------------------------------------------
	
	STRING *dfx_str_unlit = "
		//enable: Disable albedo texture
		//id:351
//		#undef _DFX_ALBEDO_
		
		//enable: Disable lightmapping
		//id:352
		#undef _DFX_LIGHTMAP_
		
		//enable: Disable normalmapping
		//id:353
		#undef _DFX_NORMALMAP_
		
		//section:
		//-------------------------------------------
		
		//enable: Disable sun lighting
		//id:360
		#undef _DFX_SUN_LIGHT_
		
		//enable: Disable ambient lighting
		//id:361
		#undef _DFX_AMBIENT_
		
		//enable: Disable diffuse lighting
		//id:362
		#undef _DFX_DIFFUSE_
		
		//enable: Disable specular reflections
		//id:363
		#undef _DFX_SPECULAR_
		
		//enable: Disable emissive color
		//id:364
		#undef _DFX_EMISSIVE_
		
		//enable: Disable PRV
		//id:365
		#undef _DFX_PRV_
		
		//enable: Disable dynamic lights
		//id:366
		#undef _DFX_DYN_LIGHTS_
		
		//section:
		//-------------------------------------------
		
		//enable: Disable fog
		//id:370
//		#undef _DFX_FOG_
		
	";
	
	void dfx_mtl_unlit_startup () {
		// section: 
		//-------------------------------------------
		
		//entry: albedo
		//id:380
		//cntl: slider -100 100 1
		mtl_unlit->albedo = 0;
		
		// section: 
		//-------------------------------------------
		
		//entry: ambient_red
		//id:381
		//cntl: slider 0 255 1
		mtl_unlit->ambient_red = 0;
		
		//entry: ambient_green
		//id:382
		//cntl: slider 0 255 1
		mtl_unlit->ambient_green = 0;
		
		//entry: ambient_blue
		//id:383
		//cntl: slider 0 255 1
		mtl_unlit->ambient_blue = 0;
		
		// section: 
		//-------------------------------------------
		
		//entry: diffuse_red
		//id:384
		//cntl: slider 0 255 1
		mtl_unlit->diffuse_red = 0;
		
		//entry: diffuse_green
		//id:385
		//cntl: slider 0 255 1
		mtl_unlit->diffuse_green = 0;
		
		//entry: diffuse_blue
		//id:386
		//cntl: slider 0 255 1
		mtl_unlit->diffuse_blue = 0;
		
		// section: 
		//-------------------------------------------
		
		//entry: specular_red
		//id:387
		//cntl: slider 0 255 1
		mtl_unlit->specular_red = 0;
		
		//entry: specular_green
		//id:388
		//cntl: slider 0 255 1
		mtl_unlit->specular_green = 0;
		
		//entry: specular_blue
		//id:389
		//cntl: slider 0 255 1
		mtl_unlit->specular_blue = 0;
		
		//entry: power
		//id:390
		//cntl: slider 1 16 1
		mtl_unlit->power = 2;
		
		// section: 
		//-------------------------------------------
		
		//entry: emissive_red
		//id:391
		//cntl: slider 0 255 1
		mtl_unlit->emissive_red = 0;
		
		//entry: emissive_green
		//id:392
		//cntl: slider 0 255 1
		mtl_unlit->emissive_green = 0;
		
		//entry: emissive_blue
		//id:393
		//cntl: slider 0 255 1
		mtl_unlit->emissive_blue = 0;
	}
	
	/********************************************************************/
	
	function dfx_engine_level_load (char *_level);
	
	function dfx_set_constants(MATERIAL *_mtl) {
		LPD3DXEFFECT _fx = _mtl->d3deffect;
		if(!_fx)
			return 0;
		
		float _fV[4];
		var _average = 128 - (ambient_color.red + ambient_color.green + ambient_color.blue) / 3;
		
		_fV[0] = ambient_color.red / 255;
		_fV[1] = ambient_color.green / 255;
		_fV[2] = ambient_color.blue / 255;
		_fV[3] = (ambient_color.red + _average ) / 255;
		_fx->SetVector("vecAmbientColor", _fV);
		
		return 1;
	}

	function dfx_level_load (char *_level) {
		dfx_engine_level_load(_level);
		
		dfx_set_constants(mtl_flat);
		dfx_set_constants(mtl_shaded);
		dfx_set_constants(mtl_terrain);
		dfx_set_constants(mtl_model);
		dfx_set_constants(mtl_sprite);
		dfx_set_constants(mtl_metal);
		dfx_set_constants(mtl_unlit);
//		dfx_set_constants(mtl_particle);
//		dfx_set_constants(mtl_sky);
//		dfx_set_constants(mtl_shadow);
		
		ENTITY *_ent = ent_next(NULL);
		for(; _ent!=NULL; _ent=ent_next(_ent))
			if(_ent->material == mtl_sprite)
				if(_ent->flags2 & CUBE)
					_ent->material = mtl_sky;
		
	}
	
	// ----------------------------------------------------------------------------------------
	
	function dfx_build_material(MATERIAL *_mtl, STRING *_str_defines) {
		str_cpy(dfx_str_temp, dfx_str_gbl_header);
		str_cat(dfx_str_temp, dfx_str_debug);
		str_cat(dfx_str_temp, _str_defines);
		str_cat(dfx_str_temp, dfx_str_include);
		effect_load(_mtl, dfx_str_temp->chars);
		dfx_set_constants(_mtl);
	}
	
	function dfx_template_startup () {
		wait(1);
		
		// custom level_load function
		dfx_engine_level_load = level_load;
		level_load = dfx_level_load;
		
		// build effects
		dfx_build_material(mtl_flat, dfx_str_flat);
		dfx_build_material(mtl_shaded, dfx_str_shaded);
		dfx_build_material(mtl_terrain, dfx_str_terrain);
		dfx_build_material(mtl_model, dfx_str_model);
		dfx_build_material(mtl_sprite, dfx_str_sprite);
		dfx_build_material(mtl_metal, dfx_str_metal);
		dfx_build_material(mtl_unlit, dfx_str_unlit);
//		dfx_build_material(mtl_particle, "");
//		dfx_build_material(mtl_sky, "");
//		dfx_build_material(mtl_shadow, "");
	}
	
#endif

