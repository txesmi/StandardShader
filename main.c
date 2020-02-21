#include <acknex.h>
#include <default.c>

#define PRAGMA_POINTER

#include "fx_default.h"

// ---------------------------------------------------------------------------

MATERIAL *mtl_bump_shaded = {
	technique = "std_normalmapped_lightmapped";
	effect    = "fx_default.fx";
	flags     = TANGENT;

	specular_red   = 255;
	specular_green = 255;
	specular_blue  = 255;

	power = 8;
}

MATERIAL *mtl_nextgen = {
	technique = "std_normalmapped";
	effect    = "fx_default.fx";
	flags     = TANGENT;

	specular_red   = 255;
	specular_green = 255;
	specular_blue  = 255;

	power = 8;
}

// ---------------------------------------------------------------------------

action actSpotlight () {
	my->material = mtl_flat;
	my->pan = 0;
	my->tilt = -90;
	my->lightrange = 500;
	my->flags |= SPOTLIGHT;
	my->blue = 255;
	my->green = 255;
	my->red = 255;
	VECTOR vecCenter;
	vec_set(&vecCenter, &my->x);
	
	while(1) {
		var _angle = (my->pan + total_ticks * 3) % 360;
		my->x = vecCenter.x + fsin(_angle, 250);
		my->y = vecCenter.y + fcos(_angle, 250);
		wait(1);
	}
}

action actOmnilight () {
	my->material = mtl_flat;
	my->pan = 180;
	my->tilt = -90;
	my->lightrange = 300;
	my->blue = 255;
	my->green = 255;
	my->red = 255;
	VECTOR vecCenter;
	vec_set(&vecCenter, &my->x);
	
	while(1) {
		var _angle = (my->pan + total_ticks * 3) % 360;
		my->x = vecCenter.x + fsin(_angle, 250);
		my->y = vecCenter.y + fcos(_angle, 250);
		wait(1);
	}
}

var wheelCount = 0;
action actWheel () {
	my->ambient = you->ambient;
	my->albedo = you->albedo;
	vec_set(&my->blue, &you->blue);
	vec_fill(&my->scale_x, you->scale_x);
	my->pan = you->pan + 180 * wheelCount;
	if(wheelCount % 4 < 2)
		my->pan -= 15;
	wheelCount += 1;
	my->tilt = you->tilt;
	my->roll = you->roll;
	my->flags |= you->flags & SHADOW;
	
	wait(1);
	my->emask &= ~DYNAMIC;
}

action actBuggy () {
	VECTOR _vPos;
	vec_set(&_vPos, vector(32, 28, -12));
	vec_rotate(&_vPos, &my->pan);
	vec_scale(&_vPos, my->scale_x);
	vec_add(&_vPos, &my->x);
	ent_create("buggy_rad1.mdl", &_vPos, actWheel);
	
	vec_set(&_vPos, vector(32, -28, -12));
	vec_rotate(&_vPos, &my->pan);
	vec_scale(&_vPos, my->scale_x);
	vec_add(&_vPos, &my->x);
	ent_create("buggy_rad1.mdl", &_vPos, actWheel);
	
	vec_set(&_vPos, vector(-64, 28, -12));
	vec_rotate(&_vPos, &my->pan);
	vec_scale(&_vPos, my->scale_x);
	vec_add(&_vPos, &my->x);
	ent_create("buggy_rad1.mdl", &_vPos, actWheel);

	vec_set(&_vPos, vector(-64, -28, -12));
	vec_rotate(&_vPos, &my->pan);
	vec_scale(&_vPos, my->scale_x);
	vec_add(&_vPos, &my->x);
	ent_create("buggy_rad1.mdl", &_vPos, actWheel);
	
	wait(1);
	my->emask &= ~DYNAMIC;
}

// ---------------------------------------------------------------------------

