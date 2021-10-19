#version 330 core								

uniform vec3 u_color;
uniform bool u_has_texture;
uniform bool u_use_light;
uniform vec3 u_light_pos;
uniform vec3 u_light_color;
uniform sampler2D u_texture;
uniform vec3 u_camera_pos;

out vec4 f_color;

in vec2 v_uv;
in vec3 v_normal;
in vec3 v_frag_pos;

void main() {
	vec3 object_color;
	if(u_has_texture) 	object_color = vec3(texture(u_texture, v_uv)) * u_color; 
	else 				object_color = u_color;

	vec3 result;
	if(u_use_light) {
		// Ambient.
		float ambient_strength = 0.1;
		vec3 ambient = ambient_strength * u_light_color
		
		// Diffuse.
		vec3 norm = normalize(v_normal);
		vec3 light_dir = normalize(u_light_pos - v_frag_pos);
		float diff = max(dot(norm, light_dir), 0.0);
		vec3 diffuse = diff * u_light_color;
		
		// Specular.
		float specular_strength = 1.0;
		vec3 view_dir = normalize(u_camera_pos - v_frag_pos);
		vec3 reflect_dir = reflect(-light_dir, norm);
		float spec = pow(max(dot(view_dir, reflect_dir), 0.0), 32);
		vec3 specular = specular_strength * spec * u_light_color;
		
		// Attenuation.
		float distance = length(u_light_pos - v_frag_pos);
		float attenuation = clamp(30 / distance, 0, 1);
		ambient *= attenuation;
		specular *= attenuation;
		diffuse *= attenuation;
		result = (ambient + diffuse + specular) * object_color * attenuation;
	} else {
		result = object_color;
	
	f_color = vec4(result, 1.0);
};