# Linux
# mplFile≔FileTools:−JoinPath(["Documents/Documents/Master/Publications/ITA/Projects/Maple/multiplicative_inverse_233.mpl"],base=homedir)

# Windows
# mplFile≔FileTools:−JoinPath(["D:\\Documents\\Master\\Publications\\ITA\\Projects\\maple-ecc\\multiplicative_inverse_233.mpl"],base=homedir)

# read mplFile

# ROM(0) <= "1000"; βi = β1 * (βi−1)^2;         ; s1
# ROM(1) <= "1000"; βi = β1 * (βi−1)^2;         ; s1
# ROM(2) <= "0001"; βi = (βi−1) * ((βi−1)^(2^p)); s3
# ROM(3) <= "1000"; βi = β1 * (βi−1)^2;         ; s1
# ROM(4) <= "0010"; βi = (βi−1) * ((βi−1)^(2^p)); s7
# ROM(5) <= "0011"; βi = (βi−1) * ((βi−1)^(2^p)); s14
# ROM(6) <= "1000"; βi = β1 * (βi−1)^2;         ; s1
# ROM(7) <= "0100"; βi = (βi−1) * ((βi−1)^(2^p)); s29
# ROM(8) <= "0101"; βi = (βi−1) * ((βi−1)^(2^p)); s58
# ROM(9) <= "0110"; βi = (βi−1) * ((βi−1)^(2^p)); s116

# βi = (βi−1) * ((βi−1)^(2^p))
# βi = β1 * (βi−1)^2

P := x^233 + x^74 + 1;
N := 233;

# definition of the input A to be inverted
GField := GF(2, N, P);
ap_int := 9489709307118967263545821199884232526959028607250683147702253942510865;
ap := GField[input](ap_int):
ap_hex := convert(ap_int, hex);

# b_1 equal to a
b_0 := ap:
# b_i equal to a
b_i := ap:

# ROM(0) <= "1000"; βi = β1 * (βi−1)^2;         ; s1
s1_b_i  := GField[`^`](b_i, 2^1):
b_i  := GField[`*`](s1_b_i, b_i):
b_1_int := GField[output](b_i):
b_1_hex := convert(b_1_int, hex);

# ROM(1) <= "1000"; βi = β1 * (βi−1)^2;         ; s1
s1_b_i  := GField[`^`](b_i, 2^1):
b_i  := GField[`*`](s1_b_i, b_i):
b_2_int := GField[output](b_i):
b_2_hex := convert(b_2_int, hex);

# ROM(2) <= "0001"; βi = (βi−1) * ((βi−1)^(2^p)); s3
s3_b_i  := GField[`^`](b_i, 2^3):
b_i  := GField[`*`](s3_b_i, b_i):
b_3_int := GField[output](b_i):
b_3_hex := convert(b_3_int, hex);

# ROM(3) <= "1000"; βi = β1 * (βi−1)^2;         ; s1
s1_b_i  := GField[`^`](b_i, 2^1):
b_i  := GField[`*`](s1_b_i, b_i):
b_4_int := GField[output](b_i):
b_4_hex := convert(b_4_int, hex);

# ROM(4) <= "0010"; βi = (βi−1) * ((βi−1)^(2^p)); s7
s7_b_i := GField[`^`](b_i, 2^7):
b_i := GField[`*`](s7_b_i, b_i):
b_5_int := GField[output](b_i):
b_5_hex := convert(b_5_int, hex);

# ROM(5) <= "0011"; βi = (βi−1) * ((βi−1)^(2^p)); s14
s14_b_i  := GField[`^`](b_i, 2^14):
b_i  := GField[`*`](s14_b_i, b_i):
b_6_int := GField[output](b_i):
b_6_hex := convert(b_6_int, hex);

# ROM(6) <= "1000"; βi = β1 * (βi−1)^2;         ; s1
s1_b_i  := GField[`^`](b_i, 2^1):
b_i  := GField[`*`](s1_b_i, b_i):
b_7_int := GField[output](b_i):
b_7_hex := convert(b_7_int, hex);

# ROM(7) <= "0100"; βi = (βi−1) * ((βi−1)^(2^p)); s29
s29_b_i  := GField[`^`](b_i, 2^29):
b_i  := GField[`*`](s29_b_i, b_i):
b_8_int := GField[output](b_i):
b_8_hex := convert(b_8_int, hex);

# ROM(8) <= "0101"; βi = (βi−1) * ((βi−1)^(2^p)); s58
s58_b_i  := GField[`^`](b_i, 2^58):
b_i  := GField[`*`](s58_b_i, b_i):
b_9_int := GField[output](b_i):
b_9_hex := convert(b_9_int, hex);

# ROM(9) <= "0110"; βi = (βi−1) * ((βi−1)^(2^p)); s116
s116_b_i  := GField[`^`](b_i, 2^116):
b_i  := GField[`*`](s116_b_i, b_i):
b_10_int := GField[output](b_i):
b_10_hex := convert(b_10_int, hex);

# Itoh-Tsuji Inverse
ap_ita_inv := GField[`^`](b_i, 2):
ap_ita_inv_int := GField[output](ap_ita_inv):
ap_ita_inv_hex := convert(ap_ita_inv_int, hex);

# test the result by sumply multiply ap by its inverse multiplicative
test_ita := GField[`*`](ap, ap_ita_inv):
test_ita_int := GField[output](test_ita):
test_ita_invXa_hex := convert(test_ita_int, hex);

# real inverse
ap_inverse := GField[inverse](ap):
ap_inverse_int := GField[output](ap_inverse):
ap_inverse_hex := convert(ap_inverse_int, hex);

# test the result by sumply multiply ap by its inverse multiplicative
test := GField[`*`](ap, ap_inverse):
test_int := GField[output](test):
test_hex := convert(test_int, hex);
