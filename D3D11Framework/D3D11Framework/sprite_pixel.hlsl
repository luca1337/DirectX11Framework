
Texture2D albedo_texture : register(t0);
SamplerState texture_sampler : register(s0);

cbuffer sprite_buffer
{
    float4 color;
    int use_texture;
};

struct ps_in
{
    float4 world_position   : SV_Position;
    float3 world_normal     : NORMALS;
    float2 world_uv         : UVS;
};

struct ps_out
{
    float4 out_pixel : SV_Target;
};

ps_out main(ps_in IN)
{
    ps_out OUT;

    if (use_texture)
        OUT.out_pixel = albedo_texture.Sample(texture_sampler, IN.world_uv);
    else
        OUT.out_pixel = color;

    return OUT;
}