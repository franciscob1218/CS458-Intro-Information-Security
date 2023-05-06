# LAB 3 - MD5 Collision Attack Lab:

## Task 1: Generating Two Different Files with the Same MD5 Hash

### Question 1. If the length of your prefix file is not multiple of 64 , what is going to happen?

### Step 1: Create a prefix file to use:

<aside>
💡 To test this question I created a file called prefix.txt

</aside>

```bash
seed@VM:~/Desktop$ vim prefix.txt
seed@VM:~/Desktop$ :wq #this is to save the file after creating it with VIM

#using bless you can check to see that the file is empty
seed@VM:~/Desktop$ bless prefix.txt
```

![Untitled](LAB%203%20-%20MD5%20Collision%20Attack%20Lab%20752f5406cb2640ff92c83e56a71c1b9f/Untitled.png)

---

---

### Step 2: Create a Msg in prefix.txt:

<aside>
💡 Now we will add a message to our prefix.txt using echo

</aside>

```bash
seed@VM:~/Desktop$ echo "Frans Seed Lab" >> prefix.txt
# And we can open that in bless to see that this all looks like in binary. 
seed@VM:~/Desktop$ bless prefix.txt
```

![Untitled](LAB%203%20-%20MD5%20Collision%20Attack%20Lab%20752f5406cb2640ff92c83e56a71c1b9f/Untitled%201.png)

---

---

### Step 3: Truncate prefix.txt:

<aside>
💡 Now we can truncate this file to a version that is not a multiple of 64.

For this example, I will use the number 70 as it is not a multiple of 64.

Then we can check that file again with ***bless*** after it has been truncated

</aside>

```bash
seed@VM:~/Desktop$ truncate -s 70 prefix.txt

seed@VM:~/Desktop$ bless prefix.txt
```

![Untitled](LAB%203%20-%20MD5%20Collision%20Attack%20Lab%20752f5406cb2640ff92c83e56a71c1b9f/Untitled%202.png)

---

---

### Step 4: Run md5collgen:

<aside>
💡 Now we will run the prefix.txt file through md5collgen and create 2 out files

and then we will check their values using ***bless***

</aside>

```bash
seed@VM:~/Desktop$ md5collgen -p prefix.txt -o out1_1.bin out2_1.bin

seed@VM:~/Desktop$ bless out1_1.bin out2_1.bin
```

![Untitled](LAB%203%20-%20MD5%20Collision%20Attack%20Lab%20752f5406cb2640ff92c83e56a71c1b9f/Untitled%203.png)

![Untitled](LAB%203%20-%20MD5%20Collision%20Attack%20Lab%20752f5406cb2640ff92c83e56a71c1b9f/Untitled%204.png)

---

---

### Conclusion:

<aside>
💡 As you can see in the screen shots below. The position underlined in red was the end of prefix file after being truncated to 70bytes

This clearly indicates that the md5collgen ***added extra padding*** to the prefix to fit into a multiple of 64 at 256 with the last bit at 0xff = 255 which is 256 when offset from 0

</aside>

![Untitled](LAB%203%20-%20MD5%20Collision%20Attack%20Lab%20752f5406cb2640ff92c83e56a71c1b9f/Untitled%205.png)

---

---

---

### Question 2. Create a prefix file with exactly 64 bytes, and run the collision tool again, and see what happens.

### Step 1: Re-Truncate prefix.txt:

<aside>
💡 Here we will start the next question by modifying  prefix.txt using truncate to have end up with 64 bytes

And we can check that by running ***Bless*** on the file

</aside>

```bash
seed@VM:~/Desktop$ truncate -s 64 prefix.txt

seed@VM:~/Desktop$ bless prefix.txt
```

![Untitled](LAB%203%20-%20MD5%20Collision%20Attack%20Lab%20752f5406cb2640ff92c83e56a71c1b9f/Untitled%206.png)

---

---

### Step 2: Run md5collgen again:

<aside>
💡 Now we will run the prefix.txt file through md5collgen and create 2 files these will be named a bit different to keep things consistent

and then we will check their values using ***bless***

</aside>

```bash
seed@VM:~/Desktop$ md5collgen -p prefix.txt -o out1_2.bin out2_2.bin

seed@VM:~/Desktop$ bless out1_2.bin out2_2.bin
```

