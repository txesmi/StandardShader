

/******************************************************************************/
// textures

#ifdef _DFX_ALBEDO_
	Texture entSkin1;
	sampler smpAlbedo = sampler_state { Texture = <entSkin1>; MipFilter = Linear; };
#endif

#ifdef _DFX_LIGHTMAP_
	Texture LightMap;
	sampler smpLightmap  = sampler_state { Texture = <LightMap>; MipFilter = Linear; };
	
	#ifdef _DFX_NORMALMAP_
		Texture entSkin3;
		sampler smpNormalmap  = sampler_state { Texture = <entSkin3>; MipFilter = Linear; };
	#endif
#else
	#ifdef _DFX_NORMALMAP_
		#ifdef _DFX_BLOCK_
			Texture entSkin3;
			sampler smpNormalmap  = sampler_state { Texture = <entSkin3>; MipFilter = Linear; };
		#else
			Texture entSkin2;
			sampler smpNormalmap  = sampler_state { Texture = <entSkin2>; MipFilter = Linear; };
		#endif
	#endif
#endif

/******************************************************************************/
// data structs

// primary uv coordinates
#ifdef _DFX_ALBEDO_
	#define _DFX_DATA_UV1_
#else
	#ifdef _DFX_LIGHTMAP_
		#define _DFX_DATA_UV1_
	#else
		#ifdef _DFX_NORMALMAP_
			#define _DFX_DATA_UV1_
		#endif
	#endif
#endif

// rest of data
#ifdef _DFX_DIFFUSE_
	// normal
	#define _DFX_DATA_NORMAL_
	
	// world pos
	#define _DFX_DATA_WORLD_
	
	// secondary uv coordinates
	#ifdef _DFX_LIGHTMAP_
		#ifdef _DFX_BLOCK_
			#define _DFX_DATA_UV2_
		#endif
	#endif
	
	// tangent
	#ifdef _DFX_NORMALMAP_
		#define _DFX_DATA_TANGENT_
	#endif
#endif

// vertex data
struct vtx_in_t { 
	float4 pos        : POSITION;  // vertex position in object space
	
	#ifdef _DFX_DATA_NORMAL_
		float3 normal  : NORMAL;    // surface normal in model space
	#endif
	
	#ifdef _DFX_DATA_UV1_
		float2 uv      : TEXCOORD0; // primary uv coordinates
	#endif
	
	#ifdef _DFX_DATA_UV2_
		float2 uv2     : TEXCOORD1; // secondary uv coordinates
	#endif
	
	#ifdef _DFX_DATA_TANGENT_
		float3 tangent : TEXCOORD2; // tangent in object space
	#endif
};

// vertex shader out data
struct vtx_out_t { 
	float4 pos        : POSITION;  // position in clip space
	
	#ifdef _DFX_DATA_NORMAL_
		float4 normal  : TEXCOORD0; // normal in world space (xyz) + specular term (w)
	#endif
	
	#ifdef _DFX_DATA_UV1_
		#ifdef _DFX_DATA_UV2_
			float4 uv   : TEXCOORD1; // uv coordinates (xy) + uv2 coordinates (zw)
		#else
			float2 uv   : TEXCOORD1; // uv coordinates (xy)
		#endif
	#endif
	
	#ifdef _DFX_DATA_WORLD_
		float3 wpos    : TEXCOORD2; // world position
	#endif
	
	#ifdef _DFX_DATA_TANGENT_
		float3 tangent : TEXCOORD3; // tangent in world space
	#endif
	
	#ifdef _DFX_FOG_
		float  fog     : FOG;       // fog strength
	#endif
};

// pixel shader out data
struct pixel_out_t { 
	float4 color0  : COLOR0; // primary screen color
};

/******************************************************************************/
// vertex shader

float4x4 matWorldViewProj;
#ifdef _DFX_DATA_NORMAL_
	float4x4 matWorld;
#endif