function main() {
	video_mode = 10;
	wait(3);
	
	effect_load(mtl_bump_shaded, "fx_default.fx");
	effect_load(mtl_nextgen, "fx_default.fx");
	
	camera->flags &= ~SHOW;
	fx_level_load("scene/scene.wmb");
	fx_set_constants(mtl_bump_shaded);
	fx_set_constants(mtl_nextgen);
	camera->flags |= SHOW;
	
//	fog_color = 1;
	camera->clip_far = 8000;
	camera->fog_start = 1000;
	camera->fog_end = camera->clip_far;
	
	on_f1 = on_f2 = on_f3 = on_f4 =  on_f5 =  on_f6 = on_f7 = on_f8 = NULL;
	var keyF1 = 0, keyF2 = 0, keyF3 = 0, keyF4 = 0, keyF5 = 0, keyF6 = 0, keyF7 = 0, keyF8 = 0;
	var key1 = 0, key2 = 0, key3 = 0, key4 = 0, key5 = 0, key6 = 0, key7 = 0, key8 = 0;
	
	while(1) {
		camera->pan = ang(camera->pan - mickey.x * 0.2);
		camera->tilt = clamp(camera->tilt - mickey.y * 0.2, -90, 90);
		VECTOR _vMove;
		vec_set(&_vMove, vector(key_w - key_s, key_a - key_d, 0));
		vec_normalize(&_vMove, (10 + 20 * key_shift) * time_step);
		vec_rotate(&_vMove, &camera->pan);
		vec_add(&camera->x, &_vMove);
		
//		if(key_1 && !key1) {
//			VECTOR vP, vA;
//			vec_set(&vP, &camera->x);
//			vec_set(&vA, &camera->pan);
//			level_load("scene/scene.wmb");
//			vec_set(&camera->x, &vP);
//			vec_set(&camera->pan, &vA);
//		}
		
		if(key_f1 && !keyF1)
			mtl_nextgen->skill1 = mtl_bump_shaded->skill1 = mtl_metal->skill1 = mtl_model->skill1 = mtl_terrain->skill1 = mtl_shaded->skill1 = mtl_flat->skill1 = floatv((var)(fixv(mtl_flat->skill1) + 1) % 2);
		if(key_f2 && !keyF2)
			mtl_nextgen->skill2 = mtl_bump_shaded->skill2 = mtl_metal->skill2 = mtl_model->skill2 = mtl_terrain->skill2 = mtl_shaded->skill2 = mtl_flat->skill2 = floatv((var)(fixv(mtl_flat->skill2) + 1) % 2);
		if(key_f3 && !keyF3)
			mtl_nextgen->skill3 = mtl_bump_shaded->skill3 = mtl_metal->skill3 = mtl_model->skill3 = mtl_terrain->skill3 = mtl_shaded->skill3 = mtl_flat->skill3 = floatv((var)(fixv(mtl_flat->skill3) + 1) % 2);
		if(key_f4 && !keyF4)
			mtl_nextgen->skill4 = mtl_bump_shaded->skill4 = mtl_metal->skill4 = mtl_model->skill4 = mtl_terrain->skill4 = mtl_shaded->skill4 = mtl_flat->skill4 = floatv((var)(fixv(mtl_flat->skill4) + 1) % 2);
		if(key_f5 && !keyF5)
			mtl_nextgen->skill5 = mtl_bump_shaded->skill5 = mtl_metal->skill5 = mtl_model->skill5 = mtl_terrain->skill5 = mtl_shaded->skill5 = mtl_flat->skill5 = floatv((var)(fixv(mtl_flat->skill5) + 1) % 2);
		if(key_f6 && !keyF6)
			mtl_nextgen->skill6 = mtl_bump_shaded->skill6 = mtl_metal->skill6 = mtl_model->skill6 = mtl_terrain->skill6 = mtl_shaded->skill6 = mtl_flat->skill6 = floatv((var)(fixv(mtl_flat->skill6) + 1) % 2);
		if(key_f7 && !keyF7)
			mtl_nextgen->skill7 = mtl_bump_shaded->skill7 = mtl_metal->skill7 = mtl_model->skill7 = mtl_terrain->skill7 = mtl_shaded->skill7 = mtl_flat->skill7 = floatv((var)(fixv(mtl_flat->skill7) + 1) % 2);
		if(key_f8 && !keyF8)
			mtl_nextgen->skill8 = mtl_bump_shaded->skill8 = mtl_metal->skill8 = mtl_model->skill8 = mtl_terrain->skill8 = mtl_shaded->skill8 = mtl_flat->skill8 = floatv((var)(fixv(mtl_flat->skill8) + 1) % 2);
		
		keyF1 = key_f1; keyF2 = key_f2; keyF3 = key_f3; keyF4 = key_f4; keyF5 = key_f5; keyF6 = key_f6; keyF7 = key_f7; keyF8 = key_f8;
		key1 = key_1; key2 = key_2; key3 = key_3; key4 = key_4; key5 = key_5; key6 = key_6; key7 = key_7; key8 = key_8;
		
		DEBUG_VAR(fixv(mtl_nextgen->skill1), 100);
		DEBUG_VAR(fixv(mtl_nextgen->skill2), 120);
		DEBUG_VAR(fixv(mtl_nextgen->skill3), 140);
		DEBUG_VAR(fixv(mtl_nextgen->skill4), 160);
		
		DEBUG_VAR(fixv(mtl_nextgen->skill5), 200);
		DEBUG_VAR(fixv(mtl_nextgen->skill6), 220);
		DEBUG_VAR(fixv(mtl_nextgen->skill7), 240);
		DEBUG_VAR(fixv(mtl_nextgen->skill8), 260);
		
		wait(1);
	}

}
