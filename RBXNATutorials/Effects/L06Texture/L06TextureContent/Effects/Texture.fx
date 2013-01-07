float4x4 World;
float4x4 View;
float4x4 Projection;

float4 AmbientColor = float4(1, 1, 1, 1);
float AmbientIntensity = 0.1;

float4x4 WorldInverseTranspose; // the transpose of the inverse of the world matrix

float3 DiffuseLightDirection = float3(1, 0, 0);
float4 DiffuseColor = float4(1, 1, 1, 1);
float DiffuseIntensity = 1;

float Shininess = 200;  // �����, ֵԽ����ԽС, ���淴����Խǿ, ����Խ����. ������ 100~500, �������������
float4 SpecularColor = float4(1, 1, 1, 1);
float SpecularIntensity = 1;    // Lower intensities will result in dimmer highlights.
float3 ViewVector = float3(1, 0, 0);

texture ModelTexture;
sampler2D textureSampler = sampler_state {
    Texture = (ModelTexture);
    MagFilter = Linear;
    MinFilter = Linear;
    AddressU = Clamp;
    AddressV = Clamp;
};

struct VertexShaderInput
{
    float4 Position : POSITION0;
    float4 Normal : NORMAL0;
    float2 TextureCoordinate : TEXCOORD0;
};

struct VertexShaderOutput
{
    float4 Position : POSITION0;
    float4 Color : COLOR0;
    float3 Normal : TEXCOORD0;
    float2 TextureCoordinate : TEXCOORD1;
};

VertexShaderOutput VertexShaderFunction(VertexShaderInput input)
{
    VertexShaderOutput output;

    float4 worldPosition = mul(input.Position, World);
    float4 viewPosition = mul(worldPosition, View);
    output.Position = mul(viewPosition, Projection);

    // takes the normal and transforms it in such a way that the normal is now relative to where the object is in the world.
    float4 normal = mul(input.Normal, WorldInverseTranspose);
    float lightIntensity = dot(normal, DiffuseLightDirection);
    // saturate: take a color and ensure that it has values between 0 and 1 for each of the components.
    output.Color = saturate(DiffuseColor * DiffuseIntensity * lightIntensity);

    output.Normal = normal;
    output.TextureCoordinate = input.TextureCoordinate;

    return output;
}

float4 PixelShaderFunction(VertexShaderOutput input) : COLOR0
{
    float3 light = normalize(DiffuseLightDirection);
    float3 normal = normalize(input.Normal);
    float3 r = normalize(2 * dot(light, normal) * normal - light);  // �������
    float3 v = normalize(mul(normalize(ViewVector), World));    // �۲췽��

    float dotProduct = dot(r, v);   // ���䷽��͹۲췽��ļн� cos
    // ������Խ�� length(input.Color) ԽС, ���淴��Խ��
    float4 specular = SpecularIntensity * SpecularColor * max(pow(dotProduct, Shininess), 0) * length(input.Color);

    // ���������е�������ɫֵ
    float4 textureColor = tex2D(textureSampler, input.TextureCoordinate);
    textureColor.a = 1; // because the texture sampler doesn't pull out the alpha value from the texture.

    // ��������ɫֵ factor with our diffuse light. diffuse ���� shade (������ɫ) ������
    return saturate(textureColor * (input.Color) + AmbientColor * AmbientIntensity + specular);
}

technique Textured
{
    pass Pass1
    {
        VertexShader = compile vs_2_0 VertexShaderFunction();
        PixelShader = compile ps_2_0 PixelShaderFunction();
    }
}