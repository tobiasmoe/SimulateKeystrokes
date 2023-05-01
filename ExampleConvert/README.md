## This python program shows how to convert a csv file to the format needed for the C++ program to run.
The format used in this example is the following:

*Column 1: ID of user <br>
Column 2: Gender of the user (1=Female, 0=Male)<br>
Column 3: Age of the user<br>
Of the remaining 2n+1 values are there first (n+1) duration values, followed by n latency values<br>*

Example of a row where the password is "leonardo dicaprio":<br>
*1	1	34	192	72	97	94	48	72	72	72	97	72	72	48	72	96	72	88	120	424	0	266	87	144	96	-24	136	143	24	136	168	48	168	-24	48*<br>

You can customize the password by changing **line 31** and entering the keycodes for the password in chronological order.<br>
You also need to change **line 32 and 33** to specify the input and output csv file.
