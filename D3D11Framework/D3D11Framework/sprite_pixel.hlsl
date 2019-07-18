
Texture2D albedo_texture : register(t0);
SamplerState texture_sampler : register(s0);

cbuffer sprite_buffer : register(b0)
{
    float4 color;
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

    OUT.out_pixel = albedo_texture.Sample(texture_sampler, float2(IN.world_uv.x, 1 - IN.world_uv.y));
    OUT.out_pixel *= color;

    return OUT;
}