vtx_out_t vs(vtx_in_t _in)
{
	vtx_out_t _out;
	
	_out.pos = mul(_in.pos, matWorldViewProj);
	
	#ifdef _DFX_DATA_NORMAL_
		_out.normal.xyz = mul(_in.normal, (float3x3)matWorld);
		_out.normal.w = 1;
	#endif
	
	#ifdef _DFX_DATA_UV1_
		_out.uv.xy = _in.uv;	
	#endif
	
	#ifdef _DFX_DATA_UV2_
		_out.uv.zw = _in.uv2;	
	#endif
	
	#ifdef _DFX_DATA_WORLD_
		_out.wpos = mul(_in.pos, matWorld).xyz;
	#endif
	
	#ifdef _DFX_DATA_TANGENT_
		_out.tangent = mul(_in.tangent.xyz, (float3x3)matWorld);
	#endif
	
	#ifdef _DFX_FOG_
		_out.fog = _out.pos.w;
	#endif
	
	return _out;
}

/******************************************************************************/
// pixel shader:

float fAlpha;

#ifdef _DFX_SUN_LIGHT_
	float4 vecSunDir;
	float4 vecSunColor;
#endif

#ifdef _DFX_AMBIENT_
	float4 vecAmbient;
	float4 vecAmbientColor;
#endif

#ifdef _DFX_EMISSIVE_
	float4 vecEmissive;
#endif

#ifdef _DFX_DIFFUSE_
	float4 vecDiffuse;
	float fAmbient;
	
	#ifdef _DFX_NORMALMAP_
		float3x3 matTangent;
	#endif
	
	#ifdef _DFX_SPECULAR_
		float4 vecViewPos;
		float4 vecSpecular;
		float fPower;
	#endif
#endif

#ifdef _DFX_ALBEDO_
	float fAlbedo;
#else
	float4 vecColor;
#endif

#ifdef _DFX_PRV_
	float4 vecLight;
#endif

#ifdef _DFX_FOG_
	float4 vecFog;
	float4 vecFogColor;
#endif

#ifdef _DFX_DYN_LIGHTS_
	float iLights;
	float4 vecLightPos[8];
	float4 vecLightColor[8];
	float4 vecLightDir[8];
#endif

float3 do_gamma(float3 color) {
	return pow(color * 256.0, gamma);
}

float3 undo_gamma(float3 color) {
	return pow(color, 1.0/gamma) / 256.0;
}