![Untitled](LAB%203%20-%20MD5%20Collision%20Attack%20Lab%20752f5406cb2640ff92c83e56a71c1b9f/Untitled%207.png)

---

---

### Conclusion:

<aside>
💡 As seen in the last 2 screenshots the end of the prefix file at 0x3f did not change meaning md5collgen did not add Zeros for padding to make the file a multiple of 64bytes

</aside>

---

---

---

### Question 3. Are the data ( ***128*** bytes) generated by ***md5collgen*** completely different for the two output files? Please identify all the bytes that are different.

<aside>
💡 After running the md5collgen multiple times there only seem to be a couple of differences

You can see these differences in the screen shot below and they happen at these positions: 84, 110, 124, 174, 188

</aside>

![Untitled](LAB%203%20-%20MD5%20Collision%20Attack%20Lab%20752f5406cb2640ff92c83e56a71c1b9f/Untitled%208.png)

![Untitled](LAB%203%20-%20MD5%20Collision%20Attack%20Lab%20752f5406cb2640ff92c83e56a71c1b9f/Untitled%209.png)

<aside>
💡 We can also evaluate the 2 files using the diff command and the md5sum command. The result are shown in the screenshot

</aside>

```bash
seed@VM:~/Desktop$ xxd out1_2.bin >> out1_2.txt
seed@VM:~/Desktop$ xxd out2_2.bin >> out2_2.txt
# then manually remove the hex values outputted in hte txt files

seed@VM:~/Desktop$ diff out1_2.txt out2_2.txt
seed@VM:~/Desktop$ md5sum out1_2.bin
seed@VM:~/Desktop$ md5sum out2_2.bin
```

![Untitled](LAB%203%20-%20MD5%20Collision%20Attack%20Lab%20752f5406cb2640ff92c83e56a71c1b9f/Untitled%2010.png)

---

---

---

## Task 2: Understanding MD5’s Property

<aside>
💡 One intriguing fact is that even though adding the same file to the outputs of md5collgen changes the MD5 hash, both of the new hashes remain the same. This is due to the length extension that can occur with many hash functions, including SHA-1, SHA-2, and MD5. A compression function is applied to the current state and the current block by the hash function, which processes the message in fixed blocks while maintaining an internal state.

It is safe to assume that the internal state following the algorithm's execution was the same because the MD5 hashes of both files were identical. We'll refer to this internal state as s. As a result, after appending a file, there will be a stage in which the compression algorithm is run on s and the current block. This algorithm would be the same for both modified files. The MD5 hash for both files would be the same as this.

To test this, we will go through the following steps.

</aside>

### Step 1: Create a prefix file to use:

```bash
seed@VM:~/Desktop$ vim prefix2.txt
seed@VM:~/Desktop$ :wq #this is to save the file after creating it with VIM

#using bless you can check to see that the file is empty
```

---

---

### Step 2: Create a Msg in prefix2.txt:

<aside>
💡 Now we will add a message to our prefix.txt using echo

</aside>

```bash
seed@VM:~/Desktop$ echo "Frans Property" >> prefix2.txt
# And we can open that in bless to see that this all looks like in binary. 
seed@VM:~/Desktop$ bless prefix2.txt
```

![Untitled](LAB%203%20-%20MD5%20Collision%20Attack%20Lab%20752f5406cb2640ff92c83e56a71c1b9f/Untitled%2011.png)

---

---

### Step 3: Run md5collgen:

<aside>
💡 Now we will run the prefix.txt file through md5collgen and create 2 out files

And then we can verify that the MD5 hashes are the same using md5sum

</aside>

```bash
seed@VM:~/Desktop$ md5collgen -p prefix2.txt -o out1_3.bin out2_3.bin

seed@VM:~/Desktop$ md5sum out1_3.bin out2_3.bin
```

![Untitled](LAB%203%20-%20MD5%20Collision%20Attack%20Lab%20752f5406cb2640ff92c83e56a71c1b9f/Untitled%2012.png)

---

---

### Step 4: append a new message:

<aside>
💡 Now let’s append a random string to the end of both files and check the MD5 hashes of both files again.

Then we will again verify that the MD5 hashes are the same.

