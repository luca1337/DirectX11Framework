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

    OUT.world_vertex = float4(IN.vertex, 1.0f);

    return OUT;
}