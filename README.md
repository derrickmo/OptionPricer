# OptionPricer

An option pricer I built from scratch in 2019!

STL Library is required. A sample output is provided below.

Testing constructors:
Test1: Type: C, T: 1, K: 100, sig: 0.2, r: 0.05, S: 100, b: 0.05, unam: and price is 10.4506
Test2: Type: C, T: 0.75, K: 95, sig: 0.2, r: 0.05, S: 120, b: 0.05, unam: and price is 28.9529
Test3: Type: P, T: 1.25, K: 145, sig: 0.1, r: 0.02, S: 150, b: 0.02, unam: and price is 3.08563
Test4: Type: P, T: 1.25, K: 145, sig: 0.1, r: 0.02, S: 150, b: 0.02, unam: and price is 3.08563
Invalid input, please enter "C" or "P" as option type. The option is initialized as a call option
Test5: Type: C, T: 1.25, K: 145, sig: 0.1, r: 0.02, S: 150, b: 0.02, unam: and price is 11.6657

Testing constructors:
gsTest: Type: C, T: 1, K: 100, sig: 0.2, r: 0.05, S: 100, b: 0.05, unam: and price is 10.4506
New type is: P
New T is: 2
New Strike is: 250
New Sigma is: 0.3
New Risk-free rate is: 0.02
New Spot is: 300
New Carry is: 0.03
New unam is: c++ is awesome!!!
New price is: 20.0881
Final gsTest: Type: P, T: 2, K: 250, sig: 0.3, r: 0.02, S: 300, b: 0.03, unam: c++ is awesome!!!and price is 20.0881

Test for question A1.a
Batch 1's call price is 2.13337 and put price is 5.84628
Batch 2's call price is 7.96557 and put price is 7.96557
Batch 3's call price is 0.204058 and put price is 4.07326
Batch 4's call price is 92.1757 and put price is 1.2475

Test for question A1.b
Batch 1's call price is 2.13337, partiy price is 2.13337 and parity check is 1
Batch 2's call price is 7.96557, partiy price is 7.96557 and parity check is 1
Batch 3's call price is 0.204058, partiy price is 0.204058 and parity check is 1
Batch 4's call price is 92.1757, partiy price is 92.1757 and parity check is 1
Batch 1's put price is 5.84628, partiy price is 5.84628 and parity check is 1
Batch 2's put price is 7.96557, partiy price is 7.96557 and parity check is 1
Batch 3's put price is 4.07326, partiy price is 4.07326 and parity check is 1
Batch 4's put price is 1.2475, partiy price is 1.2475 and parity check is 1

Test for question A1.c
Spot    Call            Put
60      2.13337         5.84628
61      2.52699         5.2399
62      2.96317         4.67608
63      3.44196         4.15487
64      3.96293         3.67584
65      4.5252          3.23811
66      5.12747         2.84039
67      5.76813         2.48104
68      6.44526         2.15817
69      7.15673         1.86965
70      7.90027         1.61319

Test for question A1.d
Rows: T from 0.1 to 1.0, Columns: S from 60 to 65
Type: C, T: 0.25, K: 65, sig: 0.3, r: 0.08, S: 60, b: 0.08, unam:
                60              61              62              63              64              65
0.1             0.761           1.027           1.353           1.742           2.197           2.717
0.15            1.244           1.568           1.945           2.375           2.859           3.397
0.2             1.701           2.065           2.475           2.933           3.438           3.989
0.25            2.133           2.527           2.963           3.442           3.963           4.525
0.3             2.545           2.962           3.419           3.915           4.449           5.021
0.35            2.939           3.376           3.85            4.36            4.906           5.486
0.4             3.318           3.772           4.261           4.783           5.339           5.927
0.45            3.683           4.153           4.654           5.188           5.753           6.348
0.5             4.038           4.52            5.034           5.577           6.15            6.752

Rows: S from 60 to 65, Columns: T from 0.05 to 0.3
Type: P, T: 0.25, K: 65, sig: 0.3, r: 0.08, S: 60, b: 0.08, unam:
                0.05            0.1             0.15            0.2             0.25            0.3
60              5.009           5.243           5.469           5.669           5.846           6.004
61              4.174           4.509           4.793           5.033           5.24            5.421
62              3.406           3.835           4.17            4.444           4.676           4.878
63              2.718           3.225           3.6             3.901           4.155           4.374
64              2.118           2.679           3.084           3.406           3.676           3.908
65              1.609           2.199           2.622           2.957           3.238           3.48

Rows: r from 0.15 to 0.25, Columns: K from 70 to 130
Type: C, T: 1, K: 100, sig: 0.2, r: 0, S: 100, b: 0, unam:
                70              80              90              100             110             120             130

0.15            26.03           18.23           11.7            6.856           3.694           1.848           0.8683

0.16            25.78           18.05           11.58           6.788           3.657           1.83            0.8597

0.17            25.52           17.87           11.46           6.72            3.621           1.812           0.8511

0.18            25.27           17.7            11.35           6.653           3.585           1.794           0.8427

0.19            25.01           17.52           11.24           6.587           3.549           1.776           0.8343

0.2             24.77           17.35           11.13           6.522           3.514           1.758           0.826

0.21            24.52           17.17           11.02           6.457           3.479           1.741           0.8178

0.22            24.27           17              10.91           6.393           3.444           1.723           0.8096

0.23            24.03           16.83           10.8            6.329           3.41            1.706           0.8016

