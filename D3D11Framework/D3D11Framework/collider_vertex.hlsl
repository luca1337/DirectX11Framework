cbuffer matrices
{
    matrix model;
    matrix view;
    matrix projection;
};

struct vs_in
{
    float3 vertex : VERTICES;
};

struct vs_out
{
    float4 world_vertex : SV_Position;
};

vs_out main(vs_in IN)
{
    vs_out OUT;

    OUT.world_vertex = mul(model, float4(IN.vertex, 1.0f));
    OUT.world_vertex = mul(view, OUT.world_vertex);
    OUT.world_vertex = mul(projection, OUT.world_vertex);

    return OUT;
}