
#define _DEBUG_LAYERS

/******************************************************************************/
// textures

Texture entSkin1;
Texture entSkin2;
Texture entSkin3;
Texture LightMap;

float4 vecSkill1;
float4 vecSkill5;

// primary surface color
sampler smpAlbedo = sampler_state { Texture = <entSkin1>; MipFilter = Linear; };
samplerCUBE smpSky = sampler_state { Texture = <entSkin1>; MipFilter = Linear; };

// shadowmap
sampler smpShadowmap  = sampler_state { Texture = <LightMap>; MipFilter = Linear; };

// multi-purpose second and third skin sampler
sampler smpSkin2  = sampler_state { Texture = <entSkin2>; MipFilter = Linear; };
sampler smpSkin3  = sampler_state { Texture = <entSkin3>; MipFilter = Linear; };

/******************************************************************************/
// data structs

struct vtx_in_t // vertexshader eingabe
{
	float4 pos     : POSITION;  // vertex position in model space
	float3 normal  : NORMAL;    // surface normal in model space
	float2 uv      : TEXCOORD0; // primary uv coordinates (albedo)
	float2 uv2     : TEXCOORD1; // second uv coordinates (lightmap)
	float3 tangent : TEXCOORD2; // tangent in model space
};

struct vtx_out_t // vertexshader ausgabe
{
	float4 pos     : POSITION;  // position in screen coordinates
	float4 normal  : TEXCOORD0; // normal in world space (xyz) + specular term (w)
	float4 uv      : TEXCOORD1; // uv coordinates (xy) + uv2 coordinates (zw)
	float3 wpos    : TEXCOORD2; // world position
	float3 tangent : TEXCOORD3; // tangent in world space
	float  fog     : FOG;       // fog strength
};

struct pixel_out_t
{
	float4 color : COLOR0; // primary screen color
};

/******************************************************************************/
// static table

float4x4 matWorld;
float4x4 matWorldViewProj;

//float4 vecTime;
float4 vecViewDir;
float4 vecViewPos;
float4 vecSunDir;
float4 vecSunColor;
float4 vecAmbientColor;

float4 vecAmbient;
float4 vecDiffuse;
float4 vecSpecular;
float4 vecEmissive;
float fPower;
float fAmbient;
float fAlbedo;
float fAlpha;

float4 vecColor;
float4 vecLight;

float4 vecFog;
float4 vecFogColor;

float iLights;
float4 vecLightPos[8];
float4 vecLightColor[8];
float4 vecLightDir[8];

//float4 vecAverage;

/******************************************************************************/
// vertex shader:

vtx_out_t vs(vtx_in_t _in)
{
    vtx_out_t _out;

    float4 pos = _in.pos;

    _out.pos = mul(pos, matWorldViewProj);

    _out.normal.xyz = mul(_in.normal, (float3x3)matWorld);
    _out.normal.w = 1; //(vecSpecular.r + vecSpecular.g + vecSpecular.b) / 3.0; // average of material's specular color 
    _out.uv.xy = _in.uv;
    _out.uv.zw = _in.uv2;
    _out.wpos = mul(_in.pos, matWorld).xyz;

    _out.tangent = mul(_in.tangent.xyz, (float3x3)matWorld );

    _out.fog = _out.pos.w;

    return _out;
}

/******************************************************************************/
// pixel shader library:

#ifdef _DEBUG_LAYERS
	float3 fx_layers(float3 sColor, vtx_out_t vtx, float4 normal, float3 lightmap) {
		if(step(0.5, vecSkill1.x) > 0)
			sColor.rgb = vecLight.rgb * 0.5;
		if(step(0.5, vecSkill1.y) > 0)
			sColor.rgb = lightmap * 0.5;
		if(step(0.5, vecSkill1.z) > 0)
			sColor.rgb = 0.5 + vtx.normal.xyz * 0.5;
		if(step(0.5, vecSkill1.w) > 0)
			sColor.rgb = 0.5 + normal.xyz * 0.5;
		
		if(step(0.5, vecSkill5.x) > 0)
			sColor.rgb = normal.w;
		if(step(0.5, vecSkill5.y) > 0)
			sColor.rgb = 0.5 + vtx.tangent * 0.5;
		if(step(0.5, vecSkill5.z) > 0)
			sColor.rgb = 0.5 + vecLight.rgb - vecColor.rgb;
		
		return sColor;
	}
#endif

