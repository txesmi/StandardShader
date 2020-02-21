#include <d3d9.h>

function fx_default_startup () 
{
	wait(1);
	
	mtl_flat->technique = "std_flat";
	effect_load(mtl_flat, "fx_default.fx");
	
	mtl_shaded->technique = "std_lightmapped";
	effect_load(mtl_shaded, "fx_default.fx");
	
	mtl_terrain->technique = "std_terrain";
	effect_load(mtl_terrain, "fx_default.fx");
	
	mtl_model->technique = "std_default";
	effect_load(mtl_model, "fx_default.fx");
	
	mtl_sprite->technique = "std_default";
	effect_load(mtl_sprite, "fx_default.fx");
	
	mtl_metal->technique = "std_default";
	effect_load(mtl_metal, "fx_default.fx");
	
	mtl_unlit->technique = "std_flat";
	effect_load(mtl_unlit, "fx_default.fx");
	
	mtl_particle->technique = "std_flat";
	effect_load(mtl_particle, "fx_default.fx");
	
//	mtl_sky->technique = "std_sky";
//	effect_load(mtl_sky, "fx_default.fx");
	
//	mtl_shadow->technique = "std_default";
//	effect_load(mtl_shadow, "fx_default.fx");
	
}

void fx_set_constants(MATERIAL *_mtl) {
	LPD3DXEFFECT _fx = _mtl->d3deffect;
	if(!_fx) {
		printf("Error while retrieving a material d3deffect");
		return;
	}
	
	float _fV[4];
	_fV[0] = ambient_color.red / 255;
	_fV[1] = ambient_color.green / 255;
	_fV[2] = ambient_color.blue / 255;
	_fV[3] = (ambient_color.red + 128 - (ambient_color.red + ambient_color.green + ambient_color.blue) / 3) / 255;
	_fx->SetVector("vecAmbientColor", _fV);
}

void fx_level_load(char *_chrLevel) 
{
	level_load(_chrLevel);
	
	fx_set_constants(mtl_flat);
	fx_set_constants(mtl_shaded);
	fx_set_constants(mtl_terrain);
	fx_set_constants(mtl_model);
	fx_set_constants(mtl_sprite);
	fx_set_constants(mtl_metal);
	fx_set_constants(mtl_unlit);
	fx_set_constants(mtl_particle);
//	fx_set_constants(mtl_sky);
//	fx_set_constants(mtl_shadow);
	
	ENTITY *_ent = ent_next(NULL);
	for(; _ent!=NULL; _ent=ent_next(_ent))
		if(_ent->material == mtl_sprite)
			if(_ent->flags2 & CUBE)
				_ent->material = mtl_sky;
	
//	if(sky_cube_level) {
//		BMAP *sky_texture = ent_getskin(sky_cube_level, 1);
//		bmap_to_cubemap(sky_texture);
//		ent_setskin(sky_cube_level, sky_texture, 1);
//		
////		ent_remove(sky_cube_level);
////		sky_cube_level = ent_createlayer(NULL, SKY, 1);
////		ent_setskin(sky_cube_level, sky_texture, 1);
//		
//		sky_cube_level->material = mtl_sky;
//		
//		while(1) {
//			draw_text(sky_texture->link.name, 100, 100, COLOR_WHITE);
//			DEBUG_BMAP(sky_texture, 0, 0.25);
//			wait(1);
//		}
//	}
}