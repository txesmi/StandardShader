///////////////////////////////
#include <acknex.h>
#include <default.c>
#include "dfx_template.h"
///////////////////////////////

action actSpotlight () {
	my->material = mtl_flat;
	my->pan = 0;
	my->tilt = -90;
	my->lightrange = 500;
	my->flags |= SPOTLIGHT;
	my->blue = 0;
	my->green = 200;
	my->red = 200;
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
	my->blue = 200;
	my->green = 200;
	my->red = 0;
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
	my->material = you->material;
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
	my->flags |= you->flags & (SHADOW || METAL);
	
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


function main() {
	video_mode = 10;
	wait(2);
	level_load("scene.wmb");
	def_move();
}
