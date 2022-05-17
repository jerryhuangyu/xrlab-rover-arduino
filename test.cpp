struct Odom{
    float a, b, c, d;
};

Odom ComputeOdom(Odom odom)
{
    odom.a = 1.0f;
    odom.b = 2.0f;
    odom.c = 3.0f;
    odom.d = 4.0f;

    return (odom);
}

void main(){
    Odom ans = ComputeOdom(ans);
    ans.a;
}