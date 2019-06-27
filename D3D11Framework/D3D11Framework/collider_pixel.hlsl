struct vs_in
{
    float4 world_vertex : SV_Position;
};

struct vs_out
{
    float4 out_pixel : SV_Target;
};

vs_out main(vs_in IN)
{
    vs_out OUT;

    OUT.out_pixel = float4(1.0f, 0.0f, 0.0f, 1.0f);

    return OUT;
}