0.24            23.79           16.67           10.69           6.266           3.376           1.689           0.7936

0.25            23.56           16.5            10.58           6.204           3.343           1.672           0.7857


Test for question A2.a
Type: C, T: 0.5, K: 100, sig: 0.36, r: 0.1, S: 105, b: 0, unam:
This option's call delta is 0.5946
This option's put delta is -0.3566
This option's gamma is 0.01349

Test for question A2.b/c
PutDelta:
Type: P, T: 0.5, K: 100, sig: 0.36, r: 0.1, S: 105, b: 0, unam:
                96              98              100             102             104
0.06            -0.2546         -0.2816         -0.3093         -0.3375         -0.3662
0.08            -0.2521         -0.2788         -0.3062         -0.3342         -0.3625
0.1             -0.2496         -0.276          -0.3031         -0.3308         -0.3589
0.12            -0.2471         -0.2733         -0.3001         -0.3276         -0.3554
0.14            -0.2447         -0.2705         -0.2971         -0.3243         -0.3518

CallDelta:
Type: C, T: 0.5, K: 100, sig: 0.36, r: 0.1, S: 105, b: 0, unam:
                96              98              100             102             104
0.06            0.7656          0.7386          0.7109          0.6827          0.654
0.08            0.7579          0.7313          0.7039          0.6759          0.6475
0.1             0.7504          0.724           0.6969          0.6692          0.6411
0.12            0.7429          0.7168          0.6899          0.6625          0.6347
0.14            0.7355          0.7097          0.6831          0.6559          0.6284

Gamma:
Type: C, T: 0.5, K: 100, sig: 0.36, r: 0.1, S: 105, b: 0, unam:
                96              98              100             102             104
0.06            0.01212         0.01276         0.01333         0.01384         0.01427
0.08            0.012           0.01263         0.0132          0.0137          0.01412
0.1             0.01188         0.01251         0.01307         0.01356         0.01398
0.12            0.01176         0.01238         0.01294         0.01343         0.01384
0.14            0.01164         0.01226         0.01281         0.01329         0.01371

Test for question A2.d
Delta using formula is 0.3725
Gamma using formula is 0.04204
With h =20 and delta is 0.414649 and the difference is 0.0421659
With h =20 and gamma is -0.0414649 and the difference is -0.0835076
With h =10 and delta is 0.385555 and the difference is 0.0130717
With h =10 and gamma is -0.0771109 and the difference is -0.119154
With h =5 and delta is 0.375868 and the difference is 0.00338491
With h =5 and gamma is -0.150347 and the difference is -0.19239
With h =2.5 and delta is 0.373334 and the difference is 0.000851447
With h =2.5 and gamma is -0.298667 and the difference is -0.34071
With h =1.25 and delta is 0.372696 and the difference is 0.000213146
With h =1.25 and gamma is -0.596314 and the difference is -0.638356
With h =0.625 and delta is 0.372536 and the difference is 5.33035e-05
With h =0.625 and gamma is -1.19212 and the difference is -1.23416
With h =0.3125 and delta is 0.372496 and the difference is 1.33269e-05
With h =0.3125 and gamma is -2.38398 and the difference is -2.42602
With h =0.15625 and delta is 0.372486 and the difference is 3.3318e-06
With h =0.15625 and gamma is -4.76782 and the difference is -4.80987
With h =0.078125 and delta is 0.372484 and the difference is 8.32954e-07
With h =0.078125 and gamma is -9.53558 and the difference is -9.57762
With h =0.0390625 and delta is 0.372483 and the difference is 2.08239e-07
With h =0.0390625 and gamma is -19.0711 and the difference is -19.1132

Type: C, T: 0.5, K: 100, sig: 0.1, r: 0.1, S: 110, b: 0.02, unam:
American Call's price is 18.5035
Type: P, T: 0.5, K: 100, sig: 0.1, r: 0.1, S: 110, b: 0.02, unam:
American Put's price is 3.03106

Spot    Call            Put
90      9.7027          10.5537
92      10.4136         9.20584
94      11.1595         8.05372
96      11.9416         7.06565
98      12.7605         6.21556
100     13.6174         5.48192
102     14.5131         4.84691
104     15.4486         4.29572
106     16.4249         3.81598
108     17.4429         3.39733
110     18.5035         3.03106

Rows: S from 85 to 115, Columns: K from 90 to 110
Type: C, T: 0.5, K: 100, sig: 0.1, r: 0.1, S: 110, b: 0.02, unam:
                90              95              100             105             110
85              10.2            9.045           8.073           7.245           6.535
90              12.26           10.87           9.703           8.708           7.855
95              14.58           12.94           11.55           10.36           9.347
100             17.2            15.26           13.62           12.22           11.02
105             20.12           17.85           15.93           14.3            12.9
110             23.37           20.73           18.5            16.61           14.98
115             26.97           23.92           21.35           19.16           17.28

Rows: S from 85 to 115, Columns: T from 90 to 110
Type: P, T: 0.5, K: 100, sig: 0.1, r: 0.1, S: 110, b: 0.02, unam:
                90              95              100             105             110
85              7.039           10.4            15.06           21.41           29.95
90              4.934           7.288           10.55           15.01           21
95              3.525           5.208           7.541           10.72           15
100             2.563           3.786           5.482           7.796           10.91
105             1.892           2.795           4.048           5.756           8.052
110             1.417           2.093           3.031           4.31            6.03
115             1.075           1.588           2.299           3.27            4.574
