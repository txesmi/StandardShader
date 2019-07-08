# Standard Shader

HLSL Reimplementation of the Gamestudio Default Shading. With normal maps and per pixel lighting.

Provides `fx_default.fx` with the following techniques:
- `std_default` (skin1=albedo)
- `std_normalmapped` (skin1=albedo, skin2=normalmap)
- `std_lightmapped` (skin1=albedo, skin2=lightmap)
- `std_normalmapped_lightmapped` (skin1=albedo, skin2=lightmap,skin3=normalmap)

## Known Bugs
- `std_normalmapped_lightmapped` does not work right now
