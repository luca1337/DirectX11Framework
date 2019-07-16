
cbuffer matrices : register(b0)
{
    matrix model;
    matrix view;
    matrix projection;
};

struct vs_in
{
    float3 position : VERTICES;
    float3 normal   : NORMALS;
    float2 uv       : UVS;
};

struct vs_out
{
    float4 world_position   : SV_Position;
    float3 world_normal     : NORMALS;
    float2 world_uv         : UVS;
};

vs_out main(vs_in IN)
{
    vs_out OUT;

    // Compute vertex transformations
    OUT.world_position = mul(model, float4(IN.position, 1.0f));
    OUT.world_position = mul(view, OUT.world_position);
    OUT.world_position = mul(projection, OUT.world_position);

    // Compute normals transformations
    OUT.world_normal = mul(model, float4(IN.normal, 1.0f));

    // Assign to pixel shader struct the uv "as-is"
    OUT.world_uv = IN.uv;

    return OUT;
}