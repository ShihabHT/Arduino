Here's a walkthrough of how to calculate the checksum.

Take your card number (this is just directly quoted from your text)



&nbsp;	I received: 2
	I received: 51
	I received: 67
	I received: 48
	I received: 48
	I received: 67
	I received: 69
	I received: 55
	I received: 53
	I received: 52
	I received: 67
	I received: 67
	I received: 66
	I received: 3


This would give you a number that is equivalent to the following:

&nbsp;	2 51 67 48 48 67 69 55 53 52 67 67 66 3



The first number (2) indicates that this is the beginning of a request.

The last number (3) indicates that this is the end of a request.

&nbsp;	**2** 51 67 48 48 67 69 55 53 52 67 67 66 **3**



For the purposes of calculating the checksum, we are going to remove these two numbers. So your new number is now:

&nbsp;	51 67 48 48 67 69 55 53 52 67 67 66



The last two numbers that you have are your checksum. The remaining numbers are your card number. So:

Your card number is:

&nbsp;	51 67 48 48 67 69 55 53 52 67



And your checksum is:

&nbsp;	67 66



Next you need to convert your Card Number and your Checksum to ASCII values:

Your card number is:

&nbsp;	3 C 0 0 C E 7 5 4 C



And your checksum is:

&nbsp;	C B



Next, grab each number into pairs:

Your card number is:

&nbsp;	3C 00 CE 75 4C



And your checksum is:

&nbsp;	CB



Then you need to treat each pair as a HEXIDECIMAL value and do an XOR against them. So basically you need to prove the following:

&nbsp;	(3C ^ 00) ^ CE ^ 75 ^ 4C == CB

&nbsp;	(3C ^ CE) ^ 75 ^ 4C == CB

&nbsp;	(F2 ^ 75) ^ 4C == CB

&nbsp;	(87 ^ 4C) = CB

&nbsp;	CB == CB



Because CB == CB, this is a valid transaction.