// ---------------------------------------------------------------------------

pixel_out_t do_lighting(vtx_out_t vtx, float4 normal, float3 lightmap)
{
	float3 diffuse = 0;
	float3 specular = 0;
	
//	// sun diffuse
	float ambient = vecAmbientColor.rgb + lightmap;
	diffuse += ambient * saturate(-dot(vecSunDir.xyz, normal.xyz)) * vecSunColor.w;
	
//	// sun specular
	float specPower = 1.0 + fPower * normal.w;
	float3 refl = reflect(vecSunDir.xyz, normal.xyz);
	specular += ambient * pow(saturate(-dot(refl, vecViewDir.xyz)), specPower) * vecSunColor.w;
	
	// multiple dynamic lights
	float light = 0;
	float lastLight = iLights - vecSunColor.w;
	for(; light < lastLight; light += 1.0)
	{
		// light ray
		float3 ray = vtx.wpos - vecLightPos[light].xyz;
		
		// spotlight factor
		float depth = saturate(dot(vecLightDir[light].xyz, ray) / vecLightPos[light].w);
		float spot = 1.0 - saturate(length(cross(vecLightDir[light].xyz, ray)) / (vecLightPos[light].w * depth));
		
		// normalize the light ray
		float dist = length(ray);
		ray /= dist; 
		
		// attenuation
		float att = 1.0 - saturate(dist / vecLightPos[light].w);
		
		// final light factor
		float strength = vecLightDir[light].w ? spot * att : att;
		
		// diffuse term
		diffuse += vecLightColor[light].rgb * saturate(-dot(ray, normal.xyz)) * strength;
		
		// specular term
		refl = reflect(ray, normal.xyz);
		specular += vecLightColor[light].rgb * pow(saturate(-dot(refl, vecViewDir.xyz)), specPower) * strength;
	}
	
	// surface albedo
	float4 albedo = tex2D(smpAlbedo, vtx.uv.xy);
	albedo.rgb *= 1.0 + fAlbedo;
	
	// lighted surface
	float4 surfaceColor = float4(vecEmissive.rgb, albedo.a * fAlpha);
	surfaceColor.rgb += albedo.rgb * (vecAmbientColor.rgb * vecAmbient.rgb + diffuse * vecDiffuse.rgb);
	surfaceColor.rgb += surfaceColor.rgb * fAmbient;
	surfaceColor.rgb += specular * vecSpecular.rgb * normal.w;
	
	// fog
	float strengthFog = vecFogColor.w * saturate((vtx.fog - vecFog.x) * vecFog.z);
	surfaceColor.rgb = lerp(surfaceColor.rgb, vecFogColor.rgb, strengthFog);
	
#ifdef _DEBUG_LAYERS
	surfaceColor.rgb = fx_layers(surfaceColor.rgb, vtx, normal, lightmap);
#endif

	// determine our output color
	pixel_out_t pixel;
	pixel.color = surfaceColor;
	return pixel;
}

// ---------------------------------------------------------------------------

float4 do_normalmap(vtx_out_t vtx, sampler smpNormalmap)
{
	vtx.tangent = normalize(vtx.tangent);
	
	float3x3 trafo;
	trafo[0] = vtx.tangent;
	trafo[1] = cross(vtx.tangent, vtx.normal.xyz);
	trafo[2] = vtx.normal.xyz;
	
	float4 normalmap = tex2D(smpNormalmap, vtx.uv.xy);
	normalmap.xyz = normalize(mul(normalmap.xyz - 0.5, trafo));
	normalmap.w *= vtx.normal.w;
	return normalmap;
}

// ---------------------------------------------------------------------------

float3 do_block_light(float3 lightmap) 
{
	return saturate(lightmap - vecAmbientColor.rgb * 0.9) * (1.0 + (vecLight.r - vecAmbientColor.w) /** 2.56*/);
}

float3 do_entity_light(float3 lightmap) 
{
	return lightmap * saturate(vecLight.rgb - vecAmbientColor.rgb * 0.9);
}

// ---------------------------------------------------------------------------

float3 do_lightmap(float2 uv)
{
	return tex2D(smpShadowmap, uv).rgb;
}

float3 do_sun_diffuse (float3 normal) 
{
	return saturate(-dot(vecSunDir.xyz, normal));
}

/******************************************************************************/
// pixel shaders:

