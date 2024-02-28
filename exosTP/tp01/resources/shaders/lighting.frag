#version 330 core
out vec4 FragColor;

in vec4 vColor;
in vec2 TexCoord;
in vec3 Normal;


struct DirectionalLight {
	vec3 color;
    float ambientIntensity;
    float diffuseIntensity;
    vec3 direction;

};

uniform sampler2D theTexture;

uniform DirectionalLight directionalLight;

void main() {
    vec4 ambientColor = vec4(directionalLight.color, 1.0) * directionalLight.ambientIntensity;

    float diffuseFactor = max(dot(normalize(Normal), normalize(directionalLight.direction) ), 0.0f);

    vec4 diffuseColor = vec4(directionalLight.color, 1.0f) * directionalLight.diffuseIntensity * diffuseFactor;
	if (diffuseFactor > 0) {
		diffuseColor = vec4(directionalLight.color, 1.0) * directionalLight.diffuseIntensity * diffuseFactor;
	}

    FragColor = texture(theTexture, TexCoord) * (ambientColor + diffuseColor);
}
