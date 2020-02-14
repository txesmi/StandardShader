
/******************************************************************************/
// textures

Texture entSkin1;
Texture entSkin2;
Texture entSkin3;

// primary surface color
sampler smpAlbedo = sampler_state { Texture = <entSkin1>; MipFilter = Linear; };

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
	float3 normal  : TEXCOORD0; // normal in world space
	float2 uv      : TEXCOORD1; // uv coordinates
	float3 wpos    : TEXCOORD2; // world position
	float3 tangent : TEXCOORD3; // tangent in world space
	float2 uv2     : TEXCOORD4; // second uv coordinates (lightmap)
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
float4 vecAmbientColor;
float4 vecSunDir;
float4 vecSunColor;
float4 vecViewDir;

float4 vecAmbient;
float4 vecDiffuse;
float4 vecSpecular;
float4 vecEmissive;
float fPower;
float fAmbient;
float fAlbedo;
float fAlpha;

//float4 vecColor;
float4 vecLight;

float4 vecFog;
float4 vecFogColor;

float iLights;
float4 vecLightPos[8];
float4 vecLightColor[8];

/******************************************************************************/
// vertex shader:

vtx_out_t vs(vtx_in_t _in)
{
    vtx_out_t _out;

    float4 pos = _in.pos;

    _out.pos = mul(pos, matWorldViewProj);

    _out.normal = mul(_in.normal, (float3x3)matWorld);
    _out.uv = _in.uv;
    _out.uv2 = _in.uv2;
    _out.wpos = mul(_in.pos, matWorld).xyz;

    _out.tangent = mul(_in.tangent.xyz, (float3x3)matWorld );

    _out.fog = _out.pos.w;

    return _out;
}

/******************************************************************************/
// pixel shader library:

pixel_out_t do_lighting(vtx_out_t vtx, float3 normal, float4 lightmap, float sunActive)
{
	// ambient term
	float3 lighting = vecAmbientColor.rgb + lightmap.rgb;
	
	// ambient factor
	lighting += lightmap.rgb * fAmbient;
	
	// sun diffuse
	lighting += vecDiffuse.rgb * vecSunColor.rgb * saturate(-dot(vecSunDir, normal)) * sunActive;
	
	// sun specular
	float3 refl = reflect(vecSunDir, normal);
	lighting += vecSpecular.rgb * vecSunColor.rgb * pow(saturate(-dot(refl, vecViewDir.xyz)), fPower) * sunActive;
	
	// multiple dynamic lights
	float light = 0;
	float lastLight = iLights - vecSunColor.w;
	for(; light < lastLight; light += 1.0)
	{
		// light ray
		float3 ray = vtx.wpos - vecLightPos[light].xyz;
		float dist = length(ray);
		ray /= dist; // normalize the light ray
		
		// distance factor
		float strength = saturate(1.0 - dist / vecLightPos[light].w);
		
		// diffuse term
		lighting += vecLightColor[light].rgb * saturate(-dot(ray, normal)) * strength;
		
		// specular term
		float3 refl = reflect(ray, normal);
		lighting += vecLightColor[light].rgb * pow(saturate(-dot(refl, vecViewDir.xyz)), fPower) * strength;
	}
	
	// surface albedo
	float4 albedo = tex2D(smpAlbedo, vtx.uv);
	albedo.rgb *= 1.0 + fAlbedo;
	albedo.rgb *= vecLight.rgb;
	albedo.a *= fAlpha;
	
	// lighted surface
	float4 surfaceColor = float4(vecEmissive.rgb, 0) + float4(lighting, 1.0) * albedo;
	
	// fog
	float strengthFog = vecFogColor.w * saturate((vtx.fog - vecFog.x) * vecFog.z);
	surfaceColor.rgb = lerp(surfaceColor.rgb, vecFogColor.rgb, strengthFog);
	
	// determine our output color
	// by applying fog to the surface color.
	pixel_out_t pixel;
	pixel.color = surfaceColor;
	return pixel;
}

float3 do_normal(vtx_out_t vtx, sampler smpNormalmap)
{
	float3x3 trafo;
	trafo[0] = normalize(vtx.tangent);
	trafo[1] = normalize(cross(vtx.tangent, vtx.normal));
	trafo[2] = normalize(vtx.normal);
	
	float3 normal = normalize(tex2D(smpNormalmap, vtx.uv).xyz - 0.5);
	
	return mul(normal, trafo);
}

float4 do_lightmap(vtx_out_t vtx, sampler smpLightmap)
{
	return tex2D(smpLightmap, vtx.uv2);
}

/******************************************************************************/
// pixel shaders:

// default shading, no normalmap, no lightmap
pixel_out_t ps_default(vtx_out_t vtx)
{
	return do_lighting(vtx, vtx.normal, vecAmbient + vecLight, vecSunColor.w);
}

// only lightmapping
pixel_out_t ps_lightmapped(vtx_out_t vtx)
{
	return do_lighting(vtx, vtx.normal, do_lightmap(vtx, smpSkin2), saturate(vecSunColor.w - 1.0));
}

// only normalmapping
pixel_out_t ps_normalmapped(vtx_out_t vtx)
{
	return do_lighting(vtx, do_normal(vtx, smpSkin2), vecAmbient + vecLight, vecSunColor.w);
}

// everything combined
pixel_out_t ps_normalmapped_lightmapped(vtx_out_t vtx)
{
	return do_lighting(vtx, do_normal(vtx, smpSkin3), do_lightmap(vtx, smpSkin2), saturate(vecSunColor.w - 1.0));
}

/******************************************************************************/
// techniques:

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

