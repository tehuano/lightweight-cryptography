# mplFile≔FileTools:−JoinPath(["/home/disorder/Documents/Documents/Master/Publications/ITA/Projects/Maple/multiplicative_inverse.𝚖𝚙𝚕"],base=homedir)
# read mplFile

P := x^193+x^15+1;
N := 193;

GField := GF(2, N, P);
a := (rand(2^N))();
ap := GField[input](a);
ax := convert(a, hex);
ap_inverse := GField[inverse](ap);
a_inverso := GField[output](ap_inverse);
a_inversox := convert(a_inverso, hex);
comp := GField[`*`](ap, ap_inverse);
