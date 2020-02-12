#include <acknex.h>
#include <default.c>

#define PRAGMA_PATH "%EXE_DIR%\\templates\\models"

MATERIAL * mtl_nextgen =
{
	effect    = "fx_default.fx";
	technique = "ps_normalmapped";
	flags = AUTORELOAD | TANGENT;

	ambient_red   = 100;
	ambient_green = 100;
	ambient_blue  = 100;

	diffuse_red = 200;
	diffuse_green = 200;
	diffuse_blue = 200;

	specular_red = 0;
	specular_green = 0;
	specular_blue = 0;

	emissive_red = 0;
	emissive_green = 0;
	emissive_blue = 0;

	power = 2;
}

function main()
{
	level_load("scene/scene.wmb");

//	ENTITY *_entCylinder = ent_create("cylinder.mdl", vector(64, 16, 0), NULL);
	ENTITY *_entBuggy = ent_create("buggy.mdl", vector(64, -16, -70), NULL);
//	_entBuggy.material = mtl_nextgen;

	while(!key_space)
		wait(1);

	mtl_shaded.technique = "std_lightmapped";
	effect_load(mtl_shaded, "fx_default.fx");
	
	mtl_model.technique = "std_default";
	effect_load(mtl_model, "fx_default.fx");
	
}