// flat shading, no lighting
pixel_out_t ps_flat(vtx_out_t vtx)
{
	pixel_out_t pixel;
	pixel.color = float4(vecEmissive.rgb, 0) + vecColor * tex2D(smpAlbedo, vtx.uv.xy); 
	
#ifdef _DEBUG_LAYERS
	vtx.normal.xyz = normalize(vtx.normal.xyz);
	pixel.color.rgb = fx_layers(pixel.color.rgb, vtx, vtx.normal, float3(1, 1, 1));
#endif

	return pixel;
}

// sky
pixel_out_t ps_sky(vtx_out_t vtx)
{
	pixel_out_t pixel;
	pixel.color = texCUBE(smpSky, vtx.wpos - vecViewPos.xyz); 
	
#ifdef _DEBUG_LAYERS
	vtx.normal.xyz = normalize(vtx.normal.xyz);
	pixel.color.rgb = fx_layers(pixel.color.rgb, vtx, vtx.normal, float3(1, 1, 1));
#endif

	return pixel;
}

// sprites
pixel_out_t ps_sprite(vtx_out_t vtx)
{
	vtx.normal = float4(-vecViewDir.xyz, vtx.normal.w);
	return do_lighting(vtx, vtx.normal, do_entity_light(do_sun_diffuse(vtx.normal.xyz)));
}

// terrain
pixel_out_t ps_terrain(vtx_out_t vtx)
{
	vecLight.rgb += vecSunColor.rgb;
	vtx.normal.xyz = normalize(vtx.normal.xyz);
	return do_lighting(vtx, vtx.normal, do_entity_light(do_lightmap(vtx.uv.xy)));
}

// ---------------------------------------------------------------------------

// default shading, no normalmap, no lightmap
pixel_out_t ps_default(vtx_out_t vtx)
{
	vtx.normal.xyz = normalize(vtx.normal.xyz);
	return do_lighting(vtx, vtx.normal, do_entity_light(do_sun_diffuse(vtx.normal.xyz)));
}

// only lightmapping with uv2
pixel_out_t ps_lightmapped(vtx_out_t vtx)
{
	vtx.normal.xyz = normalize(vtx.normal.xyz);
	return do_lighting(vtx, vtx.normal, do_block_light(do_lightmap(vtx.uv.zw)));
}

// only normalmapping
pixel_out_t ps_normalmapped(vtx_out_t vtx)
{
	vtx.normal.xyz = normalize(vtx.normal.xyz);
	return do_lighting(vtx, do_normalmap(vtx, smpSkin2), do_entity_light(do_sun_diffuse(vtx.normal.xyz)));
}

// everything combined
pixel_out_t ps_normalmapped_lightmapped(vtx_out_t vtx)
{
	vtx.normal.xyz = normalize(vtx.normal.xyz);
	return do_lighting(vtx, do_normalmap(vtx, smpSkin3), do_block_light(do_lightmap(vtx.uv.zw)));
}

/******************************************************************************/
// techniques:

technique std_flat
{
	pass one
	{
		VertexShader = compile vs_3_0 vs();
		PixelShader  = compile ps_3_0 ps_flat();
	}
}

technique std_sky
{
	pass one
	{
		VertexShader = compile vs_3_0 vs();
		PixelShader  = compile ps_3_0 ps_sky();
	}
}

technique std_terrain
{
	pass one
	{
		VertexShader = compile vs_3_0 vs();
		PixelShader  = compile ps_3_0 ps_terrain();
	}
}

technique std_sprite
{
	pass one
	{
		VertexShader = compile vs_3_0 vs();
		PixelShader  = compile ps_3_0 ps_sprite();
	}
}

technique std_default
{
	pass one
	{
		VertexShader = compile vs_3_0 vs();
		PixelShader  = compile ps_3_0 ps_default();
	}
}

technique std_normalmapped
{
	pass one
	{
		VertexShader = compile vs_3_0 vs();
		PixelShader  = compile ps_3_0 ps_normalmapped();
	}
}

technique std_lightmapped
{
	pass one
	{
		VertexShader = compile vs_3_0 vs();
		PixelShader  = compile ps_3_0 ps_lightmapped();
	}
}

technique std_normalmapped_lightmapped
{
	pass one
	{
		VertexShader = compile vs_3_0 vs();
		PixelShader  = compile ps_3_0 ps_normalmapped_lightmapped();
	}
}

technique fallback { pass one { } } // empty fallback causes normal rendering without effect