</aside>

```bash
seed@VM:~/Desktop$ echo "Dont Touch" >> out1_3.bin 

seed@VM:~/Desktop$ echo "Dont Touch" >> out2_3.bin

seed@VM:~/Desktop$ md5sum out1_3.bin out2_3.bin

```

![Untitled](LAB%203%20-%20MD5%20Collision%20Attack%20Lab%20752f5406cb2640ff92c83e56a71c1b9f/Untitled%2013.png)

<aside>
💡 We can see that the MD5 hashes remain identical.

</aside>

---

---

---

## Task 3: Generating Two Executable Files with the Same MD5 Hash

### Step 1: First we Need to create Program.C

<aside>
💡 Will take the program that was given to us in the instructions and make the file program.c

</aside>

```c
#include <stdio.h>
unsigned char xyz[200] = {
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5'
};

int main(){
	int i;
	for (i=0; i<200; i++){
		printf("%x", xyz[i]);
	}
	printf("\n");
}
```

<aside>
💡 Then we will compile the Program Above

</aside>

```bash
seed@VM:~/Desktop$ gcc program.c -o program.out
```

![Untitled](LAB%203%20-%20MD5%20Collision%20Attack%20Lab%20752f5406cb2640ff92c83e56a71c1b9f/Untitled%2014.png)

---

---

### Step 2: Running the Head command

<aside>
💡 It is simple to pinpoint the location where the array values are stored. 0x1040 is equivalent to 4160 in decimal form. Although this can be divided by 64, we'll choose a prefix length of 4224 bytes (0x1080) for now. (This is optional, but I wanted the split to be in the center of the array.) 

Now we will run head at the 4224 shift

</aside>

```bash
seed@VM:~/Desktop$ head -c 4224 a.out > prefix3
seed@VM:~/Desktop$ md5collgen -p prefix3 -o agen bgen
```

![Untitled](LAB%203%20-%20MD5%20Collision%20Attack%20Lab%20752f5406cb2640ff92c83e56a71c1b9f/Untitled%2015.png)

---

---

### Step 3: Checking the files using Bless

<aside>
💡 Now we have two files with the same MD5 hash but different suffixes. Looking at both agen and bgen in bless

</aside>

```bash
seed@VM:~/Desktop$ bless agen bgen
```

![Untitled](LAB%203%20-%20MD5%20Collision%20Attack%20Lab%20752f5406cb2640ff92c83e56a71c1b9f/Untitled%2016.png)

![Untitled](LAB%203%20-%20MD5%20Collision%20Attack%20Lab%20752f5406cb2640ff92c83e56a71c1b9f/Untitled%2017.png)

---

---

### Step 4: Appending the Common end

<aside>
💡 Now we will get the common end to be appended the Tail command

Then we will put them together, after we will need to add executable permissions. Then we can run both outs

We can then also check if the 2 file differ

</aside>

```bash
seed@VM:~/Desktop$ tail -c 4353 program.out > thecommonend.

seed@VM:~/Desktop$ cat thecommonend >> agen
seed@VM:~/Desktop$ cat thecommonend >> bgen

seed@VM:~/Desktop$ chmod +x agen
seed@VM:~/Desktop$ chmod +x agen

seed@VM:~/Desktop$ ./agen
seed@VM:~/Desktop$ ./bgen

seed@VM:~/Desktop$ ./agen > aoutput
seed@VM:~/Desktop$ ./bgen > boutput

seed@VM:~/Desktop$ diff -q aoutput boutput
```

![Untitled](LAB%203%20-%20MD5%20Collision%20Attack%20Lab%20752f5406cb2640ff92c83e56a71c1b9f/Untitled%2018.png)

<aside>
💡 Note that the output Differs here

</aside>

---

---

---

## Task 4: Making the Two Programs Behave Differently

### Step 1: First we Need to create Program2.C

<aside>
💡 Will take the program that was given to us in the instructions and make the file program2.c

</aside>

```c
#include <stdio.h>

unsigned char abc[300] = {
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5'
};
unsigned char xyz[300] = {
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5',
	'T','E','S','T','I','N','G','M','D','5'
};

int main()
{
        int i;
        int isSame=1;
        for(i = 0; i < 200; i++)
        {
                if(abc[i]!=xyz[i])
                        isSame=0;
        }
        if(isSame)
                printf("This would run the safe code and display the intended behaviour");
        else
                printf("This is where malicious code would be run");
        printf("\n");
}

```

