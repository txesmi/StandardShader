#include <acknex.h>
#include <default.c>

MATERIAL * mtl_nextgen =
{
	effect    = "fx_default.fx";
	technique = "std_normalmapped";
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
	level_load(NULL);

	ent_create("cylinder.mdl", vector(64, 16, 0), NULL);
	you = ent_create("cylinder.mdl", vector(64, -16, 4), NULL);
	you.material = mtl_nextgen;
}
