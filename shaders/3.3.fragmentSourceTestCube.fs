#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;

uniform vec3 lightPos; 
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 cameraPos;


void main()
{
    float ambientStrngth = 0.1f;
    float specularStrength = 0.5f;
    vec3 ambient = lightColor * ambientStrngth;

    //diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    //speculat
    vec3 viewDir = normalize(cameraPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm); 
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor; 

    vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor = vec4(result, 1.0);
}