pixel_out_t ps(vtx_out_t vtx) {
	#ifdef _DFX_GAMMA_
		#ifdef _DFX_AMBIENT_
			vecAmbientColor.rgb = do_gamma(vecAmbientColor.rgb);
		#endif
		#ifdef _DFX_DIFFUSE_
			#ifdef _DFX_SUN_LIGHT_
				vecSunColor.rgb = do_gamma(vecSunColor.rgb);
			#endif
		#endif
		#ifdef _DFX_EMISSIVE_
			vecEmissive.rgb = do_gamma(vecEmissive.rgb);
		#endif
	#endif
	
	#ifdef _DFX_DIFFUSE_
		// normalize the surface normal
		vtx.normal.xyz = normalize(vtx.normal.xyz);
		
		// diffuse lighting variables
		float3 diffuse = 0;
		
		// starting diffuse
		#ifdef _DFX_LIGHTMAP_
			#ifdef _DFX_BLOCK_
				diffuse = tex2D(smpLightmap, vtx.uv.zw).rgb;
				#ifdef _DFX_GAMMA_
					diffuse = do_gamma(diffuse);
				#endif
				#ifdef _DFX_PRV_
					#ifdef _DFX_AMBIENT_
						diffuse *= (1.0 + (vecLight.r - vecAmbientColor.w) /** 2.56*/);
					#else
						diffuse *= vecLight.rgb;
					#endif
				#endif
			#else
				diffuse = tex2D(smpLightmap, vtx.uv.xy).rgb;
				#ifdef _DFX_GAMMA_
					diffuse = do_gamma(diffuse);
				#endif
				#ifdef _DFX_PRV_
					diffuse *= vecLight.rgb;
				#endif
			#endif
		#else
			#ifdef _DFX_SUN_LIGHT_
				diffuse = vecSunColor.rgb;
				#ifdef _DFX_AMBIENT_
					diffuse += vecAmbientColor.rgb;
				#endif
				diffuse *= saturate(-dot(vecSunDir.xyz, vtx.normal.xyz));
			#endif
			#ifdef _DFX_PRV_
				#ifdef _DFX_BLOCK_
					#ifdef _DFX_AMBIENT_
						diffuse *= (1.0 + (vecLight.r - vecAmbientColor.w) /** 2.56*/);
					#else
						diffuse *= vecLight.rgb;
					#endif
				#else
					float3 prvProp = 1;
//					#ifdef _DFX_SUN_LIGHT_
//						prvProp = vecSunColor.rgb;
//						#ifdef _DFX_AMBIENT_
//							prvProp += vecAmbientColor.rgb;
//						#endif
//					#endif
					diffuse *= vecLight.rgb / prvProp;
				#endif
			#else
				diffuse *= 0.8;
			#endif
			#ifdef _DFX_AMBIENT_
				diffuse += vecAmbientColor.rgb;
			#endif
		#endif
		
		// specular reflection variables
		#ifdef _DFX_DIFFUSE_
			#ifdef _DFX_SPECULAR_
				float specPower = 1 + fPower * vtx.normal.w;
				float3 viewDir = normalize(vtx.wpos - vecViewPos.xyz);
				float3 refl;
				float3 specular = 0;
			#endif
		#endif
		
		// apply normalmap
		#ifdef _DFX_NORMALMAP_
			// normalize the surface tangent
			vtx.tangent = normalize(vtx.tangent);
			
			// build space transforming matrix
			float3x3 trafo;
			trafo[0] = vtx.tangent;
			trafo[1] = cross(vtx.tangent, vtx.normal.xyz);
			trafo[2] = vtx.normal.xyz;
			
			// transform normal
			float4 normalmap;
			normalmap = tex2D(smpNormalmap, vtx.uv.xy);
			vtx.normal.xyz = normalize(mul(normalmap.xyz - 0.5, trafo));
			vtx.normal.w = normalmap.a;
		#endif
	#endif
	
	
	// sun light
	#ifdef _DFX_SUN_LIGHT_
		//	sun diffuse
		#ifdef _DFX_DIFFUSE_
			diffuse += diffuse * saturate(-dot(vecSunDir.xyz, vtx.normal.xyz)) - diffuse;
			
			//	sun specular
			#ifdef _DFX_SPECULAR_
				refl = reflect(vecSunDir.xyz, vtx.normal.xyz);
				specular += diffuse * pow(saturate(-dot(refl, viewDir)), specPower);
			#endif
		#endif
	#endif
	
	// multiple dynamic lights
	#ifdef _DFX_DYN_LIGHTS_
		#ifdef _DFX_DIFFUSE_
			float light = 0;
			float lastLight = iLights;
			#ifdef _DFX_SUN_LIGHT_
				lastLight -= vecSunColor.w;
			#endif
			float lPow = 1.0 + lightsPower / 50.0;
			for(; light < lastLight; light += 1.0)
			{
				#ifdef _DFX_GAMMA_
					vecLightColor[light].rgb = do_gamma(vecLightColor[light].rgb);
				#endif
				vecLightColor[light].rgb *= lPow;
				
				// light ray
				float3 ray = vtx.wpos - vecLightPos[light].xyz;
				
				// spotlight factor
				#ifdef _DFX_SPOTLIGHT_
					float depth = saturate(dot(vecLightDir[light].xyz, ray) / vecLightPos[light].w);
					float spot = 1.0 - saturate(length(cross(vecLightDir[light].xyz, ray)) / (vecLightPos[light].w * depth));
				#endif
				
				// normalize the light ray
				float dist = length(ray);
				ray /= dist; 
				
				// attenuation
				float att = 1.0 - saturate(dist / vecLightPos[light].w);
				
				// final light factor
				#ifdef _DFX_SPOTLIGHT_
					att *= vecLightDir[light].w ? spot : 1.0;
				#endif
				
				// diffuse term
				diffuse += vecLightColor[light].rgb * saturate(-dot(ray, vtx.normal.xyz)) * att;
				
				// specular term
				#ifdef _DFX_SPECULAR_
					refl = reflect(ray, vtx.normal.xyz);
					specular += vecLightColor[light].rgb * pow(saturate(-dot(refl, viewDir)), specPower) * att;
				#endif
			}
		#endif
	#endif
	
	// determine our output color
	pixel_out_t pixel;
	
	// albedo
	#ifdef _DFX_ALBEDO_
		pixel.color0 = tex2D(smpAlbedo, vtx.uv.xy);
		pixel.color0.rgb *= 1.0 + fAlbedo;
	#else
		pixel.color0 = vecColor;
	#endif
	#ifdef _DFX_GAMMA_
		pixel.color0.rgb = do_gamma(pixel.color0.rgb);
	#endif
	
	// difuse
	#ifdef _DFX_DIFFUSE_
		float3 difFactor = diffuse * vecDiffuse.rgb;
		#ifdef _DFX_AMBIENT_
			difFactor += vecAmbientColor.rgb * vecAmbient.rgb;
		#endif
		#ifdef _DFX_GAMMA_
			difFactor = undo_gamma(difFactor);
		#endif
		pixel.color0.rgb *= saturate(difFactor);
		pixel.color0.rgb += do_gamma(saturate(difFactor - 1.0));
		pixel.color0.rgb += pixel.color0.rgb * fAmbient;
		
		// specular
		#ifdef _DFX_SPECULAR_
			pixel.color0.rgb += specular * vecSpecular.rgb * vtx.normal.w;
		#endif
	#endif
	
	// emissive
	#ifdef _DFX_EMISSIVE_
		pixel.color0.rgb += vecEmissive.rgb;
	#endif
	
	#ifdef _DFX_GAMMA_
		pixel.color0.rgb = undo_gamma(pixel.color0.rgb);
	#endif
	
	// alpha
	pixel.color0.a *= fAlpha;
	
	// fog
	#ifdef _DFX_FOG_
		float strengthFog = vecFogColor.w * saturate((vtx.fog - vecFog.x) * vecFog.z);
		pixel.color0.rgb = lerp(pixel.color0.rgb, vecFogColor.rgb, strengthFog);
	#endif
	
	#ifdef _DFX_CONTRAST_BRIGHTNESS_
		pixel.color0.rgb = (pixel.color0.rgb - 0.5) * (100.0 + contrast) / 100.0 + 0.5;
		pixel.color0.rgb += brightness / 100.0;
	#endif
	
//	#define AMB_COLOR          0.0
//	#define AMB_PRV            1.0
//	#define DIF_COLOR          2.0
//	#define SPEC_COLOR         3.0
//	#define SPEC_TERM          4.0
//	#define WORLD_NORMALS      5.0
//	#define TAN_NORMALS        6.0
//	#define LIGHTMAP           7.0
	
	#ifdef _DFX_DEBUG_
		pixel.color0.rgb = 0;
		debug_layer -= 0.5;
		if(debug_layer < AMB_COLOR) {
			#ifdef _DFX_AMBIENT_
				pixel.color0.rgb = vecAmbientColor.rgb * vecAmbient.rgb;
			#endif
		} else if(debug_layer < AMB_PRV) {
			#ifdef _DFX_PRV_
				pixel.color0.rgb = vecLight.rgb;
			#endif
		} else if(debug_layer < DIF_COLOR) {
			#ifdef _DFX_DIFFUSE_
				pixel.color0.rgb = diffuse * vecDiffuse.rgb;
			#endif
		} else if(debug_layer < SPEC_COLOR) {
			#ifdef _DFX_DIFFUSE_
				#ifdef _DFX_SPECULAR_
					pixel.color0.rgb = specular * vtx.normal.w * vecSpecular.rgb;
				#endif
			#endif
		} else if(debug_layer < SPEC_TERM) {
			#ifdef _DFX_DIFFUSE_
				#ifdef _DFX_SPECULAR_
					pixel.color0.rgb = vecSpecular.rgb * vtx.normal.w;
				#endif
			#endif
		} else if(debug_layer < WORLD_NORMALS) {
			#ifdef _DFX_DIFFUSE_
				pixel.color0.rgb = 0.5 + vtx.normal.xyz;
			#endif
		} else if(debug_layer < TAN_NORMALS) {
			#ifdef _DFX_DIFFUSE_
				#ifdef _DFX_NORMALMAP_
					pixel.color0.rgb = normalmap.rgb;
				#endif
			#endif
		} else if(debug_layer < LIGHTMAP) {
			#ifdef _DFX_DIFFUSE_
				#ifdef _DFX_LIGHTMAP_
					#ifdef _DFX_BLOCK_
						pixel.color0.rgb = tex2D(smpLightmap, vtx.uv.zw).rgb;
					#else
						pixel.color0.rgb = tex2D(smpLightmap, vtx.uv.xy).rgb;
					#endif
				#endif
			#endif
		}
	#endif
	
	return pixel;
}

/******************************************************************************/
// technique:

technique dfx_template {
	pass one {
		VertexShader = compile vs_3_0 vs();
		PixelShader  = compile ps_3_0 ps();
	}
}

technique fallback { pass one { } }
