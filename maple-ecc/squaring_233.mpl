# Linux
# mplFile≔FileTools:−JoinPath(["Documents/Documents/Master/Publications/ITA/Projects/maple-ecc/squaring_233.mpl"],base=homedir)

# Windows
# mplFile≔FileTools:−JoinPath(["D:\\Documents\\Master\\Publications\\ITA\\Projects\\maple-ecc\\squaring_233.mpl"],base=homedir)

# read mplFile

P := x^233 + x^74 + 1;
N := 233;

GField := GF(2, N, P);
ap_int := 9489709307118967263545821199884232526959028607250683147702253942510865;
ap := GField[input](ap_int):
ap_hex := convert(ap_int, hex);

a_s1  := GField[`^`](ap, 2^1):
a_int := GField[output](a_s1):
a_s1_hex := convert(a_int, hex);

a_s3  := GField[`^`](ap, 2^3):
a_int := GField[output](a_s3):
a_s3_hex := convert(a_int, hex);

a_s3 := GField[`^`](ap, 2^1):
a_s3 := GField[`^`](a_s3, 2^1):
a_int := GField[output](a_s3):
a_s2_hex := convert(a_int, hex);
a_s3 := GField[`^`](a_s3, 2^1):
a_int := GField[output](a_s3):
a_s3_hex := convert(a_int, hex);

a_s2 := GField[`^`](ap, 2^2):
a_int := GField[output](a_s2):
a_s2_hex := convert(a_int, hex);

a_s7 := GField[`^`](ap, 2^7):
a_int := GField[output](a_s7):
a_s7_hex := convert(a_int, hex);

a_s14 := GField[`^`](ap, 2^14):
a_int := GField[output](a_s14):
a_s14_hex := convert(a_int, hex);

a_s29 := GField[`^`](ap, 2^29):
a_int := GField[output](a_s29):
a_s29_hex := convert(a_int, hex);

a_s58 := GField[`^`](ap, 2^58):
a_int := GField[output](a_s58):
a_s58_hex := convert(a_int, hex);

a_s116 := GField[`^`](ap, 2^116):
a_int := GField[output](a_s116):
a_s116_hex := convert(a_int, hex);



