# Linux
# mplFile≔FileTools:−JoinPath(["Documents/Documents/Master/Publications/ITA/Projects/Maple/multiplicative_inverse_163.mpl"],base=homedir)

# Windows
# mplFile≔FileTools:−JoinPath(["D:\\Documents\\Master\\Publications\\ITA\\Projects\\Maple\\squaring_163.mpl"],base=homedir)

# read mplFile

P := x^163 + x^7 + x^6 + x^3 + 1;
N := 163;

GField := GF(2, N, P);
ap_int := 6044006412955031049079471306680227034553282705375;
ap := GField[input](ap_int):
ap_hex := convert(a_int, hex);

a_s1  := GField[`^`](ap, 2^1):
a_int := GField[output](a_s1):
a_s1_hex := convert(a_int, hex);

a_s2 := GField[`^`](ap, 2^2):
a_int := GField[output](a_s2):
a_s2_hex := convert(a_int, hex);

a_s5 := GField[`^`](ap, 2^5):
a_int := GField[output](a_s5):
a_s5_hex := convert(a_int, hex);

a_s10 := GField[`^`](ap, 2^10):
a_int := GField[output](a_s10):
a_s10_hex := convert(a_int, hex);

a_s20 := GField[`^`](ap, 2^20):
a_int := GField[output](a_s20):
a_s20_hex := convert(a_int, hex);

a_s40 := GField[`^`](ap, 2^40):
a_int := GField[output](a_s40):
a_s40_hex := convert(a_int, hex);

a_s81 := GField[`^`](ap, 2^81):
a_int := GField[output](a_s81):
a_s81_hex := convert(a_int, hex);



