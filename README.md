# Standard Shader

HLSL Reimplementation of the Gamestudio Default Shading. With normal maps and per pixel lighting.

Provides `fx_default.fx` with the following techniques:
- `std_default` (skin1=albedo)
- `std_normalmapped` (skin1=albedo, skin2=normalmap)
- `std_lightmapped` (skin1=albedo, skin2=lightmap)
- `std_normalmapped_lightmapped` (skin1=albedo, skin2=lightmap,skin3=normalmap)

## Usage

```c
// skin1: albedo
MATERIAL * mtl_std_default = 
{
	effect    = "fx_default.fx";
	technique = "std_default";
}

// skin1: albedo
// skin2: normalmap
MATERIAL * mtl_std_normalmapped = 
{
	effect    = "fx_default.fx";
	technique = "std_normalmapped";
	flags = TANGENT;
}

// skin1: albedo
// skin2: lightmap
MATERIAL * mtl_std_lightmapped = 
{
	effect    = "fx_default.fx";
	technique = "std_lightmapped";
}

// skin1: albedo
// skin2: lightmap
// skin3: normalmap
MATERIAL * mtl_std_normalmapped_lightmapped = 
{
	effect    = "fx_default.fx";
	technique = "std_normalmapped_lightmapped";
	flags = TANGENT;
}
```

## Known Bugs
- `std_normalmapped_lightmapped` does not work right now
