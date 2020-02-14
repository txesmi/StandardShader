#include <acknex.h>
#include <default.c>

#define PRAGMA_PATH "%EXE_DIR%\\templates\\models"

MATERIAL * mtl_nextgen =
{
	effect    = "fx_default.fx";
	technique = "std_normalmapped";
	flags     = TANGENT | ENABLE_RENDER;

	ambient_red   = 200;
	ambient_green = 200;
	ambient_blue  = 200;

	diffuse_red   = 255;
	diffuse_green = 255;
	diffuse_blue  = 255;

	specular_red   = 255;
	specular_green = 255;
	specular_blue  = 255;

	emissive_red   = 0;
	emissive_green = 0;
	emissive_blue  = 0;

	power = 2;
}

void cameraMove () {
	camera->pan = ang(camera->pan - mickey.x * 0.2);
	camera->tilt = clamp(camera->tilt - mickey.y * 0.2, -90, 90);
	VECTOR _vMove;
	vec_set(&_vMove, vector(key_w - key_s, key_a - key_d, 0));
	vec_normalize(&_vMove, (10 + 20 * key_shift) * time_step);
	vec_rotate(&_vMove, &camera->pan);
	vec_add(&camera->x, &_vMove);
}

function main()
{
	level_load("scene/scene.wmb");
	
	ENTITY *_entCylinder = ent_create("cylinder.mdl", vector(-64, 128, 0), NULL);
	vec_fill(_entCylinder.blue, 255);
	_entCylinder->material = mtl_nextgen;
	
	ENTITY *_entBuggy0 = ent_create("buggy.mdl", vector(0, 0, -90), NULL);
	vec_fill(_entBuggy0.blue, 255);

	ENTITY *_entBuggy1 = ent_create("buggy.mdl", vector(0, 450, -90), NULL);
	vec_fill(_entBuggy1.blue, 255);

//	_entBuggy0.flags |= TRANSLUCENT;

//	ENTITY *_entBuggy1 = ent_create("buggy.mdl", vector(0, 450, -90), NULL);

	while(!key_space) {
		cameraMove ();
		wait(1);
	}

	mtl_shaded.technique = "std_lightmapped";
	effect_load(mtl_shaded, "fx_default.fx");
	

	mtl_model.technique = "std_default";
	effect_load(mtl_model, "fx_default.fx");
	
	while(1) {
		cameraMove ();
		wait(1);
	}

}
