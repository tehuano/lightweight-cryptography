# Linux
# mplFile≔FileTools:−JoinPath(["Documents/Documents/Master/Publications/ITA/Projects/Maple/multiplicative_inverse_163.mpl"],base=homedir)

# Windows
# mplFile≔FileTools:−JoinPath(["D:\\Documents\\Master\\Publications\\ITA\\Projects\\Maple\\squaring_163.mpl"],base=homedir)

# read mplFile

# ROM(0) <= "1000"; βi = β1 * (βi−1)^2;           s1
# ROM(1) <= "0001"; βi = (βi−1) * ((βi−1)^(2^p)); s2
# ROM(2) <= "1000"; βi = β1 * (βi−1)^2;           s1
# ROM(3) <= "0010"; βi = (βi−1) * ((βi−1)^(2^p)); s5
# ROM(4) <= "0011"; βi = (βi−1) * ((βi−1)^(2^p)); s10
# ROM(5) <= "0100"; βi = β1 * (βi−1)^2;           s20
# ROM(6) <= "0101"; βi = (βi−1) * ((βi−1)^(2^p)); s40
# ROM(7) <= "1000"; βi = β1 * (βi−1)^2;           s1
# ROM(8) <= "0110"; βi = (βi−1) * ((βi−1)^(2^p)); s81

# βi = (βi−1) * ((βi−1)^(2^p))
# βi = β1 * (βi−1)^2

P := x^163 + x^7 + x^6 + x^3 + 1;
N := 163;

# definition of the input A to be inverted
GField := GF(2, N, P);
ap_int := 6044006412955031049079471306680227034553282705375;
ap := GField[input](a_int):
ap_hex := convert(ap_int, hex);

# b_1 equal to a 
b_0 := ap:
# 
b_i := ap:

# ROM(0) <= "1000"; βi = β1 * (βi−1)^2; s1
s1_b_i  := GField[`^`](b_i, 2^1):
b_i  := GField[`*`](s1_b_i, b_i):
b_1_int := GField[output](b_i):
b_1_hex := convert(b_1_int, hex);

# ROM(1) <= "0001"; βi = (βi−1) * ((βi−1)^(2^p)); s2
s2_b_i  := GField[`^`](b_i, 2^2):
b_i  := GField[`*`](s2_b_i, b_i):
b_2_int := GField[output](b_i):
b_2_hex := convert(b_2_int, hex);

# ROM(2) <= "1000"; βi = β1 * (βi−1)^2; s1
s1_b_i  := GField[`^`](b_i, 2^1):
b_i  := GField[`*`](s1_b_i, b_i):
b_3_int := GField[output](b_i):
b_3_hex := convert(b_3_int, hex);

# ROM(3) <= "0010"; βi = (βi−1) * ((βi−1)^(2^p)); s5
s5_b_i  := GField[`^`](b_i, 2^5):
b_i  := GField[`*`](s5_b_i, b_i):
b_4_int := GField[output](b_i):
b_4_hex := convert(b_4_int, hex);

# ROM(4) <=	"0011"; βi = (βi−1) * ((βi−1)^(2^p)); s10
s10_b_i := GField[`^`](b_i, 2^10):
b_i := GField[`*`](s10_b_i, b_i):
b_5_int := GField[output](b_i):
b_5_hex := convert(b_5_int, hex);

# ROM(5) <= "0100"; βi = β1 * (βi−1)^2; s20
s20_b_i  := GField[`^`](b_i, 2^20):
b_i  := GField[`*`](s20_b_i, b_i):
b_6_int := GField[output](b_i):
b_6_hex := convert(b_6_int, hex);

# ROM(6) <= "0101"; βi = (βi−1) * ((βi−1)^(2^p)); s40
s40_b_i  := GField[`^`](b_i, 2^40):
b_i  := GField[`*`](s40_b_i, b_i):
b_7_int := GField[output](b_i):
b_7_hex := convert(b_7_int, hex);

# ROM(7) <= "1000"; βi = β1 * (βi−1)^2; s1
s1_b_i  := GField[`^`](b_i, 2^1):
b_i  := GField[`*`](s1_b_i, b_i):
b_8_int := GField[output](b_i):
b_8_hex := convert(b_8_int, hex);

# ROM(8) <= "0110"; βi = (βi−1) * ((βi−1)^(2^p)); s81
s81_b_i  := GField[`^`](b_i, 2^81):
b_i  := GField[`*`](s81_b_i, b_i):
b_9_int := GField[output](b_i):
b_9_hex := convert(b_9_int, hex);

# Itoh-Tsuji Inverse
ap_ita_inv := GField[`^`](b_i, 2):
ap_ita_inv_int := GField[output](ap_ita_inv):
ap_ita_inv_hex := convert(ap_ita_inv_int, hex);

# test the result by sumply multiply ap by its inverse multiplicative
test_ita := GField[`*`](ap, ap_ita_inv):
test_ita_int := GField[output](test_ita):
test_ita_hex := convert(test_int, hex);

# real inverse
ap_inverse := GField[inverse](ap):
ap_inverse_int := GField[output](ap_inverse):
ap_inverse_hex := convert(ap_inverse_int, hex);

# test the result by sumply multiply ap by its inverse multiplicative
test := GField[`*`](ap, ap_inverse):
test_int := GField[output](test):
test_hex := convert(test_int, hex);