```bash
seed@VM:~/Desktop$ gcc program2.c -o program2.out
```

![Untitled](LAB%203%20-%20MD5%20Collision%20Attack%20Lab%20752f5406cb2640ff92c83e56a71c1b9f/Untitled%2019.png)

---

---

### Step 2: Look at the contents using Bless

<aside>
💡 Lets open program2.out using Bless

</aside>

```bash
seed@VM:~/Desktop$ bless program2.out
```

![Untitled](LAB%203%20-%20MD5%20Collision%20Attack%20Lab%20752f5406cb2640ff92c83e56a71c1b9f/Untitled%2020.png)

<aside>
💡 We note that the first array starts at position **0x1040 = 4160**. As before, he prefix can extend until there, but I will continue to use the position **0x1080** so that the generated data will start in the middle of the array.

</aside>

---

---

### Step 3: Running the Head command

<aside>
💡 Since **0x1080** will refer to the first 4224 bytes of the data, we will run ***head*** to store the first 4224 bytes in prefix. Then we will run ***md5collgen*** which will generate two binaries with the same MD5 sum but they will differ.

Then we will open both files using ***bless***

</aside>

```bash
seed@VM:~/Desktop$ head -c 4224 program2.out > prefix4
seed@VM:~/Desktop$ md5collgen -p prefix4 -o pgen qgen

seed@VM:~/Desktop$ bless pgen qgen

```

![Untitled](LAB%203%20-%20MD5%20Collision%20Attack%20Lab%20752f5406cb2640ff92c83e56a71c1b9f/Untitled%2021.png)

<aside>
💡 We can see the 128 characters generated by md5collgen. The MD5 sums of **pgen** and **qgen** will be identical

</aside>

```bash
seed@VM:~/Desktop$ md5sum pgen qgen
```

![Untitled](LAB%203%20-%20MD5%20Collision%20Attack%20Lab%20752f5406cb2640ff92c83e56a71c1b9f/Untitled%2022.png)

---

---

### Step 4: Creating the common end

<aside>
💡 We can then select and create two files **p** and **q** having the generated values found in **pgen** and **qgen** respectively. To get the middle section note where the generated data begins in the first array. In the second instance of “TESTINGMD5……” (where the second area is located) we place a marker at where the data should be replaced and take it out. (We can do this by creating a new file **head -c +4353 program2.out > end** and selecting until the marker.)

To create the common **end** file, we would need the characters from the **end** file created earlier after accounting for a 128+192 (size of **middle**) offset. 

</aside>

```bash
seed@VM:~/Desktop$ tail -c 128 pgen > p
seed@VM:~/Desktop$ tail -c 128 qgen > q

seed@VM:~/Desktop$ head -c +4353 program2.out > end2

seed@VM:~/Desktop$ tail -c +321 end2 > thecommonend2
```

![Untitled](LAB%203%20-%20MD5%20Collision%20Attack%20Lab%20752f5406cb2640ff92c83e56a71c1b9f/Untitled%2023.png)

---

---

### Step 5: Putting all the files together

<aside>
💡 Now to put all the files together and run them

</aside>

```bash
seed@VM:~/Desktop$ cp pgen benigncode
seed@VM:~/Desktop$ cp qgen maliciouscode

seed@VM:~/Desktop$ cat middle >> benigncode
seed@VM:~/Desktop$ cat middle >> maliciouscode

seed@VM:~/Desktop$ cat p >> benigncode
seed@VM:~/Desktop$ cat p >> maliciouscode

seed@VM:~/Desktop$ cat thecommonend2 >> benigncode
seed@VM:~/Desktop$ cat thecommonend2 >> maliciouscode

```

<aside>
💡 Finally Verify using **md5sum benigncode maliciouscode** and check if the hashes are the same.

</aside>

```bash
seed@VM:~/Desktop$ chmod +x benigncode maliciouscode
seed@VM:~/Desktop$ ./benigncode
seed@VM:~/Desktop$ ./maliciouscode
```

---

---

---