# writeup

To analyze the bob.apk given as a problem file, start the analysis using the decompile tool (JEB, JADX, etc.).

### ○ manifest.xml

![Untitled](writeup%208bcf035e69504ff198d6e5bd82ba8a40/Untitled.png)

If you look at manifest, you analyze the class by executing the activity "MainActivity" first.

### ○ MainActivity

![Untitled](writeup%208bcf035e69504ff198d6e5bd82ba8a40/Untitled%201.png)

![Untitled](writeup%208bcf035e69504ff198d6e5bd82ba8a40/Untitled%202.png)

There are various patterns such as routing and debugging detection. However, key and native library "ctf" and check_code() in verify() are the key in [Figure].

When executing check_code(), the same thing as key can be determined by looking at the factor.

Let's analyze the class as check_code() is a function defined in the CodeCheck class, as shown in Figure.

![Untitled](writeup%208bcf035e69504ff198d6e5bd82ba8a40/Untitled%203.png)

If you look at the check_code() of the CodeCheck class, it internally calls a function called keyme(). However, since keyme() is a native function, it is not possible to verify the source with the java decompiler.

![Untitled](writeup%208bcf035e69504ff198d6e5bd82ba8a40/Untitled%204.png)

In order to analyze the native function, it is necessary to analyze the so file defined internally.

Therefore, the bob.apk is decompiled using the apktool.

### ○ example command

```bash
apktool d bob.apk -o bob_ctf
```

![Untitled](writeup%208bcf035e69504ff198d6e5bd82ba8a40/Untitled%205.png)

The results of analyzing bob.apk are stored in the bob_ctf folder.

If you look inside the folder, there are various files, and we check the lib folder by analyzing the native library.

![Untitled](writeup%208bcf035e69504ff198d6e5bd82ba8a40/Untitled%206.png)

If you access the architecture folder that corresponds to your environment among the four architectures, libctf as shown in [figure].You can check the file called so.

![Untitled](writeup%208bcf035e69504ff198d6e5bd82ba8a40/Untitled%207.png)

Analyzing libctf.so as IDA64 shows that a JNI function called keyme is defined, as shown in [Figure].

![Untitled](writeup%208bcf035e69504ff198d6e5bd82ba8a40/Untitled%208.png)

If you check keyme(), you can see that it has a logic that outputs the result value at the end.

Looking at the code, the factor a3 is copied to the v10 variable through memcpy_chk().

For reference, **`keyme(arg1) == check_code(arg1)`** indicates that a3 is the key value first checked.

### ○ generator()

![Untitled](writeup%208bcf035e69504ff198d6e5bd82ba8a40/Untitled%209.png)

After that, a generator (key) using `v10 == key` as a factor is executed, and the code shows that the internal logic is very complicated and long.

However, as can be seen from the analysis, the function has no effect with respect to key or result as a fake.

![Untitled](writeup%208bcf035e69504ff198d6e5bd82ba8a40/Untitled%208.png)

In summary, the part related to the result value is the red box part.

Simply summarizing the code in the red part, v6[] and v10[] are stored in v5 and output as results.

As mentioned above, it can be seen that v10 == key and v6[] is defined in hexadecimal form.

If the code logic of the red box is implemented in C language as it is, the solve code is written as follows.

## ○ solve.c

```python
#include<stdio.h>
#include<string.h>

int main(void) {
  unsigned char secret[] = "\x1f\x1f\x1f\x1f\x1f\x1f\x1f\x1f\x1f\x1f\x1f\x1f\x1f\x1f\x1f\x1f\x75\x25\x25\x25\x25\x05";
  char xorkey[] = "}p}dTZF@vl@RvqZ>T[[[[{~}";
  int i;
  char flag[24];

  for (i = 0; i < 24; i++) {
    flag[i] = secret[i] ^ xorkey[i];
  }
  flag[25] = '\0';

  printf("[!] Found flag: %s\n", flag);

  return 0;
}
```

![Untitled](writeup%208bcf035e69504ff198d6e5bd82ba8a40/Untitled%2010.png)

If you compile and run `solve.c`, you can get a flag as shown in [figure].